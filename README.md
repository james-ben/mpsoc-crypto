MPSoc Cryptography
=======================

This repo contains examples of how to use the ARM v8 Cryptography instructions.

The date of the first commit is erroneous; the Ultra96 had the wrong date saved.

This is based on the code found at [this repo](https://github.com/kokke/tiny-AES-c), with my own Makefile.


AES
====

Software Implementation
------------------------

To build, execute `make`

To run, execute `make run`


ARM Neon Implementation
-------------------------

Same build commands, but in the neon directory instead.

I got a lot of the understanding for how the instructions work by looking at [this post](https://community.arm.com/developer/tools-software/tools/b/tools-software-ides-blog/posts/porting-putty-to-windows-on-arm) on the ARM forums.

**Basic idea:**

- the `AESE` instruction does the same thing as
  - XOR the state with the round key
  - [SubBytes](https://developer.arm.com/docs/ddi0596/e/shared-pseudocode-functions/shared-functionscrypto-pseudocode#impl-shared.AESSubBytes.1)
  - [ShiftRows](https://developer.arm.com/docs/ddi0596/e/shared-pseudocode-functions/shared-functionscrypto-pseudocode#impl-shared.AESShiftRows.1)
- the `AESMC` does the same as MixColumns
- But at the end, there is only an XOR, so we have to use the intrinsic `veorq_u8` instead


TODO
------

- Make two copies of the repo, one of which will have its functions replaced with intrinsics
- look at https://developer.arm.com/architectures/instruction-sets/simd-isas/neon/intrinsics?search=crypto
  - https://github.com/noloader/AES-Intrinsics/blob/master/aes-arm.c


Resources
------------

- https://blog.michaelbrase.com/2018/06/04/optimizing-x86-aes-intrinsics-on-armv8-a/
- https://botan.randombit.net/doxygen/aes__armv8_8cpp_source.html
- https://reviews.freebsd.org/D8297
