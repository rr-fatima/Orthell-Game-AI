
#include <sys/time.h>
#include <sys/resource.h>

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "reversiAlgB.h"

int countPieces(char board[][26], int n);
int countMobility(char board[][26], int n, char colour);
int countIdealScore(char board[][26], int n, char colour);
int countPlayerPieces(char board[][26], int n, char colour);
int evaluate(char board[][26], int n, char colour);
int minimax(char board[][26], int n, int depth, bool maxPlayer, char player);
int makeMove(const char board[][26], int n, char turn, int *row, int *col);

// checks if the row and column are in bounds
bool positionInBounds(int n, int row, int col){
  bool check = false;

  if ((row < n && row > -1) && (col < n && col > -1)) {
    check = true;
  }

  return check;
}

// for deciding who won the game
void decideWin(char board[][26], int n) {
  int Bscore = 0;
  int Wscore = 0;
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (board[row][col] == 'B') {
        Bscore++;
      } else if (board[row][col] == 'W') {
        Wscore++;
      }
    }
  }

  if (Bscore > Wscore) {
    printf("B player wins.\n");
  } else if (Bscore < Wscore) {
    printf("W player wins.\n");
  } else {
    printf("Draw!\n");
  }
}

// checks if a move is valid
bool validMove(char board[][26], int n, int row, int col, char colour) {
  bool done = false;
  if (board[row][col] == 'U') {
    if (checkLegalInDirection(board, n, row, col, colour, 1, 0)) {  // S
      done = true;
    } else if (checkLegalInDirection(board, n, row, col, colour, 1, -1)) {  // SW
      done = true;
    } else if (checkLegalInDirection(board, n, row, col, colour, 0, -1)) {  // W
      done = true;
    } else if (checkLegalInDirection(board, n, row, col, colour, -1,-1)) {  // NW
      done = true;
    } else if (checkLegalInDirection(board, n, row, col, colour, -1, 0)) {  // N
      done = true;
    } else if (checkLegalInDirection(board, n, row, col, colour, -1, 1)) {  // NE
      done = true;
    } else if (checkLegalInDirection(board, n, row, col, colour, 0, 1)) {  // E
      done = true;
    } else if (checkLegalInDirection(board, n, row, col, colour, 1, 1)) {  // SE
      done = true;
    }
  }

  return done;
}

// tells if the colour have moves available
bool moveAvai(char board[][26], int n, char colour) {
  bool avai = false;

  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if(validMove(board, n, row, col, colour)){
        avai = true;
        break;
      }
    }
  }
  return avai;
}

// prints the board
void printBoard(char board[][26], int n) {
  printf("  ");
  for (char i = 'a'; (i - 'a') < n; i++) {
    printf("%c", i);
  }
  printf("\n");

  for (int row = 0; row < n; row++) {
    printf("%c ", 'a' + row);
    for (int col = 0; col < n; col++) {
      printf("%c", board[row][col]);
    }
    printf("\n");
  }
}

// checks if its legal to place W or B in the row and column, based on the
// objects in this direction
bool checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol) {
  bool check = false;

  if (colour == 'W') {
    if (positionInBounds(n, row + (2 * deltaRow), col + (2 * deltaCol))) {
      if (board[row + deltaRow][col + deltaCol] == 'B') {
        for (int i = 2;
             positionInBounds(n, row + (deltaRow * i), col + (deltaCol * i));
             i++) {
          int tempRow = row + (deltaRow * i);
          int tempCol = col + (deltaCol * i);
          if (board[tempRow][tempCol] == 'W') {
            check = true;
            break;
          } else if (board[tempRow][tempCol] == 'U') {
            break;
          }
        }
      }
    }

  } else if (colour == 'B') {
    if (positionInBounds(n, row + (2 * deltaRow), col + (2 * deltaCol))) {
      if (board[row + deltaRow][col + deltaCol] == 'W') {
        for (int i = 2;
             positionInBounds(n, row + (deltaRow * i), col + (deltaCol * i));
             i++) {
          int tempRow = row + (deltaRow * i);
          int tempCol = col + (deltaCol * i);
          if (board[tempRow][tempCol] == 'B') {
            check = true;
            break;
          } else if (board[tempRow][tempCol] == 'U') {
            break;
          }
        }
      }
    }
  }

  return check;
}

