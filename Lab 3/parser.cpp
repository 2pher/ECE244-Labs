//
//  parser.cpp
//  lab3
//
//  Modified by Tarek Abdelrahman on 2020-10-04.
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018-2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "Shape.h"
#include "globals.h"

// This is the shape array, to be dynamically allocated
Shape** shapesArray;

// The number of shapes in the database, to be incremented
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here
bool validCommand(string);
bool validArgType(stringstream&);
bool validArgInput(stringstream&);
bool validArgInputEnd(stringstream&);
bool validShapeName(string name);
bool duplicateName(Shape**&, int, string);
bool validNameCreateInput(Shape**&, int, string, stringstream&);
bool validNameInput(Shape**&, int, string, stringstream&);
bool validNameInputEnd(Shape**&, int, string, stringstream&);
bool validShapeType(string, stringstream&);
bool validNumber(int);
bool validValue(int, stringstream&);

void maxShapes(Shape**&, int&, stringstream&);
void createShape(Shape**&, int, int&, stringstream&);
void moveShape(Shape**&, int, stringstream&);
void rotateShape(Shape**&, int, stringstream&);
void drawShape(Shape**&, int, stringstream&);
void deleteShape(Shape**&, int, int&, stringstream&);

// Command validity
bool validCommand(string command) {
  if (command == "maxShapes" || command == "create" || command == "move" ||
      command == "rotate" || command == "draw" || command == "delete") {
    return true;
  }
  return false;
}

// Validates argument type
bool validArgType(stringstream& lineStream) {
  if (!lineStream.fail()) {
    return true;
  }
  cout << "Error: invalid argument" << endl;
  return false;
}

// Checks for too few args (all but last arg inputs)
bool validArgInput(stringstream& lineStream) {
  char spaceCheck;
  if (!lineStream.eof()) {
    while(lineStream.peek() != EOF) {
      lineStream.peek();
      if (lineStream.peek() != ' ') {
        return true;
      }
      lineStream.ignore();
    }
  }
  cout << "Error: too few arguments" << endl;
  return false;
}

// Checks for too many args (last arg input)
bool validArgInputEnd(stringstream& lineStream) {
  char spaceCheck;
  while(lineStream.peek() != EOF) {
    lineStream.get(spaceCheck);
    if (spaceCheck != ' ') {
      cout << "Error: too many arguments" << endl;
      return false;
    }
  }
  return true;
}

// Checks if name to-be-inputted matches with any keywords
bool validShapeName(string name) {
  for (int i = 0; i < NUM_KEYWORDS; i++) {
    if (name == keyWordsList[i]) {
      cout << "Error: invalid shape name" << endl;
      return false;
    }
  }
  for (int i = 0; i < NUM_TYPES; i++) {
    if (name == shapeTypesList[i]) {
      cout << "Error: invalid shape name" << endl;
      return false;
    }
  }
  return true;
}

bool validSearchName(string name) {
  if (name == "all") {
    return true;
  }
  for (int i = 0; i < NUM_KEYWORDS; i++) {
    if (name == keyWordsList[i]) {
      cout << "Error: invalid shape name" << endl;
      return false;
    }
  }
  for (int i = 0; i < NUM_TYPES; i++) {
    if (name == shapeTypesList[i]) {
      cout << "Error: invalid shape name" << endl;
      return false;
    }
  }
  return true;
}

// Checks for duplicate name in shapesArray
bool duplicateName(Shape**& shapesArray, int max_shapes, string name) {
  for (int i = 0; i < max_shapes; i++) {
    if (shapesArray[i] != nullptr && name == shapesArray[i]->getName()) {
      return true;
    }
  }
  return false;
}

// Checks for type, keyword, duplicate and too little args for name
bool validNameCreateInput(Shape**& shapesArray, int max_shapes, string name,
                          stringstream& lineStream) {
  if (validArgType(lineStream)) {
    if (validShapeName(name)) {
      if (!duplicateName(shapesArray, max_shapes, name)) {
        if (validArgInput(lineStream)) {
          return true;
        }
      } else {
        cout << "Error: shape " << name << " exists" << endl;
      }
    }
  }
  return false;
}

