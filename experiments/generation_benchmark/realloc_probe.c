#define _GNU_SOURCE

#include <malloc.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

/*
 * Small glibc-only LD_PRELOAD probe used by the FIgenerator benchmarks.
 * It does not allocate memory in realloc() and reports only aggregate counts.
 */
extern void *__libc_realloc(void *pointer, size_t size);

static unsigned long long total_calls;
static unsigned long long null_pointer_calls;
static unsigned long long zero_size_calls;
static unsigned long long failed_calls;
static unsigned long long same_pointer_calls;
static unsigned long long moved_calls;
static unsigned long long growth_calls;
static unsigned long long in_place_growth_calls;
static unsigned long long moved_growth_calls;
static unsigned long long moved_copy_upper_bound;
static unsigned long long largest_moved_copy_upper_bound;

void *realloc(void *pointer, size_t size)
{
    size_t old_usable = pointer ? malloc_usable_size(pointer) : 0;
    void *result = __libc_realloc(pointer, size);
    size_t copy_upper_bound = old_usable < size ? old_usable : size;

    __sync_fetch_and_add(&total_calls, 1);
    if (!pointer) __sync_fetch_and_add(&null_pointer_calls, 1);
    if (size == 0) __sync_fetch_and_add(&zero_size_calls, 1);
    if (!result && size != 0) __sync_fetch_and_add(&failed_calls, 1);

    if (pointer && result)
    {
        if (result == pointer)
            __sync_fetch_and_add(&same_pointer_calls, 1);
        else
        {
            __sync_fetch_and_add(&moved_calls, 1);
            __sync_fetch_and_add(&moved_copy_upper_bound, copy_upper_bound);
            unsigned long long observed = largest_moved_copy_upper_bound;
            while (copy_upper_bound > observed &&
                   !__sync_bool_compare_and_swap(
                       &largest_moved_copy_upper_bound, observed, copy_upper_bound))
                observed = largest_moved_copy_upper_bound;
        }

        if (size > old_usable)
        {
            __sync_fetch_and_add(&growth_calls, 1);
            if (result == pointer)
                __sync_fetch_and_add(&in_place_growth_calls, 1);
            else
                __sync_fetch_and_add(&moved_growth_calls, 1);
        }
    }
    return result;
}

__attribute__((destructor)) static void report_realloc_totals(void)
{
    char buffer[2048];
    int length = snprintf(
        buffer,
        sizeof(buffer),
        "REALLOC_PROBE total_calls=%llu null_pointer_calls=%llu zero_size_calls=%llu "
        "failed_calls=%llu same_pointer_calls=%llu moved_calls=%llu growth_calls=%llu "
        "in_place_growth_calls=%llu moved_growth_calls=%llu "
        "moved_copy_upper_bound=%llu largest_moved_copy_upper_bound=%llu\n",
        total_calls,
        null_pointer_calls,
        zero_size_calls,
        failed_calls,
        same_pointer_calls,
        moved_calls,
        growth_calls,
        in_place_growth_calls,
        moved_growth_calls,
        moved_copy_upper_bound,
        largest_moved_copy_upper_bound);
    if (length > 0)
        (void)write(STDERR_FILENO, buffer, (size_t)length);
}
