//
//  GameState.cpp
//  Connect Four Game
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Modified by Tarek Abdelrahman on 2020-09-17.
//  Modified by Salma Emara and Ethan Hugh on 2023-09-06.
//  Copyright © 2019-2020 Tarek Abdelrahman. All rights reserved.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//

#include "GameState.h"

#include "globals.h"

// ECE244 Student: add your code below

GameState::GameState() {
  // Initialize constructor
  selectedRow = 0;
  selectedColumn = 0;
  moveValid = true;
  gameOver = false;
  turn = true;
  winner = Empty;
  
  for (int row = 0; row < boardSize; row++) {
    for (int col = 0; col < boardSize; col++) {
        gameBoard[row][col] = Empty;
    }
  }
}

int GameState::get_selectedRow() {
    return selectedRow;
}

int GameState::get_selectedColumn() {
    return selectedColumn;
}

void GameState::set_selectedRow(int value) {
    if (value <= boardSize-1 && value >= 0) {
        selectedRow = value;
    }
    return;    
}

void GameState::set_selectedColumn(int value) {
    if (value <= boardSize-1 && value >= 0) {
        selectedColumn = value;
    }
    return;
}

bool GameState::get_moveValid() {
    return moveValid;
}

void GameState::set_moveValid(bool value) {
    moveValid = value;
}

bool GameState::get_gameOver() {
    return gameOver;
}

void GameState::set_gameOver(bool value) {
    gameOver = value;
}

bool GameState::get_turn() {
    return turn;
}

void GameState::set_turn(bool value) {
    turn = value;
}

int GameState::get_winner() {
    return winner;
}

void GameState::set_winner(int value) {
    winner = value;
}

int GameState::get_gameBoard(int row, int col) {
    if (row <= boardSize-1 && row >= 0 && col <= boardSize-1 && col >= 0) {
        int value = gameBoard[row][col];
        return value;
    }
    return Empty;
}

void GameState::set_gameBoard(int row, int col, int value) {
    if (row <= boardSize-1 && row >= 0 && col <= boardSize-1 && col >= 0) {
        gameBoard[row][col] = value;
    }
    return;
}
