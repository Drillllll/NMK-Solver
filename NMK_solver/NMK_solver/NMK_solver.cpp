#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>

struct Pos {
    int y, x;
};

struct Game {
    char** board;
    int n, m, k;
    int moveCount;
    char actPlayer;

    int lastX, lastY;

    void genAllPosMov();
    void genAllPosMovCutIfGameOver();

    void scanParametersAndBoard();
    void deleteBoard();
    void replaceAndPrint(int y, int x);
    void printAllPosMov();
    bool isPartOfWinningSequence(int y, int x, char player);
    bool didPrevPlayerWin(char prevP);
    char givePrevPlayer(char actP);
    int countEmptyFields();
    int minMax(char activePlayer);
    void solveGameState();
    bool isBoardFull();
    Pos* giveAllEmptyCoordinates(int emptyFields);

};


int main()
{
    Game game;
    char command[100];

    while (true) {
        scanf("%s", command);
        if (feof(stdin) != 0) break;

        if (strcmp(command, "GEN_ALL_POS_MOV") == 0) game.genAllPosMov();
        if (strcmp(command, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER") == 0) game.genAllPosMovCutIfGameOver();
        if (strcmp(command, "SOLVE_GAME_STATE") == 0) game.solveGameState();
    }
}

void Game::solveGameState() {
    scanParametersAndBoard();

    lastX = 0; lastY = 0;
    char prevP = givePrevPlayer(actPlayer);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (board[i][j] == prevP) {
                lastY = i;
                lastX = j;
                break;
            }

    int verdict;
    if (didPrevPlayerWin(givePrevPlayer(actPlayer))) {
        if (actPlayer == '1') verdict = -10;
        else verdict = 10;
    }
    else verdict = minMax(actPlayer);


    if (verdict < 0) printf("SECOND_PLAYER_WINS \n");
    else if (verdict > 0) printf("FIRST_PLAYER_WINS \n");
    else if (verdict == 0) printf("BOTH_PLAYERS_TIE \n");
}

int Game::minMax(char activePlayer) {

    if (isPartOfWinningSequence(lastY, lastX, givePrevPlayer(activePlayer))) {
        if (activePlayer == '1') return -10;
        else return 10;
    }

    if (isBoardFull()) return 0;



    int emptyFields = countEmptyFields();
    Pos* pos = giveAllEmptyCoordinates(emptyFields);

    int best;
    if (activePlayer == '1') {
        best = -10;
        for (int e = 0; e < emptyFields; e++) {
            //"makes move"
            board[pos[e].y][pos[e].x] = activePlayer;

            lastY = pos[e].y;
            lastX = pos[e].x;

            int v = minMax(givePrevPlayer(activePlayer));
            if (v > best) best = v;

            lastY = pos[e].y;
            lastX = pos[e].x;
            board[pos[e].y][pos[e].x] = '0';

            if (v == 10) break;
        }
    }
    else {
        best = 10;
        for (int e = 0; e < emptyFields; e++) {
            //"makes move"
            board[pos[e].y][pos[e].x] = activePlayer;

            lastY = pos[e].y;
            lastX = pos[e].x;

            int v = minMax(givePrevPlayer(activePlayer));
            if (v < best) best = v;

            lastY = pos[e].y;
            lastX = pos[e].x;
            board[pos[e].y][pos[e].x] = '0';

            if (v == -10) break;
        }
    }
    delete[] pos;
    return best;
}

bool Game::isBoardFull() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (board[i][j] == '0') return false;

    return true;
}

Pos* Game::giveAllEmptyCoordinates(int emptyFields) {
    Pos* pos = new Pos[emptyFields];
    int capacity = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (board[i][j] == '0') {
                Pos tmpPos;
                tmpPos.y = i; tmpPos.x = j;
                pos[capacity] = tmpPos;
                capacity++;
            }
    return pos;
}

char Game::givePrevPlayer(char actP) {
    if (actP == '1') return '2';
    else return '1';
}

void Game::scanParametersAndBoard() {
    scanf("%d %d %d %c", &n, &m, &k, &actPlayer);

    //creating a board
    board = new char* [n];
    for (int i = 0; i < n; i++) board[i] = new char[m];

    //scanning the board
    char v;
    scanf("%c", &v); //new line 
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            scanf("%c%*c", &v); //read the board and discard the newline character
            board[i][j] = v;
        }
}

