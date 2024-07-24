#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <ctime>

class Room {
public:
    int id;
    std::string type;
    double pricePerNight;
    bool isAvailable;

    Room(int id, const std::string& type, double pricePerNight, bool isAvailable)
        : id(id), type(type), pricePerNight(pricePerNight), isAvailable(isAvailable) {}

    void display() const {
        std::cout << "Room ID: " << id << "\nType: " << type << "\nPrice per Night: " << pricePerNight << "\nAvailable: " << (isAvailable ? "Yes" : "No") << "\n";
    }
};

class Customer {
public:
    int id;
    std::string name;
    std::string email;

    Customer(int id, const std::string& name, const std::string& email)
        : id(id), name(name), email(email) {}

    void display() const {
        std::cout << "Customer ID: " << id << "\nName: " << name << "\nEmail: " << email << "\n";
    }
};

class Reservation {
public:
    int id;
    int roomId;
    int customerId;
    std::string startDate;
    std::string endDate;
    double totalAmount;

    Reservation(int id, int roomId, int customerId, const std::string& startDate, const std::string& endDate, double totalAmount)
        : id(id), roomId(roomId), customerId(customerId), startDate(startDate), endDate(endDate), totalAmount(totalAmount) {}

    void display() const {
        std::cout << "Reservation ID: " << id << "\nRoom ID: " << roomId << "\nCustomer ID: " << customerId << "\nStart Date: " << startDate << "\nEnd Date: " << endDate << "\nTotal Amount: " << totalAmount << "\n";
    }
};

class HotelReservationSystem {
private:
    std::vector<Room> rooms;
    std::vector<Customer> customers;
    std::vector<Reservation> reservations;
    int nextRoomId = 1;
    int nextCustomerId = 1;
    int nextReservationId = 1;

    bool isValidDate(const std::string& date) const {
        // Simple date validation (YYYY-MM-DD)
        if (date.size() != 10 || date[4] != '-' || date[7] != '-') return false;
        return true;
    }

    bool isDateAvailable(const std::string& startDate, const std::string& endDate, int roomId) const {
        // Simple date availability check
        for (const auto& reservation : reservations) {
            if (reservation.roomId == roomId) {
                // Check if dates overlap
                if ((startDate <= reservation.endDate && endDate >= reservation.startDate)) {
                    return false;
                }
            }
        }
        return true;
    }

    double calculateDaysDifference(const std::string& startDate, const std::string& endDate) const {
        // Dummy implementation to calculate difference (should be replaced with proper date handling)
        return 1.0; // Assuming 1 night stay for simplicity
    }

public:
    void addRoom(const std::string& type, double pricePerNight) {
        rooms.emplace_back(nextRoomId++, type, pricePerNight, true);
        std::cout << "Room added successfully.\n";
    }

    void updateRoom(int id, const std::string& newType, double newPricePerNight, bool newIsAvailable) {
        auto it = std::find_if(rooms.begin(), rooms.end(), [id](const Room& r) { return r.id == id; });
        if (it != rooms.end()) {
            it->type = newType;
            it->pricePerNight = newPricePerNight;
            it->isAvailable = newIsAvailable;
            std::cout << "Room updated successfully.\n";
        } else {
            std::cout << "Room not found.\n";
        }
    }

    void removeRoom(int id) {
        auto it = std::remove_if(rooms.begin(), rooms.end(), [id](const Room& r) { return r.id == id; });
        if (it != rooms.end()) {
            rooms.erase(it, rooms.end());
            std::cout << "Room removed successfully.\n";
        } else {
            std::cout << "Room not found.\n";
        }
    }

    void addCustomer(const std::string& name, const std::string& email) {
        customers.emplace_back(nextCustomerId++, name, email);
        std::cout << "Customer added successfully.\n";
    }

    void updateCustomer(int id, const std::string& newName, const std::string& newEmail) {
        auto it = std::find_if(customers.begin(), customers.end(), [id](const Customer& c) { return c.id == id; });
        if (it != customers.end()) {
            it->name = newName;
            it->email = newEmail;
            std::cout << "Customer updated successfully.\n";
        } else {
            std::cout << "Customer not found.\n";
        }
    }

    void removeCustomer(int id) {
        auto it = std::remove_if(customers.begin(), customers.end(), [id](const Customer& c) { return c.id == id; });
        if (it != customers.end()) {
            customers.erase(it, customers.end());
            std::cout << "Customer removed successfully.\n";
        } else {
            std::cout << "Customer not found.\n";
        }
    }

    void makeReservation(int roomId, int customerId, const std::string& startDate, const std::string& endDate) {
        if (!isValidDate(startDate) || !isValidDate(endDate)) {
            std::cout << "Invalid date format.\n";
            return;
        }
        if (!isDateAvailable(startDate, endDate, roomId)) {
            std::cout << "Room is not available for the selected dates.\n";
            return;
        }
        auto it = std::find_if(rooms.begin(), rooms.end(), [roomId](const Room& r) { return r.id == roomId; });
        if (it != rooms.end()) {
            double totalAmount = it->pricePerNight * calculateDaysDifference(startDate, endDate);
            reservations.emplace_back(nextReservationId++, roomId, customerId, startDate, endDate, totalAmount);
            it->isAvailable = false; // Mark room as unavailable
            std::cout << "Reservation made successfully.\n";
        } else {
            std::cout << "Room not found.\n";
        }
    }

