#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <optional>
#include <limits> // For numeric_limits

using namespace std;

// Utility functions for input validation
bool intIsValid(const string& input) {
    if (input.empty() || input[0] == '-') return false;

    for (char c : input) {
        if (!isdigit(c)) return false;
    }

    return stoi(input) > 0;
}

bool doubleIsValid(const string& input) {
    if (input.empty() || input[0] == '-') return false;

    bool hasDecimalPoint = false;
    for (size_t i = 0; i < input.length(); i++) {
        char c = input[i];
        if (c == '.') {
            if (hasDecimalPoint) return false; // Multiple decimal points
            hasDecimalPoint = true;
        } else if (!isdigit(c)) {
            return false;
        }
    }

    return stod(input) > 0.0;
}

string toUpper(string str) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 32; // Convert lowercase to uppercase
        }
    }
    return str;
}

// Class Room
class Room {
private:
    int roomNo;
    string roomType;
    double price;
    bool isAvailable;

public:
    Room(int roomNo, string roomType, double price)
        : roomNo(roomNo), roomType(roomType), price(price), isAvailable(true) {}

    // Getters
    int getRoomNo() const { return roomNo; }
    string getRoomType() const { return roomType; }
    double getRoomPrice() const { return price; }
    bool roomIsAvailable() const { return isAvailable; }

    // Setters
    void setRoomNo(int roomNo) { this->roomNo = roomNo; }
    void setRoomType(const string& roomType) { this->roomType = roomType; }
    void setRoomPrice(double roomPrice) { this->price = roomPrice; }
    void setIsAvailable(bool isAvailable) { this->isAvailable = isAvailable; }
};

// Class User
class User {
protected:
    string name, email, password;
    string role; // Role (e.g., "Customer" or "Employee")

public:
    User(const string& name, const string& email, const string& password, const string& role)
        : name(name), email(email), password(password), role(role) {}

    // Getters
    string getName() const { return name; }
    string getEmail() const { return email; }
    string getRole() const { return role; }

    // Setters
    void setName(const string& name) { this->name = name; }
    void setEmail(const string& email) { this->email = email; }
};

// Derived class Employee
class Employee : public User {
public:
    Employee(const string& name, const string& email, const string& password)
        : User(name, email, password, "EMPLOYEE") {}

    // Add a room to the system
    void addRoom(vector<Room>& rooms) {
        int roomNo;
        string roomNoInput;
        string roomType;
        double price;
        string priceInput;

        // Input and validate room number
        do {
            cout << "Enter room number (positive integer): ";
            cin >> roomNoInput;

            if (!intIsValid(roomNoInput)) {
                cout << "Invalid room number. Please enter a positive integer.\n";
                continue;
            }

            roomNo = stoi(roomNoInput);

            // Check if room number already exists
            bool roomExists = false;
            for (const auto& room : rooms) {
                if (room.getRoomNo() == roomNo) {
                    roomExists = true;
                    cout << "Room number already exists. Please enter a unique room number.\n";
                    break;
                }
            }

            if (!roomExists) {
                break; // Valid and unique room number
            }

        } while (true);

        // Input and validate room type
        cin.ignore(); // Clear input buffer
        do {
            cout << "Enter room type (non-empty): ";
            getline(cin, roomType);

            if (roomType.empty()) {
                cout << "Room type cannot be empty. Please try again.\n";
            } else {
                break; // Valid room type
            }
        } while (true);

        // Input and validate room price
        do {
            cout << "Enter room price (positive decimal): ";
            cin >> priceInput;

            if (!doubleIsValid(priceInput)) {
                cout << "Invalid price. Please enter a positive decimal value.\n";
                continue;
            }

            price = stod(priceInput);
            break; // Valid room price
        } while (true);

        // Create and add Room object
        rooms.emplace_back(Room(roomNo, roomType, price));
        cout << "Room added successfully!\n";
    }

    // Edit a room in the system
    void editRoom(vector<Room>& rooms) {
        int roomNo;
        string roomNoInput;
        cout << "Enter the room number of the room to edit: ";
        cin >> roomNoInput;

        if (!intIsValid(roomNoInput)) {
            cout << "Invalid room number. Please enter a positive integer.\n";
            return;
        }

        roomNo = stoi(roomNoInput);

        // Search for the room
        auto it = find_if(rooms.begin(), rooms.end(), [&](const Room& room) {
            return room.getRoomNo() == roomNo;
        });

        if (it == rooms.end()) {
            cout << "Room not found.\n";
            return;
        }

        // Edit options
        int choice;
        cout << "Editing Room #" << roomNo << ":\n";
        cout << "[1] Edit Room Type\n";
        cout << "[2] Edit Room Price\n";
        cout << "[3] Edit Availability\n";
        cout << "[0] Cancel\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string newType;
            cin.ignore();
            cout << "Enter new room type: ";
            getline(cin, newType);
            it->setRoomType(newType);
            cout << "Room type updated successfully!\n";
            break;
        }
        case 2: {
            string newPriceInput;
            double newPrice;
            do {
                cout << "Enter new room price: ";
                cin >> newPriceInput;
                if (!doubleIsValid(newPriceInput)) {
                    cout << "Invalid price. Please enter a positive decimal value.\n";
                    continue;
                }
                newPrice = stod(newPriceInput);
                break;
            } while (true);

            it->setRoomPrice(newPrice);
            cout << "Room price updated successfully!\n";
            break;
        }
        case 3: {
            int availability;
            cout << "Enter availability (1 for Available, 0 for Not Available): ";
            cin >> availability;
            it->setIsAvailable(availability == 1);
            cout << "Room availability updated successfully!\n";
            break;
        }
        case 0:
            cout << "Edit canceled.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    }

