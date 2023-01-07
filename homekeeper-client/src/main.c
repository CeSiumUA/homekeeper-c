#include "main.h"

#define SEED_SIZE           32
#define PUBLIC_KEY_SIZE     32
#define PRIVATE_KEY_SIZE    64
#define SIGNATURE_SIZE      64
#define KEY_FILE_NAME       "key"
#define REMOTE_IP           "127.0.0.1"
#define REMOTE_PORT         1432

static void ensure_key_exists(void);
static void generate_server_file(void);
static void start_sender(void);
static bool load_key(key_pair *kp);
static void send_message(int socketfd);

int main(int argc, char *argv[]){
    ensure_key_exists();

    if(getopt(argc, argv, "g") != -1){
        generate_server_file();
        return 0;
    }

    start_sender();
}

static void generate_server_file(void){
    printf("generating server file...\n");

    key_pair kp;
    client_key ck;
    if(!load_key(&kp)){
        printf("could not load key\n");
        return;
    }

    printf("saving file...\n");

    memcpy(ck.public_key, kp.public_key, PUBLIC_KEY_SIZE);

    ck.id = kp.id;
    ck.is_notified = false;
    ck.last_online = time(NULL);
    
    char file_name[sizeof(long)];

    sprintf(file_name, "%lu", ck.id);

    FILE *fd = fopen(file_name, "wb");

    fwrite(&ck, sizeof(client_key), 1, fd);

    fclose(fd);
}

static void ensure_key_exists(void){
    FILE *fd = fopen(KEY_FILE_NAME, "rb");
    if(fd != NULL){
        printf("key already exists\n");
        fclose(fd);
        return;
    }

    printf("key does not exists, generating new\n");

    printf("enter client id:\n");
    ulong client_id;
    scanf("%lu", &client_id);

    uint8_t seed_buffer[SEED_SIZE];
    if(ed25519_create_seed(seed_buffer) != 0){
        printf("failed to create seed\n");
        exit(0);
    }

    uint8_t private_key_buffer[PRIVATE_KEY_SIZE];
    uint8_t public_key_buffer[PUBLIC_KEY_SIZE];

    ed25519_create_keypair(public_key_buffer, private_key_buffer, seed_buffer);

    key_pair kp;

    memcpy(kp.private_key, private_key_buffer, sizeof(private_key_buffer));
    memcpy(kp.public_key, public_key_buffer, sizeof(public_key_buffer));

    kp.id = client_id;

    fd = fopen(KEY_FILE_NAME, "wb");

    fwrite(&kp, sizeof(key_pair), 1, fd);

    fclose(fd);
}

static bool load_key(key_pair *kp){
    FILE *fd = fopen(KEY_FILE_NAME, "rb");

    if(fd == NULL){
        fclose(fd);
        return false;
    }

    fread(kp, sizeof(key_pair), 1, fd);

    fclose(fd);

    return true;
}

static void start_sender(void){
    struct sockaddr_in server_address = {0};

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        printf("error opening socket...\n");
        exit(0);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(REMOTE_IP);
    server_address.sin_port = htons(REMOTE_PORT);

    if(connect(sockfd, (struct sockaddr*)&server_address, sizeof(struct sockaddr_in)) != 0){
        printf("connection failed...");
        exit(0);
    }

    send_message(sockfd);

    close(sockfd);
}

static void send_message(int socketfd){
    key_pair kp;
    if(!load_key(&kp)){
        printf("key load failed...\n");
        return;
    }

    uint8_t message_buf[SIGNATURE_SIZE + sizeof(u_long) + sizeof(u_long)];

    u_long arg = time(NULL);

    ed25519_sign(message_buf + (2*sizeof(u_long)), (uint8_t *)&arg, sizeof(u_long), kp.public_key, kp.private_key);

    memcpy(message_buf, &kp.id, sizeof(u_long));
    memcpy(message_buf + sizeof(u_long), &arg, sizeof(u_long));

    write(socketfd, message_buf, sizeof(message_buf));
}