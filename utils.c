/*
 * utils.c - Utility function implementations
 *
 * Sprint 3 deliverable: safe player input system.
 * Handles numeric validation and input buffer cleanup.
 */

#include <stdio.h>
#include "utils.h"

/*
 * clear_input_buffer - Discard characters until newline or EOF.
 */
void clear_input_buffer(void)
{
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
        /* intentionally empty: consume and discard each character */
    }
}

/*
 * read_integer_in_range - Validate that input is a number in [min, max].
 *
 * Rejects letters, symbols, and out-of-range values by returning 0
 * and clearing the input buffer so the user can try again cleanly.
 */
int read_integer_in_range(int min, int max, int *value)
{
    int result;

    if (scanf("%d", &result) != 1) {
        clear_input_buffer();
        return 0;
    }

    if (result < min || result > max) {
        clear_input_buffer();
        return 0;
    }

    *value = result;
    return 1;
}