    // Delete a room in the system
    void deleteRoom(vector<Room>& rooms) {
        int roomNo;
        string roomNoInput;
        cout << "Enter the room number of the room to delete: ";
        cin >> roomNoInput;

        if (!intIsValid(roomNoInput)) {
            cout << "Invalid room number. Please enter a positive integer.\n";
            return;
        }

        roomNo = stoi(roomNoInput);

        // Search for the room
        auto it = find_if(rooms.begin(), rooms.end(), [&](const Room& room) {
            return room.getRoomNo() == roomNo;
        });

        if (it == rooms.end()) {
            cout << "Room not found.\n";
            return;
        }

        rooms.erase(it);
        cout << "Room deleted successfully!\n";
    }
};

class Customer : public User {
    private:
        vector<Booking> bookingHistory;
        vector<Payment> paymentHistory;
        vector<Booking> currentBookings;
    
    public:
        Customer(string name, string email, string password) : User(name, email, password, "CUSTOMER") {}

        void addPayment() {
            int choice;
            string ccno, ccexpy, ccvcode, gcno;

            do {
                cout << "\nAdd Payment\n";
                cout << "[1] Credit or Debit Card\n";
                cout << "[2] GCash\n";
                cout << "[0] Back\n";
                cout << "INPUT: ";
                string input;
                getline(cin, input);

                // Validate input to ensure it's an integer between 0 and 2
                if (intIsValid(input)) {
                    choice = stoi(input);
                } else {
                    cout << "Invalid choice. Please enter 0, 1, or 2.\n";
                    choice = -1; // Reset choice to an invalid state
                }
            } while (choice < 0 || choice > 2);

            switch (choice) {
                case 1: // Credit or Debit Card
                    do {
                        cout << "\nEnter Credit/Debit Card Number (16 digits): ";
                        getline(cin, ccno);
                    } while (ccno.length() != 16 || !intIsValid(ccno));

                    do {
                        cout << "Enter Expiry Year (YYYY, current or future): ";
                        getline(cin, ccexpy);
                        // Ensure year is valid and in the future
                        if (intIsValid(ccexpy)) {
                            int year = stoi(ccexpy);
                            int currentYear = 2024; // Replace with dynamic year retrieval if needed
                            if (year >= currentYear) {
                                break;
                            }
                        }
                        cout << "Invalid expiry year. Please enter a valid year.\n";
                    } while (true);

                    do {
                        cout << "Enter CVV Code (3 digits): ";
                        getline(cin, ccvcode);
                    } while ((ccvcode.length() != 3 || ccvcode.length() != 4) || !intIsValid(ccvcode));

                    cout << "\nPayment added successfully with Credit/Debit Card.\n";
                    break;

                case 2: // GCash
                    do {
                        cout << "\nEnter GCash Number (11 digits): ";
                        getline(cin, gcno);
                    } while (gcno.length() != 11 || !intIsValid(gcno));

                    cout << "\nPayment added successfully with GCash.\n";
                    break;

                case 0: // Back
                    cout << "\nReturning to the previous menu.\n";
                    break;

                default:
                    cout << "Unexpected error.\n";
            }
        }
};

// Main system class: ParkInnLodge
class ParkInnLodge {
private:
    vector<User> users;
    vector<Room> rooms;

public:
    // Function to allow an employee to manage rooms
    void manageRooms(Employee& employee) {
        int choice;
        do {
            cout << "Room Management:\n";
            cout << "[1] Add Room\n";
            cout << "[2] Edit Room\n";
            cout << "[3] Delete Room\n";
            cout << "[0] Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                employee.addRoom(rooms);
                break;
            case 2:
                employee.editRoom(rooms);
                break;
            case 3:
                employee.deleteRoom(rooms);
                break;
            case 0:
                cout << "Exiting room management.\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        } while (true);
    }

    void createAccount() {
        string name;
        string email;
        string password;
        string confirmPass;
        string account_type;
        cout << "Enter name: ";
        getline(cin, name);
        cin.clear();
        cin.ignore();
        cout << "Enter email: ";
        getline(cin, name);
        cin.clear();
        cin.ignore();

        do {
            cout << "Enter password: ";
            getline(cin, password);
            cin.clear();
            cin.ignore();
            cout << "Confirm password: ";
            getline(cin, confirmPass);
            cin.clear();
            cin.ignore();
        } while (password != confirmPass);

        do {
            cout << "Account type\n";
            cout << "- Customer\n";
            cout << "- Employee\n";
            cout << "INPUT: ";
            getline(cin, account_type);
            account_type = toUpper(account_type);
            cin.clear();
            cin.ignore();
        } while (!(account_type == "CUSTOMER" || account_type == "EMPLOYEE"));

        if (account_type == "EMPLOYEE") {
            Employee(name, email, password);
        } else {
            Customer(name, email, password);
        }

        users.emplace_back(name, email, password, role);
    }

    // Display rooms
    void viewRooms() const {
        if (rooms.empty()) {
            cout << "No rooms available.\n";
            return;
        }

        cout << left << setw(15) << "ROOM NO" << setw(20) << "ROOM TYPE"
             << setw(10) << "PRICE" << setw(15) << "AVAILABILITY" << "\n";
        cout << "----------------------------------------------------------\n";

        for (const auto& room : rooms) {
            cout << left << setw(15) << room.getRoomNo()
                 << setw(20) << room.getRoomType()
                 << setw(10) << room.getRoomPrice()
                 << setw(15) << (room.roomIsAvailable() ? "Available" : "Not Available")
                 << "\n";
        }
    }
};