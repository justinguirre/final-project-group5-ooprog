#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <memory>
#include <regex>
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
// + checkin/out (not implemented yet)
// - generate report (not implemented yet)

bool intIsValid(int input) {
    bool isIntValid = true;
    string inputString = to_string(input);
    if (input <= 0) {
        isIntValid = false;
    }
    for (char c: inputString) {
        if (!isdigit(c)) {
            isIntValid = false;
            break;
        }
    }
    return isIntValid;
}

bool doubleIsValid(double input) {
    bool isDoubleValid = true;
    string inputString = to_string(input);

    if (input <= 0) {
        isDoubleValid = false;
    }
    for (char c : inputString) {
        if (!isdigit(c) && c != '.') {
            isDoubleValid = false;
            break;
        }
    }
    return isDoubleValid;
}

string toUpper(string str) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 32; // Convert lowercase to uppercase
        }
    }
    return str;
}

bool idIsValid(string idInput) {
    if (idInput == "") {
        return false;
    }
    for (char c : idInput) {
        if (!isalnum(c)) {
            return false;
        }
    }
    return true;
}

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
    string getBookingId() const { return bookingId; }

    void setRoomNo(const string &no) { this->roomNo = no; }
    void setRoomType(const string &type) { this->roomType = type; }
    void setRoomPrice(double p) { this->price = p; }
    void setRoomAvailability(bool available) { isAvailable = available; }
    void setBookingId(string bookingid) { this->bookingId = bookingid; } 

    virtual void displayRoomInfo() {
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

    void displayRoomInfo() override {
        Room::displayRoomInfo(); // ;)
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

    void displayRoomInfo() override {
        cout << "[ID: " << roomNo << "] " << roomType << "\n"
             << "- Price: Php " << price << "/night\n"
             << "- Features: " << features << "\n"
             << "- Availability: " << (isAvailable ? "Available" : "Not Available") << endl;
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

    void displayRoomInfo() override {
        cout << "[ID: " << roomNo << "] " << roomType << "\n"
             << "- Price: Php " << price << "/night\n"
             << "- Features: " << features << "\n"
             << "- Availability: " << (isAvailable ? "Available" : "Not Available") << endl;
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
    string paymentMethod;
    double totalPrice;
    bool hasCheckedIn;
    bool hasCheckedOut;
    int guests;

public:
    Booking(string id, string room, string from, string to, int guests, string payment, double price, string email) 
        : bookingID(id), roomNo(room), fromDate(from), toDate(to), guests(guests), paymentMethod(payment), totalPrice(price), hasCheckedIn(false) {}

    void displayBookingDetails() const {
        cout << setprecision(2) << fixed << "Booking ID: " << bookingID << endl
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
    string getRoomNo() const { return roomNo; }
    double getTotalPrice() const { return totalPrice; }
    bool getHasCheckedIn() const { return hasCheckedIn; }
    bool getHasCheckedOut() const { return hasCheckedOut; }

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
    void setHasCheckedIn(bool val) {
        this->hasCheckedIn = val;
    }

    void setHasCheckedOut(bool val) {
        this->hasCheckedOut = val;
    }
};

class User {
    vector<User*> users;
protected:
    string name, email, password, role;

public:
    User(string n, string e, string p, string r) : name(n), email(e), password(p), role(r) {}
    string getName() { return name; }
    string getEmail() const { return email; }
    string getPassword() { return password; }
    string getRole() { return role; }
    
    virtual ~User() {}

    // Getter for role
    string getRole() const { return role; }

    virtual void createAccount() = 0;

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
    vector<User*> users;
private:
    vector<Booking*> bookings;
public:
    Employee(string n, string e, string p) : User(n, e, p, "Employee") {}

    void createAccount() override {
        cout << "Employee account created for: " << name << endl;
    }

    void deleteAccount() {
        cout << "Employee account deleted for: " << name << endl;
    }

    void addRoom(vector<Room*>& rooms) {
        string roomNo, roomType, features;
        double price;

        cout << "Enter Room Number: ";
        getline(cin, roomNo);
        roomNo = toUpper(roomNo);
        cin.clear();
        cin.ignore();
        cout << "Enter Room Type: ";
        getline(cin, roomType);
        roomType = toUpper(roomType);
        cin.clear();
        cin.ignore();
        cout << "Enter Features: ";
        getline(cin, features);
        cin.clear();
        cin.ignore();
        cout << "Enter Price: ";
        (cin, price);
        cin.clear();
        cin.ignore();

        Room* newRoom = nullptr;

        if (roomType == "STANDARD") {
            newRoom = new StandardRoom(roomNo, price, features);
        } else if (roomType == "DELUXE") {
            newRoom = new DeluxeRoom(roomNo, price, features);
        } else if (roomType == "SUITE") {
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
        getline(cin, roomNo);
        roomNo = toUpper(roomNo);
        cin.clear();
        cin.ignore();

        for (auto it = rooms.begin(); it != rooms.end(); ++it) {
            if ((*it)->getRoomNo() == roomNo) {
                // delete *it;  // Delete room
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
    
    /*
    void generateReport(const vector<Booking*>& bookings) const {
      cout << "----------ParkInnLodge Report----------\n";
      cout << "**Booking Details:**\n";
      cout << "| Booking ID | Room No | Check-in | Check-out | Guests | Payment Method | Total Price |\n";
      cout << "|---|---|---|---|---|---|---|\n";
    
      // Iterate through all bookings
      for (const auto& booking : bookings) {
        cout << "|" << setw(12) << booking->getBookingID() << " |";
        cout << setw(9) << booking->getRoomNo() << " |";
        cout << setw(10) << booking->getFromDate() << " |";
        cout << setw(10) << booking->getToDate() << " |";
        cout << setw(7) << booking->getGuests() << " |";
        cout << setw(17) << booking->getPaymentMethod() << " |";
        cout << setw(13) << fixed << setprecision(2) << booking->getTotalPrice() << " |\n";
      }
    }
    */
};

class Customer : public User {
    vector<string> paymentHistory;
    vector<int> currentBookings;
    vector<string> paymentMethods;
    vector<User*> users;

public:
    vector<Booking*> bookings;
        
    Customer(string n, string e, string p) : User(n, e, p, "Customer") {}

    void createAccount() override {
        cout << "Customer account created for: " << name << endl;
    }

    bool deleteAccount(vector<User*>& users) {
    string passEntered;
    cout << "Confirm password to delete account: ";
    getline(cin, passEntered);
    cin.clear();
    cin.ignore();

    if (passEntered == password) {
        auto it = std::find_if(users.begin(), users.end(),
                              [this](const User* user) { return user->getEmail() == email; });
        if (it != users.end()) {
            users.erase(it);
            cout << "Customer account deleted for: " << name << endl;
            return true;
        } else {
            cout << "Cannot delete account: incorrect password" << endl;
            return false;
        }
    } else {
        cout << "Cannot delete account: incorrect password" << endl;
        return false;
    }
}

    void bookRoom(string roomNo, string fromDate, string toDate, int guests, string paymentMethod, double price, string email) {
        string bookingID = "B" + to_string(bookings.size() + 1); // Example of generating a booking ID
        Booking* newBooking = new Booking(bookingID, roomNo, fromDate, toDate, guests, paymentMethod, price, email);
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
                        cout << "Choose Payment Method\n1. Cash\n2. Digital Wallet\n3. Credit/Debit Card): ";
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
                // delete *it;
                bookings.erase(it);
                cout << "Booking cancelled successfully.\n";
                return;
            }
        }
        cout << "Booking ID not found.\n";
    }

    void addPaymentMethod(string paymentMethod) {
        paymentMethods.push_back(paymentMethod);
    }

    void viewBookingHistory() {
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
                if (customer.getEmail() == cust->getEmail()) {
                    cout << "Email already exists!" << endl;
                    found = true;
                    break;
                }
            }

            if (!found) {
                users.push_back(&customer);
                cout << "Account created for " << customer.getName() << endl;
            }
        }

        void addRoom(Room& room) {
            bool found = false;
            for (auto& rewm : rooms) {
                if (room.getRoomNo() == rewm->getRoomNo()) {
                    cout << "Room number already exists!" << endl;
                    found = true;
                    break;
                }
            }

            if (!found) {
                rooms.push_back(&room);
                cout << "Room " << room.getRoomNo() << " created";
            }
        }

        void editRoom(Room& room, string toEdit, string newValue) {
            if (toEdit == "ROOMNO") {
                bool found = false;
                for (auto& rewm : rooms) {
                    if (newValue == rewm->getRoomNo()) {
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

        void deleteRoom(Room& roomToDelete) {
            auto it = remove_if(rooms.begin(), rooms.end(),
                [&roomToDelete](Room* room) {
                    return room->getRoomNo() == roomToDelete.getRoomNo();  // Compare by room number
                });

            // Check if the room was found and removed
            if (it != rooms.end()) {
                rooms.erase(it, rooms.end());  // Erase the element from the vector
                cout << "Room deleted successfully!" << endl;
            } else {
                cout << "Room not found!" << endl;
            }
        }

        void bookRoom(Booking& booking) {
            bookings.push_back(&booking);
            cout << "Booking success!" << endl;
        }

        void viewAvailableRooms() {
            if (rooms.empty()) {
                cout << "No rooms available." << endl;
                return;
            }
            for (const auto& room : rooms) {
                if (room->getRoomAvailability()) {
                    room->displayRoomInfo();
                }
            }
        }

         void viewCheckIns(const vector<pair<string, string>>& checkIns) const {
        cout << "------ Check-Ins ------\n";
        if (checkIns.empty()) {
            cout << "No check-ins to display.\n";
            return;
        }
        for (const auto& entry : checkIns) {
            cout << "Guest Name: " << entry.first << ", Room No: " << entry.second << endl;
        }
    }

    void viewCheckOuts(const vector<pair<string, string>>& checkOuts) const {
        cout << "------ Check-Outs ------\n";
        if (checkOuts.empty()) {
            cout << "No check-outs to display.\n";
            return;
        }
        for (const auto& entry : checkOuts) {
            cout << "Guest Name: " << entry.first << ", Room No: " << entry.second << endl;
        }
    }
        
        const vector<Booking*>& getBookings() const {
            return bookings;
        }

};

bool isValidRoomID(const string& roomID);
bool isValidDate(const string& date);

void display() {
    vector<User*> users;
    vector<Room*> rooms;
    bool running = true;

    users.push_back(new Employee("Employee Park Inn Lodge", "admin@example.com", "pil123"));
    users.push_back(new Customer("John Doe", "john@example.com", "pil456"));

    while (running) {
        cout << "Hotel Management System\n";
        cout << "1. Guest Login\n";
        cout << "2. Employee Login\n";
        cout << "3. Register as Customer\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        int choice;
        (cin, choice);
        cin.clear();
        cin.ignore();

        switch (choice) {
            case 1: { // Guest Login
                string email, password;
                cout << "Enter Email: ";
                getline(cin, email);
                email = toUpper(email);
                cin.clear();
                cin.ignore();
                cout << "Enter Password: ";
                getline(cin, password);
                cin.clear();
                cin.ignore();

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
                        (cin, guestOption);
                        cin.clear();
                        cin.ignore();

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

                                do {
                                    cout << "Enter the Room ID you want to book: ";
                                    cin >> roomNo;
                                if (roomNo.empty()) {
                                    cout << "Room ID cannot be empty. Please enter a valid Room ID.\n";
                                    }
                                } while (roomNo.empty());

    
                                auto isValidDate = [](const string& date) -> bool {
                                    if (date.length() != 10 || date[4] != '-' || date[7] != '-') return false;
                                    for (int i = 0; i < date.length(); ++i) {
                                        if ((i != 4 && i != 7) && !isdigit(date[i])) return false;
                                    }
                                    return true;
                                };

                                do {
                                    cout << "Enter Check-in Date (YYYY-MM-DD): ";
                                    cin >> fromDate;
                                if (!isValidDate(fromDate)) {
                                    cout << "Invalid date format. Please use YYYY-MM-DD.\n";
                                    }
                                } while (!isValidDate(fromDate));

                                do {
                                    cout << "Enter Check-out Date (YYYY-MM-DD): ";
                                    cin >> toDate;
                                if (!isValidDate(toDate)) {
                                    cout << "Invalid date format. Please use YYYY-MM-DD.\n";
                                }
                                    } while (!isValidDate(toDate));

    
                                do {
                                    cout << "Enter the Number of Guests (maximum 10): ";
                                    cin >> guests;
                                    if (guests <= 0 || guests > 10) {
                                        cout << "Invalid number of guests. Please enter a value between 1 and 10.\n";
                                    }
                                    } while (guests <= 0 || guests > 10);

    
                                    int paymentChoice;
                                do {
                                    cout << "Choose Payment Method (1: Cash, 2: Gcash, 3: Card): ";
                                    cin >> paymentChoice;
                                    if (paymentChoice < 1 || paymentChoice > 3) {
                                        cout << "Invalid payment choice. Please select 1, 2, or 3.\n";
                                    }
                                } while (paymentChoice < 1 || paymentChoice > 3);

                                switch (paymentChoice) {
                                    case 1:
                                        paymentMethod = "Cash";
                                        break;
                                    case 2:
                                        paymentMethod = "Gcash";
                                        break;
                                    case 3: {
                                        
                                        string cardNumber, expiration, pin;
                                        bool isCredit;
                                        
                                        int cardTypeChoice;
                                        do {
                                         cout << "Select Card Type (1: Credit, 2: Debit): ";
                                         cin >> cardTypeChoice;
                                        if (cardTypeChoice == 1) {
                                         isCredit = true;
                                         paymentMethod = "Credit Card";
                                        } else if (cardTypeChoice == 2) {
                                         isCredit = false;
                                         paymentMethod = "Debit Card";
                                        } else {
                                        cout << "Invalid choice. Please select 1 for Credit or 2 for Debit.\n";
                                             }
                                        } while (cardTypeChoice != 1 && cardTypeChoice != 2);
                                        
                                        do {
                                            cout << "Enter Card Number (16 digits): ";
                                            cin >> cardNumber;
                                            if (cardNumber.length() != 16 || !all_of(cardNumber.begin(), cardNumber.end(), ::isdigit)) {
                                                cout << "Invalid card number. It must be exactly 16 digits.\n";
                                            }
                                        } while (cardNumber.length() != 16 || !all_of(cardNumber.begin(), cardNumber.end(), ::isdigit));

                                        
                                        do {
                                            cout << "Enter Expiration Date (MM/YY): ";
                                            cin >> expiration;

                                            regex expPattern("^\\d{2}/\\d{2}$");
                                            if (!regex_match(expiration, expPattern)) {
                                                cout << "Invalid expiration date format. Use MM/YY.\n";
                                                continue;
                                            }

                                            int expMonth, expYear;
                                            sscanf(expiration.c_str(), "%d/%d", &expMonth, &expYear);
                                            if (expMonth < 1 || expMonth > 12) {
                                                cout << "Invalid month in expiration date. Please try again.\n";
                                                continue;
                                            }

                                           
                                            time_t now = time(nullptr);
                                            tm* current = localtime(&now);
                                            int currentYear = (current->tm_year % 100); 
                                            int currentMonth = current->tm_mon + 1;    

                                            if (expYear < currentYear || (expYear == currentYear && expMonth < currentMonth)) {
                                                cout << "Card is expired. Please use a valid card.\n";
                                                continue;
                                            }
                                            break;
                                        } while (true);

                                      
                                        do {
                                            cout << "Enter Card PIN (4 digits): ";
                                            cin >> pin;
                                            if (pin.length() != 4 || !all_of(pin.begin(), pin.end(), ::isdigit)) {
                                                cout << "Invalid PIN. It must be exactly 4 digits.\n";
                                            }
                                        } while (pin.length() != 4 || !all_of(pin.begin(), pin.end(), ::isdigit));

                                        paymentMethod = "Debit Card"; 
                                        break;
                                    }
                                }

                                double price = 2000; 
                                customer->bookRoom(roomNo, fromDate, toDate, guests, paymentMethod, price, customer->getEmail());
                                break;

                            }
                            case 3: { // Edit Booking
                                string bookingID;
                                cout << "----------Park Inn Lodge Edit Booking----------\n";
                                cout << "Enter Booking ID to edit: ";
                                getline(cin, bookingID);
                                bookingID = toUpper(bookingID);
                                cin.clear();
                                cin.ignore();
                                // Add logic to edit booking details here.
                                break;
                            }
                            case 4: { // Cancel Booking
                                string bookingID;
                                cout << "----------Park Inn Lodge Cancel Booking----------\n";
                                cout << "Enter Booking ID to cancel: ";
                                getline(cin, bookingID);
                                bookingID = toUpper(bookingID);
                                cin.clear();
                                cin.ignore();
                                customer->cancelBooking(bookingID);
                                break;
                            }
                            case 5: { // View Booking and Payment History
                                cout << "----------Park Inn Lodge Booking History----------\n";
                                customer->viewBookingHistory();
                                break;
                            }
                            case 6: { // Delete Account
                                string passEntered;
                                cout << "Enter password to delete account: ";
                                getline(cin, passEntered);
                                cin.clear();
                                cin.ignore();
                                
                                if (customer->getPassword() == passEntered) {
                                    if (customer->deleteAccount(users)) {
                                        cout << "Account deleted." << endl;
                                        guestMenu = false;
                                    }
                                } else {
                                    cout << "Cannot delete account: incorrect password" << endl;
                                }
                                break;
                            }
                            case 7: { // Logout
                                guestMenu = false;
                                break;
                            }
                            case 69: { // Spawn rooms
                                rooms.push_back(new DeluxeRoom("101", 5000.0));
                                rooms.push_back(new StandardRoom("102", 3000.0));
                                rooms.push_back(new SuiteRoom("201", 10000.0));
                                cout << "thank you beyoncé 😭🙏" << endl;
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
                getline(cin, email);
                email = toUpper(email);
                cin.clear();
                cin.ignore();
                cout << "Enter Password: ";
                getline(cin, password);

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
                        (cin, adminChoice);
                        cin.clear();
                        cin.ignore();
                        switch (adminChoice) {
                            case 1: {
                                cout << "----------Park Inn Lodge Adding Rooms----------\n";
                                admin->addRoom(rooms);
                                break;
                            }
                            case 2: {
                                string passEntered;
                                cout << "----------Park Inn Lodge Deleting Rooms----------\n";
                                cout << "Enter password to delete room: ";
                                getline(cin, passEntered);
                                cin.clear();
                                cin.ignore();
                                
                                if (admin->getPassword() == passEntered) {
                                    admin->deleteRoom(rooms);
                                    cout << "Deleted room." << endl;
                                } else {
                                    cout << "Cannot delete room: incorrect password" << endl;
                                }
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
                                // admin->generateReport();
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
                getline(cin, name);
                name = toUpper(name);
                cin.clear();
                cin.ignore();
                cout << "Enter your Email: ";
                getline(cin, email);
                name = toUpper(email);
                cin.clear();
                cin.ignore();
                cout << "Enter your Password: ";
                getline(cin, password);
                cin.clear();
                cin.ignore();

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
}

int main() {
    display();

}
