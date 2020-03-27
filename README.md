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

Basic idea:
-----------

- the `AESE` instruction does the same thing as
  - XOR the state with the round key
  - [SubBytes](https://developer.arm.com/docs/ddi0596/e/shared-pseudocode-functions/shared-functionscrypto-pseudocode#impl-shared.AESSubBytes.1)
  - [ShiftRows](https://developer.arm.com/docs/ddi0596/e/shared-pseudocode-functions/shared-functionscrypto-pseudocode#impl-shared.AESShiftRows.1)
- the `AESMC` does the same as MixColumns
- But at the end, there is only an XOR, so we have to use the intrinsic `veorq_u8` instead
- Doing the decryption (`AESD`), we need a slightly different key schedule, to account for some differences in the Neon hardware
  - This is (kind of) explained in the [same post](https://community.arm.com/developer/tools-software/tools/b/tools-software-ides-blog/posts/porting-putty-to-windows-on-arm) as above, but I also looked [here](https://github.com/freebsd/freebsd/blob/b25216505e3b0336ead4a0b98046ace71a7d58da/contrib/wpa/src/crypto/aes-internal-dec.c) for some help


Resources
------------

- https://blog.michaelbrase.com/2018/06/04/optimizing-x86-aes-intrinsics-on-armv8-a/
- https://botan.randombit.net/doxygen/aes__armv8_8cpp_source.html
- https://reviews.freebsd.org/D8297
- https://github.com/freebsd/freebsd/blob/1d6e4247415d264485ee94b59fdbc12e0c566fd0/contrib/wpa/src/crypto/aes-internal.c
- https://github.com/freebsd/freebsd/blob/b25216505e3b0336ead4a0b98046ace71a7d58da/contrib/wpa/src/crypto/aes-internal-dec.c
