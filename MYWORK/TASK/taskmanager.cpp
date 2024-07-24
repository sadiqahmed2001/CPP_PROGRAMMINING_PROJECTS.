#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <iomanip>

class Task {
public:
    std::string title;
    std::string description;
    std::chrono::system_clock::time_point dueDate;
    int priority;
    std::string status;

    Task(std::string t, std::string d, std::chrono::system_clock::time_point due, int p, std::string s)
        : title(t), description(d), dueDate(due), priority(p), status(s) {}

    void display() const {
        std::cout << "Title: " << title << "\nDescription: " << description
                  << "\nDue Date: " << std::chrono::system_clock::to_time_t(dueDate)
                  << "\nPriority: " << priority << "\nStatus: " << status << "\n";
    }

    bool isOverdue() const {
        return std::chrono::system_clock::now() > dueDate;
    }

    friend std::ostream& operator<<(std::ostream& os, const Task& task);
    friend std::istream& operator>>(std::istream& is, Task& task);
};

std::ostream& operator<<(std::ostream& os, const Task& task) {
    os << task.title << "\n" << task.description << "\n" << std::chrono::system_clock::to_time_t(task.dueDate) << "\n" << task.priority << "\n" << task.status << "\n";
    return os;
}

std::istream& operator>>(std::istream& is, Task& task) {
    std::time_t dueDate;
    is >> std::ws;
    std::getline(is, task.title);
    std::getline(is, task.description);
    is >> dueDate >> task.priority >> task.status;
    task.dueDate = std::chrono::system_clock::from_time_t(dueDate);
    return is;
}

class TaskManager {
private:
    std::vector<Task> tasks;

public:
    void addTask(const std::string& title, const std::string& description, const std::chrono::system_clock::time_point& dueDate, int priority, const std::string& status) {
        tasks.emplace_back(title, description, dueDate, priority, status);
        std::cout << "Task added successfully.\n";
    }

    void searchTask(const std::string& query) const {
        auto it = std::find_if(tasks.begin(), tasks.end(), [&](const Task& t) { return t.title == query || t.status == query; });
        if (it != tasks.end()) {
            it->display();
        } else {
            std::cout << "Task not found.\n";
        }
    }

    void updateTask(const std::string& title, const std::string& newDescription, const std::chrono::system_clock::time_point& newDueDate, int newPriority, const std::string& newStatus) {
        auto it = std::find_if(tasks.begin(), tasks.end(), [&](const Task& t) { return t.title == title; });
        if (it != tasks.end()) {
            it->description = newDescription;
            it->dueDate = newDueDate;
            it->priority = newPriority;
            it->status = newStatus;
            std::cout << "Task updated successfully.\n";
        } else {
            std::cout << "Task not found.\n";
        }
    }

    void deleteTask(const std::string& title) {
        auto it = std::remove_if(tasks.begin(), tasks.end(), [&](const Task& t) { return t.title == title; });
        if (it != tasks.end()) {
            tasks.erase(it, tasks.end());
            std::cout << "Task deleted successfully.\n";
        } else {
            std::cout << "Task not found.\n";
        }
    }

    void listAllTasks() const {
        if (tasks.empty()) {
            std::cout << "No tasks to display.\n";
        } else {
            for (const auto& task : tasks) {
                task.display();
                std::cout << "----------------\n";
            }
        }
    }

    void listOverdueTasks() const {
        bool found = false;
        for (const auto& task : tasks) {
            if (task.isOverdue()) {
                task.display();
                std::cout << "----------------\n";
                found = true;
            }
        }
        if (!found) {
            std::cout << "No overdue tasks.\n";
        }
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& task : tasks) {
                file << task;
            }
            file.close();
            std::cout << "Tasks saved to file successfully.\n";
        } else {
            std::cout << "Unable to open file.\n";
        }
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            tasks.clear();
            Task task("", "", std::chrono::system_clock::now(), 0, "");
            while (file >> task) {
                tasks.push_back(task);
            }
            file.close();
            std::cout << "Tasks loaded from file successfully.\n";
        } else {
            std::cout << "Unable to open file.\n";
        }
    }

    void sortTasksByDueDate() {
        std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
            return a.dueDate < b.dueDate;
        });
        std::cout << "Tasks sorted by due date.\n";
    }

    void sortTasksByPriority() {
        std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
            return a.priority < b.priority;
        });
        std::cout << "Tasks sorted by priority.\n";
    }

    void sortTasksByStatus() {
        std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
            return a.status < b.status;
        });
        std::cout << "Tasks sorted by status.\n";
    }
};

int main() {
    TaskManager manager;
    int choice;
    std::string title, description, status, filename;
    int priority;
    std::chrono::system_clock::time_point dueDate;
    std::time_t dueDateInput;

    do {
        std::cout << "Task Management System\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. Search Task\n";
        std::cout << "3. Update Task\n";
        std::cout << "4. Delete Task\n";
        std::cout << "5. List All Tasks\n";
        std::cout << "6. List Overdue Tasks\n";
        std::cout << "7. Save to File\n";
        std::cout << "8. Load from File\n";
        std::cout << "9. Sort Tasks by Due Date\n";
        std::cout << "10. Sort Tasks by Priority\n";
        std::cout << "11. Sort Tasks by Status\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // to ignore the newline character after choice input

        switch (choice) {
            case 1:
                std::cout << "Enter title: ";
                std::getline(std::cin, title);
                std::cout << "Enter description: ";
                std::getline(std::cin, description);
                std::cout << "Enter due date (as time_t): ";
                std::cin >> dueDateInput;
                dueDate = std::chrono::system_clock::from_time_t(dueDateInput);
                std::cout << "Enter priority: ";
                std::cin >> priority;
                std::cin.ignore(); // to ignore the newline character after priority input
                std::cout << "Enter status: ";
                std::getline(std::cin, status);
                manager.addTask(title, description, dueDate, priority, status);
                break;

            case 2:
                std::cout << "Enter title or status to search: ";
                std::getline(std::cin, title); // using title variable for query input
                manager.searchTask(title);
                break;

            case 3:
                std::cout << "Enter title to update: ";
                std::getline(std::cin, title);
                std::cout << "Enter new description: ";
                std::getline(std::cin, description);
                std::cout << "Enter new due date (as time_t): ";
                std::cin >> dueDateInput;
                dueDate = std::chrono::system_clock::from_time_t(dueDateInput);
                std::cout << "Enter new priority: ";
                std::cin >> priority;
                std::cin.ignore(); // to ignore the newline character after priority input
                std::cout << "Enter new status: ";
                std::getline(std::cin, status);
                manager.updateTask(title, description, dueDate, priority, status);
                break;

            case 4:
                std::cout << "Enter title to delete: ";
                std::getline(std::cin, title);
                manager.deleteTask(title);
                break;

            case 5:
                manager.listAllTasks();
                break;

            case 6:
                manager.listOverdueTasks();
                break;

            case 7:
                std::cout << "Enter filename to save: ";
                std::getline(std::cin, filename);
                manager.saveToFile(filename);
                break;

            case 8:
                std::cout << "Enter filename to load: ";
                std::getline(std::cin, filename);
                manager.loadFromFile(filename);
                break;

            case 9:
                manager.sortTasksByDueDate();
                break;

            case 10:
                manager.sortTasksByPriority();
                break;

            case 11:
                manager.sortTasksByStatus();
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
