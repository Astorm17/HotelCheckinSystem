/*
* Room.h
* A header file for the Room class. A room consists of it's room ID and the
* number of beds it has in the room.
* June 17th, 2018
* Alex Testani
*/

#ifndef ROOM_H
#define ROOM_H

class Room {
public:
  Room();
  Room(std::string id, int beds);
  Room(const Room &room);
  ~Room();
  std::string getRoom();
  int getBeds();
private:
  std::string roomId;
  int numberOfBeds;
  static int numOfObjects;
};

int Room::numOfObjects = 0;


//default constructor
Room::Room() {
  roomId = "";
  numberOfBeds = 0;
  numOfObjects++;
}

//constructor
Room::Room(std::string id, int beds) {
  roomId = id;
  numberOfBeds = beds;
  numOfObjects++;
}

//copy constructor
Room::Room(const Room &room) {
  roomId = room.roomId;
  numberOfBeds = room.numberOfBeds;
  numOfObjects++;
}

//destructor
Room::~Room() {
  numOfObjects--;
}

//returns the room ID
std::string Room::getRoom() {
  return roomId;
}

//returns the size of the room
int Room::getBeds() {
  return numberOfBeds;
}

#endif
