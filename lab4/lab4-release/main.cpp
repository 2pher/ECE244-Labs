#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>

#include "Customer.h"
#include "QueueList.h"
#include "Register.h"
#include "RegisterList.h"

using namespace std;

// Function Declarations:
void systemUpdate(string);
void queueSingleCustomers();
void printStatistics();

// Set mode of the simulation
string getMode();

// Register
void parseRegisterAction(stringstream &lineStream, string mode);
void openRegister(
    stringstream &lineStream,
    string mode);  // register opens (it is upto customers to join)
void closeRegister(stringstream &lineStream,
                   string mode);  // register closes 

// Customer
void addCustomer(stringstream &lineStream,
                 string mode);  // customer wants to join


// Helper functions
bool getInt(stringstream &lineStream, int &iValue);
bool getDouble(stringstream &lineStream, double &dValue);
bool foundMoreArgs(stringstream &lineStream);

// Global variables
RegisterList *registerList; // holding the list of registers
QueueList *doneList; // holding the list of customers served
QueueList *singleQueue; // holding customers in a single virtual queue
double expTimeElapsed; // time elapsed since the beginning of the simulation

// List of commands:
// To open a register
// register open <ID> <secPerItem> <setupTime> <timeElapsed>
// To close register
// register close <ID> <timeElapsed>
// To add a customer
// customer <items> <timeElapsed>

int main() {
  registerList = new RegisterList();
  doneList = new QueueList();
  singleQueue = new QueueList();
  expTimeElapsed = 0;

  // Set mode by the user
  string mode = getMode();

  string line;
  string command;

  cout << "> ";  // Prompt for input
  getline(cin, line);

  while (!cin.eof()) {
    stringstream lineStream(line);
    lineStream >> command;
    if (command == "register") {
      parseRegisterAction(lineStream, mode);
    } else if (command == "customer") {
      addCustomer(lineStream, mode);
    } else {
      cout << "Invalid operation" << endl;
    }
    cout << "> ";  // Prompt for input
    getline(cin, line);
  }

  printStatistics();
  // You have to make sure all dynamically allocated memory is freed 
  // before return 0
  return 0;
}

string getMode() {
  string mode;
  cout << "Welcome to ECE 244 Grocery Store Queue Simulation!" << endl;
  cout << "Enter \"single\" if you want to simulate a single queue or "
          "\"multiple\" to "
          "simulate multiple queues: \n> ";
  getline(cin, mode);

  if (mode == "single") {
    cout << "Simulating a single queue ..." << endl;
  } else if (mode == "multiple") {
    cout << "Simulating multiple queues ..." << endl;
  }

  return mode;
}

void addCustomer(stringstream &lineStream, string mode) {
  int items;
  double timeElapsed;
  if (!getInt(lineStream, items) || !getDouble(lineStream, timeElapsed)) {
    cout << "Error: too few arguments." << endl;
    return;
  }
  if (foundMoreArgs(lineStream)) {
    cout << "Error: too many arguments." << endl;
    return;
  }
  // Depending on the mode of the simulation (single or multiple),
  // add the customer to the single queue or to the register with
  // fewest
  expTimeElapsed += timeElapsed;
  Customer* customer = new Customer(expTimeElapsed, items);
  systemUpdate(mode); // Check for any customer departures BEFORE adding a customer
  cout << "A customer entered" << endl; // Default line for all customer entries
 
  // If mode == single, put into single queue
  if (mode == "single") {
    // Queue customer in single queue
    singleQueue->enqueue(customer);
    queueSingleCustomers();
  }
  
  // If mode == multiple, find reg with least items and place into its reg queue
  if (mode == "multiple") {
    // Identify the register with the fewest items
    Register* minItemsReg = registerList->get_min_items_register();
    // Queue customer in register queue
    minItemsReg->get_queue_list()->enqueue(customer);
    cout << "Queued a customer with quickest register" << minItemsReg->get_ID() << endl;
  }
}

void parseRegisterAction(stringstream &lineStream, string mode) {
  string operation;
  lineStream >> operation;
  if (operation == "open") {
    openRegister(lineStream, mode);
  } else if (operation == "close") {
    closeRegister(lineStream, mode);
  } else {
    cout << "Invalid operation" << endl;
  }
}

