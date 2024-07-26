#include <iostream>
#include <vector> 
#include <string>
#include <algorithm>
#include <fstream>

// Flight class definition
class Flight {
public:
    Flight(const std::string& flightNumber, const std::string& origin, const std::string& destination, const std::string& date, int seats)
        : flightNumber(flightNumber), origin(origin), destination(destination), date(date), seats(seats) {}

    std::string flightNumber;
    std::string origin;
    std::string destination;
    std::string date;
    int seats;
};

// Passenger class definition
class Passenger {
public:
    Passenger(const std::string& name, const std::string& passportNumber)
        : name(name), passportNumber(passportNumber) {}

    std::string name;
    std::string passportNumber;
};

// Reservation class definition
class Reservation {
public:
    Reservation(const std::string& reservationID, const Flight& flight, const Passenger& passenger, const std::string& seatNumber)
        : reservationID(reservationID), flight(flight), passenger(passenger), seatNumber(seatNumber) {}

    std::string reservationID;
    Flight flight;
    Passenger passenger;
    std::string seatNumber;
};

// FlightReservationSystem class definition
class FlightReservationSystem {
public:
    void addFlight(const std::string& fNum, const std::string& orig, const std::string& dest, const std::string& date, int seats);
    void updateFlight(const std::string& fNum, const std::string& orig, const std::string& dest, const std::string& date, int seats);
    void deleteFlight(const std::string& fNum);

    void addPassenger(const std::string& name, const std::string& passportNumber);
    void updatePassenger(const std::string& name, const std::string& passportNumber);
    void deletePassenger(const std::string& passportNumber);

    void makeReservation(const std::string& resID, const std::string& flightNumber, const std::string& passportNumber, const std::string& seatNumber);
    void cancelReservation(const std::string& resID);
    void printTicket(const std::string& resID) const;
    void checkAvailability(const std::string& flightNumber, const std::string& date) const;
    void saveToFile(const std::string& filename) const;

private:
    const Flight* findFlight(const std::string& flightNumber) const;
    const Passenger* findPassenger(const std::string& passportNumber) const;
    const Reservation* findReservation(const std::string& resID) const;

    std::vector<Flight> flights;
    std::vector<Passenger> passengers;
    std::vector<Reservation> reservations;
};

const Flight* FlightReservationSystem::findFlight(const std::string& flightNumber) const {
    for (const auto& flight : flights) {
        if (flight.flightNumber == flightNumber) {
            return &flight;
        }
    }
    return nullptr;
}

const Passenger* FlightReservationSystem::findPassenger(const std::string& passportNumber) const {
    for (const auto& passenger : passengers) {
        if (passenger.passportNumber == passportNumber) {
            return &passenger;
        }
    }
    return nullptr;
}

const Reservation* FlightReservationSystem::findReservation(const std::string& resID) const {
    for (const auto& reservation : reservations) {
        if (reservation.reservationID == resID) {
            return &reservation;
        }
    }
    return nullptr;
}

void FlightReservationSystem::addFlight(const std::string& fNum, const std::string& orig, const std::string& dest, const std::string& date, int seats) {
    flights.emplace_back(fNum, orig, dest, date, seats);
}

void FlightReservationSystem::updateFlight(const std::string& fNum, const std::string& orig, const std::string& dest, const std::string& date, int seats) {
    Flight* flight = const_cast<Flight*>(findFlight(fNum));
    if (flight) {
        flight->origin = orig;
        flight->destination = dest;
        flight->date = date;
        flight->seats = seats;
    }
}

void FlightReservationSystem::deleteFlight(const std::string& fNum) {
    auto it = std::remove_if(flights.begin(), flights.end(), [&fNum](const Flight& f) { return f.flightNumber == fNum; });
    flights.erase(it, flights.end());
}

void FlightReservationSystem::addPassenger(const std::string& name, const std::string& passportNumber) {
    passengers.emplace_back(name, passportNumber);
}

void FlightReservationSystem::updatePassenger(const std::string& name, const std::string& passportNumber) {
    Passenger* passenger = const_cast<Passenger*>(findPassenger(passportNumber));
    if (passenger) {
        passenger->name = name;
    }
}

void FlightReservationSystem::deletePassenger(const std::string& passportNumber) {
    auto it = std::remove_if(passengers.begin(), passengers.end(), [&passportNumber](const Passenger& p) { return p.passportNumber == passportNumber; });
    passengers.erase(it, passengers.end());
}

void FlightReservationSystem::makeReservation(const std::string& resID, const std::string& flightNumber, const std::string& passportNumber, const std::string& seatNumber) {
    const Flight* flight = findFlight(flightNumber);
    const Passenger* passenger = findPassenger(passportNumber);
    if (flight && passenger) {
        reservations.emplace_back(resID, *flight, *passenger, seatNumber);
    }
}

void FlightReservationSystem::cancelReservation(const std::string& resID) {
    auto it = std::remove_if(reservations.begin(), reservations.end(), [&resID](const Reservation& r) { return r.reservationID == resID; });
    reservations.erase(it, reservations.end());
}

