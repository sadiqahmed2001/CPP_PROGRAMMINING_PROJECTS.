#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

class Property {
public:
    std::string id;
    std::string address;
    double price;
    std::string type; // Sale or Rent

    Property(const std::string& i, const std::string& addr, double p, const std::string& t)
        : id(i), address(addr), price(p), type(t) {}

    void printDetails() const {
        std::cout << "Property ID: " << id << "\nAddress: " << address 
                  << "\nPrice: $" << price << "\nType: " << type << std::endl;
    }
};

class Client {
public:
    std::string id;
    std::string name;
    std::string phone;

    Client(const std::string& i, const std::string& n, const std::string& p)
        : id(i), name(n), phone(p) {}

    void printDetails() const {
        std::cout << "Client ID: " << id << "\nName: " << name 
                  << "\nPhone: " << phone << std::endl;
    }
};

class Transaction {
public:
    std::string id;
    std::string propertyId;
    std::string clientId;
    std::string date;
    double amount;

    Transaction(const std::string& i, const std::string& pId, const std::string& cId, const std::string& d, double amt)
        : id(i), propertyId(pId), clientId(cId), date(d), amount(amt) {}

    void printDetails() const {
        std::cout << "Transaction ID: " << id << "\nProperty ID: " << propertyId 
                  << "\nClient ID: " << clientId << "\nDate: " << date 
                  << "\nAmount: $" << amount << std::endl;
    }
};

class RealEstateManagementSystem {
private:
    std::vector<Property> properties;
    std::vector<Client> clients;
    std::vector<Transaction> transactions;

    Property* findProperty(const std::string& id) {
        for (auto& property : properties) {
            if (property.id == id) return &property;
        }
        return nullptr;
    }

    Client* findClient(const std::string& id) {
        for (auto& client : clients) {
            if (client.id == id) return &client;
        }
        return nullptr;
    }

    Transaction* findTransaction(const std::string& id) {
        for (auto& transaction : transactions) {
            if (transaction.id == id) return &transaction;
        }
        return nullptr;
    }

public:
    void addProperty(const std::string& id, const std::string& address, double price, const std::string& type) {
        properties.emplace_back(id, address, price, type);
        std::cout << "Property added successfully.\n";
    }

    void updateProperty(const std::string& id, const std::string& address, double price, const std::string& type) {
        Property* property = findProperty(id);
        if (property) {
            property->address = address;
            property->price = price;
            property->type = type;
            std::cout << "Property updated successfully.\n";
        } else {
            std::cout << "Property not found.\n";
        }
    }

    void deleteProperty(const std::string& id) {
        auto it = std::remove_if(properties.begin(), properties.end(), [&id](const Property& p) { return p.id == id; });
        if (it != properties.end()) {
            properties.erase(it, properties.end());
            std::cout << "Property deleted successfully.\n";
        } else {
            std::cout << "Property not found.\n";
        }
    }

    void addClient(const std::string& id, const std::string& name, const std::string& phone) {
        clients.emplace_back(id, name, phone);
        std::cout << "Client added successfully.\n";
    }

    void updateClient(const std::string& id, const std::string& name, const std::string& phone) {
        Client* client = findClient(id);
        if (client) {
            client->name = name;
            client->phone = phone;
            std::cout << "Client updated successfully.\n";
        } else {
            std::cout << "Client not found.\n";
        }
    }

    void deleteClient(const std::string& id) {
        auto it = std::remove_if(clients.begin(), clients.end(), [&id](const Client& c) { return c.id == id; });
        if (it != clients.end()) {
            clients.erase(it, clients.end());
            std::cout << "Client deleted successfully.\n";
        } else {
            std::cout << "Client not found.\n";
        }
    }

    void listProperties() const {
        for (const auto& property : properties) {
            property.printDetails();
            std::cout << std::endl;
        }
    }

    void searchProperties(const std::string& criteria) const {
        for (const auto& property : properties) {
            if (property.address.find(criteria) != std::string::npos || 
                std::to_string(property.price).find(criteria) != std::string::npos || 
                property.type.find(criteria) != std::string::npos) {
                property.printDetails();
                std::cout << std::endl;
            }
        }
    }

    void recordTransaction(const std::string& id, const std::string& propertyId, const std::string& clientId, const std::string& date, double amount) {
        if (findProperty(propertyId) && findClient(clientId)) {
            transactions.emplace_back(id, propertyId, clientId, date, amount);
            std::cout << "Transaction recorded successfully.\n";
        } else {
            std::cout << "Property or Client not found.\n";
        }
    }