    void updateReservation(int id, int newRoomId, const std::string& newStartDate, const std::string& newEndDate) {
        if (!isValidDate(newStartDate) || !isValidDate(newEndDate)) {
            std::cout << "Invalid date format.\n";
            return;
        }
        auto it = std::find_if(reservations.begin(), reservations.end(), [id](const Reservation& r) { return r.id == id; });
        if (it != reservations.end()) {
            // Free the previously booked room
            auto roomIt = std::find_if(rooms.begin(), rooms.end(), [it](const Room& r) { return r.id == it->roomId; });
            if (roomIt != rooms.end()) {
                roomIt->isAvailable = true;
            }
            // Make new reservation
            makeReservation(newRoomId, it->customerId, newStartDate, newEndDate);
            reservations.erase(it);
        } else {
            std::cout << "Reservation not found.\n";
        }
    }

    void cancelReservation(int id) {
        auto it = std::find_if(reservations.begin(), reservations.end(), [id](const Reservation& r) { return r.id == id; });
        if (it != reservations.end()) {
            auto roomIt = std::find_if(rooms.begin(), rooms.end(), [it](const Room& r) { return r.id == it->roomId; });
            if (roomIt != rooms.end()) {
                roomIt->isAvailable = true; // Mark room as available
            }
            reservations.erase(it);
            std::cout << "Reservation canceled successfully.\n";
        } else {
            std::cout << "Reservation not found.\n";
        }
    }

    void generateBill(int id) const {
        auto it = std::find_if(reservations.begin(), reservations.end(), [id](const Reservation& r) { return r.id == id; });
        if (it != reservations.end()) {
            std::cout << "Generating bill for reservation ID: " << id << "\n";
            std::cout << "Total Amount: " << it->totalAmount << "\n";
        } else {
            std::cout << "Reservation not found.\n";
        }
    }

    void displayRooms() const {
        for (const auto& room : rooms) {
            room.display();
            std::cout << "------------------------\n";
        }
    }

    void displayCustomers() const {
        for (const auto& customer : customers) {
            customer.display();
            std::cout << "------------------------\n";
        }
    }

    void displayReservations() const {
        for (const auto& reservation : reservations) {
            reservation.display();
            std::cout << "------------------------\n";
        }
    }
};

int main() {
    HotelReservationSystem system;
    int choice;
    std::string type, email, startDate, endDate;
    double price;
    int id, roomId, customerId;

    do {
        std::cout << "\nHotel Reservation System\n";
        std::cout << "1. Add Room\n2. Update Room\n3. Remove Room\n4. Add Customer\n5. Update Customer\n6. Remove Customer\n7. Make Reservation\n8. Update Reservation\n9. Cancel Reservation\n10. Generate Bill\n11. Display Rooms\n12. Display Customers\n13. Display Reservations\n0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                std::cout << "Enter room type: ";
                std::getline(std::cin, type);
                std::cout << "Enter price per night: ";
                std::cin >> price;
                std::cin.ignore();
                system.addRoom(type, price);
                break;
            case 2:
                std::cout << "Enter room ID to update: ";
                std::cin >> id;
                std::cin.ignore();
                std::cout << "Enter new room type: ";
                std::getline(std::cin, type);
                std::cout << "Enter new price per night: ";
                std::cin >> price;
                std::cout << "Is room available (1 for yes, 0 for no): ";
                bool isAvailable;
                std::cin >> isAvailable;
                std::cin.ignore();
                system.updateRoom(id, type, price, isAvailable);
                break;
            case 3:
                std::cout << "Enter room ID to remove: ";
                std::cin >> id;
                std::cin.ignore();
                system.removeRoom(id);
                break;
            case 4:
                std::cout << "Enter customer name: ";
                std::getline(std::cin, type);
                std::cout << "Enter customer email: ";
                std::getline(std::cin, email);
                system.addCustomer(type, email);
                break;
            case 5:
                std::cout << "Enter customer ID to update: ";
                std::cin >> id;
                std::cin.ignore();
                std::cout << "Enter new customer name: ";
                std::getline(std::cin, type);
                std::cout << "Enter new customer email: ";
                std::getline(std::cin, email);
                system.updateCustomer(id, type, email);
                break;
            case 6:
                std::cout << "Enter customer ID to remove: ";
                std::cin >> id;
                std::cin.ignore();
                system.removeCustomer(id);
                break;
            case 7:
                std::cout << "Enter room ID: ";
                std::cin >> roomId;
                std::cin.ignore();
                std::cout << "Enter customer ID: ";
                std::cin >> customerId;
                std::cin.ignore();
                std::cout << "Enter start date (YYYY-MM-DD): ";
                std::getline(std::cin, startDate);
                std::cout << "Enter end date (YYYY-MM-DD): ";
                std::getline(std::cin, endDate);
                system.makeReservation(roomId, customerId, startDate, endDate);
                break;
            case 8:
                std::cout << "Enter reservation ID to update: ";
                std::cin >> id;
                std::cin.ignore();
                std::cout << "Enter new room ID: ";
                std::cin >> roomId;
                std::cin.ignore();
                std::cout << "Enter new start date (YYYY-MM-DD): ";
                std::getline(std::cin, startDate);
                std::cout << "Enter new end date (YYYY-MM-DD): ";
                std::getline(std::cin, endDate);
                system.updateReservation(id, roomId, startDate, endDate);
                break;
            case 9:
                std::cout << "Enter reservation ID to cancel: ";
                std::cin >> id;
                std::cin.ignore();
                system.cancelReservation(id);
                break;
            case 10:
                std::cout << "Enter reservation ID to generate bill: ";
                std::cin >> id;
                std::cin.ignore();
                system.generateBill(id);
                break;
            case 11:
                system.displayRooms();
                break;
            case 12:
                system.displayCustomers();
                break;
            case 13:
                system.displayReservations();
                break;
            case 0:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 0);

    return 0;
}