void FlightReservationSystem::printTicket(const std::string& resID) const {
    const Reservation* reservation = findReservation(resID);
    if (reservation) {
        std::cout << "Reservation ID: " << reservation->reservationID << '\n';
        std::cout << "Flight Number: " << reservation->flight.flightNumber << '\n';
        std::cout << "Passenger Name: " << reservation->passenger.name << '\n';
        std::cout << "Seat Number: " << reservation->seatNumber << '\n';
    } else {
        std::cout << "Reservation not found.\n";
    }
}

void FlightReservationSystem::checkAvailability(const std::string& flightNumber, const std::string& date) const {
    const Flight* flight = findFlight(flightNumber);
    if (flight && flight->date == date) {
        std::cout << "Flight " << flight->flightNumber << " is available.\n";
    } else {
        std::cout << "Flight not available.\n";
    }
}

void FlightReservationSystem::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& flight : flights) {
            file << "Flight " << flight.flightNumber << " from " << flight.origin << " to " << flight.destination << " on " << flight.date << " with " << flight.seats << " seats.\n";
        }
        for (const auto& passenger : passengers) {
            file << "Passenger " << passenger.name << " with passport number " << passenger.passportNumber << ".\n";
        }
        for (const auto& reservation : reservations) {
            file << "Reservation " << reservation.reservationID << " for flight " << reservation.flight.flightNumber << " by passenger " << reservation.passenger.name << " for seat " << reservation.seatNumber << ".\n";
        }
    } else {
        std::cout << "Unable to open file for writing.\n";
    }
}

// Main function
int main() {
    FlightReservationSystem system;

    int choice;
    int availableSeats;
    do {
        std::cout << "\n1. Add Flight\n2. Update Flight\n3. Delete Flight\n4. Add Passenger\n5. Update Passenger\n6. Delete Passenger\n7. Make Reservation\n8. Cancel Reservation\n9. Print Ticket\n10. Check Availability\n11. Save Data\n12. Load Data\n0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        std::string flightNumber, origin, destination, date, passengerName, passportNumber, resID, seatNumber, filename;
        switch (choice) {
            case 1:
                std::cout << "Enter flight number, origin, destination, date (YYYY-MM-DD), available seats: ";
                std::getline(std::cin, flightNumber);
                std::getline(std::cin, origin);
                std::getline(std::cin, destination);
                std::getline(std::cin, date);
                std::cin >> availableSeats;
                std::cin.ignore();
                system.addFlight(flightNumber, origin, destination, date, availableSeats);
                break;
            case 2:
                std::cout << "Enter flight number to update: ";
                std::getline(std::cin, flightNumber);
                std::cout << "Enter new origin, destination, date (YYYY-MM-DD), available seats: ";
                std::getline(std::cin, origin);
                std::getline(std::cin, destination);
                std::getline(std::cin, date);
                std::cin >> availableSeats;
                std::cin.ignore();
                system.updateFlight(flightNumber, origin, destination, date, availableSeats);
                break;
            case 3:
                std::cout << "Enter flight number to delete: ";
                std::getline(std::cin, flightNumber);
                system.deleteFlight(flightNumber);
                break;
            case 4:
                std::cout << "Enter passenger name and passport number: ";
                std::getline(std::cin, passengerName);
                std::getline(std::cin, passportNumber);
                system.addPassenger(passengerName, passportNumber);
                break;
            case 5:
                std::cout << "Enter passport number and new name: ";
                std::getline(std::cin, passportNumber);
                std::getline(std::cin, passengerName);
                system.updatePassenger(passengerName, passportNumber);
                break;
            case 6:
                std::cout << "Enter passport number to delete: ";
                std::getline(std::cin, passportNumber);
                system.deletePassenger(passportNumber);
                break;
            case 7:
                std::cout << "Enter reservation ID, flight number, passenger passport number, and seat number: ";
                std::getline(std::cin, resID);
                std::getline(std::cin, flightNumber);
                std::getline(std::cin, passportNumber);
                std::getline(std::cin, seatNumber);
                system.makeReservation(resID, flightNumber, passportNumber, seatNumber);
                break;
            case 8:
                std::cout << "Enter reservation ID to cancel: ";
                std::getline(std::cin, resID);
                system.cancelReservation(resID);
                break;
            case 9:
                std::cout << "Enter reservation ID to print ticket: ";
                std::getline(std::cin, resID);
                system.printTicket(resID);
                break;
            case 10:
                std::cout << "Enter flight number and date (YYYY-MM-DD): ";
                std::getline(std::cin, flightNumber);
                std::getline(std::cin, date);
                system.checkAvailability(flightNumber, date);
                break;
            case 11:
                std::cout << "Enter filename to save data: ";
                std::getline(std::cin, filename);
                system.saveToFile(filename);
                break;
            case 12:
                std::cout << "Enter filename to load data: ";
                std::getline(std::cin, filename);
                // system.loadFromFile(filename); // Uncomment if you implement loadFromFile
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
