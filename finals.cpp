#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

class Room {
protected:
    string roomNo;
    string roomType;
    double price;
    bool isAvailable;
    string features;

public:
    Room(string no, string type, double p, string f)
        : roomNo(no), roomType(type), price(p), isAvailable(true), features(f) {}

    string getRoomNo() const { return roomNo; }
    string getRoomType() const { return roomType; }
    double getRoomPrice() const { return price; }
    bool getRoomAvailability() const { return isAvailable; }
    string getRoomFeatures() const { return features; }

    void setRoomNo(const string &no) { this->roomNo = no; }
    void setRoomType(const string &type) { this->roomType = type; }
    void setRoomPrice(double p) { this->price = p; }
    void setRoomAvailability(bool available) { isAvailable = available; }

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
    int guests;
    string paymentMethod;
    double totalPrice;

public:
    Booking(string id, string room, string from, string to, int guests, string payment, double price) 
        : bookingID(id), roomNo(room), fromDate(from), toDate(to), guests(guests), paymentMethod(payment), totalPrice(price) {}

    void displayBookingDetails() const {
        cout << "Booking ID: " << bookingID << endl
             << "Room: " << roomNo << endl
             << "Check-in: " << fromDate << endl
             << "Check-out: " << toDate << endl
             << "Total Price: Php " << totalPrice << endl
             << "Payment Method: " << paymentMethod << endl;
    }

    string getBookingID() const { return bookingID; }
    string getFromDate() const { return fromDate; }
    string getToDate() const { return toDate; }
    int getGuests() const { return guests; }
    string getPaymentMethod() const { return paymentMethod; }
    double getTotalPrice() const { return totalPrice; }

    // Setter methods
    void setFromDate(string newFromDate) { fromDate = newFromDate; }
    void setToDate(string newToDate) { toDate = newToDate; }
    void setGuests(int newGuests) { guests = newGuests; }
    void setPaymentMethod(string newPaymentMethod) { paymentMethod = newPaymentMethod; }
    void setTotalPrice(double newPrice) { totalPrice = newPrice; }

    void editBookingDetails(string newFromDate, string newToDate, int newGuests, string newPaymentMethod, double newTotalPrice) {
        fromDate = newFromDate;
        toDate = newToDate;
        guests = newGuests;
        paymentMethod = newPaymentMethod;
        totalPrice = newTotalPrice;
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

    void editBooking(string bookingID) {
    for (auto& booking : bookings) {
        if (booking->getBookingID() == bookingID) {
            cout << "\nEditing Booking ID: " << bookingID << endl;
            int choice;
            bool done = false;

            while (!done) {
                // Display menu options for editing
                cout << "\nSelect the detail to edit:\n";
                cout << "1. Check-in Date\n";
                cout << "2. Check-out Date\n";
                cout << "3. Number of Guests\n";
                cout << "4. Payment Method\n";
                cout << "5. Save and Exit\n";
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                    case 1: {
                        // Edit Check-in Date
                        string newFromDate;
                        cout << "Enter new Check-in Date (YYYY-MM-DD): ";
                        cin >> newFromDate;
                        booking->editBookingDetails(newFromDate, booking->getToDate(), booking->getGuests(),
                                                    booking->getPaymentMethod(), booking->getTotalPrice());
                        cout << "Check-in date updated successfully.\n";
                        break;
                    }
                    case 2: {
                        // Edit Check-out Date
                        string newToDate;
                        cout << "Enter new Check-out Date (YYYY-MM-DD): ";
                        cin >> newToDate;
                        booking->editBookingDetails(booking->getFromDate(), newToDate, booking->getGuests(),
                                                    booking->getPaymentMethod(), booking->getTotalPrice());
                        cout << "Check-out date updated successfully.\n";
                        break;
                    }
                    case 3: {
                        // Edit Number of Guests
                        int newGuests;
                        cout << "Enter new Number of Guests: ";
                        cin >> newGuests;
                        double newPrice = 2000 * newGuests; // Example price recalculation
                        booking->editBookingDetails(booking->getFromDate(), booking->getToDate(), newGuests,
                                                    booking->getPaymentMethod(), newPrice);
                        cout << "Number of guests updated successfully.\n";
                        break;
                    }
                    case 4: {
                        // Edit Payment Method
                        string newPaymentMethod;
                        cout << "Choose new Payment Method (1: Cash, 2: Digital Wallet, 3: Credit/Debit Card): ";
                        int paymentChoice;
                        cin >> paymentChoice;
                        switch (paymentChoice) {
                            case 1: newPaymentMethod = "Cash"; break;
                            case 2: newPaymentMethod = "Digital Wallet"; break;
                            case 3: newPaymentMethod = "Credit/Debit Card"; break;
                            default: newPaymentMethod = booking->getPaymentMethod(); break;
                        }
                        booking->editBookingDetails(booking->getFromDate(), booking->getToDate(), booking->getGuests(),
                                                    newPaymentMethod, booking->getTotalPrice());
                        cout << "Payment method updated successfully.\n";
                        break;
                    }
                    case 5: {
                        // Save changes and exit
                        done = true;
                        cout << "Changes saved successfully.\n";
                        break;
                    }
                    default: {
                        cout << "Invalid choice. Please try again.\n";
                    }
                }
            }
            return;
        }
    }
    cout << "Booking ID not found.\n";
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

    void viewBookingHistory() const {
        cout << "Booking History for " << name << ":\n";
        for (auto& booking : bookings) {
            booking->displayBookingDetails();
        }
    }
};

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
        cout << "\n========== Hotel Management System ==========\n";
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
                        cout << "6. Delete Account\n";
                        cout << "7. Logout\n";
                        cout << "Choose an option: ";
                        int guestOption;
                        cin >> guestOption;

