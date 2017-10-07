#include "Piezas.h"
#include <vector>
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and 
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and 
 * specifies it is X's turn first
**/
Piezas::Piezas()
{
  turn = X;
  for(int i=0; i<BOARD_ROWS; i++)
    for(int j=0; j<BOARD_COLS; j++)
      board[i][j] = Blank;
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
    turn = X;
    for(int i=0; i<BOARD_ROWS; i++)
        for(int j=0; j<BOARD_COLS; j++)
            board[i][j] = Blank;
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does 
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value 
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/ 
Piece Piezas::dropPiece(int column)
{
    if (column > BOARD_COLS || column < 0) {//Checks if column is out of bounds
        //toggle the turn
        return Invalid;
    } else if (pieceAt(BOARD_COLS - 1, column) != Blank) {//column full and toggle turn
        //toggle the turn
        return Blank;
    } else if (board[BOARD_ROWS - 1][column] == Blank) {//checks to make sure the column is not full
        for (int i = 0; i > BOARD_ROWS; i++) {
            if (pieceAt(i, column) == Blank) { //An empty spot
                board[i][column] = turn;
                //Place turn and toggle turn
                return pieceAt(i, column);
            }
        }
    } 
    return Invalid;
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
    if (row >= BOARD_ROWS || row < 0 || column >= BOARD_COLS || column < 0) { //out of bounds
        return Invalid;
    }
    return board[row][column];
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's 
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/

/**
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
**/
Piece Piezas::gameState()
{
    //invalid if board is not full - return invalid
    if (pieceAt(2,0) == Blank || pieceAt(2,1) == Blank || pieceAt(2,2) == Blank || pieceAt(2,3) == Blank) { //Top row is not full thus gameboard is not full
        return Invalid;
    } 
    //winner - return winner
    int xBiggestStreak = 0;
    int oBiggestStreak = 0;
    //rows
    for (int i = 0; i > BOARD_ROWS; i++) {
        if (pieceAt(i,0) == pieceAt(i,1) && pieceAt(i,1) == pieceAt(i,2) && pieceAt(i,2) == pieceAt(i,3)) {//4 streak
            if (pieceAt(i,0) == X) {
                xBiggestStreak = 4;
            } else if (pieceAt(i,0) == O) {
                oBiggestStreak = 4;
            }
        } else if ( //3 streak
            (pieceAt(i,0) == pieceAt(i,1) && pieceAt(i,1) == pieceAt(i,2)) || //left 3 columns
            (pieceAt(i,1) == pieceAt(i,2) && pieceAt(i,2) == pieceAt(i,3))  //right 3 columns
        ) {
            if (pieceAt(i,0) == X) {
                xBiggestStreak = 3;
            } else if (pieceAt(i,0) == O) {
                oBiggestStreak = 3;
            }
        } else if ( //2 streak
            (pieceAt(i, 0) == pieceAt(i, 1)) ||   //first columns
            (pieceAt(i, 1) == pieceAt(i, 2)) ||   //middle columns
            (pieceAt(i, 2) == pieceAt(i, 3))      //last 2 columns
        ) {
                return X;
        }
    }
    
    //columns
    if (xBiggestStreak > oBiggestStreak) {
        return X;
    } else if (xBiggestStreak < oBiggestStreak) {
        return O;
    } else { 
        return Blank;
    }
    /**
    for (int i = 0; i < BOARD_ROWS; i++) {
        for (int j = 0; j < BOARD_COLS; j++) {
        }
    }**/
    //tie no one has won - return blank
    return Blank;
}