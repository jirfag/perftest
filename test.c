#include <stdint.h>

int num_cmp(const void *a, const void *b)
{
	return *(uint32_t *)a - *(uint32_t *)b;
}
