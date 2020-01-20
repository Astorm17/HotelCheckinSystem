/*
* HotelSystem.cpp
* A program that acts as a hotel system which takes a list of customers, stores their data
* in a vector and provides the customer a hotel room based on their requested bed amount.
* This program makes use of the Hotel class which uses a linked list to store customers that
* are currently staying at the hotel.
* June 17th, 2018
* Alex Testani
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Hotel.h"
#include "Customer.h"

using namespace std;

//a function thats used to tokenize a string and returns the tokens inside a vector<string>
vector<string> tokenizer(string str, char delim) {
  vector<string> tokens;
  string token;
  istringstream stream(str);

  while(getline(stream, token, delim))
    tokens.push_back(token);

  return tokens;
}

//a function that calculates the customers checkout date based on the duration of their stay and their check in date
string getCheckout(const string checkIn, string duration) {
  vector<string> date = tokenizer(checkIn, '/');

  int daysStayed = stoi(duration); // convert duration into int
  int day = stoi(date[0]); //check in day
  int month = stoi(date[1]); //check in month
  int year = stoi(date[2]); //check in year


  int months[] = {31, 28, 31, 30, 31, 30 ,31, 31, 30, 31, 30, 31}; // all the months starting with jan

  int k = 0;
  int newDay, newMonth;
  string checkOut = "";

  for(int i = 0; i < month; i++) //calculates the the total days of the current month from the beginning of year
    k += months[i];

  k += daysStayed + day; //add the current day of the month + the duration the customer will be staying
  if(k <= 365) { //if customers duration doesn't go on to the next year
    for(int i = 0; i < 12; i++) { //go through the months from beginning of year
      newDay = k - months[i]; //subtract from total
      if(newDay <= months[i+1]) { //check to see if the customer stayed til the next month
        newMonth = i + 1; //move the checkout to the next month
        break;
      }
      else
        k = newDay;
    }
    checkOut = to_string(newDay) + "/" + to_string(newMonth) + "/" + to_string(year); //set checkout date
  }
  else { //do the same as above, but increment the year at the end
    k -= 365;
    for(int i = 0; i < 12; i++) {
      newDay = k - months[i];
      if(newDay <= months[i+1]) {
        newMonth = i + 1;
        break;
      }
      else
        k = newDay;
    }
    checkOut = checkOut = to_string(newDay) + "/" + to_string(newMonth) + "/" + to_string(year + 1);
  }

  return checkOut;
}

//a function that takes the hotel log file and creates a vector of customers with their information
vector<Customer> initialize() {
  vector<string> customers; //stores the lines from the text file
  vector<Customer> customerList; //creates a list of customers with information
  string info; //the line containing customer information
  ifstream infile;
  infile.open("test.txt");

  while(!infile.eof()) { //fills customerInfo with unformatted string
    getline(infile, info);
    info.erase(std::remove(info.begin(), info.end(), ' '), info.end()); //remove whitespace
    customers.push_back(info);
  }
  infile.close();

  vector<string> customerInfo; // stores the information from the lines formatted
  for(string str : customers) {
    istringstream stream(str);

    while(getline(stream, info, ','))
      customerInfo.push_back(info);


    customerInfo[3] = getCheckout(customerInfo[0], customerInfo[3]); //convert duration into checkout date
    Customer c(customerInfo[0], customerInfo[1], stoi(customerInfo[2]), customerInfo[3]);
    customerList.push_back(c);
    customerInfo.clear();
  }

  return customerList;
}

int main() {
  int maxBeds;
  cout << "Please enter the maximum size of beds for the hotel: ";
  cin >> maxBeds;
  vector<Hotel*> hotelSystem;

  int numOfRooms;
  for(int i = 0; i < maxBeds; i++) {
    cout << "Enter the number of " << i + 1 << " bed bedrooms: ";
    cin >> numOfRooms;
    hotelSystem.push_back(new Hotel(numOfRooms, i+1));
  }

  vector<Customer> customerList = initialize();

  ofstream out;
  out.open("log.txt");
  bool available = false;
  for(Customer c : customerList) {
    for(int i = c.getRequestedBeds() - 1; i < maxBeds; i++) { //check available rooms, starting with requested room size
      if(hotelSystem[i]->isAvailable()) { //if its available, assign to customer and break
        hotelSystem[i]->assignRoom(c);
        out << "Customer " << c.getId() << " that wanted " << c.getRequestedBeds();
        out << " bed(s) has been assigned to a room with " << i+1 << " bed(s)" << endl;
        available = true;
        break;
      }
      available = false;
    }

    if(!available && (c.getRequestedBeds() - 1 < maxBeds)) { //if no rooms were available notify customer
      out << "Customer " << c.getId() << ", unfortunately all rooms are booked. ";
      out << "The earliest available room with " << c.getRequestedBeds() << " bed(s) ";
      out << "will be available " << hotelSystem[c.getRequestedBeds() - 1]->getEarliestDate() << ". ";
      out << "We are sorry for the inconvenience." << endl;
    } //if end
  }//for end
  out.close();
}
