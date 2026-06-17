/*
 * game.h - Tic Tac Toe game module interface
 *
 * Sprint 1 deliverable: project skeleton with constants, enums,
 * structures, and public function declarations.
 */

#ifndef GAME_H
#define GAME_H

/* -------------------------------------------------------------------------
 * Constants (Sprint 1)
 * ------------------------------------------------------------------------- */

#define BOARD_SIZE   3
#define EMPTY_CELL   ' '
#define PLAYER_X     'X'
#define PLAYER_O     'O'

/* -------------------------------------------------------------------------
 * Enumerations
 * ------------------------------------------------------------------------- */

/*
 * GameStatus - Represents the outcome after each move check.
 *
 * GAME_ONGOING : match continues
 * GAME_DRAW    : board full, no winner
 * GAME_WIN_X   : Player X has three in a row
 * GAME_WIN_O   : Player O has three in a row
 */
typedef enum {
    GAME_ONGOING = 0,
    GAME_DRAW,
    GAME_WIN_X,
    GAME_WIN_O
} GameStatus;

/* -------------------------------------------------------------------------
 * Structures (Sprint 1)
 * ------------------------------------------------------------------------- */

/*
 * Board - 3x3 grid; each cell stores EMPTY_CELL, PLAYER_X, or PLAYER_O.
 */
typedef struct {
    char cells[BOARD_SIZE][BOARD_SIZE];
} Board;

/*
 * Scoreboard - Session statistics (Sprint 8).
 * Persists across replays until the program exits.
 */
typedef struct {
    int x_wins;
    int o_wins;
    int draws;
} Scoreboard;

/* -------------------------------------------------------------------------
 * Board management (Sprint 2)
 * ------------------------------------------------------------------------- */

void init_board(Board *board);
void display_board(const Board *board);

/* -------------------------------------------------------------------------
 * Player actions (Sprint 3 & 4)
 * ------------------------------------------------------------------------- */

int get_player_move(const Board *board, char player, int *row, int *col);
void make_move(Board *board, int row, int col, char player);
char switch_player(char current_player);

/* -------------------------------------------------------------------------
 * Validation (Sprint 4)
 * ------------------------------------------------------------------------- */

int is_valid_move(const Board *board, int row, int col);

/* -------------------------------------------------------------------------
 * Game state (Sprint 5 & 6)
 * ------------------------------------------------------------------------- */

GameStatus check_winner(const Board *board);
int is_board_full(const Board *board);

/* -------------------------------------------------------------------------
 * Game flow (Sprint 7)
 * ------------------------------------------------------------------------- */

/*
 * play_game - Run one complete match.
 * Updates and displays the session scoreboard when the game ends.
 * Returns 0 if input ended early (EOF); otherwise returns 1.
 */
int play_game(Scoreboard *scoreboard);
int ask_play_again(void);

/* -------------------------------------------------------------------------
 * Scoreboard (Sprint 8)
 * ------------------------------------------------------------------------- */

void update_scoreboard(Scoreboard *scoreboard, GameStatus status);
void display_scoreboard(const Scoreboard *scoreboard);

#endif /* GAME_H */
