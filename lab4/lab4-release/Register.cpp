
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
  double departTime = -1;
  if (queue != nullptr) {
    // Customer has already been in line by time register becomes available; add reg available time
    if (queue->get_head()->get_arrivalTime() <= availableTime) {
      departTime = (secPerItem * queue->get_head()->get_numOfItems()) + overheadPerCustomer + availableTime;
    } else {
      // Customer arrives AFTER register becomes available; add arrival time instead
      departTime = (secPerItem * queue->get_head()->get_numOfItems()) + overheadPerCustomer + queue->get_head()->get_arrivalTime();
    }
  }
  return departTime;
}

void Register::departCustomer(QueueList* doneList) {
  // dequeue the head, set last dequeue time, add to doneList,
  // update availableTime of the register
  if (queue != nullptr) {
    // Calculate depart time of customer
    double departTime = calculateDepartTime();
    // Set departure time of customer
    queue->get_head()->set_departureTime(departTime);
    // Dequeue customer
    QueueList* dequeuedCustomer = queue->dequeue();
    // Enqueue the dequeued customer to done list
    doneList->enqueue(dequeuedCustomer);
    // Set the register's available time to time which customer was dequeued
    availableTime = departTime;
    return;
  }
  doneList->enqueue(nullptr);
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
