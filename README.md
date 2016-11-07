# micro-aes

[![Build Status](https://travis-ci.org/SmarterUM/micro-aes.svg?branch=master)](https://travis-ci.org/SmarterUM/micro-aes)
![MIT](https://img.shields.io/badge/license-MIT-brightgreen.svg)

A permissively licensed AES implementation optimised for running on micro-controllers.

This library has developed been developed and open sourced by [AndrewCarterUK ![(Twitter)](http://i.imgur.com/wWzX9uB.png)](https://twitter.com/AndrewCarterUK) from [Smart Carbon Control](http://www.smartcarboncontrol.com/). We are always on the lookout for programming talent, so please [message me](https://twitter.com/AndrewCarterUK) if you are interested in this sort of work.

## Features

- Does not use dynamic memory allocation
- Uses timing-safe algorithms in place of lookup tables (where possible) to reduce code size
- API designed for use in a low memory environment (cipher text overwrites plain text on encryption)

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
