#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../aes.h"

#define X2D(x) \
  ((x) <= 'F' && (x) >= 'A' ? (x) - 'A' + 10 : \
    ((x) <= 'f' && (x) >= 'a' ? (x) - 'a' + 10 : \
      ((x) <= '9' && (x) >= '0' ? (x) - '0' : 0)))

void aes_256(uint8_t *key, uint8_t *block, int decrypt)
{
  aes_256_context_t ctx;

  aes_256_init(&ctx, key);

  if (decrypt) aes_256_decrypt(&ctx, block);
  else aes_256_encrypt(&ctx, block);
}

void aes_192(uint8_t *key, uint8_t *block, int decrypt)
{
  aes_192_context_t ctx;

  aes_192_init(&ctx, key);

  if (decrypt) aes_192_decrypt(&ctx, block);
  else aes_192_encrypt(&ctx, block);
}

void aes_128(uint8_t *key, uint8_t *block, int decrypt)
{
  aes_128_context_t ctx;

  aes_128_init(&ctx, key);

  if (decrypt) aes_128_decrypt(&ctx, block);
  else aes_128_encrypt(&ctx, block);
}

int main(int argc, char *argv[])
{
  int key_size = 256, decrypt = 0, i, c;
  char *hex_key = NULL, *hex_block = NULL;
  uint8_t key[32], block[16];

  memset(key, 0, sizeof(key));
  memset(block, 0, sizeof(block));

  while ((c = getopt(argc, argv, "k:b:s:d")) != -1) {
    switch (c) {
      case 'k': hex_key = optarg; break;
      case 'b': hex_block = optarg; break;
      case 's': key_size = atoi(optarg); break;
      case 'd': decrypt = 1; break;
    }
  }

  if (key_size != 128 && key_size != 192 && key_size != 256) {
    puts("Key size must be 128, 192 or 256");
    return 0;
  }

  if (hex_key == NULL || hex_block == NULL) {
    puts("Key and block must be provided");
    return 0;
  }

  for (i = 0; hex_key[i] && hex_key[i + 1] && i < key_size >> 2; i += 2) {
    key[i >> 1] = (X2D(hex_key[i]) << 4) | X2D(hex_key[i | 1]);
  }

  if (i != key_size >> 2) {
    puts("Provided key not long enough");
    return 0;
  }

  for (i = 0; hex_block[i] && hex_block[i + 1] && i < 32; i += 2) {
    block[i >> 1] = (X2D(hex_block[i]) << 4) | X2D(hex_block[i | 1]);
  }

  if (i != 32) {
    puts("Block must be 16 bytes long");
    return 0;
  }

  switch (key_size) {
    case 256: aes_256(key, block, decrypt); break;
    case 192: aes_192(key, block, decrypt); break;
    case 128: aes_128(key, block, decrypt); break;
  }

  for (i = 0; i < 16; i++) {
    printf("%02X", block[i]);
  }

  putc('\n', stdout);

  return 0;
}