// turns the existing objects based on the move
void turn(char board[][26], int n, int row, int col, char colour, int deltaRow,  int deltaCol) {
  if (colour == 'W') {
    board[row][col] = 'W';

    for (int i = 1;
         positionInBounds(n, row + (deltaRow * i), col + (deltaCol * i)); i++) {
      int tempRow = row + (deltaRow * i);
      int tempCol = col + (deltaCol * i);
      if (board[tempRow][tempCol] == 'W') {
        break;
      } else {
        board[tempRow][tempCol] = 'W';
      }
    }

  } else if (colour == 'B') {
    board[row][col] = 'B';

    for (int i = 1;
         positionInBounds(n, row + (deltaRow * i), col + (deltaCol * i)); i++) {
      int tempRow = row + (deltaRow * i);
      int tempCol = col + (deltaCol * i);
      if (board[tempRow][tempCol] == 'B') {
        break;
      } else {
        board[tempRow][tempCol] = 'B';
      }
    }
  }
}

// turns the object already assuming the row and col are legal 
bool fullTurn(char board[][26], int n, int row, int col, char colour) {
  bool done = false;

  if (checkLegalInDirection(board, n, row, col, colour, 1, 0)) {  // S
    turn(board, n, row, col, colour, 1, 0);
    done = true;
  }
  if (checkLegalInDirection(board, n, row, col, colour, 1, -1)) {  // SW
    turn(board, n, row, col, colour, 1, -1);
    done = true;
  }
  if (checkLegalInDirection(board, n, row, col, colour, 0, -1)) {  // W
    turn(board, n, row, col, colour, 0, -1);
    done = true;
  }
  if (checkLegalInDirection(board, n, row, col, colour, -1, -1)) {  // NW
    turn(board, n, row, col, colour, -1, -1);
    done = true;
  }
  if (checkLegalInDirection(board, n, row, col, colour, -1, 0)) {  // N
    turn(board, n, row, col, colour, -1, 0);
    done = true;
  }
  if (checkLegalInDirection(board, n, row, col, colour, -1, 1)) {  // NE
    turn(board, n, row, col, colour, -1, 1);
    done = true;
  }
  if (checkLegalInDirection(board, n, row, col, colour, 0, 1)) {  // E
    turn(board, n, row, col, colour, 0, 1);
    done = true;
  }
  if (checkLegalInDirection(board, n, row, col, colour, 1, 1)) {  // SE
    turn(board, n, row, col, colour, 1, 1);
    done = true;
  }

  return done;
}

// makes the computer move
bool compMove(char board[][26], int n, char compColour) {
  bool done = false;
  int tempNum = 0;
  int prefRow = 0;
  int prefCol = 0;

  if (moveAvai(board, n, compColour)) {
    
    tempNum = makeMove(board, n, compColour, &prefRow, &prefCol);

    done = fullTurn(board, n, prefRow, prefCol, compColour);
    printf("Computer places %c at %c%c. \n", compColour,'a' + prefRow, 'a' + prefCol);
    printBoard(board, n);

  } else {
    printf("%c player has no valid move.\n", compColour);
  }

  return done;
}

// get the move from the user
bool userMove(char board[][26], int n, char colour) {

  char colA, rowA;
  bool legal = false;
  int row = 0;
  int col = 0;
  
  printf("Enter move for colour %c (RowCol): ", colour);
  scanf(" %c%c", &rowA, &colA);
  row = rowA - 'a';
  col = colA - 'a';

  if (col < 26 && col > -1 && row < 26 && row > -1) {
    if (positionInBounds(n, row, col) && board[row][col] == 'U') {
      
      legal = fullTurn(board,n,row, col, colour);

      if (legal == true) {
        printBoard(board, n);
      } else {
        printf("Invalid move.\n");
      }

    } else {
      printf("Invalid move.\n");
    }
  } else {
    printf("Invalid move.\n");
  }

  return legal;

}

// begins the game
void startsGame(char board[][26], int n, char compColour) {
  bool legal = true;
  bool available = true;
  bool moveB = false;
  bool moveW = false;

  while (legal && available) {
    if (compColour == 'B') {
      moveB = compMove(board, n, 'B');
      moveW = moveAvai(board, n, 'W');

      if (!moveAvai(board, n, 'W') && !moveAvai(board, n, 'B')) {
        break;
      }

      if (moveW) {
        legal = userMove(board, n, 'W');
      } else {
        printf("W player has no valid move.\n");
      }

    } else {
      moveB = moveAvai(board, n, 'B');

      if (moveB) {
        legal = userMove(board, n, 'B');
      } else {
        printf("B player has no valid move.\n");
      }

      if (!moveAvai(board, n, 'W') && !moveAvai(board, n, 'B')) {
        break;
      }

      if (legal) {
        moveW = compMove(board, n, 'W');
      }
    }

    if (!moveAvai(board, n, 'W') && !moveAvai(board, n, 'B')) {
      break;
    }
  }

  decideWin(board, n);
  
}

