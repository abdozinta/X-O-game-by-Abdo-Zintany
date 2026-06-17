/*
 * game.c - Tic Tac Toe game logic implementation
 *
 * Implements board rendering, turn management, win/draw detection,
 * scoreboard tracking, and the complete game loop.
 */

#include <stdio.h>
#include <ctype.h>
#include "game.h"
#include "utils.h"

/* =========================================================================
 * Sprint 2 — Board System
 * ========================================================================= */

/*
 * init_board - Set every cell to EMPTY_CELL.
 */
void init_board(Board *board)
{
    int row;
    int col;

    for (row = 0; row < BOARD_SIZE; row++) {
        for (col = 0; col < BOARD_SIZE; col++) {
            board->cells[row][col] = EMPTY_CELL;
        }
    }
}

/*
 * display_board - Render the 3x3 grid with coordinate labels.
 */
void display_board(const Board *board)
{
    int row;
    int col;

    printf("\n");
    printf("  ");
    for (col = 0; col < BOARD_SIZE; col++) {
        printf(" %d  ", col + 1);
    }
    printf("\n");

    for (row = 0; row < BOARD_SIZE; row++) {
        printf("+---+---+---+\n");
        printf("%d", row + 1);

        for (col = 0; col < BOARD_SIZE; col++) {
            char mark = board->cells[row][col];
            if (mark == EMPTY_CELL) {
                printf("|   ");
            } else {
                printf("| %c ", mark);
            }
        }
        printf("|\n");
    }
    printf("+---+---+---+\n\n");
}

/* =========================================================================
 * Sprint 4 — Validation and move placement
 * ========================================================================= */

/*
 * is_valid_move - Return 1 if the cell is inside the board and empty.
 */
int is_valid_move(const Board *board, int row, int col)
{
    if (row < 0 || row >= BOARD_SIZE) {
        return 0;
    }
    if (col < 0 || col >= BOARD_SIZE) {
        return 0;
    }
    if (board->cells[row][col] != EMPTY_CELL) {
        return 0;
    }
    return 1;
}

/*
 * make_move - Place the current player's mark on the board.
 */
void make_move(Board *board, int row, int col, char player)
{
    board->cells[row][col] = player;
}

/*
 * switch_player - Alternate between X and O after each valid turn.
 */
char switch_player(char current_player)
{
    if (current_player == PLAYER_X) {
        return PLAYER_O;
    }
    return PLAYER_X;
}

/* =========================================================================
 * Sprint 5 — Win detection
 * ========================================================================= */

/*
 * cells_match - Return 1 when three cells share the same non-empty mark.
 */
static int cells_match(char first, char second, char third)
{
    return (first != EMPTY_CELL) && (first == second) && (second == third);
}

/*
 * check_winner - Test all 8 winning lines (3 rows, 3 columns, 2 diagonals).
 *
 * Sprint 6 adds draw detection when the board is full with no winner.
 */
GameStatus check_winner(const Board *board)
{
    int index;

    /* Check rows */
    for (index = 0; index < BOARD_SIZE; index++) {
        if (cells_match(board->cells[index][0],
                        board->cells[index][1],
                        board->cells[index][2])) {
            return (board->cells[index][0] == PLAYER_X) ? GAME_WIN_X : GAME_WIN_O;
        }
    }

    /* Check columns */
    for (index = 0; index < BOARD_SIZE; index++) {
        if (cells_match(board->cells[0][index],
                        board->cells[1][index],
                        board->cells[2][index])) {
            return (board->cells[0][index] == PLAYER_X) ? GAME_WIN_X : GAME_WIN_O;
        }
    }

    /* Check main diagonal */
    if (cells_match(board->cells[0][0],
                    board->cells[1][1],
                    board->cells[2][2])) {
        return (board->cells[1][1] == PLAYER_X) ? GAME_WIN_X : GAME_WIN_O;
    }

    /* Check anti-diagonal */
    if (cells_match(board->cells[0][2],
                    board->cells[1][1],
                    board->cells[2][0])) {
        return (board->cells[1][1] == PLAYER_X) ? GAME_WIN_X : GAME_WIN_O;
    }

    /* Sprint 6 — draw when every cell is filled */
    if (is_board_full(board)) {
        return GAME_DRAW;
    }

    return GAME_ONGOING;
}

/* =========================================================================
 * Sprint 6 — Draw detection helper
 * ========================================================================= */

/*
 * is_board_full - Return 1 when no empty cells remain.
 */
int is_board_full(const Board *board)
{
    int row;
    int col;

    for (row = 0; row < BOARD_SIZE; row++) {
        for (col = 0; col < BOARD_SIZE; col++) {
            if (board->cells[row][col] == EMPTY_CELL) {
                return 0;
            }
        }
    }
    return 1;
}

