#include "util.h"

int x;
// send bit without any interval
void send_bit(bool one, ADDR_PTR addr) {

	if(one) {
		// flush current and adjacent cache line 
		clflush(addr);
		clflush((ADDR_PTR)((char *)addr + CACHE_BLOCK_SIZE));
	}
	else {
		// load current and adjacent cache line
		x = *((int *)addr);
		x = *((int *)((char *)addr + CACHE_BLOCK_SIZE));
	}
}

bool bit;

int main(int argc, char **argv) {
	if(argc == 2)
	{
		bit = atoi(argv[1]) ? true : false;
	}
	
	init_shared_address(SHARED_FILE_NAME);
	send_bit(bit, shared_address);
	printf("Transmitted bit = %d\n", bit);
	return 0;
} 