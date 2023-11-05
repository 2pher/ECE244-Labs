//
//  connectfour.cpp
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
//  ECE244 Student: Complete the skeletal code of the main function in this file

#include <iostream>
#include <string>
using namespace std;

#include "GameState.h"
#include "globals.h"

// Function prototypes

// The main function
int main() {
  /**********************************************************************************/
  /* Create three initialized game state objects in an array */
  /**********************************************************************************/
  const int numOfRounds = 3;
  GameState game_state[numOfRounds];

  // Read one integer from the user that represents the column
  // the player would like to place their piece (R or Y) in
  // You can assume there will be no formatting errors in the input

  int col;
  int round = 0, R_wins = 0, Y_wins = 0;
  cout << "Game " << round+1;
  while (!game_state[round].get_gameOver()) {
    cout << "\nEnter column to place piece: ";
    cin >> col;
    // Assume move is invalid in order to check for validity
    game_state[round].set_moveValid(false);
    // Check validity of input and if not valid, handle accordingly
    while (game_state[round].get_moveValid() == false) {
      if (cin.eof()) {
        cerr << endl << "Game ended by user." << endl;
        exit(0);
      }
      if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        col = -1;  // Giving col invalid value so it will be handled as invalid input below
      }

      if (col == -1 || col < 0 || col >= boardSize) {  // Check first for invalid input
        cout << "Invalid column!\nEnter column to place piece: ";
        cin >> col;
      } else {  // Input is valid; check if column has an empty space
        for (int row = 0; row < boardSize; row++) {
          if (game_state[round].get_gameBoard(row, col) == Empty) {
            cout << "column chosen: " << col;
            // Coordinates are valid; set selectedRow and selectedColumn members
            // of game state to read values
            game_state[round].set_selectedRow(row);
            game_state[round].set_selectedColumn(col);

            if (game_state[round].get_turn() == true) {
              game_state[round].set_gameBoard(row, col, R);
            } else {
              game_state[round].set_gameBoard(row, col, Y);
            }

            game_state[round].set_moveValid(true);  // Set the move = valid to break out of while loop
            break;
          }
        }

        if (game_state[round].get_moveValid() == false) {
          cout << "Invalid column!\nEnter column to place piece: ";
          cin >> col;
        }
      }
    }
          // Call playMove
    playMove(game_state[round]);
    cout << "\n";
    // Print the GameState object, as prescribed in the handout
    for (int row = boardSize - 1; row > -1; row--) {
      for (int col = 0; col < boardSize; col++) {
        if (game_state[round].get_gameBoard(row, col) == R) {
          cout << "R";
        } else {
          if (game_state[round].get_gameBoard(row, col) == Y) {
          cout << "Y"; 
          } else {
            cout << "_";
          }
        }
      }
      cout << "\n";
    }

    // Check if a R won this round and if so handle accordingly
    if (game_state[round].get_winner() == R) {  // Red won
      game_state[round].set_gameOver(true);
      cout << "\nR won this round!\n";
      R_wins++;
      if (R_wins == 2) {
        cout << "R won the match!";
        exit(0);
      }
      round++;  // Since there is a winner, go to next round
      cout << "Game " << round+1;
    } else {
      game_state[round].set_gameOver(false);
    }
    
    if (game_state[round].get_winner() == Y) {  // Yellow won
      game_state[round].set_gameOver(true);
      cout << "\nY won this round!\n";
      Y_wins++;
      if (Y_wins == 2) {
        cout << "Y won the match!";
        exit(0);
      }
      round++;  // Since there is a winner, go to next round
      cout << "Game " << round+1;
    } else {
      game_state[round].set_gameOver(false);
    }
  }
}