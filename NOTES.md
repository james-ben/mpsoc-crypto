Project Goals
==============

 - Create an example that uses the ARM v8 Crypto Extensions, running on Linux.
 - Benchmark the speedup vs pure software implementation.

Trying to recreate some of the work done in this [white paper](https://www.xilinx.com/support/documentation/white_papers/wp512-accel-crypto.pdf).


Resources
------------

- [ARM ARM v8](https://static.docs.arm.com/ddi0487/fa/DDI0487F_a_armv8_arm.pdf)
  - C3.5.30 on page 261
- [A53 Cryptography TRM](https://static.docs.arm.com/ddi0501/f/DDI0501F_cortex_a53_cryptography_trm.pdf): how to see what version is enabled
- implenting AES [with NEON](https://www.linaro.org/blog/accelerated-aes-for-the-arm64-linux-kernel/)
- [ARM intrinsics discussion](https://stackoverflow.com/questions/38919663/intel-arm-intrinsics-equivalence?rq=1)
- [ARM AES example code](https://stackoverflow.com/questions/45528569/does-arm-and-intel-intrinsics-use-the-same-subkey-schedule-for-aes)
- look at [this commit](https://github.com/noloader/cryptopp/commit/701ec3aa1f45a754)
- another [AES implementation](https://github.com/noloader/AES-Intrinsics/blob/master/aes-arm.c) for ARM v8
- look here for [example tests](https://chromium.googlesource.com/native_client/nacl-gcc/+/b155e41c4984c3a7716829251226a41091072c4a/gcc/testsuite/gcc.target/arm) for using crypto instrinsics (crytp-*.c)


Set up board
- [Load Linux](https://www.96boards.org/documentation/consumer/ultra96/ultra96-v2/getting-started/)


Intrinsic reference
--------------------
- vmull_p64: multiply polynomial
  - see also vmull_high_p64
- vaeseq_u8: single round encryption
- vaesdq_u8: single round decryption
- vaesimcq_u8: AES inverse mix columns
- vaesmcq_u8: AES mix columns
- vsha1cq_u32: SHA1 hash update (choose)
- vsha1h_u32: SHA1 fixed rotate
- vsha1mq_u32: SHA1 hash update (majority)
- vsha1pq_u32: SHA1 hash update (parity)
- vsha1su0q_u32: SHA1 schedule update 0
- vsha1su1q_u32: SHA1 schedule update 1
- vsha256hq_u32: SHA256 hash update (part 1)
- vsha256h2q_u32: SHA256 hash update (part 2)
- vsha256su0q_u32: SHA256 schedule update 0
- vsha256su1q_u32: SHA256 schedule update 1

see also `vstrq_p128`, `vst1q_u8`, `vld1q_u8`
other encryption stuff: `vsm4eq_u32`, `vsm4ekeyq_u32`, and the `vsm3*` intrinsics
and __crc32cd
