/*
* Hotel.h
* A header file for the Hotel class. The hotel class is used to store
* the customers staying at the hotel inside a linked list. Each customer is assigned
* to a room with a unique ID. The hotel class also provides the earliest date a customer
* can check in, and if the hotel has rooms available for booking.
* June 17th, 2018
* Alex Testani
*/

#ifndef HOTEL_H
#define HOTEL_H

#include "Customer.h"
#include "LinkedList.h"

class Hotel {
public:
  Hotel();
  Hotel(int rooms, int size);
  ~Hotel();
  void assignRoom(Customer c);
  bool isAvailable();
  std::string getEarliestDate();
private:
  LinkedList<Customer> customers;
  int maxRooms;
  int roomSize;
  int currentCapacity;
  std::string earliestDate;
  void compareDates(std::string checkOut);
  std::vector<std::string> tokenizer(std::string str, char delim);
  int roomNumber;
};

//default constructor
Hotel::Hotel() {
  maxRooms = 0;
  roomSize = 0;
  currentCapacity = 0;
  roomNumber = 0;
  earliestDate = "";
}

//constructor
Hotel::Hotel(int rooms, int size) {
  maxRooms = rooms;
  roomSize = size;
  currentCapacity = 0;
  roomNumber = 0;
  earliestDate = "";
}

//destructor
Hotel::~Hotel() {
  customers.clear();
}

//assigns a room to a customer
void Hotel::assignRoom(Customer c) {
  //Room:roomSize:roomNumber
  Room room("Room:" + std::to_string(roomSize) + ":" + std::to_string(roomNumber), roomSize); //customers room
  c.setRoom(room); //set the room
  customers.add(c); //insert into list "hotel database"

  if(currentCapacity > 0)
    compareDates(c.getCheckout());
  else
    earliestDate = c.getCheckout();

  currentCapacity++; //keeps track of how many rooms are booked
  roomNumber++; //unique room number
}

bool Hotel::isAvailable() {
  return currentCapacity < maxRooms; //checks if there are any available rooms
}

std::string Hotel::getEarliestDate() {
  return earliestDate; //returns the earliest date available to book a room
}

//Compares the current earliest available room date with the current hotel room being booked
void Hotel::compareDates(std::string checkOut) {
  std::vector<std::string> date1 = tokenizer(earliestDate, '/');
  std::vector<std::string> date2 = tokenizer(checkOut, '/');

  if(stoi(date1[1]) > stoi(date2[1])) //if current month is greater change
    earliestDate = checkOut;
  else if(stoi(date1[0]) > stoi(date2[0])) //if current day is greater change
    earliestDate = checkOut;
}

//a function used to split a string into tokens then returns the tokens inside a vector
std::vector<std::string> Hotel::tokenizer(std::string str, char delim) {
  std::vector<std::string> tokens;
  std::string token;
  std::stringstream stream(str);

  while(getline(stream, token, delim))
    tokens.push_back(token);

  return tokens;
}

#endif
