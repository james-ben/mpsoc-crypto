/*********************************************************************
* Filename:   sha256.c
* Author:     Brad Conte (brad AT bradconte.com)
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Performs known-answer tests on the corresponding SHA1
              implementation. These tests do not encompass the full
              range of available test vectors, however, if the tests
              pass it is very, very likely that the code is correct
              and was compiled properly. This code also serves as
              example usage of the functions.
*********************************************************************/
/*
 * File has been edited by Benjamin James
 * See project notes for a description.
 */


/*************************** HEADER FILES ***************************/
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <time.h>

#include "sha256.h"


/****************************** MACROS ******************************/
#define NS_TO_S(ns) ((ns) / 1000000000.0)
#define NUM_TEST_RUNS   (20)
#define RUNTIME_IN_SECONDS(start, stop) ( (long)(stop.tv_sec - start.tv_sec) + \
                                        NS_TO_S((double)(stop.tv_nsec - start.tv_nsec)) )
#define PRINT_STATUS(status)    if (status) { printf("SUCCESS!\n"); } \
                                else { printf("FAILURE!\n"); }


/*********************** FUNCTION DEFINITIONS ***********************/
int sha256_test1()
{
    BYTE text1[] = {"abc"};
    BYTE hash1[SHA256_BLOCK_SIZE] = {0xba,0x78,0x16,0xbf,0x8f,0x01,0xcf,0xea,0x41,0x41,0x40,0xde,0x5d,0xae,0x22,0x23,
                                     0xb0,0x03,0x61,0xa3,0x96,0x17,0x7a,0x9c,0xb4,0x10,0xff,0x61,0xf2,0x00,0x15,0xad};
    BYTE buf[SHA256_BLOCK_SIZE];
    SHA256_CTX ctx;
    int idx;
    int pass = 1;

    sha256_hash(&ctx, text1, buf, 1);
    pass = pass && !memcmp(hash1, buf, SHA256_BLOCK_SIZE);

    return(pass);
}

int sha256_test2()
{
    BYTE text2[] = {"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"};
    BYTE hash2[SHA256_BLOCK_SIZE] = {0x24,0x8d,0x6a,0x61,0xd2,0x06,0x38,0xb8,0xe5,0xc0,0x26,0x93,0x0c,0x3e,0x60,0x39,
                                     0xa3,0x3c,0xe4,0x59,0x64,0xff,0x21,0x67,0xf6,0xec,0xed,0xd4,0x19,0xdb,0x06,0xc1};

    BYTE buf[SHA256_BLOCK_SIZE];
    SHA256_CTX ctx;
    int idx;
    int pass = 1;

    sha256_hash(&ctx, text2, buf, 1);
    pass = pass && !memcmp(hash2, buf, SHA256_BLOCK_SIZE);

    return(pass);
}

int sha256_test3()
{
    BYTE text3[] = {"aaaaaaaaaa"};
    BYTE hash3[SHA256_BLOCK_SIZE] = {0xcd,0xc7,0x6e,0x5c,0x99,0x14,0xfb,0x92,0x81,0xa1,0xc7,0xe2,0x84,0xd7,0x3e,0x67,
                                     0xf1,0x80,0x9a,0x48,0xa4,0x97,0x20,0x0e,0x04,0x6d,0x39,0xcc,0xc7,0x11,0x2c,0xd0};

    BYTE buf[SHA256_BLOCK_SIZE];
    SHA256_CTX ctx;
    int idx;
    int pass = 1;

    sha256_hash(&ctx, text3, buf, 100000);
    pass = pass && !memcmp(hash3, buf, SHA256_BLOCK_SIZE);

    return(pass);
}

int main()
{
    // initialize timing
    struct timespec start, stop;
    int clockID = CLOCK_THREAD_CPUTIME_ID;
    double numRuns = NUM_TEST_RUNS;
    long sdiff;
    double nsdiff, meanTime;
    int status;

    printf("SHA-256 test 1: ");
    clock_gettime(clockID, &start);
    for (int i = 0; i < NUM_TEST_RUNS; i++) {
        status = sha256_test1();
        clock_gettime(clockID, &stop);
        if (!i) {
            PRINT_STATUS(status);
        }
        meanTime += RUNTIME_IN_SECONDS(start, stop);
        clock_gettime(clockID, &start);
    }
    printf("Avg execution time: %fs\n", meanTime / numRuns);

    printf("SHA-256 test 2: ");
    clock_gettime(clockID, &start);
    for (int i = 0; i < NUM_TEST_RUNS; i++) {
        status = sha256_test2();
        clock_gettime(clockID, &stop);
        if (!i) {
            PRINT_STATUS(status);
        }
        meanTime += RUNTIME_IN_SECONDS(start, stop);
        clock_gettime(clockID, &start);
    }
    printf("Avg execution time: %fs\n", meanTime / numRuns);

    printf("SHA-256 test 3: ");
    clock_gettime(clockID, &start);
    for (int i = 0; i < NUM_TEST_RUNS; i++) {
        status = sha256_test3();
        clock_gettime(clockID, &stop);
        if (!i) {
            PRINT_STATUS(status);
        }
        meanTime += RUNTIME_IN_SECONDS(start, stop);
        clock_gettime(clockID, &start);
    }
    printf("Avg execution time: %fs\n", meanTime / numRuns);

    return (!status);
}
