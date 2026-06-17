/*
 * utils.h - Utility function declarations
 *
 * Provides safe console input helpers used by the game module.
 * Separating input logic keeps game.c focused on game rules.
 */

#ifndef UTILS_H
#define UTILS_H

/*
 * clear_input_buffer - Remove leftover characters from stdin.
 *
 * Called after scanf fails or reads partial input so the next
 * prompt is not affected by garbage on the input line.
 */
void clear_input_buffer(void);

/*
 * read_integer_in_range - Read one integer between min and max (inclusive).
 *
 * Parameters:
 *   min   - smallest acceptable value
 *   max   - largest acceptable value
 *   value - output: the successfully read integer
 *
 * Returns 1 on success, 0 on EOF or invalid/non-numeric input.
 */
int read_integer_in_range(int min, int max, int *value);

#endif /* UTILS_H */
