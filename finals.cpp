#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

// * TO-DO:
// * - = not done
// * = = in progress
// * + = finished
// * ~ = failed/canceled

// - edit booking (nothing happens after entering booking id)
// ~ edit account (nothing happens after typing 6)
// - delete account (not working properly)
// - view checkins (not implemented yet)
// - checkin (not implemented yet)
// - generate report (not implemented yet)

class Room {
protected:
    string roomNo;
    string roomType;
    double price;
    bool isAvailable;
    string features;
    string bookingId;

public:
    Room(string no, string type, double p, string f)
        : roomNo(no), roomType(type), price(p), isAvailable(true), features(f) {}

    string getRoomNo() const { return roomNo; }
    string getRoomType() const { return roomType; }
    double getRoomPrice() const { return price; }
    bool getRoomAvailability() const { return isAvailable; }
    string getRoomFeatures() const { return features; }
    string getBookingId() const ( return bookingId; )

    void setRoomNo(const string &no) { this->roomNo = no; }
    void setRoomType(const string &type) { this->roomType = type; }
    void setRoomPrice(double p) { this->price = p; }
    void setRoomAvailability(bool available) { isAvailable = available; }
    void setBookingId(string bookingid) { this->bookingId = bookingid; } 

    virtual void displayRoomInfo() const {
        cout << "[ID: " << roomNo << "] " << roomType << "\n"
             << "- Price: Php " << price << "/night\n"
             << "- Features: " << features << "\n"
             << "- Availability: " << (isAvailable ? "Available" : "Not Available") << endl;
    }

    virtual ~Room() {}
};

// Standard Room Class
class StandardRoom : public Room {
private:
    string bedSize;

public:
    StandardRoom(string roomNo, double price, string f = "Basic Amenities")
        : Room(roomNo, "STANDARD", price, f), bedSize("Double") {}

    string getBedSize() const { return bedSize; }
    void setBedSize(const string &size) { bedSize = size; }

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
    DeluxeRoom(string roomNo, double price, string f = "Premium Amenities")
        : Room(roomNo, "DELUXE", price, f), bedSize("Queen"), extraBedAvailable(false) {}

    string getBedSize() const { return bedSize; }
    void setBedSize(const string &size) { bedSize = size; }

    bool getExtraBedAvailable() const { return extraBedAvailable; }
    void setExtraBedAvailable(bool available) { extraBedAvailable = available; }

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
    SuiteRoom(string roomNo, double price, string f = "Luxury Amenities")
        : Room(roomNo, "SUITE", price, f), hasLivingRoom(true), hasKitchen(true), noOfBedrooms(2) {}

    bool getLivingRoom() const { return hasLivingRoom; }
    void setLivingRoom(bool livingRoom) { hasLivingRoom = livingRoom; }

    bool getKitchen() const { return hasKitchen; }
    void setKitchen(bool kitchen) { hasKitchen = kitchen; }

    int getNoOfBedrooms() const { return noOfBedrooms; }
    void setNoOfBedrooms(int bedrooms) { noOfBedrooms = bedrooms; }

    void displayRoomInfo() const override {
        Room::displayRoomInfo();
        cout << "- Living Room: " << (hasLivingRoom ? "Yes" : "No") << "\n"
             << "- Kitchen: " << (hasKitchen ? "Yes" : "No") << "\n"
             << "- No. of Bedrooms: " << noOfBedrooms << "\n" << endl;
    }
};

// Booking class with payment method
class Booking {
private:
    string bookingID;
    string roomNo;
    string fromDate;
    string toDate;
    PaymentMethod paymentMethod;
    double totalPrice;
    bool hasCheckedIn;

public:
    Booking(string id, string room, string from, string to, int guests, PaymentMethod& payment, double price) 
        : bookingID(id), roomNo(room), fromDate(from), toDate(to), paymentMethod(payment), totalPrice(price), hasCheckedIn(false) {}

    void displayBookingDetails() const {
        cout << setprecision(2) << fixed << "Booking ID: " << bookingID << endl
             << "Room: " << roomNo << endl
             << "Check-in: " << fromDate << endl
             << "Check-out: " << toDate << endl
             << "Total Price: Php " << totalPrice << endl
             << "Payment Method: " << paymentMethod << endl;
    }

