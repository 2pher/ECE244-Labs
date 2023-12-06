//
//  playMove.cpp
//  Connect Four Game
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Modified by Tarek Abdelrahman on 2020-09-17.
//  Modified by Salma Emara and Ethan Hugh on 2023-09-06
//  Copyright © 2019-2020 Tarek Abdelrahman. All rights reserved.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//
//  ECE244 Student: write your code for playMove in this file

#include "GameState.h"
#include "globals.h"

// Function prototypes (if you need)
bool check_winner(GameState& game_state);
bool check_connectFourEnd(GameState& game_state, int dRow, int dCol);
bool check_connectFourMiddle(GameState& game_state, int dRow, int dCol);
bool positionInBounds(int row, int col);

void playMove(GameState& game_state) {
  // Change turn if move is valid
  if (game_state.get_turn() == true) {
    game_state.set_turn(false);
  } else {
    game_state.set_turn(true);
  }

  // Change gameOver
  if (check_winner(game_state) == true) {
    game_state.set_gameOver(true);
  }

  // Change winner
  if (game_state.get_gameOver() == true) {
    game_state.set_winner(game_state.get_gameBoard(
    game_state.get_selectedRow(), game_state.get_selectedColumn()));
  }
}

bool check_winner(GameState& game_state) {
  /* Checks for two cases:
     1. The winning move is an end-winning piece
     2. The winning move is one of the middle pieces of the connect four */
  for (int dRow = -1; dRow < 2; dRow++) {
    for (int dCol = -1; dCol < 2; dCol++) {
      if (dRow == 0 && dCol == 0) {
        continue;
      } else {
        if (check_connectFourEnd(game_state, dRow, dCol) == true ||
            check_connectFourMiddle(game_state, dRow, dCol) == true) {
          return true;  // There is a winnner!
        }
      }
    }
  }
  return false;  // Checked all directions of board tile, no connect 4
}

bool check_connectFourEnd(GameState& game_state, int dRow, int dCol) {
  int counter = 1;             // Initialize counter to 1. [Current player tile]
  int incRow = 0, incCol = 0;  // Row/column incrementers for while-loop
  // If delta row/col is positive, we want to keep incrementing in the same
  // direction; vice-versa
  if (dRow > 0) {
    incRow = 1;
  } else {
    if (dRow < 0) {
      incRow = -1;
    }
  }
  if (dCol > 0) {
    incCol = 1;
  } else {
    if (dCol < 0) {
      incCol = -1;
    }
  }
  /* Run a while-loop that checks if adjacent square is the same value as the
     current player's turn while also being in the bounds of the board */
  while (positionInBounds(game_state.get_selectedRow() + dRow,
                          game_state.get_selectedColumn() + dCol) &&
         game_state.get_gameBoard(game_state.get_selectedRow() + dRow,
                                  game_state.get_selectedColumn() + dCol) ==
             game_state.get_gameBoard(game_state.get_selectedRow(),
                                      game_state.get_selectedColumn())) {
    counter++;
    if (counter == 4) {
      return true;
      break;
    }
    dRow += incRow;  // Set to next adjacent piece
    dCol += incCol;  // Set to next adjacent piece
    continue;
  }
  return false;  // If counter did not reach 4, there is no winning move. Return
                 // false
}

bool check_connectFourMiddle(GameState& game_state, int dRow, int dCol) {
  int counter = 1;             // Initialize counter to 1. [Current player tile]
  int incRow = 0, incCol = 0;  // Row/column incrementers for while-loop
  // Contrary to the previous function, we will start at one tile before/after
  // the currently placed tile
  int startRow = game_state.get_selectedRow() - dRow,
      startCol = game_state.get_selectedColumn() - dCol;
  // If delta row/col is positive, we want to keep incrementing in the same
  // direction; vice-versa
  if (dRow > 0) {
    incRow = 1;
  } else {
    if (dRow < 0) {
      incRow = -1;
    }
  }
  if (dCol > 0) {
    incCol = 1;
  } else {
    if (dCol < 0) {
      incCol = -1;
    }
  }
  // First check if this new starting bound is defined and equal to player's
  // tile
  if (positionInBounds(startRow, startCol) &&
      game_state.get_gameBoard(startRow, startCol) ==
      game_state.get_gameBoard(game_state.get_selectedRow(),
                               game_state.get_selectedColumn())) {
    /* Run a while-loop that checks if adjacent square is the same value as the
      current player's turn while also being in the bounds of the board */
    while (positionInBounds(startRow + incRow, startCol + incCol) &&
           game_state.get_gameBoard(startRow + incRow, startCol + incCol) ==
           game_state.get_gameBoard(game_state.get_selectedRow(),
                                    game_state.get_selectedColumn())) {
      counter++;
      if (counter == 4) {
        return true;
        break;
      }
      startRow += incRow;  // Set to next adjacent piece
      startCol += incCol;  // Set to next adjacent piece
      continue;
    }
    return false;  // If counter did not reach 4, there is no winning move.
                   // Return false
  }
  return false;
}

bool positionInBounds(int row, int col) {
  // Checks if inputted row/col is valid within the limits of the board
  if (row >= 0 && row <= boardSize && col >= 0 && col <= boardSize) {
    return true;
  }
  return false;  // New starting bound is invalid
}
