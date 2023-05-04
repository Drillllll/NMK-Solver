# NMK-solver
C++ project for solving NMK game state using min-max algorithm
[title](https://pl.wikipedia.org/wiki/Algorytm_min-max).

General version of Tic Tac Toe game - family of NMK games - takes 3 parameters N, M, K. (N x M) is the size of the board and (K) is a number of continuously adjacent squares in a continuous vertical, horizontal or diagonal line that are required to win. For simplicity tokens of first player are marked as "1", tokens of second player marked as "2" and empty fields marked as "0".

Game engine is able to:
1. generate all possible moves
2. Evaluate the game - is game over? Who won the game?
3. Solve the given NMK game state: assuming both players play optimally, who will win the current game?

The program supports 3 commands:

1. GEN_ALL_POS_MOV N M K ActivePlayer - genarates all possible moves with their number

Example:

IN:

GEN_ALL_POS_MOV 3 3 3 2 <br>
1 0 0 <br>
0 0 0 <br>
0 0 0 <br>

OUT:

`8 \n
1 2 0
0 0 0
0 0 0`

1 0 2
0 0 0
0 0 0

1 0 0
2 0 0
0 0 0

1 0 0
0 2 0
0 0 0

1 0 0
0 0 2
0 0 0

1 0 0
0 0 0
2 0 0

1 0 0
0 0 0
0 2 0

1 0 0
0 0 0
0 0 2


2. GEN_ALL_POS_MOV_CUT_IF_GAME_OVER N M K ActivePlayer - genarates all possible moves with their number. If one od the moves is winning or ending a game, only the first mobe is generated.

Example:

IN:
GEN_ALL_POS_MOV_CUT_IF_GAME_OVER 3 3 3 1
0 2 1
2 2 1
0 1 0

OUT:
1
0 2 1
2 2 1
0 1 1


3 SOLVE_GAME_STATE N M K ActivePlayer - solve the game giving one response: FIRST_PLAYER_WINS, SECOND_PLAYER_WINS, BOTH_PLAYERS_TIE.

Example:

IN:
SOLVE_GAME_STATE 3 3 3 2
1 0 0
0 0 0
0 0 0

OUT:
BOTH_PLAYERS_TIE