    string getBookingID() const { return bookingID; }
    double getTotalPrice() const { return totalPrice; }
    string getPaymentMethod() const { return paymentMethod; }
    bool getHasCheckedIn() const { return hasCheckedIn; }

    void setHasCheckedIn(bool val) {
        this->hasCheckedIn = val;
    }
};

class PaymentMethod {
public:
    virtual bool processPayment(double amount) = 0;
    virtual string getType() const = 0;
    virtual ~PaymentMethod() {}
};

class Card : public PaymentMethod {
private:
    string number;
    string expiration;
    string pin;
    bool isCredit;

public:
    Card(const string& number, const string& expiration, const string& pin, bool isCredit)
        : number(number), expiration(expiration), pin(pin), isCredit(isCredit) {}

    bool processPayment(double amount) override {
        // Simple validation
        if (number.empty() || expiration.empty() || pin.empty()) {
            cout << "Invalid card details. Payment failed.\n";
            return false;
        }

        // Simulate PIN verification
        string inputPin;
        cout << "Enter " << (isCredit ? "Credit" : "Debit") << " Card PIN: ";
        cin >> inputPin;

        if (inputPin != pin) {
            cout << "Incorrect PIN. Payment declined.\n";
            return false;
        }

        // Simulate payment processing
        cout << "Processing " << (isCredit ? "credit" : "debit") 
             << " card payment of Php " << amount << endl;
        
        // Simulate transaction confirmation
        char confirm;
        cout << "Confirm payment? (Y/N): ";
        cin >> confirm;

        if (confirm == 'Y' || confirm == 'y') {
            cout << "Payment successful!\n";
            return true;
        } else {
            cout << "Payment cancelled.\n";
            return false;
        }
    }

    string getType() const override {
        return isCredit ? "Credit Card" : "Debit Card";
    }
};

class GCash : public PaymentMethod {
private:
    string number;
    double balance;

public:
    GCash(const string& number, double initialBalance = 10000.0) 
        : number(number), balance(initialBalance) {}

    bool processPayment(double amount) override {
        // Validate phone number
        if (number.empty() || number.length() != 11) {
            cout << "Invalid GCash number. Payment failed.\n";
            return false;
        }

        // Check balance
        if (amount > balance) {
            cout << "Insufficient balance. Payment failed.\n";
            return false;
        }

        // Simulate OTP verification
        string otp;
        cout << "Enter GCash OTP: ";
        cin >> otp;

        // Simple OTP validation (just for demonstration)
        if (otp != "123456") {
            cout << "Incorrect OTP. Payment declined.\n";
            return false;
        }

        // Process payment
        balance -= amount;
        cout << "Processing GCash payment of Php" << amount << endl;
        
        // Confirm transaction
        char confirm;
        cout << "Confirm payment? (Y/N): ";
        cin >> confirm;

        if (confirm == 'Y' || confirm == 'y') {
            cout << "Payment successful!\n";
            cout << "Remaining balance: Php" << balance << endl;
            return true;
        } else {
            // Refund the amount if cancelled
            balance += amount;
            cout << "Payment cancelled.\n";
            return false;
        }
    }

    string getType() const override {
        return "GCash";
    }

    // Getter for balance (optional, but useful)
    double getBalance() const {
        return balance;
    }
};

class User {
protected:
    string name, email, password, role;

public:
    User(string n, string e, string p, string r) : name(n), email(e), password(p), role(r) {}
    string getName() { return name; }
    string getEmail() { return email; }
    string getPassword() { return password; }
    string getRole() { return role; }

    // Getter for role
    string getRole() const { return role; }

    virtual void createAccount() = 0;
    virtual void deleteAccount() = 0;

    static User* login(vector<User*>& users, string email, string password) {
        for (auto& user : users) {
            if (user->email == email && user->password == password) {
                cout << "Login successful! Welcome, " << user->name << endl;
                return user;
            }
        }
        cout << "Invalid email or password.\n";
        return nullptr;
    }
};

class Employee : public User {
public:
    Employee(string n, string e, string p) : User(n, e, p, "Employee") {}

    void createAccount() override {
        cout << "Employee account created for: " << name << endl;
    }

    void deleteAccount() override {
        cout << "Employee account deleted for: " << name << endl;
    }

