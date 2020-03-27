MPSoc Cryptography
=======================

This repo contains examples of how to use the ARM v8 Cryptography instructions.

The date of the first commit is erroneous; the Ultra96 had the wrong date saved.

This is based on the code found at [this repo](https://github.com/kokke/tiny-AES-c), with my own Makefile.


AES
====

Software Implementation
------------------------

To build, run `make`

To run, run `make run`


TODO
------

- Make two copies of the repo, one of which will have its functions replaced with intrinsics
- look at https://developer.arm.com/architectures/instruction-sets/simd-isas/neon/intrinsics?search=crypto
  - https://github.com/noloader/AES-Intrinsics/blob/master/aes-arm.c
