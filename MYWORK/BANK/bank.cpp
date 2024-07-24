#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>  // For std::remove_if

class BankAccount {
public:
    int id;
    std::string name;
    double balance;

    BankAccount(int i, const std::string& n, double b)
        : id(i), name(n), balance(b) {}
};

class BankAccountManagementSystem {
private:
    std::vector<BankAccount> accounts;

    // Make findAccount a const member function
    const BankAccount* findAccount(int id) const {
        for (const auto& account : accounts) {
            if (account.id == id) return &account;
        }
        return nullptr;
    }

public:
    void openAccount(int id, const std::string& name, double balance) {
        accounts.emplace_back(id, name, balance);
        std::cout << "Account opened successfully.\n";
    }

    void closeAccount(int id) {
        auto it = std::remove_if(accounts.begin(), accounts.end(), [id](const BankAccount& a) { return a.id == id; });
        if (it != accounts.end()) {
            accounts.erase(it, accounts.end());
            std::cout << "Account closed successfully.\n";
        } else {
            std::cout << "Account not found.\n";
        }
    }

    void deposit(int id, double amount) {
        BankAccount* account = const_cast<BankAccount*>(findAccount(id));
        if (account) {
            account->balance += amount;
            std::cout << "Deposited $" << amount << " to account " << id << ".\n";
        } else {
            std::cout << "Account not found.\n";
        }
    }

    void withdraw(int id, double amount) {
        BankAccount* account = const_cast<BankAccount*>(findAccount(id));
        if (account) {
            if (account->balance >= amount) {
                account->balance -= amount;
                std::cout << "Withdrew $" << amount << " from account " << id << ".\n";
            } else {
                std::cout << "Insufficient balance.\n";
            }
        } else {
            std::cout << "Account not found.\n";
        }
    }

    void balanceInquiry(int id) const {
        const BankAccount* account = findAccount(id);
        if (account) {
            std::cout << "Account ID: " << account->id << "\nName: " << account->name
                      << "\nBalance: $" << account->balance << std::endl;
        } else {
            std::cout << "Account not found.\n";
        }
    }

    void miniStatement(int id) const {
        const BankAccount* account = findAccount(id);
        if (account) {
            std::cout << "Mini Statement for Account ID: " << account->id
                      << "\nName: " << account->name << "\nBalance: $" << account->balance << std::endl;
        } else {
            std::cout << "Account not found.\n";
        }
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& account : accounts) {
                file << account.id << "," << account.name << "," << account.balance << "\n";
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
                std::stringstream ss(line);
                int id;
                std::string name;
                double balance;
                std::getline(ss, name, ',');
                ss >> id;
                ss.ignore();
                ss >> balance;
                accounts.emplace_back(id, name, balance);
            }
            file.close();
            std::cout << "Data loaded successfully.\n";
        } else {
            std::cout << "Unable to open file.\n";
        }
    }
};

int main() {
    BankAccountManagementSystem system;

    int choice;
    do {
        std::cout << "\n1. Open Account\n2. Close Account\n3. Deposit\n4. Withdraw\n5. Balance Inquiry\n6. Mini Statement\n7. Save Data\n8. Load Data\n0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        int id;
        double amount;
        std::string filename, name;

        switch (choice) {
            case 1:
                std::cout << "Enter Account ID: ";
                std::cin >> id;
                std::cin.ignore();
                std::cout << "Enter Account Name: ";
                std::getline(std::cin, name);
                std::cout << "Enter Initial Balance: ";
                std::cin >> amount;
                system.openAccount(id, name, amount);
                break;
            case 2:
                std::cout << "Enter Account ID to close: ";
                std::cin >> id;
                system.closeAccount(id);
                break;
            case 3:
                std::cout << "Enter Account ID to deposit into: ";
                std::cin >> id;
                std::cout << "Enter Amount to Deposit: ";
                std::cin >> amount;
                system.deposit(id, amount);
                break;
            case 4:
                std::cout << "Enter Account ID to withdraw from: ";
                std::cin >> id;
                std::cout << "Enter Amount to Withdraw: ";
                std::cin >> amount;
                system.withdraw(id, amount);
                break;
            case 5:
                std::cout << "Enter Account ID for balance inquiry: ";
                std::cin >> id;
                system.balanceInquiry(id);
                break;
            case 6:
                std::cout << "Enter Account ID for mini statement: ";
                std::cin >> id;
                system.miniStatement(id);
                break;
            case 7:
                std::cout << "Enter filename to save data: ";
                std::cin.ignore();
                std::getline(std::cin, filename);
                system.saveToFile(filename);
                break;
            case 8:
                std::cout << "Enter filename to load data from: ";
                std::cin.ignore();
                std::getline(std::cin, filename);
                system.loadFromFile(filename);
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