    void addRoom(vector<Room*>& rooms) {
        string roomNo, roomType, features;
        double price;

        cout << "Enter Room Number: ";
        cin >> roomNo;
        cout << "Enter Room Type: ";
        cin >> roomType;
        cout << "Enter Features: ";
        cin.ignore();
        getline(cin, features);
        cout << "Enter Price: ";
        cin >> price;

        Room* newRoom = nullptr;

        if (roomType == "Standard") {
            newRoom = new StandardRoom(roomNo, price, features);
        } else if (roomType == "Deluxe") {
            newRoom = new DeluxeRoom(roomNo, price, features);
        } else if (roomType == "Suite") {
            newRoom = new SuiteRoom(roomNo, price, features);
        } else {
            cout << "Invalid room type.\n";
            return;
        }

        rooms.push_back(newRoom);
        cout << "Room added successfully!\n";
    }

    void deleteRoom(vector<Room*>& rooms) {
        string roomNo;

        cout << "Enter Room Number to delete: ";
        cin >> roomNo;

        for (auto it = rooms.begin(); it != rooms.end(); ++it) {
            if ((*it)->getRoomNo() == roomNo) {
                delete *it;  // Delete room
                rooms.erase(it);  // Erase from vector
                cout << "Room " << roomNo << " deleted successfully!\n";
                return;
            }
        }

        cout << "Room " << roomNo << " not found.\n";
    }

    void viewCheckInOut() {
        cout << "Viewing all check-ins and check-outs (placeholder).\n";
    }

    void generateReport() const {
        cout << "----------[Hotel Name] Generate Report----------\n";
        cout << "1. Daily Summary\n";
        cout << "2. Weekly Summary\n";
        cout << "3. Monthly Summary\n";
        cout << "4. Custom Range\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        cout << "Viewing analytics (placeholder).\n";
    }
};

class Customer : public User {
    vector<Booking*> bookings;
    vector<string> paymentHistory;
    vector<int> currentBookings;
    vector<PaymentMethod> paymentMethods;

public:
    Customer(string n, string e, string p) : User(n, e, p, "Customer") {}

    void createAccount() override {
        cout << "Customer account created for: " << name << endl;
    }

    void deleteAccount() override {
        cout << "Customer account deleted for: " << name << endl;
    }

    void bookRoom(string roomNo, string fromDate, string toDate, int guests, string paymentMethod, double price) {
        string bookingID = "B" + to_string(bookings.size() + 1); // Example of generating a booking ID
        Booking* newBooking = new Booking(bookingID, roomNo, fromDate, toDate, guests, paymentMethod, price);
        bookings.push_back(newBooking);
        cout << "Booking confirmed! Your Booking ID: " << bookingID << endl;
    }

    void cancelBooking(string bookingID) {
        for (auto it = bookings.begin(); it != bookings.end(); ++it) {
            if ((*it)->getBookingID() == bookingID) {
                cout << "Cancelling booking: " << bookingID << endl;
                delete *it;
                bookings.erase(it);
                cout << "Booking cancelled successfully.\n";
                return;
            }
        }
        cout << "Booking ID not found.\n";
    }

    void addPaymentMethod(PaymentMethod& paymentMethod) {
        paymentMethods.push_back(paymentMethod);
    }

    void viewBookingHistory() const {
        cout << "Booking History for " << name << ":\n";
        for (auto& booking : bookings) {
            booking->displayBookingDetails();
        }
    }
};

class ParkInnLodge {
    private:
        vector<User*> users;
        vector<Room*> rooms;
        vector<Booking*> bookings;
    
    public:
        void createAccount(Customer& customer) {
            bool found = false;
            for (auto& cust : users) {
                if (customer.getEmail() == cust.getEmail()) {
                    cout << "Email already exists!" << endl;
                    found = true;
                    break;
                }
            }

            if (!found) {
                users.push_back(customer);
                cout << "Account created for " << customer.getName() << endl;
            }
        }

        void addRoom(Room& room) {
            bool found = false;
            for (auto& rewm : rooms) {
                if (room.getRoomNo == rewm.getRoomNo()) {
                    cout << "Room number already exists!" << endl;
                    found = true;
                    break;
                }
            }

            if (!found) {
                rooms.push_back(room);
                cout << "Room " << room.getRoomNo() << " created";
            }
        }