/* =========================================================================
 * Sprint 3 — Player input (uses utils.c for safe reading)
 * ========================================================================= */

/*
 * get_player_move - Prompt until the player enters a valid, empty cell.
 *
 * Accepts 1-based row and column values (1-3).
 * Returns 0 only when input ends (EOF).
 */
int get_player_move(const Board *board, char player, int *row, int *col)
{
    int input_row;
    int input_col;
    int success;

    while (1) {
        printf("Player %c - enter row (1-%d) and column (1-%d): ",
               player, BOARD_SIZE, BOARD_SIZE);

        success = read_integer_in_range(1, BOARD_SIZE, &input_row);
        if (!success) {
            printf("Invalid input. Enter numbers between 1 and %d only.\n",
                   BOARD_SIZE);
            continue;
        }

        success = read_integer_in_range(1, BOARD_SIZE, &input_col);
        if (!success) {
            printf("Invalid input. Enter numbers between 1 and %d only.\n",
                   BOARD_SIZE);
            continue;
        }

        /* Convert user-friendly 1-based input to 0-based array indices */
        *row = input_row - 1;
        *col = input_col - 1;

        if (!is_valid_move(board, *row, *col)) {
            printf("Cell is occupied. Choose an empty cell.\n");
            continue;
        }

        return 1;
    }
}

/* =========================================================================
 * Sprint 7 — Result messages and replay prompt
 * ========================================================================= */

/*
 * announce_result - Display the final outcome of a finished game.
 */
static void announce_result(GameStatus status)
{
    switch (status) {
        case GAME_WIN_X:
            printf("\n*** Player X wins! ***\n");
            break;
        case GAME_WIN_O:
            printf("\n*** Player O wins! ***\n");
            break;
        case GAME_DRAW:
            printf("\nDraw Game!\n");
            break;
        default:
            break;
    }
}

/*
 * ask_play_again - Sprint 7 replay option with validated Y/N input.
 */
int ask_play_again(void)
{
    char answer;

    while (1) {
        printf("\nPlay Again? (Y/N): ");

        if (scanf(" %c", &answer) != 1) {
            clear_input_buffer();
            return 0;
        }

        answer = (char)tolower((unsigned char)answer);

        if (answer == 'y') {
            return 1;
        }
        if (answer == 'n') {
            return 0;
        }

        printf("Please enter Y or N.\n");
        clear_input_buffer();
    }
}

/* =========================================================================
 * Sprint 8 — Session scoreboard
 * ========================================================================= */

/*
 * update_scoreboard - Increment the counter matching the game result.
 */
void update_scoreboard(Scoreboard *scoreboard, GameStatus status)
{
    switch (status) {
        case GAME_WIN_X:
            scoreboard->x_wins++;
            break;
        case GAME_WIN_O:
            scoreboard->o_wins++;
            break;
        case GAME_DRAW:
            scoreboard->draws++;
            break;
        default:
            break;
    }
}

/*
 * display_scoreboard - Show cumulative session statistics.
 */
void display_scoreboard(const Scoreboard *scoreboard)
{
    printf("\n");
    printf("=================\n");
    printf("    SCOREBOARD\n");
    printf("=================\n");
    printf("Player X Wins: %d\n", scoreboard->x_wins);
    printf("Player O Wins: %d\n", scoreboard->o_wins);
    printf("Draws:         %d\n", scoreboard->draws);
    printf("=================\n");
}

/* =========================================================================
 * Complete game flow (Sprints 4–8 combined)
 * ========================================================================= */

/*
 * play_game - Execute one full match from setup to scoreboard update.
 *
 * Turn order: X, O, X, O, ... until win or draw.
 * Returns 0 if the player ends input early; 1 when a game finishes normally.
 */
int play_game(Scoreboard *scoreboard)
{
    Board board;
    char current_player = PLAYER_X;
    int row;
    int col;
    GameStatus status;

    init_board(&board);

    printf("\n=== New Game ===\n");
    printf("Player X goes first. Enter row and column using the board labels.\n");

    while (1) {
        display_board(&board);

        if (!get_player_move(&board, current_player, &row, &col)) {
            printf("\nInput ended.\n");
            return 0;
        }

        make_move(&board, row, col, current_player);
        status = check_winner(&board);

        if (status != GAME_ONGOING) {
            display_board(&board);
            announce_result(status);
            update_scoreboard(scoreboard, status);
            display_scoreboard(scoreboard);
            return 1;
        }

        current_player = switch_player(current_player);
    }
}