// Does the same ^ except we want to check for duplicate name
bool validNameInput(Shape**& shapesArray, int max_shapes, string name,
                    stringstream& lineStream) {
  if (validArgType(lineStream)) {
    if (validShapeName(name)) {
      if (duplicateName(shapesArray, max_shapes, name)) {
        if (validArgInput(lineStream)) {
          return true;
        }
      } else {
        cout << "Error: shape " << name << " not found" << endl;
      }
    }
  }
  return false;
}

// Does the same ^ but checking for too many args (last input)
bool validNameInputEnd(Shape**& shapesArray, int max_shapes, string name,
                       stringstream& lineStream) {
  if (validArgType(lineStream)) {
    if (validSearchName(name)) {
      if (duplicateName(shapesArray, max_shapes, name) || name == "all") {
        if (validArgInputEnd(lineStream)) {
          return true;
        }
      } else {
        cout << "Error: shape " << name << " not found" << endl;
      }
    }
  }
  return false;
}

// Checks if shape type is valid
bool validShapeType(string type, stringstream& lineStream) {
  if (validArgType(lineStream)) {
    for (int i = 0; i < NUM_TYPES; i++) {
      if (type == shapeTypesList[i]) {
        if (validArgInput(lineStream)) {
          return true;
        } else {
          return false;
        }
      }
    }
    cout << "Error: invalid shape type" << endl;
  }
  return false;
}

// Checks if number is >=0
bool validNumber(int value) {
  if (value >= 0) {
    return true;
  }
  cout << "Error: invalid value" << endl;
  return false;
}

// Checks for argument, value and # of arguments
bool validValue(int value, stringstream& lineStream) {
  if (validArgType(lineStream)) {
    if (validNumber(value)) {
      if (validArgInput(lineStream)) {
        return true;
      }
    }
  }
  return false;
}

// Dynamically allocate shapesArray dependent on value
void maxShapes(Shape**& shapesArray, int& max_shapes,
               stringstream& lineStream) {
  int value;
  lineStream >> value;
  if (validArgType(lineStream)) {
    if (validNumber(value)) {
      if (validArgInputEnd(lineStream)) {
        if (shapesArray != nullptr) {
          for (int i = 0; i < max_shapes; i++) {
            delete shapesArray[i];
            shapesArray[i] = nullptr;
          }
          delete[] shapesArray;
        }
        max_shapes = value;  // Set max_shapes to value
        cout << "New database: max shapes is " << value << endl;
        shapesArray = new Shape*[max_shapes];
      }
    }
  }
}

