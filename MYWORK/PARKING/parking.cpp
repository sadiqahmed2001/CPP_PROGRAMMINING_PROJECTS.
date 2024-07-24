#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <cmath> 

class Vehicle {
public:
    std::string registrationNumber;
    std::string ownerName;
    std::string slotNumber;
    time_t entryTime;
    bool isParked;

    Vehicle(const std::string& regNum, const std::string& owner, const std::string& slot)
        : registrationNumber(regNum), ownerName(owner), slotNumber(slot), isParked(true) {
        entryTime = std::time(nullptr);  // Set current time as entry time
    }

    void exitParking() {
        isParked = false;
    }

    double calculateCharge() const {
        if (!isParked) {
            double hours = std::difftime(std::time(nullptr), entryTime) / 3600;
            return std::ceil(hours) * 10.0;  // Charge is $10 per hour
        }
        return 0.0;
    }

    void printDetails() const {
        std::cout << "Registration Number: " << registrationNumber << "\nOwner Name: " << ownerName
                  << "\nSlot Number: " << slotNumber << "\nIs Parked: " << (isParked ? "Yes" : "No")
                  << "\nEntry Time: " << std::ctime(&entryTime) << std::endl;
    }
};

class VehicleParkingSystem {
private:
    std::vector<Vehicle> vehicles;
    std::vector<std::string> parkingSlots;

    Vehicle* findVehicle(const std::string& regNum) {
        for (auto& vehicle : vehicles) {
            if (vehicle.registrationNumber == regNum) return &vehicle;
        }
        return nullptr;
    }

    const Vehicle* findVehicle(const std::string& regNum) const {
        for (const auto& vehicle : vehicles) {
            if (vehicle.registrationNumber == regNum) return &vehicle;
        }
        return nullptr;
    }

public:
    VehicleParkingSystem(int numSlots) {
        for (int i = 1; i <= numSlots; ++i) {
            parkingSlots.push_back("Slot " + std::to_string(i));
        }
    }

    void allocateSlot(const std::string& regNum, const std::string& ownerName) {
        if (findVehicle(regNum)) {
            std::cout << "Vehicle is already parked.\n";
            return;
        }
        for (const auto& slot : parkingSlots) {
            if (findVehicleInSlot(slot).empty()) {
                vehicles.emplace_back(regNum, ownerName, slot);
                std::cout << "Vehicle parked in " << slot << ".\n";
                return;
            }
        }
        std::cout << "No available parking slots.\n";
    }

    void freeSlot(const std::string& regNum) {
        Vehicle* vehicle = findVehicle(regNum);
        if (vehicle && vehicle->isParked) {
            vehicle->exitParking();
            std::cout << "Vehicle removed from " << vehicle->slotNumber << ".\n";
        } else if (vehicle) {
            std::cout << "Vehicle is already not parked.\n";
        } else {
            std::cout << "Vehicle not found.\n";
        }
    }

    void addVehicle(const std::string& regNum, const std::string& ownerName, const std::string& slot) {
        if (findVehicle(regNum)) {
            std::cout << "Vehicle with this registration number already exists.\n";
            return;
        }
        vehicles.emplace_back(regNum, ownerName, slot);
        std::cout << "Vehicle added successfully.\n";
    }

    void updateVehicle(const std::string& regNum, const std::string& newOwnerName) {
        Vehicle* vehicle = findVehicle(regNum);
        if (vehicle) {
            vehicle->ownerName = newOwnerName;
            std::cout << "Vehicle details updated successfully.\n";
        } else {
            std::cout << "Vehicle not found.\n";
        }
    }

    void removeVehicle(const std::string& regNum) {
        auto it = std::remove_if(vehicles.begin(), vehicles.end(), [&regNum](const Vehicle& v) { return v.registrationNumber == regNum; });
        if (it != vehicles.end()) {
            vehicles.erase(it, vehicles.end());
            std::cout << "Vehicle removed successfully.\n";
        } else {
            std::cout << "Vehicle not found.\n";
        }
    }

