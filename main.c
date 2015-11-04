#include "test.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

static const char *get_file_contents(const char *fname, size_t *size)
{
	__attribute__((aligned(16))) static char buf[16 * 1024 * 1024];
	FILE *f = fopen(fname, "r");
	assert(f);

	size_t read_n = 0;
	for (;;) {
		size_t n = fread(buf, 1, sizeof(buf) - read_n, f);
		if (!n)
			break;
		read_n += n;
	}
	if (size)
		*size = read_n;
	buf[read_n - 1] = '\0';
	return buf;
}

static uint32_t count_quotes_with_naive_loop(const char *ascii)
{
	uint32_t q_n = 0;
	for (const char *s = ascii; *s; ++s) {
		if (*s == '\\') {
			++s;
			if (!*s)
				break;
			continue;
		}
		if (*s == '"')
			++q_n;
	}
	return q_n;
}

static void test_strcspn()
{
	const char *ascii = get_file_contents("1mb_ascii.txt", NULL);
	uint32_t n = 1000;
	volatile uint32_t strcspn_q_n = 0;
	TIMEIT("count_quotes_with_strcspn", n,
		({
			strcspn_q_n += count_quotes_with_strcspn(ascii);
		}));

	volatile uint32_t naive_loop_q_n = 0;
	TIMEIT("count_quotes_with_naive_loop", n,
		({
			naive_loop_q_n += count_quotes_with_naive_loop(ascii);
		}));
	assert(strcspn_q_n == naive_loop_q_n);
}

int main()
{
	test_strcspn();
}
