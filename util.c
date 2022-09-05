#include "util.h"

// get current time stamp
extern inline __attribute__((always_inline))
CYCLES rdtscp(void) {
	CYCLES cycles;
	asm volatile ("rdtscp" :  "=a" (cycles));

	return cycles;
}

// flush cacheline from cache
extern inline __attribute__((always_inline))
void clflush(ADDR_PTR addr){
    asm volatile ("clflush (%0)"::"r"(addr));
}

// computes latency of a load operation
CYCLES load_latency(ADDR_PTR addr){
	
    CYCLES cycles;

    asm volatile("mov %1, %%r8\n\t"
            "lfence\n\t"
            "rdtsc\n\t"
            "mov %%eax, %%edi\n\t"
            "mov (%%r8), %%r8\n\t"
            "lfence\n\t"
            "rdtsc\n\t"
            "sub %%edi, %%eax\n\t"
    : "=a"(cycles) /*output*/
    : "r"(addr)
    : "r8", "edi");

    return cycles;
}

// computes latency of a clflush operation
inline CYCLES clflush_latency(ADDR_PTR p){
        CYCLES t1 = rdtscp();
        clflush(p);
        CYCLES t2 = rdtscp();
        return (t2-t1);
}

// initialize address
void init_shared_address(char* FILE_NAME){
	char *filename = FILE_NAME;
	int fd = open(filename, O_RDWR);
	if(fd == -1) {
		printf("Could not open file .\n");
		exit(0);
	}
	void *file_address = mmap(NULL, DEFAULT_FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE, fd, 0);
	shared_address = (ADDR_PTR) file_address;
}

// initialize address
void init_target_address(char* FILE_NAME){
	char *filename = FILE_NAME;
	int fd = open(filename, O_RDWR);
	if(fd == -1) {
		printf("Could not open file .\n");
		exit(0);
	}
	void *file_address = mmap(NULL, DEFAULT_FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE, fd, 0);
	target_address = (int *) file_address;
}