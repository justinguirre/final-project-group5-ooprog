#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Room {
protected:
    int roomNo;
    string roomType;
    double price;
    bool isAvailable;

public:
    Room(int roomNo, string roomType, double price) : roomNo(roomNo), roomType(roomType), price(price), isAvailable(true) {}

    // Getters
    int getRoomNo() const { return roomNo; }
    string getRoomType() const { return roomType; }
    double getRoomPrice() const { return price; }
    bool getRoomAvailability() const { return isAvailable; }

    // Setters
    void setRoomNo(const int &no) { this->roomNo = no; }
    void setRoomType(const string &type) { this->roomType = type; }
    void setRoomPrice(double p) { this->price = p; }
    void setRoomAvailability(bool available) { this->isAvailable = available; }

    // Display room details
    virtual void displayRoomInfo() const {
        cout << "[ID: " << roomNo << "] " << roomType << "\n"
             << "- Price: Php " << price << "/night\n"
             << "- Availability: " << (isAvailable ? "Available" : "Not Available") << endl;
    }

    virtual ~Room() {}
};

// Standard Room Class
class StandardRoom : public Room {
private:
    string bedSize;

public:
    StandardRoom(int roomNo, double price) : Room(roomNo, "STANDARD", price), bedSize("Double") {}

    // Getters and Setters
    string getBedSize() const { return bedSize; }
    void setBedSize(const string &size) { bedSize = size; }

    // Display details
    void displayRoomInfo() const override {
        Room::displayRoomInfo();
        cout << "- Bed Size: " << bedSize << "\n" << endl;
    }
};

// Deluxe Room Class
class DeluxeRoom : public Room {
    string bedSize;
    bool extraBedAvailable;

public:
    DeluxeRoom(int roomNo, double price) : Room(roomNo, "DELUXE", price), bedSize("Queen"), extraBedAvailable(false) {}

    // Getters and Setters
    string getBedSize() const { return bedSize; }
    void setBedSize(const string &size) { bedSize = size; }

    bool getExtraBedAvailable() const { return extraBedAvailable; }
    void setExtraBedAvailable(bool available) { extraBedAvailable = available; }

    // Display details
    void displayRoomInfo() const override {
        Room::displayRoomInfo();
        cout << "- Bed Size: " << bedSize << "\n"
             << "- Extra Bed Available: " << (extraBedAvailable ? "Yes" : "No") << "\n" << endl;
    }
};

// Suite Room Class
class SuiteRoom : public Room {
    bool hasLivingRoom;
    bool hasKitchen;
    int noOfBedrooms;

public:
    SuiteRoom(int roomNo, double price) : Room(roomNo, "SUITE", price), hasLivingRoom(true), hasKitchen(true), noOfBedrooms(2) {}

    // Getters and Setters
    bool getLivingRoom() const { return hasLivingRoom; }
    void setLivingRoom(bool livingRoom) { hasLivingRoom = livingRoom; }

    bool getKitchen() const { return hasKitchen; }
    void setKitchen(bool kitchen) { hasKitchen = kitchen; }

    int getNoOfBedrooms() const { return noOfBedrooms; }
    void setNoOfBedrooms(int bedrooms) { noOfBedrooms = bedrooms; }

    // Display details
    void displayRoomInfo() const override {
        Room::displayRoomInfo();
        cout << "- Living Room: " << (hasLivingRoom ? "Yes" : "No") << "\n"
             << "- Kitchen: " << (hasKitchen ? "Yes" : "No") << "\n"
             << "- No. of Bedrooms: " << noOfBedrooms << "\n" << endl;
    }
};

class Booking {
private:
    vector<int> rooms;  
    double totalPrice;
    string fromDate;
    string toDate;
    int numberOfGuests;
    string paymentMethod;

public:
    Booking(vector<int> rooms, double totalPrice, string fromDate, string toDate, int guests, string payment) 
        : rooms(rooms), totalPrice(totalPrice), fromDate(fromDate), toDate(toDate), 
          numberOfGuests(guests), paymentMethod(payment) {}

    vector<int> getRooms() const {
        return rooms;
    }

    double getTotalPrice() const {
        return totalPrice;
    }

    string getFromDate() const {
        return fromDate;
    }

    string getToDate() const {
        return toDate;
    }

    int getNumberOfGuests() const {
        return numberOfGuests;
    }

    string getPaymentMethod() const {
        return paymentMethod;
    }

    void updateDates(string newFromDate, string newToDate) {
        fromDate = newFromDate;
        toDate = newToDate;
    }

    void updateRoom(vector<int> newRooms) {
        rooms = newRooms;
    }

    void updateGuests(int newNumberOfGuests) {
        numberOfGuests = newNumberOfGuests;
    }
};

// Function to display all available rooms
void displayAvailableRooms(const vector<Room *> &rooms) {
    cout << "----------Park Inn Lodge Available Rooms----------\n" << endl;
    for (const auto &room : rooms) {
        room->displayRoomInfo();
    }
}

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

// ParkInnLodge class
class ParkInnLodge {
    vector<User *> users;
    vector<Room *> rooms;

public:
    void createAccount(User *user) {
        users.push_back(user);
        user->createAccount();
    }

    void deleteAccount(User *user) {
        auto it = std::find(users.begin(), users.end(), user);

        // If the user is found
        if (it != users.end()) {
            // Remove the user from the vector
            users.erase(it);

            cout << "User has been deleted." << endl;
        } else {
            cout << "User not found." << endl;
        }
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
        cout << "7. Delete Account\n";
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
            case 3:{
                customer->viewBookingHistory();
                break;
            }
            case 4:{
                lodge->viewAvailableRooms();
                break;
            }
            case 5:{
                cout << "Signing out...\n";
                break;
            }
            case 6:{
                cout << "Creating Customer Account\n";
                // Logic to create a new customer account (e.g., input name, email, password)
                string name, email, password;
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter email: ";
                cin >> email;
                cout << "Enter password: ";
                cin >> password;
                // Store account in a data structure, or any other method of saving the account
                Customer *newCustomer = new Customer(name, email, password);
                lodge->createAccount(newCustomer);
                cout << "Customer account created successfully!\n";
                break;
            }
            case 7: {
                lodge->deleteAccount(customer);
                cout << "Deleting account..." << endl;
                break;
            }
        }
    } while (choice != 5 && choice != 7);
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
        cout << "7. Create Account\n";
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
            case 3: {
                lodge->viewAvailableRooms();
                break;
            }
            case 4: {
                employee->viewCheckInOut();
                break;
            }
            case 5: {
                employee->viewAnalytics();
                break;
            }
            case 6: {
                cout << "Signing out...\n";
                break;
                }
            case 7: {
                cout << "Creating Customer Account\n";
                // Logic to create a new customer account (e.g., input name, email, password)
                string name, email, password;
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter email: ";
                cin >> email;
                cout << "Enter password: ";
                cin >> password;
                // Store account in a data structure, or any other method of saving the account
                Customer *newCustomer = new Customer(name, email, password);
                lodge->createAccount(newCustomer);
                cout << "Customer account created successfully!\n";
                break;
            }
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
}
