#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <optional>
using namespace std;

bool intIsValid(string input) {
  if (input.empty() || input[0] == '-') {
      return false;
  }

  for (char c : input) {
    if (!isdigit(c)) {
      return false;
    }
  }

  int num = stoi(input);
  return num > 0;
}

bool doubleIsValid(string input) {
  if (input.empty() || input[0] == '-') {
    return false;
  }

  bool hasDecPt = false;
  for (char c : input) {
    if (c == '.') {
      hasDecPt = true;
    }

    if ((!isdigit(c) && c != '.') || (c == '.' && hasDecPt)) {
      return false;
    }
  }

  double num = stod(input);
  return stod > 0.0;
}

//Class User
class User {
  protected: 
    string name, email, password;

  //Constructor
  public:
    User(string name, string email, string password) : name(name), email(email), password(password) {}

    //Getters
    string getName() const{
      return name;
    }

    string getEmail() const{
      return email;
    }
    
    //Setters
    void setName(string name) {
      this -> name = name;
    }

    void setEmail(string email) {
      this -> email = email;
    }
};

class Customer : public User {
  private:
    vector<Booking> bookingHistory;
    
}

//Class Room
class Room {
  private:
    int roomNo;
    string roomType;
    double price;
    bool isAvailable;

  public:
    // constructor
    Room(int roomNo, string roomType, double price) : roomNo(roomNo), roomType(roomType), price(price), isAvailable(true) {}

    //getter
    int getRoomNo() {
      return roomNo;
    }

    string getRoomType() {
      return roomType;
    }

    double getRoomPrice() {
      return price;
    }

    bool roomIsAvailable() {
      return isAvailable;
    }

    //setter
    void setRoomNo(int roomNo) {
      this -> roomNo = roomNo;
    }

    void setRoomType(string roomType) {
      this -> roomType = roomType;
    }

    void setRoomPrice(double roomPrice) {
      this -> price = roomPrice;
    }

    void setIsAvailable(bool isAvailable) {
      this -> isAvailable = isAvailable;
    }
};

class ParkInnLodge {
  private:
    vector(User) users;
    vector(Room) rooms;

  public:
    // construir los objetos
    void createAccount(string name, string email, string password) : User(name, email, password) {}
    void addRoom(int roomNo, string roomType, double price) : Room(roomNo, roomType, price) {}

    void editRoom() {
      int roomNo;
      int choice;
      cout << "Enter room number of the room to edit: ";
      getline(cin, roomNo);
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      // initialize the variables needed to search for the room
      bool found = false;
      optional<Room> foundRoom;

      for (const auto& room: rooms) {
        if (room.getRoomNo() == roomNo) {
          found = true;
          foundRoom = room;
          break;
        }
      }
      if (found) {
        cout << left;
        cout << setw(15) << "NUMBER" << setw(20) << "TYPE" << setw(10) << "PRICE" << setw(15) "AVAILABLE?" << setw(15) << endl;
        cout << "-----------------------------------------------------------------------------------" << endl;
        cout << setw(15) << foundRoom.getRoomNo() << setw(20) << foundRoom.getRoomType() << setw(10) << foundRoom.getRoomPrice() << setw(15) << foundRoom.roomIsAvailable() << setw(15) << endl;
        int editChoice;
        cout << "\nEdit Room:" << endl;
        cout << "[1] Number" << endl;
        cout << "[2] Type" << endl;
        cout << "[3] Price" << endl;
        cout << "[4] Availability" << endl;
        cout << "[0] Return to Home" << endl;
        cout << "INPUT: " << endl;
        getline(cin, editChoice);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (editChoice) {
          case 0:
            // return to home
            return;
          case 1:
            // edit room no
            int newRoomNo;
            do {
              cout << "Enter new room number: ";
              getline(cin, newRoomNo);
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), "\n");

              // searches if new room number typed exists
              bool roomNoExists = false;
              for (const auto& iroom: rooms) {
                if (iroom.getRoomNo() == newRoomNo) {
                  roomNoExists = true;
                  break;
                }
              }
            } while ((!intIsValid(to_string(newRoomNo))) || (roomNoExists));

            room.setRoomNo(newRoomNo);
            cout << "Room number changed from Room " << roomNo << " to Room " << newRoomNo << "!" << endl;
            break;
          
          case 2:
            // edit room type
            
            // one possible way to do this is to delete the room to be edited and create a new room with the same parameters but the new type
            break;

          case 3:
            // edit room price
            double newRoomPrice;
            double oldRoomPrice = foundRoom.getRoomPrice();
            do {
              cout << "Enter new room price: ";
              getline(cin, newRoomPrice);
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), "\n");
            } while (!doubleIsValid(tostring(newRoomPrice)))
            break;

          case 4:
            // edit room availability
            int c4choice;
            cout << "Current room availability: " << (foundRoom.roomIsAvailable ? "Available" : "Not Available") << endl;
            do {
              cout << "[1] " << (foundRoom.roomIsAvailable ? "Set to Not Available" : "Set to Available") << endl;
              cout << "[0] Back"
              cout << "INPUT: ";
              getline(cin, c4choice);
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), "\n");
            } while ((!intIsValid(tostring(c4choice))) && !(c4choice == 0 || c4choice == 1));
            break;

        }
      } else {
        cout << "Room not found." << endl;
      }

    }

    void deleteRoom() {
      int roomNo;
      do {
        cout << "Enter room number to delete: ";
        getline(cin, roomNo);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), "\n");
      } while (!intIsValid(tostring(roomNo)));

      // initialize the variables needed to search for the room
      bool found = false;
      char choice;
      optional<Room> foundRoom;

      for (const auto& room: rooms) {
        if (room.getRoomNo() == roomNo) {
          found = true;
          foundRoom = room;
          break;
        }
      }

      if (found) {
        cout << "Are you sure you want to delete this room? [Y/N]: ";
        getline(cin, choice);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), "\n");

        if (choice == 'Y' || choice == 'y') {
          rooms.erase(foundRoom);
        }
      }
    }

    virtual void viewBookingHistory () const {
      cout << "View Booking History: " << endl;
    }
};