void openRegister(stringstream &lineStream, string mode) {
  int ID;
  double secPerItem, setupTime, timeElapsed;
  // convert strings to int and double
  if (!getInt(lineStream, ID) || !getDouble(lineStream, secPerItem) ||
      !getDouble(lineStream, setupTime) ||
      !getDouble(lineStream, timeElapsed)) {
    cout << "Error: too few arguments." << endl;
    return;
  }
  if (foundMoreArgs(lineStream)) {
    cout << "Error: too many arguments" << endl;
    return;
  }

  // Check if the register is already open
  // If it's open, print an error message
  // Otherwise, open the register
  // If we were simulating a single queue, 
  // and there were customers in line, then 
  // assign a customer to the new register
  if (!registerList->foundRegister(ID)) {
    expTimeElapsed += timeElapsed;
    Register* newRegister = new Register(ID, secPerItem, setupTime, expTimeElapsed);
    registerList->enqueue(newRegister);
    cout << "Opened register " << ID << endl;
    if (mode == "single") {
      // Add customers to new register if in single queue
      queueSingleCustomers();
    }

  } else {
    // Register ID already exists. Print error message.    
    cout << "Error: register " << ID << " is already open." << endl;
  }
}

void closeRegister(stringstream &lineStream, string mode) {
  int ID;
  double timeElapsed;
  // convert string to int
  if (!getInt(lineStream, ID) || !getDouble(lineStream, timeElapsed)) {
    cout << "Error: too few arguments." << endl;
    return;
  }
  if (foundMoreArgs(lineStream)) {
    cout << "Error: too many arguments" << endl;
    return;
  }
  // Check if the register is open
  // If it is open dequeue it and free it's memory
  // Otherwise, print an error message 
  if (registerList->foundRegister(ID)) {
    expTimeElapsed += timeElapsed;
    systemUpdate(mode);
    Register* dequeuedRegister = registerList->dequeue(ID);
    delete dequeuedRegister;
    cout << "Closed register " << ID << endl;
  } else {
    cout << "Error: register " << ID << " is not open" << endl;
  }
}

bool getInt(stringstream &lineStream, int &iValue) {
  // Reads an int from the command line
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  }
  iValue = stoi(command);
  return true;
}

bool getDouble(stringstream &lineStream, double &dvalue) {
  // Reads a double from the command line
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  }
  dvalue = stod(command);
  return true;
}

bool foundMoreArgs(stringstream &lineStream) {
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  } else {
    return true;
  }
}
 
void systemUpdate(string mode) {
  Register* temp = registerList->calculateMinDepartTimeRegister(expTimeElapsed);
  Register* prev = nullptr;
  // We need to add departures of customer to done list in timely order
  while (temp != nullptr && temp->get_queue_list()->get_head() != nullptr) {
    double departTime = temp->calculateDepartTime();
    if (departTime <= expTimeElapsed) {
      temp->departCustomer(doneList);
      cout << "Departed a customer at register ID " << temp->get_ID() << " at " << departTime << endl;

      if (mode == "single") {
      // For single queue, we need to add head of single queue list to head of free register queue
        queueSingleCustomers();
      }
    }
    if (temp == prev) {
      // Break to avoid infinte loop
      break;
    }

    prev = temp;
    temp = registerList->calculateMinDepartTimeRegister(expTimeElapsed);
  }
}

void queueSingleCustomers() {
  if (singleQueue->get_head() != nullptr) {
    if (registerList->get_free_register() != nullptr) {
      cout << "Queued a customer with free register " << registerList->get_free_register()->get_ID() << endl;
      // Send single queue's head to the head of free reg's queue; dequeue head of single queue
      registerList->get_free_register()->get_queue_list()->enqueue(singleQueue->dequeue());
    } else {
      // Customer is not head of single queue, there are no free regs available
      cout << "No free registers" << endl;
    }
  }
}

void printStatistics() {
  Customer* temp = doneList->get_head();
  Customer* temp2 = doneList->get_head();
  double waitTime = 0, maxWaitTime = 0, avgWaitTime = 0, stdDevWaitTime = 0, sumWaitTime = 0, waitAvgTimeDifference = 0;
  int customers = 0;

  while (temp != nullptr) {
    customers++;
    waitTime = (temp->get_departureTime() - temp->get_arrivalTime());
    sumWaitTime += waitTime;
    if (waitTime > maxWaitTime) {
      maxWaitTime = waitTime;
    }
    temp = temp->get_next();
  }

  if (doneList->get_head() != nullptr) {
    avgWaitTime = sumWaitTime/customers;
  }

  while (temp2 != nullptr) {
    waitAvgTimeDifference += pow(((temp2->get_departureTime()-temp2->get_arrivalTime()) - avgWaitTime), 2);
    temp2 = temp2->get_next();
  }

  if (doneList->get_head() != nullptr) {
    stdDevWaitTime = sqrt((waitAvgTimeDifference)/customers);
  }

  cout << "Finished at time " << expTimeElapsed << endl << 
          "Statistics:" << endl << 
          "Maximum wait time: " << maxWaitTime << endl << 
          "Average wait time: " << avgWaitTime << endl << 
          "Standard Deviation of wait time: " << stdDevWaitTime << endl;
}
