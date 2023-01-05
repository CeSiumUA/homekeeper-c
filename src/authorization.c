#include "authorization.h"

#define PUB_KEY_SIZE        32
#define PRIVATE_KEY_SIZE    64

static void generate_new_key_pair(char *pub_buff, char *priv_buff);

void auth_init(void){
    char pub_key[PUB_KEY_SIZE];
    bool pub_load_res = load_conf_value("HK_PUBKEY", pub_key, sizeof(pub_key));
    char priv_key[PRIVATE_KEY_SIZE];
    bool priv_load_res = load_conf_value("HK_PRIVKEY", priv_key, sizeof(priv_key));

    if(!pub_load_res || !priv_load_res){

    }
}

static void generate_new_key_pair(char *pub_buff, char *priv_buff){
    
}