// main function
int main(void) {
  int size = 0;
  int middle = 0;
  char board[26][26];
  char compColour;  // stores the colour the computer should play

  // asks user for the dimension of the board
  printf("Enter the board dimension: ");
  scanf("%d", &size);
  middle = size / 2;

  // creating the board
  for (int row = 0; row < size; row++) {
    for (int col = 0; col < size; col++) {
      if ((row == middle && col == middle) ||
          (row == (middle - 1) && col == (middle - 1))) {
        board[row][col] = 'W';
      } else if ((row == middle && col == (middle - 1)) ||
                 (row == (middle - 1) && col == middle)) {
        board[row][col] = 'B';
      } else {
        board[row][col] = 'U';
      }
    }
  }

  // gets the colour for computer
  printf("Computer plays (B/W): ");
  scanf(" %c", &compColour);

  printBoard(board, size);  // prints the board

  startsGame(board, size, compColour);

  return 0;
}

int makeMove(const char board[][26], int n, char turn, int *row, int *col) {

  int bestScore = INT_MIN; // used the limit library

  for (int rowX = 0; rowX < n; rowX++) {
    for (int colX = 0; colX < n; colX++) {
      if (validMove(board, n, rowX, colX, turn)) {

        // mskes a temporary board
        char tempBoard[26][26];
        for (int x = 0; x < n; x++) {
          for (int y = 0; y < n; y++) {
            tempBoard[x][y] = board[x][y];
          }
        }

        fullTurn(tempBoard, n, rowX, colX, turn);
        int score = minimax(tempBoard, n, 5, false, turn);

        //checks if the score is better and make changes according to it
        if (score > bestScore) {
          bestScore = score;
          *row = rowX;
          *col = colX;
        }
        
      }
    }
  }

  return 0;
}

int minimax(char board[][26], int n, int depth, bool maxPlayer, char player) {
  if (depth == 0) {
    return evaluate(board,n, player);
  }

  char opponent, currentPlayer;
  int bestVal;

  if (maxPlayer) {
    bestVal = INT_MIN; // used the limit library
  } else {
    bestVal = INT_MAX; // used the limit library
  }

  if (player == 'B') {
    opponent = 'W';
  } else {
    opponent = 'B';
  }

  if(maxPlayer){
    currentPlayer = player;
  } else{
    currentPlayer = opponent;
  }

    // Iterate through all possible moves
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (validMove(board, n, i, j, currentPlayer)) {
            
          char tempBoard[26][26];
          // Make a copy of the board
          for (int x = 0; x < n; x++) {
            for (int y = 0; y < n; y++) {
              tempBoard[x][y] = board[x][y];
            }
          }
          // take a temporary board and makes a move on it
          fullTurn(tempBoard, n, i, j, currentPlayer);

          // Recur to find the best value for the other player
          int value = minimax(tempBoard, n, depth - 1, !maxPlayer, player);

          // Update the best value
          if ((maxPlayer && value > bestVal) || (!maxPlayer && value < bestVal)) {
            bestVal = value;
          }

        }
      }
    }
  return bestVal;
}

int evaluate(char board[][26], int n, char colour){

  char opponent;
  if(colour == 'B'){
    opponent = 'W';
  } else{
    opponent = 'B';
  }

  int compScore = 0;

  // for factoring in the mobility of the piece
  int computerMobility = countMobility(board, n,colour);
  int opponentMobility = countMobility(board,n, opponent);
  compScore += (computerMobility - opponentMobility) * 10;

    // for factoring in the ideal position of the pieces
  int computerControl = countIdealScore(board,n, colour);
  int opponentControl = countIdealScore(board,n,opponent);
  compScore += (computerControl - opponentControl) * 20; 

    // for factoring in the no. of pieces on the board
  int totalPieces = countPieces(board,n);
  int computerPieces = countPlayerPieces(board,n, colour);
  int opponentPieces = countPlayerPieces(board,n, opponent);
  int parityScore = (computerPieces - opponentPieces) * 100 / totalPieces;
  compScore += parityScore;

  return compScore;

}

int countPieces(char board[][26], int n){
  int count=0;
  for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++){
        if(board[i][j]!='U'){
          count++;
        }
      }
  }

  return count;
}

int countMobility(char board[][26], int n, char colour){
  int mobility = 0;
  for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
          if (validMove(board,n, i, j, colour)) {
              mobility++;
          }
      }
  }
  return mobility;
}

int countIdealScore(char board[][26], int n, char colour){
  int idealControl = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        if (board[i][j] == colour) {

          // Assign higher scores to center and edge positions as they are the most stable
          if ((i == 0 || i == n - 1 || j == 0 || j == n - 1) && (i != 0 || i != n - 1 || j != 0 || j != n - 1)) {
            idealControl += 2;
          } else {
            idealControl++;
          }
          
        }
    }
  }
  return idealControl;
}

int countPlayerPieces(char board[][26], int n, char colour){
  int count=0;
  for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++){
        if(board[i][j]== colour){
          count++;
        }
      }
  }

  return count;
}
