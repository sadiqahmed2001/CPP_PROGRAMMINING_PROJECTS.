#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

class Event {
public:
    std::string id;
    std::string name;
    std::string date;
    std::string time;
    double budget;

    Event(const std::string& i, const std::string& n, const std::string& d, const std::string& t, double b)
        : id(i), name(n), date(d), time(t), budget(b) {}

    void printDetails() const {
        std::cout << "Event ID: " << id << "\nName: " << name << "\nDate: " << date
                  << "\nTime: " << time << "\nBudget: $" << budget << std::endl;
    }
};

class Participant {
public:
    std::string id;
    std::string name;
    std::string email;

    Participant(const std::string& i, const std::string& n, const std::string& e)
        : id(i), name(n), email(e) {}

    void printDetails() const {
        std::cout << "Participant ID: " << id << "\nName: " << name << "\nEmail: " << email << std::endl;
    }
};

class Registration {
public:
    std::string eventId;
    std::string participantId;

    Registration(const std::string& eId, const std::string& pId)
        : eventId(eId), participantId(pId) {}
};

class EventManagementSystem {
private:
    std::vector<Event> events;
    std::vector<Participant> participants;
    std::vector<Registration> registrations;

    Event* findEvent(const std::string& id) {
        for (auto& event : events) {
            if (event.id == id) return &event;
        }
        return nullptr;
    }

    Participant* findParticipant(const std::string& id) {
        for (auto& participant : participants) {
            if (participant.id == id) return &participant;
        }
        return nullptr;
    }

public:
    void addEvent(const std::string& id, const std::string& name, const std::string& date, const std::string& time, double budget) {
        events.emplace_back(id, name, date, time, budget);
        std::cout << "Event added successfully.\n";
    }

    void updateEvent(const std::string& id, const std::string& name, const std::string& date, const std::string& time, double budget) {
        Event* event = findEvent(id);
        if (event) {
            event->name = name;
            event->date = date;
            event->time = time;
            event->budget = budget;
            std::cout << "Event updated successfully.\n";
        } else {
            std::cout << "Event not found.\n";
        }
    }

    void deleteEvent(const std::string& id) {
        auto it = std::remove_if(events.begin(), events.end(), [&id](const Event& e) { return e.id == id; });
        if (it != events.end()) {
            events.erase(it, events.end());
            std::cout << "Event deleted successfully.\n";
        } else {
            std::cout << "Event not found.\n";
        }
    }

    void addParticipant(const std::string& id, const std::string& name, const std::string& email) {
        participants.emplace_back(id, name, email);
        std::cout << "Participant added successfully.\n";
    }

    void updateParticipant(const std::string& id, const std::string& name, const std::string& email) {
        Participant* participant = findParticipant(id);
        if (participant) {
            participant->name = name;
            participant->email = email;
            std::cout << "Participant updated successfully.\n";
        } else {
            std::cout << "Participant not found.\n";
        }
    }

    void deleteParticipant(const std::string& id) {
        auto it = std::remove_if(participants.begin(), participants.end(), [&id](const Participant& p) { return p.id == id; });
        if (it != participants.end()) {
            participants.erase(it, participants.end());
            std::cout << "Participant deleted successfully.\n";
        } else {
            std::cout << "Participant not found.\n";
        }
    }

    void registerParticipant(const std::string& eventId, const std::string& participantId) {
        if (findEvent(eventId) && findParticipant(participantId)) {
            registrations.emplace_back(eventId, participantId);
            std::cout << "Participant registered for event successfully.\n";
        } else {
            std::cout << "Event or Participant not found.\n";
        }
    }

    void scheduleEvent(const std::string& id, const std::string& date, const std::string& time) {
        Event* event = findEvent(id);
        if (event) {
            event->date = date;
            event->time = time;
            std::cout << "Event scheduled successfully.\n";
        } else {
            std::cout << "Event not found.\n";
        }
    }