void createShape(Shape**& shapesArray, int max_shapes, int& shapeCount,
                 stringstream& lineStream) {
  string name, type;
  int loc_x, loc_y, size_x, size_y;
  lineStream >> name;
  if (validNameCreateInput(shapesArray, max_shapes, name, lineStream)) {
    lineStream >> type;
    if (validShapeType(type, lineStream)) {
      lineStream >> loc_x;
      if (validValue(loc_x, lineStream)) {
        lineStream >> loc_y;
        if (validValue(loc_y, lineStream)) {
          lineStream >> size_x;
          if (validValue(size_x, lineStream)) {
            lineStream >> size_y;
            if (validArgType(lineStream)) {
              if (validNumber(size_y)) {
                if (validArgInputEnd(lineStream)) {
                  if (type != "circle" ||
                      (type == "circle" && size_x == size_y)) {
                    bool valid = false;
                    if (shapeCount != max_shapes) {
                      for (int i = 0; i < max_shapes; i++) {
                          if (shapesArray[i] == nullptr) {
                            shapesArray[i] =
                                new Shape(name, type, loc_x, size_x, loc_y, size_y);
                            shapeCount++;
                            valid = true;
                            break;
                          }
                      }
                    }
                    if (valid) {
                      cout << "Created " << name << ": " << type << " " << loc_x
                           << " " << loc_y << " " << size_x << " " << size_y
                           << endl;
                    } else {
                      cout << "Error: shape array is full" << endl;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

void moveShape(Shape**& shapesArray, int max_shapes, stringstream& lineStream) {
  string name;
  int loc_x, loc_y;
  lineStream >> name;
  if (validNameInput(shapesArray, max_shapes, name, lineStream)) {
    lineStream >> loc_x;
    if (validValue(loc_x, lineStream)) {
      if (validNumber(loc_x)) {
        lineStream >> loc_y;
        if (validArgType(lineStream)) {
          if (validNumber(loc_y)) {
            if (validArgInputEnd(lineStream)) {
              for (int i = 0; i < max_shapes; i++) {
                if (shapesArray[i] != nullptr &&
                    shapesArray[i]->getName() == name) {
                  shapesArray[i]->setXlocation(loc_x);
                  shapesArray[i]->setYlocation(loc_y);
                  cout << "Moved " << name << " to " << loc_x << " " << loc_y
                       << endl;
                }
              }
            }
          }
        }
      }
    }
  }
}

void rotateShape(Shape**& shapesArray, int max_shapes,
                 stringstream& lineStream) {
  string name;
  int angle;
  lineStream >> name;
  if (validNameInput(shapesArray, max_shapes, name, lineStream)) {
    lineStream >> angle;
    if (validArgType(lineStream)) {
      if (angle >= 0 && angle <= 360) {
        if (validArgInputEnd(lineStream)) {
          for (int i = 0; i < max_shapes; i++) {
            if (shapesArray[i] != nullptr &&
                shapesArray[i]->getName() == name) {
              shapesArray[i]->setRotate(angle);
              cout << "Rotated " << name << " by " << angle << " degrees"
                   << endl;
            }
          }
        }
      } else {
        cout << "Error: invalid value" << endl;
      }
    }
  }
}

void drawShape(Shape**& shapesArray, int max_shapes, stringstream& lineStream) {
  string name;
  lineStream >> name;
  if (validNameInputEnd(shapesArray, max_shapes, name, lineStream)) {
    if (name == "all") {
      cout << "Drew all shapes" << endl;
      for (int i = 0; i < max_shapes; i++) {
        if (shapesArray[i] != nullptr) {
          shapesArray[i]->draw();
        }
      }
      cout << endl; 
    } else {
      bool valid = false;
      for (int i = 0; i < max_shapes; i++) {
        if (shapesArray[i] != nullptr && shapesArray[i]->getName() == name) {
          cout << "Drew";
          shapesArray[i]->draw();
          valid = true;
          break;
        }
      }
      if (valid) {
        cout << endl;
      }
    }
  }
}

void deleteShape(Shape**& shapesArray, int max_shapes, int& shapeCount,
                 stringstream& lineStream) {
  string name;
  lineStream >> name;
  if (validNameInputEnd(shapesArray, max_shapes, name, lineStream)) {
    if (name == "all") {
      for (int i = 0; i < max_shapes; i++) {
        if (shapesArray[i] != nullptr) {
          delete shapesArray[i];
          shapesArray[i] = nullptr;
        }
      }
      shapeCount = 0;
      cout << "Deleted: all shapes" << endl;
    } else {
      for (int i = 0; i < max_shapes; i++) {
        if (shapesArray[i] != nullptr && shapesArray[i]->getName() == name) {
          delete shapesArray[i];
          shapesArray[i] = nullptr;
          cout << "Deleted shape " << name << endl;
        }
      }
    }
  }
}

int main() {
  string line;
  string command;

  cout << "> ";        // Prompt for input
  getline(cin, line);  // Get a line from standard input

  while (!cin.eof()) {
    // Put the line in a linestream for parsing
    // Making a new sstream for each line so flags etc. are cleared
    stringstream lineStream(line);

    // Read from string stream into the command
    // The only way this can fail is if the eof is encountered
    lineStream >> command;

    // Check for the command and act accordingly
    // ECE244 Student: Insert your code here
    if (validCommand(command)) {
      if (validArgType(lineStream)) {
        if(validArgInput(lineStream)) {
          if (command == "maxShapes") {
            maxShapes(shapesArray, max_shapes, lineStream);
          } else if (command == "create") {
            createShape(shapesArray, max_shapes, shapeCount, lineStream);
          } else if (command == "move") {
            moveShape(shapesArray, max_shapes, lineStream);
          } else if (command == "rotate") {
            rotateShape(shapesArray, max_shapes, lineStream);
          } else if (command == "draw") {
            drawShape(shapesArray, max_shapes, lineStream);
          } else {
            deleteShape(shapesArray, max_shapes, shapeCount, lineStream);
          }
        }
      }
    } else {
      cout << "Error: invalid command" << endl;
    }

    // Once the command has been processed, prompt for the
    // next command
    cout << "> ";  // Prompt for input
    getline(cin, line);

  }  // End input loop until EOF.

  return 0;
}