void Game::genAllPosMovCutIfGameOver() {
    scanParametersAndBoard();
    if (didPrevPlayerWin(givePrevPlayer(actPlayer)) == true) {
        printf("0 \n");
    }
    else {
        int winY, winX;
        bool isWinningMove = false;
        for (int i = 0; i < n && isWinningMove == false; i++)
            for (int j = 0; j < m; j++)
                if (board[i][j] == '0')
                    if (isPartOfWinningSequence(i, j, actPlayer) == true) {
                        winY = i; winX = j;
                        isWinningMove = true;
                        break;
                    }
        if (isWinningMove == true) {
            printf("1 \n");
            replaceAndPrint(winY, winX);
        }
        else printAllPosMov();
    }
    deleteBoard();

}

void Game::genAllPosMov() {
    scanParametersAndBoard();

    //show results
    if (didPrevPlayerWin(givePrevPlayer(actPlayer)) == false) {
        printAllPosMov();
    }
    else {
        printf("0 \n");
    }

    deleteBoard();
}

bool Game::didPrevPlayerWin(char prevP) {

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (board[i][j] == prevP)
                if (isPartOfWinningSequence(i, j, prevP) == true) {
                    return true;
                }
    return false;
}

void Game::deleteBoard() {
    for (int i = 0; i < n; i++) delete[] board[i];
    delete[] board;
    board = NULL;
}

void Game::printAllPosMov() {
    int emptyFields = countEmptyFields();

    printf("\n%d \n", emptyFields);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (board[i][j] == '0') replaceAndPrint(i, j);
}

int Game::countEmptyFields() {
    int emptyFields = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (board[i][j] == '0') emptyFields++;
    return emptyFields;
}

//prints the board with field(x,y) replaced by actPlayer token
void Game::replaceAndPrint(int y, int x) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            if (i == y && j == x) printf("%c ", actPlayer);
            else printf("%c ", board[i][j]);
        printf("\n");
    }
    printf("\n");
}

//player is the owner of the sequence
bool Game::isPartOfWinningSequence(int y, int x, char player) {
    //char player = board[y][x];
    int sequence = 1;

    //col down
    for (int i = y + 1; i < n; i++) {
        if (board[i][x] == player) sequence++;
        else break;
    }
    //col up
    for (int i = y - 1; i >= 0; i--) {
        if (board[i][x] == player) sequence++;
        else break;
    }
    if (sequence >= k) return true;

    sequence = 1;
    //row to the right
    for (int j = x + 1; j < m; j++) {
        if (board[y][j] == player) sequence++;
        else break;
    }
    //row to the left
    for (int j = x - 1; j >= 0; j--) {
        if (board[y][j] == player)sequence++;
        else break;
    }
    if (sequence >= k) return true;

    sequence = 1;
    //diagonal '\' down
    for (int d = 1; y + d < n && x + d < m; d++) {
        if (board[y + d][x + d] == player) sequence++;
        else break;
    }
    //diagonal '\' up
    for (int d = 1; y - d >= 0 && x - d >= 0; d++) {
        if (board[y - d][x - d] == player) sequence++;
        else break;
    }
    if (sequence >= k) return true;

    sequence = 1;
    //diagonal '/' down
    for (int d = 1; y + d < n && x - d >= 0; d++) {
        if (board[y + d][x - d] == player) sequence++;
        else break;
    }
    //diagonal '\' up
    for (int d = 1; y - d >= 0 && x + d < m; d++) {
        if (board[y - d][x + d] == player) sequence++;
        else break;
    }
    if (sequence >= k) return true;

    return false;
}