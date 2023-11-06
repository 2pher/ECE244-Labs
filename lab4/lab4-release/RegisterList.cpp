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
  Register* reg = head;
  while (reg != nullptr) {
    Register* temp = reg;
    reg = reg->get_next();
    delete temp;
  }
}

Register* RegisterList::get_head() { return head; }

int RegisterList::get_size() { 
  // return number of registers
  int num = 0
  if (head == nullptr) {
    return num;
  } else {
    RegisterList* temp = head;
    while (temp != nullptr) {
      num++;
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
    leastItemReg->set_next(nullptr);
    return leastItemReg;
  }
}

Register* RegisterList::get_free_register() {
  // return the register with no customers
  // if all registers are occupied, return nullptr
  Register* freeReg = head;
  while (freeReg != nullptr) {
    if (freeReg->get_queue_list()->get_head() == nullptr) {
      freeReg->set_next(nullptr);
      return freeReg;
    }
    freeReg = freeReg->get_next();
  }
  return nullptr;
}

void RegisterList::enqueue(Register* newRegister) {
  // a register is placed at the end of the queue
  // if the register's list is empty, the register becomes the head
  // Assume the next of the newRegister is set to null
  // You will have to increment size 
  if (head == nullptr) {
    head = newRegister;
  } else {
    Register* temp = head;
    while (temp->get_next() != nullptr) {
      temp = temp->get_next();
    }
    temp->set_next(newRegister);
  }
  size++;
}

bool RegisterList::foundRegister(int ID) {
  // look for a register with the given ID
  // return true if found, false otherwise
  if (head == nullptr) {
    return false;
  } else {
    Register* temp = head;
    while(temp != nullptr) {
      if (temp->get_ID() == ID) {
        return true;
      }
      temp = temp->get_next();
    }
  }
}

Register* RegisterList::dequeue(int ID) {
  // dequeue the register with given ID
  // return the dequeued register
  // return nullptr if register was not found
  if (head == nullptr) {
    return nullptr;
  } else {
    Register* temp = nullptr;
    Register* dequeuedReg = head;
    while (dequeuedReg != nullptr) {
      if (dequeuedReg->get_ID() == ID) {
        // Check if temp == nullptr, meaning if head is matching ID
        if (temp != nullptr) {
          // temp reg skips over the dequeued reg to the next reg in list
          temp->set_next(dequeuedReg->get_next());
        } else {
          // ID matches head, set new head to next and remove current head
          set_head(dequeuedReg->get_next());
        }
        // Isolate dequeuedReg by setting next to nullptr
        dequeuedReg->set_next(nullptr);
        return dequeuedReg;
      }
      // temp will be one place behind dequeuedReg in register list
      temp = dequeuedReg;
      dequeuedReg = dequeuedReg->get_next();
    }
    return nullptr; // No register found; return nullptr
  }
}

Register* RegisterList::calculateMinDepartTimeRegister(double expTimeElapsed) {
  // return the register with minimum time of departure of its customer
  // if all registers are free, return nullptr
  if (head == nullptr) {
    return nullptr;
  } else {
    Register* minDepartTimeReg = head;
    Register* temp = head;
    double minDepartTime = temp->calculateDepartTime();
    while (temp != nullptr) {
      if (temp->calculateDepartTime() < minDepartTime) {
        minDepartTime = temp->calculateDepartTime();
        minDepartTimeReg = temp;
      }
      temp = temp->get_next();
    }
    minDepartTimeReg->set_next(nullptr);
    return minDepartTimeReg;
  }
}

void RegisterList::print() {
  Register* temp = head;
  while (temp != nullptr) {
    temp->print();
    temp = temp->get_next();
  }
}