    void viewTransactions() const {
        for (const auto& transaction : transactions) {
            transaction.printDetails();
            std::cout << std::endl;
        }
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& property : properties) {
                file << "P," << property.id << "," << property.address << "," << property.price << "," << property.type << "\n";
            }
            for (const auto& client : clients) {
                file << "C," << client.id << "," << client.name << "," << client.phone << "\n";
            }
            for (const auto& transaction : transactions) {
                file << "T," << transaction.id << "," << transaction.propertyId << "," << transaction.clientId << "," << transaction.date << "," << transaction.amount << "\n";
            }
            file.close();
            std::cout << "Data saved successfully.\n";
        } else {
            std::cout << "Unable to open file.\n";
        }
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                std::istringstream ss(line);
                std::string type;
                std::getline(ss, type, ',');
                if (type == "P") {
                    std::string id, address, type;
                    double price;
                    std::getline(ss, id, ',');
                    std::getline(ss, address, ',');
                    ss >> price;
                    ss.ignore();
                    std::getline(ss, type);
                    properties.emplace_back(id, address, price, type);
                } else if (type == "C") {
                    std::string id, name, phone;
                    std::getline(ss, id, ',');
                    std::getline(ss, name, ',');
                    std::getline(ss, phone);
                    clients.emplace_back(id, name, phone);
                } else if (type == "T") {
                    std::string id, propertyId, clientId, date;
                    double amount;
                    std::getline(ss, id, ',');
                    std::getline(ss, propertyId, ',');
                    std::getline(ss, clientId, ',');
                    std::getline(ss, date, ',');
                    ss >> amount;
                    transactions.emplace_back(id, propertyId, clientId, date, amount);
                }
            }
            file.close();
            std::cout << "Data loaded successfully.\n";
        } else {
            std::cout << "Unable to open file.\n";
        }
    }
};

int main() {
    RealEstateManagementSystem system;

    int choice;
    do {
        std::cout << "\n1. Add Property\n2. Update Property\n3. Delete Property\n4. Add Client\n5. Update Client\n6. Delete Client\n7. List Properties\n8. Search Properties\n9. Record Transaction\n10. View Transactions\n11. Save Data\n12. Load Data\n0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Clear the input buffer to prevent issues with `std::cin.ignore()`
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        switch (choice) {
            case 1: {
                std::string id, address, type;
                double price;
                std::cout << "Enter Property ID: ";
                std::getline(std::cin, id);
                std::cout << "Enter Address: ";
                std::getline(std::cin, address);
                std::cout << "Enter Price: ";
                std::cin >> price;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter Type (Sale/Rent): ";
                std::getline(std::cin, type);
                system.addProperty(id, address, price, type);
                break;
            }
            case 2: {
                std::string id, address, type;
                double price;
                std::cout << "Enter Property ID: ";
                std::getline(std::cin, id);
                std::cout << "Enter New Address: ";
                std::getline(std::cin, address);
                std::cout << "Enter New Price: ";
                std::cin >> price;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter New Type (Sale/Rent): ";
                std::getline(std::cin, type);
                system.updateProperty(id, address, price, type);
                break;
            }
            case 3: {
                std::string id;
                std::cout << "Enter Property ID to delete: ";
                std::getline(std::cin, id);
                system.deleteProperty(id);
                break;
            }
            case 4: {
                std::string id, name, phone;
                std::cout << "Enter Client ID: ";
                std::getline(std::cin, id);
                std::cout << "Enter Name: ";
                std::getline(std::cin, name);
                std::cout << "Enter Phone: ";
                std::getline(std::cin, phone);
                system.addClient(id, name, phone);
                break;
            }
            case 5: {
                std::string id, name, phone;
                std::cout << "Enter Client ID: ";
                std::getline(std::cin, id);
                std::cout << "Enter New Name: ";
                std::getline(std::cin, name);
                std::cout << "Enter New Phone: ";
                std::getline(std::cin, phone);
                system.updateClient(id, name, phone);
                break;
            }
            case 6: {
                std::string id;
                std::cout << "Enter Client ID to delete: ";
                std::getline(std::cin, id);
                system.deleteClient(id);
                break;
            }
            case 7:
                system.listProperties();
                break;
            case 8: {
                std::string criteria;
                std::cout << "Enter search criteria: ";
                std::getline(std::cin, criteria);
                system.searchProperties(criteria);
                break;
            }
            case 9: {
                std::string id, propertyId, clientId, date;
                double amount;
                std::cout << "Enter Transaction ID: ";
                std::getline(std::cin, id);
                std::cout << "Enter Property ID: ";
                std::getline(std::cin, propertyId);
                std::cout << "Enter Client ID: ";
                std::getline(std::cin, clientId);
                std::cout << "Enter Date (YYYY-MM-DD): ";
                std::getline(std::cin, date);
                std::cout << "Enter Amount: ";
                std::cin >> amount;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                system.recordTransaction(id, propertyId, clientId, date, amount);
                break;
            }
            case 10:
                system.viewTransactions();
                break;
            case 11: {
                std::string filename;
                std::cout << "Enter filename to save data: ";
                std::getline(std::cin, filename);
                system.saveToFile(filename);
                break;
            }
            case 12: {
                std::string filename;
                std::cout << "Enter filename to load data: ";
                std::getline(std::cin, filename);
                system.loadFromFile(filename);
                break;
            }
            case 0:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}


