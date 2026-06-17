/*
 * main.c - Program entry point
 *
 * Responsibilities:
 *   - Display welcome message
 *   - Run the main application and replay loops
 *   - Own the session scoreboard (no global variables)
 *   - Display goodbye message on exit
 */

#include <stdio.h>
#include "game.h"

int main(void)
{
    Scoreboard scoreboard = {0, 0, 0};
    int game_completed;

    printf("========================================\n");
    printf("       Welcome to Tic Tac Toe!\n");
    printf("========================================\n");
    printf("Two players alternate: X then O.\n");
    printf("Enter row and column (1-3) to place your mark.\n");

    do {
        game_completed = play_game(&scoreboard);
        if (!game_completed) {
            break;
        }
    } while (ask_play_again());

    printf("\nThanks for playing. Goodbye!\n");
    return 0;
}
