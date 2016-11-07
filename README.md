# micro-aes

A permissively licensed AES implementation optimised for running on micro-controllers.

## Features

- Does not use dynamic memory allocation
- Uses timing-safe algorithms in place of lookup tables (where possible) to reduce code size
- API designed for use in a low memory environment (cipher text overwrites plain text on encryption)

## API

```C
void aes_256_init    (aes_256_context_t *context, uint8_t key[32]);
void aes_256_encrypt (aes_256_context_t *context, uint8_t block[16]);
void aes_256_decrypt (aes_256_context_t *context, uint8_t block[16]);
void aes_192_init    (aes_192_context_t *context, uint8_t key[24]);
void aes_192_encrypt (aes_192_context_t *context, uint8_t block[16]);
void aes_192_decrypt (aes_192_context_t *context, uint8_t block[16]);
void aes_128_init    (aes_128_context_t *context, uint8_t key[16]);
void aes_128_encrypt (aes_128_context_t *context, uint8_t block[16]);
void aes_128_decrypt (aes_128_context_t *context, uint8_t block[16]);
```
