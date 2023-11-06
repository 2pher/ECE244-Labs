
// Created by Salma Emara on 2023-06-02.
#include "Register.h"
#include <iostream>

using namespace std;

Register::Register(int id, double timePerItem, double overhead,
                   double entryTime) {
  ID = id;
  secPerItem = timePerItem;
  overheadPerCustomer = overhead;
  availableTime = entryTime;
  next = nullptr;           // no other registers yet
  queue = new QueueList();  // no customers in line yet, but has to initialize a
                            // queue
}

Register::~Register() { }

QueueList* Register::get_queue_list() { return head; }

Register* Register::get_next() { return next; }

int Register::get_ID() { return ID; }

double Register::get_secPerItem() { return secPerItem; }

double Register::get_overheadPerCustomer() { return overheadPerCustomer; }

double Register::get_availableTime() { return availableTime; }

void Register::set_next(Register* nextRegister) { next = nextRegister; }


void Register::set_availableTime(double availableSince) {
  availableTime = availableSince;
}

double Register::calculateDepartTime() {
  // Get the departure time of the first customer in the queue
  // returns -1 if no customer is in the queue
  if (queue == nullptr) {
    return -1;
  } else {
    double departTime = get_secPerItem() * queue->get_items();
    return departTime;
  }
}

void Register::departCustomer(QueueList* doneList) {
  // dequeue the head, set last dequeue time, add to doneList,
  // update availableTime of the register
  
  
}

void Register::print() {
  cout << "Register ID: " << ID << endl;
  cout << "Time per item: " << secPerItem << endl;
  cout << "Overhead per customer: " << overheadPerCustomer << endl;
  if (queue->get_head() != nullptr) {
    cout << "Queue has customers: \n";
    queue->print();
  }
}
