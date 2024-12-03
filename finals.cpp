#include <iostream>
#include <vector>
#include <string>
using namespace std;

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

    void createAccount() override {
        
    }

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
                     << ") - P" << room->getRoomPrice() << endl;
            }
        }
    }

    vector<Room *> &getRooms() { return rooms; }

    vector<User *> &getUsers() { return users; }
};

// Display menu for customers
void displayCustomerMenu(Customer *customer, ParkInnLodge *lodge) {
    int choice;
    do {
        cout << "\n--- Customer Menu ---\n";
        cout << "1. Book Room\n";
        cout << "2. Cancel Booking\n";
        cout << "3. View Booking History\n";
        cout << "4. View Available Rooms\n";
        cout << "5. Sign-out\n";
        cout << "6. Create Account\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int roomNo;
            cout << "Enter room number to book: ";
            cin >> roomNo;

            // Check if the room exists and if it is available
            bool roomFound = false;
            bool roomAvailable = false;
            for (Room* room : lodge->getRooms()) {  // Assuming parkInn is an instance of ParkInn
                if (room->getRoomNo() == roomNo) {
                    roomFound = true;
                    if (room->getRoomAvailability()) {
                        roomAvailable = true;
                    }
                    break;
                }
            }

            if (!roomFound) {
                cout << "Room number " << roomNo << " does not exist.\n";
            } else if (!roomAvailable) {
                cout << "Room number " << roomNo << " is already booked.\n";
            } else {
                customer->bookRoom(roomNo);  // Proceed with booking
            }
            break;
        }

        case 2: {
            int roomNo;
            cout << "Enter room number to cancel: ";
            cin >> roomNo;
            customer->cancelBooking(roomNo);
            break;
        }
        case 3:
            customer->viewBookingHistory();
            break;
        case 4:
            lodge->viewAvailableRooms();
            break;
        case 5:
            cout << "Signing out...\n";
            break;
        case 6:
            cout << "Creating Customer Account\n";
            // Logic to create a new customer account (e.g., input name, email, password)
            string name, email, password;
            cout << "Enter name: ";
            cin >> name;
            setName(name);
            cout << "Enter email: ";
            cin >> email;
            setEmail(email);
            cout << "Enter password: ";
            cin >> password;
            setPassword(password);
            // Store account in a data structure, or any other method of saving the account
            Customer *newCustomer(name, email, password);
            parkInn.createAccount(newCustomer);
            cout << "Customer account created successfully!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}

// Display menu for employees
void displayEmployeeMenu(Employee *employee, ParkInnLodge *lodge) {
    int choice;
    do {
        cout << "\n--- Employee Menu ---\n";
        cout << "1. Add Room\n";
        cout << "2. Delete Room\n";
        cout << "3. View Available Rooms\n";
        cout << "4. View Check-Ins and Check-Outs\n";
        cout << "5. View Analytics\n";
        cout << "6. Sign-out\n";
        cout << "7. Create Account\n"
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int roomNo;
            double price;
            cout << "Enter room number: ";
            cin >> roomNo;
            cout << "Enter room price: ";
            cin >> price;
            employee->addRoom(lodge->getRooms(), new StandardRoom(roomNo, price));
            break;
        }
        case 2: {
            int roomNo;
            cout << "Enter room number to delete: ";
            cin >> roomNo;
            employee->deleteRoom(lodge->getRooms(), roomNo);
            break;
        }
        case 3:
            lodge->viewAvailableRooms();
            break;
        case 4:
            employee->viewCheckInOut();
            break;
        case 5:
            employee->viewAnalytics();
            break;
        case 6:
            cout << "Signing out...\n";
            break;
        case 7:
            cout << "Creating Customer Account\n";
            // Logic to create a new customer account (e.g., input name, email, password)
            string name, email, password;
            cout << "Enter name: ";
            cin >> name;
            setName(name);
            cout << "Enter email: ";
            cin >> email;
            setEmail(email);
            cout << "Enter password: ";
            cin >> password;
            setPassword(password);
            // Store account in a data structure, or any other method of saving the account
            Customer *newCustomer(name, email, password);
            parkInn.createAccount(newCustomer);
            cout << "Customer account created successfully!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);
}

// Main function
int main() {
    ParkInnLodge parkInn;

    // Add users
    Customer *customer1 = new Customer("John Doe", "john@example.com", "password123");
    Employee *employee1 = new Employee("Alice Smith", "alice@example.com", "password123");
    parkInn.createAccount(customer1);
    parkInn.createAccount(employee1);

    bool isRunning = true;

    while (isRunning) {
        cout << "PARKINNLODGE LOGIN PORTAL (Type -1 to exit.)" << endl;
        string email, password;
        cout << "Enter email: ";
        cin >> email;
        if (email == "-1") {
            cout << "Exiting program..." << endl;
            break;
        }
        cout << "Enter password: ";
        cin >> password;

        // Attempt to login
        User* loggedInUser = User::login(parkInn.getUsers(), email, password);
        
        if (loggedInUser != nullptr) {
            if (loggedInUser->getRole() == "Customer") {
                displayCustomerMenu(dynamic_cast<Customer*>(loggedInUser), &parkInn);
            } else if (loggedInUser->getRole() == "Employee") {
                displayEmployeeMenu(dynamic_cast<Employee*>(loggedInUser), &parkInn);
            }
        }
    }
    return 0;
};