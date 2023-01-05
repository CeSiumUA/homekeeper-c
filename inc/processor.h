#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include "config.h"
#include "storage.h"
#include "ed_crypto/ed25519.h"
#include <time.h>
#include <math.h>

#define PUB_KEY_SIZE        32
#define PRIVATE_KEY_SIZE    64

void process_data(const uint8_t *data, size_t data_size);

#endif