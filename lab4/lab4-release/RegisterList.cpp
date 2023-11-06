#include "RegisterList.h"

#include <iostream>

#include "Register.h"
using namespace std;

RegisterList::RegisterList() {
  head = nullptr;
  size = 0;
}

RegisterList::~RegisterList() {
  // Delete all registers in the list
  if (head != nullptr) {
    while (head != nullptr) {
      Register* temp = head;
      head = head->get_next();
      delete temp;
    }
  }
}

Register* RegisterList::get_head() { return head; }

int RegisterList::get_size() { 
  // return number of registers
  int num = 0
  if (head == nullptr) {
    return num;
  } else {
    Register* temp = head;
    while (temp != nullptr) {
      num ++;
      temp = temp->get_next();
    }
    return num;
  }
}


Register* RegisterList::get_min_items_register() {
  // loop all registers to find the register with least number of items
  if (head == nullptr) {
    return nullptr;
  } else {
    // Create two temporary Register* classes to compare item values
    Register* leastItemReg = head;
    Register* temp = head->get_next();
    // Access items in queue
    int leastItems = head->get_queue_list()->get_items();
    while (temp != nullptr) {
      if (temp->get_queue_list()->get_items() < leastItems) {
        leastItems = temp->get_queue_list()->get_items();
        leastItemReg = temp;
      }
      temp = temp->get_next();
    }
    return leastItemReg;
  }
}

Register* RegisterList::get_free_register() {
  // return the register with no customers
  // if all registers are occupied, return nullptr
}

void RegisterList::enqueue(Register* newRegister) {
  // a register is placed at the end of the queue
  // if the register's list is empty, the register becomes the head
  // Assume the next of the newRegister is set to null
  // You will have to increment size 
  
}

bool RegisterList::foundRegister(int ID) {
  // look for a register with the given ID
  // return true if found, false otherwise

}

Register* RegisterList::dequeue(int ID) {
  // dequeue the register with given ID

  // return the dequeued register
  // return nullptr if register was not found
}

Register* RegisterList::calculateMinDepartTimeRegister(double expTimeElapsed) {
  // return the register with minimum time of departure of its customer
  // if all registers are free, return nullptr
}

void RegisterList::print() {
  Register* temp = head;
  while (temp != nullptr) {
    temp->print();
    temp = temp->get_next();
  }
}
