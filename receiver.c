#include "util.h"

int clflush__latency, load__latency;

int main(int argc, char **argv) {
	init_shared_address(SHARED_FILE_NAME);
	init_target_address(TARGET_FILE_NAME);

	clflush__latency = clflush_latency((ADDR_PTR)((char *)shared_address + CACHE_BLOCK_SIZE));
	load__latency = load_latency(shared_address);

    if(clflush__latency >= load__latency)
        *target_address = 0;
    else 
        *target_address = 1;

    printf("Received bit = %d\n", *target_address);

	return 0;

}