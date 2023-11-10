#include "QueueList.h"

#include "Customer.h"

QueueList::QueueList() { head = nullptr; }

QueueList::QueueList(Customer* customer) { head = customer; }

QueueList::~QueueList() {
  
}

Customer* QueueList::get_head() { return head; }

void QueueList::enqueue(Customer* customer) {
  // a customer is placed at the end of the queue
  // if the queue is empty, the customer becomes the head
  customer->set_next(nullptr);
  // If list is empty, set newCustomer to queue head
  if (head == nullptr) {
    head = customer;
  } else {
    // Traverse to the end of queue list then insert customer
    Customer* temp = head;
    while(temp->get_next() != nullptr) {
      temp = temp->get_next();
    }
    temp->set_next(customer);
  }  
}

Customer* QueueList::dequeue() {
  // remove a customer from the head of the queue 
  // and return a pointer to it
  // If list is empty, can't dequeue anything
  if (head == nullptr) {
    return nullptr;
  } else {
    // Set head to head->next, return old head
    Customer* dequeuedCustomer = head;
    head = head->get_next();
    return dequeuedCustomer;
  }
  
}

int QueueList::get_items() {
  int totalItems = 0;
   Customer* customer = head;
   if (customer == nullptr) {
    return totalItems;
   } else {
    while (customer != nullptr) {
      // Loop through linked list and add total number of items
      totalItems += customer->get_numOfItems();
      customer = customer->get_next();
    }
    return totalItems;
   }
}

bool QueueList::empty_queue() {
  // if the queue is empty, return false
  // if the queue is not empty, delete all customers
  // and return true
  if (head == nullptr) {
    return false;
  } else {
    // Loop through list and delete each customer
    while (head != nullptr) {
      Customer* temp = head->get_next();
      delete head;
      head = temp;
    }
    return true;
  }
}

void QueueList::print() {
  // print customers in a queue
  Customer* temp = head;
  while (temp != nullptr) {
    temp->print();
    temp = temp->get_next();
  }
}
