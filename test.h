#ifndef _TEST_H_
#define _TEST_H_
#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int num_cmp(const void *a, const void *b);

#define TIMEIT(name_, n_, code_) ({ \
	uint32_t *times_ = malloc(sizeof(*times_) * n_); \
	for (uint32_t i_ = 0; i_ < n_; ++i_) { \
		struct timespec ts_start_; \
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_start_); \
		code_; \
		struct timespec ts_finish_; \
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_finish_); \
		int32_t diff_mksecs_ = (ts_finish_.tv_nsec - ts_start_.tv_nsec) / 1000 + (ts_finish_.tv_sec - ts_start_.tv_sec) * 1000000; \
		assert(diff_mksecs_ >= 0); \
		times_[i_] = diff_mksecs_; \
	} \
	qsort(times_, n_, sizeof(times_[0]), num_cmp); \
	uint64_t total_ = 0; \
	for (uint32_t i_ = 0;  i_ < n_; ++i_) { \
		total_ += times_[i_]; \
	} \
	uint32_t avg_ = total_ / n_; \
	uint32_t q50_ = times_[n_ / 2]; \
	uint32_t q95_ = times_[(int)(n * 0.95)]; \
	printf("%s done %u loops: total: %llu mksecs, perloop: avg=%u, q50=%u, q95=%u\n", \
		name_, (uint32_t)n_, (long long unsigned)total_, avg_, q50_, q95_); \
})

#define MIN(a_, b_) ((a_) < (b_) ? (a_) : (b_))

uint32_t count_quotes_with_strcspn(const char *ascii);

#endif // _TEST_H_
