#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
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
    // construct objects
    void createAccount(string name, string email, string password) : User(name, email, password) {}
    void addRoom(int roomNo, string roomType, double price) : Room(roomNo, roomType, price) {}

    void editRoom() {
      int roomNo;
      int choice;
      cout << "Enter room number of the room to edit: ";
      getline(cin, roomNo);
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      bool found = false;
      for (const auto& room: rooms) {
        if (room.getRoomNo() == roomNo) {
          found = true;
          break;
        }
      }
      if (found) {
        cout << left;
        cout << setw(15) << "NUMBER" << setw(20) << "TYPE" << setw(10) << "PRICE" << setw(15) "AVAILABLE?" << setw(15) << endl;
        cout << "-----------------------------------------------------------------------------------" << endl;
        for (const auto& room: rooms) {
          if (room.getRoomNo() == roomNo) {
            cout << setw(15) << room.getRoomNo() << setw(20) << room.getRoomType() << setw(10) << room.getRoomPrice() << setw(15) << room.roomIsAvailable() << setw(15) << endl;
          }
        }
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
              cin.ignore(numeric_limits<streamsize>::max(), '\n');

              bool roomNoExists = false;
              for (const auto& iroom: rooms) {
                if (iroom.getRoomNo() == newRoomNo) {
                  roomNoExists = true;
                  break;
                }
              }
            } while ((!intIsValid(newRoomNo)) || (roomNoExists));

            room.setRoomNo(newRoomNo);
            break;
          
          case 2:
            // edit room type
            break;

          case 3:
            // edit room price
            break;

          case 4:
            // edit room availability
            break;

        }
      }

    }

    virtual void viewBookingHistory () const {
      cout << "View Booking History: " << endl;
    }
};