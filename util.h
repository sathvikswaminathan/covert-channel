#ifndef UTIL_H
#define UTIL_H

#define _GNU_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sched.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#ifdef _MSC_VER
# include <intrin.h>
#else
# include <x86intrin.h>
#endif

#define CYCLES uint32_t
#define ADDR_PTR uint64_t

#define SHARED_FILE_NAME 	"/home/sathvik/Desktop/TCC/shared.txt"
#define DEFAULT_FILE_OFFSET	0x0
#define DEFAULT_FILE_SIZE	4096
#define TARGET_FILE_NAME	"/home/sathvik/Desktop/TCC/target.txt"

#define CACHE_BLOCK_SIZE	64


// Function declarations

// get current time stamp
CYCLES rdtscp();

// flush a cache line from all cache heirarchies
void clflush(ADDR_PTR addr);

// computes latency of a load operation
CYCLES load_latency(ADDR_PTR p);

// computes latency of a clflush operation
CYCLES clflush_latency(ADDR_PTR p);

// initializes shared address
void init_shared_address(char *FILE_NAME);

// initializes target address
void init_target_address(char *FILE_NAME);

// shared address between sender and receiver
ADDR_PTR shared_address;

// shared address between receivers
int* target_address;

#endif
