#define _HAVE_STRING_ARCH_strcspn
#include <string.h>
#include <stdint.h>

uint32_t count_quotes_with_strcspn(const char *ascii)
{
	__attribute__((aligned(16))) const char pattern[] = "\\\"";
	uint32_t q_n = 0;
	for (const char *s = ascii; *s;) {
		s += strcspn(s, pattern);

		if (*s == '"') {
			++q_n;
		} else if (*s == '\\') {
			++s;
			if (!*s)
				break;
		} else {
			break;
		}
		++s;
	}
	return q_n;
}