                        switch (guestOption) {
                            case 1: { // View Available Rooms
                                cout << "\n----------[Hotel Name] Available Rooms----------\n";
                                for (size_t i = 0; i < rooms.size(); ++i) {
                                    rooms[i]->displayRoomInfo();
                                    cout << endl;
                                }
                                break;
                            }
                            case 2: { // Book Room
                                string roomNo, fromDate, toDate, paymentMethod;
                                int guests;

                                cout << "\n----------Park Inn Lodge Book Room----------\n";

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
                                cout << "\n----------Park Inn Lodge Edit Booking----------\n";
                                cout << "Enter Booking ID to edit: ";
                                cin >> bookingID;
                                customer->editBooking(bookingID);
                                break;
                            }
                            case 4: { // Cancel Booking
                                string bookingID;
                                cout << "\n----------Park Inn Lodge Cancel Booking----------\n";
                                cout << "Enter Booking ID to cancel: ";
                                cin >> bookingID;
                                customer->cancelBooking(bookingID);
                                break;
                            }
                            case 5: { // View Booking and Payment History
                                cout << "\n----------Park Inn Lodge Booking History----------\n";
                                customer->viewBookingHistory();
                                break;
                            }
                            case 6: { // Delete Account
                                customer->deleteAccount();
                                guestMenu = false;
                                break;
                            }
                            case 7: { // Logout
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
                        cout << "\n========== Hotel Management System - Employee Menu ==========\n";
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
                                cout << "\n----------Park Inn Lodge Adding Rooms----------\n";
                                admin->addRoom(rooms);
                                break;
                            }
                            case 2: {
                                cout << "\n----------Park Inn Lodge Deleting Rooms----------\n";
                                admin->deleteRoom(rooms);
                                break;
                            }
                            case 3: {
                                cout << "\n----------Park Inn Lodge Available Rooms----------\n";
                                for (size_t i = 0; i < rooms.size(); ++i) {
                                    rooms[i]->displayRoomInfo();
                                    cout << endl;
                                }
                                break;
                            }
                            case 4: {
                                cout << "\n----------Park Inn Lodge Viewing Check-in and Check-out----------\n";
                                admin->viewCheckInOut();
                                break;
                            }
                            case 5: {
                                cout << "\n----------Park Inn Lodge Generate Report----------\n";
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
