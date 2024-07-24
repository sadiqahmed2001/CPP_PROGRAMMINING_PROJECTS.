#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>

class Employee {
public:
    int id;
    std::string name;
    double salary;
    int daysWorked;
    int performanceScore;

    Employee(int id, const std::string& name, double salary)
        : id(id), name(name), salary(salary), daysWorked(0), performanceScore(0) {}

    void updateDetails(const std::string& newName, double newSalary) {
        name = newName;
        salary = newSalary;
    }

    void addAttendance(int days) {
        daysWorked += days;
    }

    void addPerformanceScore(int score) {
        performanceScore = score;
    }

    double calculateMonthlySalary() const {
        return salary / 30 * daysWorked;
    }

    void printDetails() const {
        std::cout << "ID: " << id << "\nName: " << name << "\nSalary: " << salary << "\nDays Worked: " << daysWorked << "\nPerformance Score: " << performanceScore << "\n";
    }
};

class EmployeeManagementSystem {
private:
    std::vector<Employee> employees;
    int nextEmployeeId = 1;

    Employee* findEmployee(int id) {
        for (auto& employee : employees) {
            if (employee.id == id) return &employee;
        }
        return nullptr;
    }

public:
    void addEmployee(const std::string& name, double salary) {
        employees.emplace_back(nextEmployeeId++, name, salary);
        std::cout << "Employee added successfully.\n";
    }

    void updateEmployee(int id, const std::string& newName, double newSalary) {
        Employee* employee = findEmployee(id);
        if (employee) {
            employee->updateDetails(newName, newSalary);
            std::cout << "Employee updated successfully.\n";
        } else {
            std::cout << "Employee not found.\n";
        }
    }

    void deleteEmployee(int id) {
        auto it = std::remove_if(employees.begin(), employees.end(), [id](const Employee& e) { return e.id == id; });
        if (it != employees.end()) {
            employees.erase(it, employees.end());
            std::cout << "Employee deleted successfully.\n";
        } else {
            std::cout << "Employee not found.\n";
        }
    }

    void addAttendance(int id, int days) {
        Employee* employee = findEmployee(id);
        if (employee) {
            employee->addAttendance(days);
            std::cout << "Attendance updated successfully.\n";
        } else {
            std::cout << "Employee not found.\n";
        }
    }

    void addPerformanceScore(int id, int score) {
        Employee* employee = findEmployee(id);
        if (employee) {
            employee->addPerformanceScore(score);
            std::cout << "Performance score updated successfully.\n";
        } else {
            std::cout << "Employee not found.\n";
        }
    }

    void printPayroll() const {
        std::cout << "\nPayroll Report:\n";
        for (const auto& employee : employees) {
            std::cout << "ID: " << employee.id << ", Name: " << employee.name
                      << ", Monthly Salary: " << std::fixed << std::setprecision(2) << employee.calculateMonthlySalary() << "\n";
        }
    }

    void printPerformanceReports() const {
        std::cout << "\nPerformance Reports:\n";
        for (const auto& employee : employees) {
            std::cout << "ID: " << employee.id << ", Name: " << employee.name
                      << ", Performance Score: " << employee.performanceScore << "\n";
        }
    }

    void generateReport() const {
        std::cout << "\nEmployee Report:\n";
        for (const auto& employee : employees) {
            employee.printDetails();
            std::cout << "------------------------\n";
        }
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& employee : employees) {
                file << employee.id << "," << employee.name << "," << employee.salary << "," << employee.daysWorked << "," << employee.performanceScore << "\n";
            }
            std::cout << "Data saved successfully.\n";
        } else {
            std::cout << "Unable to open file.\n";
        }
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            employees.clear();
            std::string line;
            while (std::getline(file, line)) {
                std::istringstream ss(line);
                std::string token;
                std::getline(ss, token, ',');
                int id = std::stoi(token);
                std::getline(ss, token, ',');
                std::string name = token;
                std::getline(ss, token, ',');
                double salary = std::stod(token);
                std::getline(ss, token, ',');
                int daysWorked = std::stoi(token);
                std::getline(ss, token, ',');
                int performanceScore = std::stoi(token);

                Employee employee(id, name, salary);
                employee.addAttendance(daysWorked);
                employee.addPerformanceScore(performanceScore);

                employees.push_back(employee);
            }
            std::cout << "Data loaded successfully.\n";
        } else {
            std::cout << "Unable to open file.\n";
        }
    }
};

int main() {
    EmployeeManagementSystem system;
    int choice;
    std::string name;
    double salary;
    int id, days, score;

    do {
        std::cout << "\nEmployee Management System\n";
        std::cout << "1. Add Employee\n2. Update Employee\n3. Delete Employee\n4. Add Attendance\n5. Add Performance Score\n6. Print Payroll\n7. Print Performance Reports\n8. Generate Report\n9. Save to File\n10. Load from File\n0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                std::cout << "Enter name: ";
                std::getline(std::cin, name);
                std::cout << "Enter salary: ";
                std::cin >> salary;
                std::cin.ignore();
                system.addEmployee(name, salary);
                break;
            case 2:
                std::cout << "Enter employee ID to update: ";
                std::cin >> id;
                std::cin.ignore();
                std::cout << "Enter new name: ";
                std::getline(std::cin, name);
                std::cout << "Enter new salary: ";
                std::cin >> salary;
                std::cin.ignore();
                system.updateEmployee(id, name, salary);
                break;
            case 3:
                std::cout << "Enter employee ID to delete: ";
                std::cin >> id;
                std::cin.ignore();
                system.deleteEmployee(id);
                break;
            case 4:
                std::cout << "Enter employee ID to add attendance: ";
                std::cin >> id;
                std::cin.ignore();
                std::cout << "Enter number of days: ";
                std::cin >> days;
                std::cin.ignore();
                system.addAttendance(id, days);
                break;
            case 5:
                std::cout << "Enter employee ID to add performance score: ";
                std::cin >> id;
                std::cin.ignore();
                std::cout << "Enter performance score: ";
                std::cin >> score;
                std::cin.ignore();
                system.addPerformanceScore(id, score);
                break;
            case 6:
                system.printPayroll();
                break;
            case 7:
                system.printPerformanceReports();
                break;
            case 8:
                system.generateReport();
                break;
            case 9:
                system.saveToFile("employees.txt");
                break;
            case 10:
                system.loadFromFile("employees.txt");
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