        void editRoom(Room& room, string toEdit, string newValue) {
            if (toEdit == "ROOMNO") {
                bool found = false;
                for (auto& rewm : rooms) {
                    if (newValue == rewm.getRoomNo()) {
                        cout << "Room number already exists!" << endl;
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    room.setRoomNo(newValue);
                    cout << "Room number changed successfully!" << endl;
                }
            } else if (toEdit == "ROOMPRICE") {
                room.setRoomPrice(stod(newValue));
                cout << "Room price changed successfully!" << endl;
            } else if (toEdit == "ROOMAVAIL") {
                room.setRoomAvailability(newValue == "TRUE" || newValue == "true");
                cout << "Room availability changed successfully!" << endl;
            } else {
                cout << "Invalid parameters!" << endl;
            }
        }

        void deleteRoom(Room& room) {
            auto it = remove_if(rooms.begin(), rooms.end(),
                [&roomToDelete](const Room& room) {
                    return room.getRoomNo() == roomToDelete.getRoomNo();  // Compare by room number
                });

            // Check if the room was found and removed
            if (it != rooms.end()) {
                rooms.erase(it, rooms.end());  // Erase the element from the vector
                cout << "Room deleted successfully!" << endl;
            } else {
                cout << "Room not found!" << endl;
            }
        }

        void bookRoom(const Booking& booking) {
            bookings.push_back(booking);
            cout << "Booking success!" << endl;
        }

        void viewAvailableRooms() {
            if (rooms.empty()) {
                cout << "No rooms available." << endl;
                return;
            }
            for (const auto& room : rooms) {
                if (room.getRoomAvailability()) {
                    room.displayRoomInfo();
                }
            }
        }
}

void display() {

}

// Main function with hotel flow
int main() {
    vector<User*> users;
    vector<Room*> rooms;
    bool running = true;

    rooms.push_back(new DeluxeRoom("101", 5000.0));
    rooms.push_back(new StandardRoom("102", 3000.0));
    rooms.push_back(new SuiteRoom("201", 10000.0));

    // Create sample users
    users.push_back(new Employee("Employee Park Inn Lodge", "admin@example.com", "pil123"));

    while (running) {
        cout << "Hotel Management System\n";
        cout << "1. Guest Login\n";
        cout << "2. Employee Login\n";
        cout << "3. Register as Customer\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: { // Guest Login
                string email, password;
                cout << "Enter Email: ";
                cin >> email;
                cout << "Enter Password: ";
                cin >> password;

                User* loggedInUser = User::login(users, email, password);
                if (loggedInUser && loggedInUser->getRole() == "Customer") {  // Using the getter
                    Customer* customer = static_cast<Customer*>(loggedInUser);
                    bool guestMenu = true;

                    while (guestMenu) {
                        cout << "\n========== Hotel Management System - Guest Menu ==========\n";
                        cout << "1. View Room Available\n";
                        cout << "2. Book Room\n";
                        cout << "3. Edit Booking\n";
                        cout << "4. Cancel Booking\n";
                        cout << "5. View Booking and Payment History\n";
                        cout << "6. Edit Account\n";
                        cout << "7. Delete Account\n";
                        cout << "8. Logout\n";
                        cout << "Choose an option: ";
                        int guestOption;
                        cin >> guestOption;

                        switch (guestOption) {
                            case 1: { // View Available Rooms
                                cout << "----------[Hotel Name] Available Rooms----------\n";
                                for (size_t i = 0; i < rooms.size(); ++i) {
                                    rooms[i]->displayRoomInfo();
                                    cout << endl;
                                }
                                break;
                            }
                            case 2: { // Book Room
                                string roomNo, fromDate, toDate, paymentMethod;
                                int guests;

                                cout << "----------Park Inn Lodge Book Room----------\n";

                                cout << "Enter the Room ID you want to book: ";
                                cin >> roomNo;
                                cout << "Enter Check-in Date (YYYY-MM-DD): ";
                                cin >> fromDate;
                                cout << "Enter Check-out Date (YYYY-MM-DD): ";
                                cin >> toDate;
                                cout << "Enter the Number of Guests: ";
                                cin >> guests;
                                cout << "Choose Payment Method (1: Cash, 2: Digital Wallet, 3: Credit/Debit Card): ";
                                int paymentChoice;
                                cin >> paymentChoice;
                                switch (paymentChoice) {
                                    case 1: paymentMethod = "Cash"; break;
                                    case 2: paymentMethod = "Digital Wallet"; break;
                                    case 3: paymentMethod = "Credit/Debit Card"; break;
                                }
                                double price = 2000; // Example room price, adjust based on room
                                customer->bookRoom(roomNo, fromDate, toDate, guests, paymentMethod, price);
                                break;
                            }
                            case 3: { // Edit Booking
                                string bookingID;
                                cout << "----------Park Inn Lodge Edit Booking----------\n";
                                cout << "Enter Booking ID to edit: ";
                                cin >> bookingID;
                                // Add logic to edit booking details here.
                                break;
                            }
                            case 4: { // Cancel Booking
                                string bookingID;
                                cout << "----------Park Inn Lodge Cancel Booking----------\n";
                                cout << "Enter Booking ID to cancel: ";
                                cin >> bookingID;
                                customer->cancelBooking(bookingID);
                                break;
                            }
                            case 5: { // View Booking and Payment History
                                cout << "----------Park Inn Lodge Booking History----------\n";
                                customer->viewBookingHistory();
                                break;
                            }
                            case 6: { // Edit Account
                                // Logic to edit account details (email, password)
                                break;
                            }
                            case 7: { // Delete Account
                                customer->deleteAccount();
                                guestMenu = false;
                                break;
                            }
                            case 8: { // Logout
                                guestMenu = false;
                                break;
                            }
                            default:
                                cout << "Invalid option. Try again.\n";
                        }
                    }
                }
                break;
            }
            case 2: { // Employee Login
                string email, password;
                cout << "Enter Email: ";
                cin >> email;
                cout << "Enter Password: ";
                cin >> password;

                User* loggedInEmployee = User::login(users, email, password);
                if (loggedInEmployee && loggedInEmployee->getRole() == "Employee") {
                    Employee* admin = dynamic_cast<Employee*>(loggedInEmployee);
                    bool adminMenuActive = true;
                    while (adminMenuActive) {
                        cout << "1. Add Room\n";
                        cout << "2. Delete Room\n";
                        cout << "3. View Available Rooms\n";
                        cout << "4. View Check-Ins and Check-Outs\n";
                        cout << "5. Generate Report\n";
                        cout << "6. Logout\n";
                        cout << "Enter your choice: ";
                        int adminChoice;
                        cin >> adminChoice;
                        switch (adminChoice) {
                            case 1: {
                                cout << "----------Park Inn Lodge Adding Rooms----------\n";
                                admin->addRoom(rooms);
                                break;
                            }
                            case 2: {
                                cout << "----------Park Inn Lodge Deleting Rooms----------\n";
                                admin->deleteRoom(rooms);
                                break;
                            }
                            case 3: {
                                cout << "----------Park Inn Lodge Available Rooms----------\n";
                                for (size_t i = 0; i < rooms.size(); ++i) {
                                    rooms[i]->displayRoomInfo();
                                    cout << endl;
                                }
                                break;
                            }
                            case 4: {
                                cout << "----------Park Inn Lodge Viewing Check-in and Check-out----------\n";
                                admin->viewCheckInOut();
                                break;
                            }
                            case 5: {
                                cout << "----------Park Inn Lodge Generate Report----------\n";
                                admin->generateReport();
                                break;
                            }
                            case 6:
                                adminMenuActive = false;
                                break;
                            default:
                                cout << "Invalid option.\n";
                        }
                    }
                }
                break;
            }
            case 3: { // Register as Customer
                string name, email, password;
                cout << "Enter your Name: ";
                cin >> name;
                cout << "Enter your Email: ";
                cin >> email;
                cout << "Enter your Password: ";
                cin >> password;

                User* newCustomer = new Customer(name, email, password);
                newCustomer->createAccount();
                users.push_back(newCustomer);
                cout << "Customer account created successfully!\n";
                break;
            }
            case 4:
                running = false;
                break;
            default:
                cout << "Invalid option. Try again.\n";
        }
    }

    // Cleanup memory (deleting rooms, users, etc.)
    for (auto user : users) delete user;
    for (auto room : rooms) delete room;

    return 0;
}
