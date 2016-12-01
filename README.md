# micro-aes

[![GitHub release](https://img.shields.io/github/release/SmarterUM/micro-aes.svg)](https://github.com/SmarterUM/micro-aes/releases/tag/v1.0.0)
![C](https://img.shields.io/badge/langauge-C-blue.svg)
[![Build Status](https://travis-ci.org/SmarterUM/micro-aes.svg?branch=master)](https://travis-ci.org/SmarterUM/micro-aes)
[![MIT](https://img.shields.io/badge/license-MIT-brightgreen.svg)](https://github.com/SmarterUM/micro-aes/blob/master/LICENSE)

A permissively licensed Advanced Encryption Standard (AES) implementation optimised for running on micro-controllers.

This library has been developed and open sourced by [AndrewCarterUK ![(Twitter)](http://i.imgur.com/wWzX9uB.png)](https://twitter.com/AndrewCarterUK) from [Smart Carbon Control](http://www.smartcarboncontrol.com/). We are always on the lookout for programming talent, so please [message me](https://twitter.com/AndrewCarterUK) if you are interested in this sort of work.

## License

Like all technology firms, here at [Smart Carbon Control](http://www.smartcarboncontrol.com/) we rely heavily on open source software. In turn, we like to contribute back to the open source community when we can. This library is provided free of charge, under the terms of the [MIT license](https://github.com/SmarterUM/micro-aes/blob/master/LICENSE).

Although there is no obligation to do so, we would really appreciate it if you could [get in touch](https://twitter.com/AndrewCarterUK) and let us know how you are using our software.

## Features

- Does not use dynamic memory allocation
- Uses timing-safe algorithms in place of lookup tables (where possible) to reduce code size
- API designed for use in a low memory environment (cipher text overwrites plain text on encryption)

## Important Note

This library provides the basic AES operations for encrypting and decrypting data. There are different ways to apply a block cipher (called the modes of operation), but this library does not deal with them.

**It is very important to understand these modes of operation if you intend to use AES encryption (or any block cipher)**.

The two most simplest modes are [ECB (not very secure)](https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation#ECB) and [CBC (much more secure)](https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation#CBC).

An example implementation of CBC mode is [presented below](#usage-example-cipher-block-chaining-cbc).

## API

```C
// AES-256
void aes_256_init    (aes_256_context_t *context, uint8_t key[32]);
void aes_256_encrypt (aes_256_context_t *context, uint8_t block[16]);
void aes_256_decrypt (aes_256_context_t *context, uint8_t block[16]);

// AES-192
void aes_192_init    (aes_192_context_t *context, uint8_t key[24]);
void aes_192_encrypt (aes_192_context_t *context, uint8_t block[16]);
void aes_192_decrypt (aes_192_context_t *context, uint8_t block[16]);

// AES-128
void aes_128_init    (aes_128_context_t *context, uint8_t key[16]);
void aes_128_encrypt (aes_128_context_t *context, uint8_t block[16]);
void aes_128_decrypt (aes_128_context_t *context, uint8_t block[16]);
```

## Usage Example: Cipher Block Chaining (CBC)

The functions below show an example implementation of [CBC mode](https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation#CBC) using this AES library. The `init()` function must be called again between the encryption and decryption procedures.

```C
aes_128_context_t context;
uint8_t current_vector[16];

void init(uint8_t key[16], uint8_t initialization_vector[16])
{
  // Initialise the context with the key
  aes_128_init(&context, key);

  // Copy the IV into the current vector array
  memcpy(current_vector, initialization_vector, 16);
}

void encrypt(uint8_t block[16])
{
  int i;

  // XOR the current vector with the block before encrypting
  for (i = 0; i < 16; i++) {
    block[i] ^= current_vector[i];
  }

  // Encrypt the block
  aes_128_encrypt(&context, block);

  // Copy the cipher output to the current vector
  memcpy(current_vector, block, 16);
}

void decrypt(uint8_t block[16])
{
  uint8_t temp_vector[16];
  int i;

  // Copy the cipher output to the temporary vector
  memcpy(temp_vector, block, 16);

  // Decrypt the block
  aes_128_decrypt(&context, block);

  // XOR the output with the current vector to fully decrypt
  for (i = 0; i < 16; i++) {
    block[i] ^= current_vector[i];
  }

  // Copy the temporary vector to the current vector
  memcpy(current_vector, temp_vector, 16);
}
```
