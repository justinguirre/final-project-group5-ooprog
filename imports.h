#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Base class: User
class User {
protected:
    string name, email, password, role;

public:
    User(string n, string e, string p, string r) : name(n), email(e), password(p), role(r) {}
    string getName() { return name; }
    string getEmail() { return email; }
    string getPassword() { return password; }
    string getRole() { return role; }
    
    virtual void createAccount() {
        cout << "User account created for: " << name << endl;
    }
    virtual void deleteAccount() {
        cout << "User account deleted for: " << name << endl;
    }
    
    static User* login(vector<User*>& users, string email, string password) {
        for (auto& user : users) {
            if (user->getEmail() == email && user->getPassword() == password) {
                cout << "Login successful! Welcome, " << user->getName() << endl;
                return user;
            }
        }
        cout << "Invalid email or password.\n";
        return nullptr;
    }
};

// Derived class: Customer
class Customer : public User {
    vector<string> bookingHistory;
    vector<string> paymentHistory;
    vector<int> currentBookings;

public:
    Customer(string n, string e, string p)
        : User(n, e, p, "Customer") {}

    void bookRoom(int roomNo) {
        currentBookings.push_back(roomNo);
        bookingHistory.push_back("Booked room " + to_string(roomNo));
        cout << "Room " << roomNo << " booked successfully!\n";
    }

    void cancelBooking(int roomNo) {
        for (auto it = currentBookings.begin(); it != currentBookings.end(); ++it) {
            if (*it == roomNo) {
                currentBookings.erase(it);
                bookingHistory.push_back("Canceled room " + to_string(roomNo));
                cout << "Room " << roomNo << " canceled successfully!\n";
                return;
            }
        }
        cout << "Booking not found for room " << roomNo << ".\n";
    }

    void viewBookingHistory() {
        cout << "Booking History for " << name << ":\n";
        for (const string &history : bookingHistory) {
            cout << "- " << history << endl;
        }
    }
};

// Derived class: Employee
class Employee : public User {
public:
    Employee(string n, string e, string p)
        : User(n, e, p, "Employee") {}

    void addRoom(vector<class Room *> &rooms, Room *room) {
        rooms.push_back(room);
        cout << "Room " << room->getRoomNo() << " added successfully!\n";
    }

    void deleteRoom(vector<class Room *> &rooms, int roomNo) {
        for (auto it = rooms.begin(); it != rooms.end(); ++it) {
            if ((*it)->getRoomNo() == roomNo) {
                delete *it; // Free memory
                rooms.erase(it);
                cout << "Room " << roomNo << " deleted successfully!\n";
                return;
            }
        }
        cout << "Room " << roomNo << " not found.\n";
    }

    void viewCheckInOut() {
        cout << "Viewing all check-ins and check-outs (placeholder).\n";
    }

    void viewAnalytics() {
        cout << "Viewing analytics (placeholder).\n";
    }
};

// Base class: Room
class Room {
protected:
    int roomNo;
    string roomType;
    double price;
    bool isAvailable;

public:
    Room(int no, string type, double p)
        : roomNo(no), roomType(type), price(p), isAvailable(true) {}

    int getRoomNo() { return roomNo; }
    string getRoomType() { return roomType; }
    double getRoomPrice() { return price; }
    bool getRoomAvailability() { return isAvailable; }
    void setRoomAvailability(bool available) { isAvailable = available; }
};

// Derived class: StandardRoom
class StandardRoom : public Room {
public:
    StandardRoom(int no, double p) : Room(no, "Standard", p) {}
};

// Derived class: DeluxeRoom
class DeluxeRoom : public Room {
public:
    DeluxeRoom(int no, double p) : Room(no, "Deluxe", p) {}
};

// Derived class: SuiteRoom
class SuiteRoom : public Room {
public:
    SuiteRoom(int no, double p) : Room(no, "Suite", p) {}
};

// ParkInnLodge class
class ParkInnLodge {
    vector<User *> users;
    vector<Room *> rooms;

public:
    void createAccount(User *user) {
        users.push_back(user);
        user->createAccount();
    }

    void addRoom(Room *room) {
        rooms.push_back(room);
        cout << "Room added: " << room->getRoomNo() << endl;
    }

    void viewAvailableRooms() {
        cout << "\nAvailable Rooms:\n";
        for (auto &room : rooms) {
            if (room->getRoomAvailability()) {
                cout << "- Room " << room->getRoomNo() << " (" << room->getRoomType()
                     << ") - $" << room->getRoomPrice() << endl;
            }
        }
    }

    vector<Room *> &getRooms() { return rooms; }

    vector<User *> &getUsers() { return users; }
};