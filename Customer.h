/*
* Customer.h
* A header file for the Customer class. A customer consists of its
* check in date, check out date, the number of beds the customer would like
* a unique ID to the customer, and the room it is staying in.
* June 17th, 2018
* Alex Testani
*/

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Room.h"

class Customer {
public:
  Customer();
  Customer(std::string checkIn, std::string id, int beds, std::string checkOut);
  ~Customer();
  void setRoom(Room &newRoom);
  int getRequestedBeds();
  std::string getId();
  std::string getRoomId();
  std::string getCheckout();
private:
  std::string customerId;
  int numOfRequestedBeds;
  std::string checkIn;
  std::string checkOut;
  Room room;
  static int numOfObjects;
};

int Customer::numOfObjects = 0; //keeps track of objects

//Default constructor
Customer::Customer() {
  std::string customerId = "";
  int numOfRequestedBeds = 0;
  std::string checkIn = "";
  std::string checkOut = "";
  numOfObjects++;
}

//constructor
Customer::Customer(std::string in, std::string id, int beds, std::string out) {
  checkIn = in;
  customerId = id;
  numOfRequestedBeds = beds;
  checkOut = out;
  numOfObjects++;
}

//destructor
Customer::~Customer() {
  numOfObjects--;
}

//sets the customers room to the newly assigned room
void Customer::setRoom(Room &newRoom) {
  room = newRoom;
}

//returns the customers room size of choice
int Customer::getRequestedBeds() {
  return numOfRequestedBeds;
}

//returns the customers unique ID
std::string Customer::getId() {
  return customerId;
}

//returns the room ID the customer is currently staying in
std::string Customer::getRoomId() {
  std::cout << room.getRoom() << std::endl;
  return room.getRoom();
}

//returns the customers checkout date
std::string Customer::getCheckout() {
  return checkOut;
}

#endif
