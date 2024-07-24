#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Contact {
public:
    std::string name;
    std::string phoneNumber;
    std::string email;

    Contact(std::string n, std::string p, std::string e) : name(n), phoneNumber(p), email(e) {}

    void display() const {
        std::cout << "Name: " << name << "\nPhone Number: " << phoneNumber << "\nEmail: " << email << "\n";
    }
};

class ContactManager {
private:
    std::vector<Contact> contacts;

public:
    void addContact(const std::string& name, const std::string& phoneNumber, const std::string& email) {
        contacts.emplace_back(name, phoneNumber, email);
        std::cout << "Contact added successfully.\n";
    }

    void searchContact(const std::string& name) const {
        auto it = std::find_if(contacts.begin(), contacts.end(), [&](const Contact& c) { return c.name == name; });
        if (it != contacts.end()) {
            it->display();
        } else {
            std::cout << "Contact not found.\n";
        }
    }

    void updateContact(const std::string& name, const std::string& newPhoneNumber, const std::string& newEmail) {
        auto it = std::find_if(contacts.begin(), contacts.end(), [&](const Contact& c) { return c.name == name; });
        if (it != contacts.end()) {
            it->phoneNumber = newPhoneNumber;
            it->email = newEmail;
            std::cout << "Contact updated successfully.\n";
        } else {
            std::cout << "Contact not found.\n";
        }
    }

    void deleteContact(const std::string& name) {
        auto it = std::remove_if(contacts.begin(), contacts.end(), [&](const Contact& c) { return c.name == name; });
        if (it != contacts.end()) {
            contacts.erase(it, contacts.end());
            std::cout << "Contact deleted successfully.\n";
        } else {
            std::cout << "Contact not found.\n";
        }
    }

    void listAllContacts() const {
        if (contacts.empty()) {
            std::cout << "No contacts to display.\n";
        } else {
            for (const auto& contact : contacts) {
                contact.display();
                std::cout << "----------------\n";
            }
        }
    }
};

int main() {
    ContactManager manager;
    int choice;
    std::string name, phoneNumber, email;

    do {
        std::cout << "Contact Management System\n";
        std::cout << "1. Add Contact\n";
        std::cout << "2. Search Contact\n";
        std::cout << "3. Update Contact\n";
        std::cout << "4. Delete Contact\n";
        std::cout << "5. List All Contacts\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // to ignore the newline character after choice input

        switch (choice) {
            case 1:
                std::cout << "Enter name: ";
                std::getline(std::cin, name);
                std::cout << "Enter phone number: ";
                std::getline(std::cin, phoneNumber);
                std::cout << "Enter email: ";
                std::getline(std::cin, email);
                manager.addContact(name, phoneNumber, email);
                break;

            case 2:
                std::cout << "Enter name to search: ";
                std::getline(std::cin, name);
                manager.searchContact(name);
                break;

            case 3:
                std::cout << "Enter name to update: ";
                std::getline(std::cin, name);
                std::cout << "Enter new phone number: ";
                std::getline(std::cin, phoneNumber);
                std::cout << "Enter new email: ";
                std::getline(std::cin, email);
                manager.updateContact(name, phoneNumber, email);
                break;

            case 4:
                std::cout << "Enter name to delete: ";
                std::getline(std::cin, name);
                manager.deleteContact(name);
                break;

            case 5:
                manager.listAllContacts();
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
