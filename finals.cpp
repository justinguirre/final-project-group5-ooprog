#include <iostream>
#include <string>
#include <vector>
using namespace std;

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



    virtual void viewBookingHistory () const {
      cout << "View Booking History: " << endl;
    }
};