    void printBill(const std::string& regNum) const {
        const Vehicle* vehicle = findVehicle(regNum);
        if (vehicle) {
            double charge = vehicle->calculateCharge();
            if (charge > 0) {
                std::cout << "Bill for " << regNum << ": $" << std::fixed << std::setprecision(2) << charge << std::endl;
            } else {
                std::cout << "Vehicle is still parked.\n";
            }
        } else {
            std::cout << "Vehicle not found.\n";
        }
    }

    void searchVehicle(const std::string& regNum) const {
        const Vehicle* vehicle = findVehicle(regNum);
        if (vehicle) {
            vehicle->printDetails();
        } else {
            std::cout << "Vehicle not found.\n";
        }
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& vehicle : vehicles) {
                file << vehicle.registrationNumber << "," << vehicle.ownerName << "," << vehicle.slotNumber << "," << vehicle.entryTime << "," << vehicle.isParked << "\n";
            }
            std::cout << "Data saved successfully.\n";
        } else {
            std::cout << "Unable to open file.\n";
        }
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            vehicles.clear();
            std::string line;
            while (std::getline(file, line)) {
                std::istringstream ss(line);
                std::string token;
                std::getline(ss, token, ',');
                std::string regNum = token;
                std::getline(ss, token, ',');
                std::string ownerName = token;
                std::getline(ss, token, ',');
                std::string slot = token;
                std::getline(ss, token, ',');
                time_t entryTime = std::stoll(token);
                std::getline(ss, token, ',');
                bool isParked = token == "1";

                Vehicle vehicle(regNum, ownerName, slot);
                vehicle.entryTime = entryTime;
                vehicle.isParked = isParked;

                vehicles.push_back(vehicle);
            }
            std::cout << "Data loaded successfully.\n";
        } else {
            std::cout << "Unable to open file.\n";
        }
    }

private:
    std::string findVehicleInSlot(const std::string& slot) const {
        for (const auto& vehicle : vehicles) {
            if (vehicle.slotNumber == slot && vehicle.isParked) {
                return vehicle.registrationNumber;
            }
        }
        return "";
    }
};

int main() {
    VehicleParkingSystem system(10);  // Initialize system with 10 parking slots
    int choice;
    std::string regNum, ownerName, slot;
    double amount;

    do {
        std::cout << "\nVehicle Parking System\n";
        std::cout << "1. Allocate Slot\n2. Free Slot\n3. Add Vehicle\n4. Update Vehicle\n5. Remove Vehicle\n6. Print Bill\n7. Search Vehicle\n8. Save to File\n9. Load from File\n0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                std::cout << "Enter registration number: ";
                std::getline(std::cin, regNum);
                std::cout << "Enter owner name: ";
                std::getline(std::cin, ownerName);
                system.allocateSlot(regNum, ownerName);
                break;
            case 2:
                std::cout << "Enter registration number to free slot: ";
                std::getline(std::cin, regNum);
                system.freeSlot(regNum);
                break;
            case 3:
                std::cout << "Enter registration number: ";
                std::getline(std::cin, regNum);
                std::cout << "Enter owner name: ";
                std::getline(std::cin, ownerName);
                std::cout << "Enter slot number: ";
                std::getline(std::cin, slot);
                system.addVehicle(regNum, ownerName, slot);
                break;
            case 4:
                std::cout << "Enter registration number to update: ";
                std::getline(std::cin, regNum);
                std::cout << "Enter new owner name: ";
                std::getline(std::cin, ownerName);
                system.updateVehicle(regNum, ownerName);
                break;
            case 5:
                std::cout << "Enter registration number to remove: ";
                std::getline(std::cin, regNum);
                system.removeVehicle(regNum);
                break;
            case 6:
                std::cout << "Enter registration number to print bill: ";
                std::getline(std::cin, regNum);
                system.printBill(regNum);
                break;
            case 7:
                std::cout << "Enter registration number to search: ";
                std::getline(std::cin, regNum);
                system.searchVehicle(regNum);
                break;
            case 8:
                system.saveToFile("vehicles.txt");
                break;
            case 9:
                system.loadFromFile("vehicles.txt");
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