    void generateReport() const {
        std::cout << "\nEvent Participation Report:\n";
        for (const auto& event : events) {
            event.printDetails();
            int count = 0;
            for (const auto& reg : registrations) {
                if (reg.eventId == event.id) {
                    count++;
                }
            }
            std::cout << "Participants Registered: " << count << std::endl;
        }

        std::cout << "\nFinancial Report:\n";
        double totalBudget = 0.0;
        for (const auto& event : events) {
            totalBudget += event.budget;
        }
        std::cout << "Total Budget Allocated: $" << std::fixed << std::setprecision(2) << totalBudget << std::endl;
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& event : events) {
                file << "E," << event.id << "," << event.name << "," << event.date << "," << event.time << "," << event.budget << "\n";
            }
            for (const auto& participant : participants) {
                file << "P," << participant.id << "," << participant.name << "," << participant.email << "\n";
            }
            for (const auto& registration : registrations) {
                file << "R," << registration.eventId << "," << registration.participantId << "\n";
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
                if (type == "E") {
                    std::string id, name, date, time;
                    double budget;
                    std::getline(ss, id, ',');
                    std::getline(ss, name, ',');
                    std::getline(ss, date, ',');
                    std::getline(ss, time, ',');
                    ss >> budget;
                    events.emplace_back(id, name, date, time, budget);
                } else if (type == "P") {
                    std::string id, name, email;
                    std::getline(ss, id, ',');
                    std::getline(ss, name, ',');
                    std::getline(ss, email);
                    participants.emplace_back(id, name, email);
                } else if (type == "R") {
                    std::string eventId, participantId;
                    std::getline(ss, eventId, ',');
                    std::getline(ss, participantId);
                    registrations.emplace_back(eventId, participantId);
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
    EventManagementSystem system;

    int choice;
    do {
        std::cout << "\n1. Add Event\n2. Update Event\n3. Delete Event\n4. Add Participant\n5. Update Participant\n6. Delete Participant\n7. Register Participant\n8. Schedule Event\n9. Generate Report\n10. Save Data\n11. Load Data\n0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        std::string id, name, email, date, time, eventId, participantId, filename;
        double budget;

        switch (choice) {
            case 1:
                std::cout << "Enter event ID, name, date (YYYY-MM-DD), time (HH:MM), budget: ";
                std::getline(std::cin, id);
                std::getline(std::cin, name);
                std::getline(std::cin, date);
                std::getline(std::cin, time);
                std::cin >> budget;
                std::cin.ignore();
                system.addEvent(id, name, date, time, budget);
                break;

            case 2:
                std::cout << "Enter event ID, new name, new date (YYYY-MM-DD), new time (HH:MM), new budget: ";
                std::getline(std::cin, id);
                std::getline(std::cin, name);
                std::getline(std::cin, date);
                std::getline(std::cin, time);
                std::cin >> budget;
                std::cin.ignore();
                system.updateEvent(id, name, date, time, budget);
                break;

            case 3:
                std::cout << "Enter event ID to delete: ";
                std::getline(std::cin, id);
                system.deleteEvent(id);
                break;

            case 4:
                std::cout << "Enter participant ID, name, email: ";
                std::getline(std::cin, id);
                std::getline(std::cin, name);
                std::getline(std::cin, email);
                system.addParticipant(id, name, email);
                break;

            case 5:
                std::cout << "Enter participant ID, new name, new email: ";
                std::getline(std::cin, id);
                std::getline(std::cin, name);
                std::getline(std::cin, email);
                system.updateParticipant(id, name, email);
                break;

            case 6:
                std::cout << "Enter participant ID to delete: ";
                std::getline(std::cin, id);
                system.deleteParticipant(id);
                break;

            case 7:
                std::cout << "Enter event ID and participant ID to register: ";
                std::getline(std::cin, eventId);
                std::getline(std::cin, participantId);
                system.registerParticipant(eventId, participantId);
                break;

            case 8:
                std::cout << "Enter event ID, new date (YYYY-MM-DD), new time (HH:MM): ";
                std::getline(std::cin, id);
                std::getline(std::cin, date);
                std::getline(std::cin, time);
                system.scheduleEvent(id, date, time);
                break;

            case 9:
                system.generateReport();
                break;

            case 10:
                std::cout << "Enter filename to save data: ";
                std::getline(std::cin, filename);
                system.saveToFile(filename);
                break;

            case 11:
                std::cout << "Enter filename to load data: ";
                std::getline(std::cin, filename);
                system.loadFromFile(filename);
                break;

            case 0:
                std::cout << "Exiting...\n";
                break;

            default:
                std::cout << "Invalid choice. Try again.\n";
                break;
        }
    } while (choice != 0);

    return 0;
}
