#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

class Patient {
public:
    std::string id;
    std::string name;
    std::string address;
    std::string phone;

    Patient(const std::string& i, const std::string& n, const std::string& a, const std::string& p)
        : id(i), name(n), address(a), phone(p) {}

    void printDetails() const {
        std::cout << "Patient ID: " << id << "\nName: " << name << "\nAddress: " << address
                  << "\nPhone: " << phone << std::endl;
    }
};

class Doctor {
public:
    std::string id;
    std::string name;
    std::string specialty;
    std::string phone;

    Doctor(const std::string& i, const std::string& n, const std::string& s, const std::string& p)
        : id(i), name(n), specialty(s), phone(p) {}

    void printDetails() const {
        std::cout << "Doctor ID: " << id << "\nName: " << name << "\nSpecialty: " << specialty
                  << "\nPhone: " << phone << std::endl;
    }
};

class Appointment {
public:
    std::string id;
    std::string patientId;
    std::string doctorId;
    std::string date;
    std::string time;

    Appointment(const std::string& i, const std::string& pId, const std::string& dId, const std::string& d, const std::string& t)
        : id(i), patientId(pId), doctorId(dId), date(d), time(t) {}

    void printDetails() const {
        std::cout << "Appointment ID: " << id << "\nPatient ID: " << patientId << "\nDoctor ID: " << doctorId
                  << "\nDate: " << date << "\nTime: " << time << std::endl;
    }
};

class MedicalRecord {
public:
    std::string patientId;
    std::string record;

    MedicalRecord(const std::string& pId, const std::string& r) : patientId(pId), record(r) {}

    void printDetails() const {
        std::cout << "Patient ID: " << patientId << "\nRecord: " << record << std::endl;
    }
};

class Bill {
public:
    std::string patientId;
    double amount;
    std::string details;

    Bill(const std::string& pId, double amt, const std::string& d) : patientId(pId), amount(amt), details(d) {}

    void printDetails() const {
        std::cout << "Patient ID: " << patientId << "\nAmount: $" << amount << "\nDetails: " << details << std::endl;
    }
};
// MedicalRecord class remains unchanged

class HospitalManagementSystem {
private:
    std::vector<Patient> patients;
    std::vector<Doctor> doctors;
    std::vector<Appointment> appointments;
    std::vector<MedicalRecord> records;
    std::vector<Bill> bills;

    Patient* findPatient(const std::string& id) {
        for (auto& patient : patients) {
            if (patient.id == id) return &patient;
        }
        return nullptr;
    }

    Doctor* findDoctor(const std::string& id) {
        for (auto& doctor : doctors) {
            if (doctor.id == id) return &doctor;
        }
        return nullptr;
    }

    Appointment* findAppointment(const std::string& id) {
        for (auto& appointment : appointments) {
            if (appointment.id == id) return &appointment;
        }
        return nullptr;
    }

    const MedicalRecord* findRecord(const std::string& patientId) const {
        for (const auto& record : records) {
            if (record.patientId == patientId) return &record;
        }
        return nullptr;
    }

public:
    void addPatient(const std::string& id, const std::string& name, const std::string& address, const std::string& phone) {
        patients.emplace_back(id, name, address, phone);
        std::cout << "Patient added successfully.\n";
    }

    void updatePatient(const std::string& id, const std::string& name, const std::string& address, const std::string& phone) {
        Patient* patient = findPatient(id);
        if (patient) {
            patient->name = name;
            patient->address = address;
            patient->phone = phone;
            std::cout << "Patient updated successfully.\n";
        } else {
            std::cout << "Patient not found.\n";
        }
    }

    void deletePatient(const std::string& id) {
        auto it = std::remove_if(patients.begin(), patients.end(), [&id](const Patient& p) { return p.id == id; });
        if (it != patients.end()) {
            patients.erase(it, patients.end());
            std::cout << "Patient deleted successfully.\n";
        } else {
            std::cout << "Patient not found.\n";
        }
    }

    void addDoctor(const std::string& id, const std::string& name, const std::string& specialty, const std::string& phone) {
        doctors.emplace_back(id, name, specialty, phone);
        std::cout << "Doctor added successfully.\n";
    }

    void updateDoctor(const std::string& id, const std::string& name, const std::string& specialty, const std::string& phone) {
        Doctor* doctor = findDoctor(id);
        if (doctor) {
            doctor->name = name;
            doctor->specialty = specialty;
            doctor->phone = phone;
            std::cout << "Doctor updated successfully.\n";
        } else {
            std::cout << "Doctor not found.\n";
        }
    }

    void deleteDoctor(const std::string& id) {
        auto it = std::remove_if(doctors.begin(), doctors.end(), [&id](const Doctor& d) { return d.id == id; });
        if (it != doctors.end()) {
            doctors.erase(it, doctors.end());
            std::cout << "Doctor deleted successfully.\n";
        } else {
            std::cout << "Doctor not found.\n";
        }
    }

    void scheduleAppointment(const std::string& id, const std::string& patientId, const std::string& doctorId, const std::string& date, const std::string& time) {
        if (findPatient(patientId) && findDoctor(doctorId)) {
            appointments.emplace_back(id, patientId, doctorId, date, time);
            std::cout << "Appointment scheduled successfully.\n";
        } else {
            std::cout << "Patient or Doctor not found.\n";
        }
    }

    void updateAppointment(const std::string& id, const std::string& date, const std::string& time) {
        Appointment* appointment = findAppointment(id);
        if (appointment) {
            appointment->date = date;
            appointment->time = time;
            std::cout << "Appointment updated successfully.\n";
        } else {
            std::cout << "Appointment not found.\n";
        }
    }

    void cancelAppointment(const std::string& id) {
        auto it = std::remove_if(appointments.begin(), appointments.end(), [&id](const Appointment& a) { return a.id == id; });
        if (it != appointments.end()) {
            appointments.erase(it, appointments.end());
            std::cout << "Appointment canceled successfully.\n";
        } else {
            std::cout << "Appointment not found.\n";
        }
    }

    void addMedicalRecord(const std::string& patientId, const std::string& record) {
        records.emplace_back(patientId, record);
        std::cout << "Medical record added successfully.\n";
    }

    void viewMedicalRecord(const std::string& patientId) const {
        const MedicalRecord* record = findRecord(patientId);
        if (record) {
            record->printDetails();
        } else {
            std::cout << "Medical record not found.\n";
        }
    }

    void generateBill(const std::string& patientId, double amount, const std::string& details) {
        bills.emplace_back(patientId, amount, details);
        std::cout << "Bill generated successfully.\n";
    }

    void viewBill(const std::string& patientId) const {
        for (const auto& bill : bills) {
            if (bill.patientId == patientId) {
                bill.printDetails();
            }
        }
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& patient : patients) {
                file << "P," << patient.id << "," << patient.name << "," << patient.address << "," << patient.phone << "\n";
            }
            for (const auto& doctor : doctors) {
                file << "D," << doctor.id << "," << doctor.name << "," << doctor.specialty << "," << doctor.phone << "\n";
            }
            for (const auto& appointment : appointments) {
                file << "A," << appointment.id << "," << appointment.patientId << "," << appointment.doctorId << "," << appointment.date << "," << appointment.time << "\n";
            }
            for (const auto& record : records) {
                file << "R," << record.patientId << "," << record.record << "\n";
            }
            for (const auto& bill : bills) {
                file << "B," << bill.patientId << "," << bill.amount << "," << bill.details << "\n";
            }
            file.close();
        } else {
            std::cout << "Unable to open file for writing.\n";
        }
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                std::stringstream ss(line);
                std::string type;
                std::getline(ss, type, ',');
                if (type == "P") {
                    std::string id, name, address, phone;
                    std::getline(ss, id, ',');
                    std::getline(ss, name, ',');
                    std::getline(ss, address, ',');
                    std::getline(ss, phone, ',');
                    patients.emplace_back(id, name, address, phone);
                } else if (type == "D") {
                    std::string id, name, specialty, phone;
                    std::getline(ss, id, ',');
                    std::getline(ss, name, ',');
                    std::getline(ss, specialty, ',');
                    std::getline(ss, phone, ',');
                    doctors.emplace_back(id, name, specialty, phone);
                } else if (type == "A") {
                    std::string id, patientId, doctorId, date, time;
                    std::getline(ss, id, ',');
                    std::getline(ss, patientId, ',');
                    std::getline(ss, doctorId, ',');
                    std::getline(ss, date, ',');
                    std::getline(ss, time, ',');
                    appointments.emplace_back(id, patientId, doctorId, date, time);
                } else if (type == "R") {
                    std::string patientId, record;
                    std::getline(ss, patientId, ',');
                    std::getline(ss, record);
                    records.emplace_back(patientId, record);
                } else if (type == "B") {
                    std::string patientId, details;
                    double amount;
                    std::getline(ss, patientId, ',');
                    ss >> amount;
                    ss.ignore();
                    std::getline(ss, details);
                    bills.emplace_back(patientId, amount, details);
                }
            }
            file.close();
        } else {
            std::cout << "Unable to open file for reading.\n";
        }
    }

    // Public methods to access private details
    Patient* getPatient(const std::string& id) { return findPatient(id); }
    Doctor* getDoctor(const std::string& id) { return findDoctor(id); }
    Appointment* getAppointment(const std::string& id) { return findAppointment(id); }
};



int main() {
    HospitalManagementSystem hms;

    int choice;
    do {
        std::cout << "\nHospital Management System Menu:\n";
        std::cout << "1. Add Patient\n";
        std::cout << "2. Update Patient\n";
        std::cout << "3. Delete Patient\n";
        std::cout << "4. Add Doctor\n";
        std::cout << "5. Update Doctor\n";
        std::cout << "6. Delete Doctor\n";
        std::cout << "7. Schedule Appointment\n";
        std::cout << "8. Update Appointment\n";
        std::cout << "9. Cancel Appointment\n";
        std::cout << "10. Add Medical Record\n";
        std::cout << "11. View Medical Record\n";
        std::cout << "12. Generate Bill\n";
        std::cout << "13. View Bill\n";
        std::cout << "14. Save to File\n";
        std::cout << "15. Load from File\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

        switch (choice) {
            case 1: {
                std::string id, name, address, phone;
                std::cout << "Enter Patient ID: ";
                std::getline(std::cin, id);
                std::cout << "Enter Name: ";
                std::getline(std::cin, name);
                std::cout << "Enter Address: ";
                std::getline(std::cin, address);
                std::cout << "Enter Phone: ";
                std::getline(std::cin, phone);
                hms.addPatient(id, name, address, phone);
                break;
            }
            case 2: {
                std::string id, name, address, phone;
                std::cout << "Enter Patient ID to update: ";
                std::getline(std::cin, id);
                std::cout << "Enter New Name: ";
                std::getline(std::cin, name);
                std::cout << "Enter New Address: ";
                std::getline(std::cin, address);
                std::cout << "Enter New Phone: ";
                std::getline(std::cin, phone);
                hms.updatePatient(id, name, address, phone);
                break;
            }
            case 3: {
                std::string id;
                std::cout << "Enter Patient ID to delete: ";
                std::getline(std::cin, id);
                hms.deletePatient(id);
                break;
            }
            case 4: {
                std::string id, name, specialty, phone;
                std::cout << "Enter Doctor ID: ";
                std::getline(std::cin, id);
                std::cout << "Enter Name: ";
                std::getline(std::cin, name);
                std::cout << "Enter Specialty: ";
                std::getline(std::cin, specialty);
                std::cout << "Enter Phone: ";
                std::getline(std::cin, phone);
                hms.addDoctor(id, name, specialty, phone);
                break;
            }
            case 5: {
                std::string id, name, specialty, phone;
                std::cout << "Enter Doctor ID to update: ";
                std::getline(std::cin, id);
                std::cout << "Enter New Name: ";
                std::getline(std::cin, name);
                std::cout << "Enter New Specialty: ";
                std::getline(std::cin, specialty);
                std::cout << "Enter New Phone: ";
                std::getline(std::cin, phone);
                hms.updateDoctor(id, name, specialty, phone);
                break;
            }
            case 6: {
                std::string id;
                std::cout << "Enter Doctor ID to delete: ";
                std::getline(std::cin, id);
                hms.deleteDoctor(id);
                break;
            }
            case 7: {
                std::string id, patientId, doctorId, date, time;
                std::cout << "Enter Appointment ID: ";
                std::getline(std::cin, id);
                std::cout << "Enter Patient ID: ";
                std::getline(std::cin, patientId);
                std::cout << "Enter Doctor ID: ";
                std::getline(std::cin, doctorId);
                std::cout << "Enter Date (YYYY-MM-DD): ";
                std::getline(std::cin, date);
                std::cout << "Enter Time (HH:MM AM/PM): ";
                std::getline(std::cin, time);
                hms.scheduleAppointment(id, patientId, doctorId, date, time);
                break;
            }
            case 8: {
                std::string id, date, time;
                std::cout << "Enter Appointment ID to update: ";
                std::getline(std::cin, id);
                std::cout << "Enter New Date (YYYY-MM-DD): ";
                std::getline(std::cin, date);
                std::cout << "Enter New Time (HH:MM AM/PM): ";
                std::getline(std::cin, time);
                hms.updateAppointment(id, date, time);
                break;
            }
            case 9: {
                std::string id;
                std::cout << "Enter Appointment ID to cancel: ";
                std::getline(std::cin, id);
                hms.cancelAppointment(id);
                break;
            }
            case 10: {
                std::string patientId, record;
                std::cout << "Enter Patient ID: ";
                std::getline(std::cin, patientId);
                std::cout << "Enter Medical Record: ";
                std::getline(std::cin, record);
                hms.addMedicalRecord(patientId, record);
                break;
            }
            case 11: {
                std::string patientId;
                std::cout << "Enter Patient ID to view record: ";
                std::getline(std::cin, patientId);
                hms.viewMedicalRecord(patientId);
                break;
            }
            case 12: {
                std::string patientId, details;
                double amount;
                std::cout << "Enter Patient ID for Bill: ";
                std::getline(std::cin, patientId);
                std::cout << "Enter Amount: ";
                std::cin >> amount;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
                std::cout << "Enter Details: ";
                std::getline(std::cin, details);
                hms.generateBill(patientId, amount, details);
                break;
            }
            case 13: {
                std::string patientId;
                std::cout << "Enter Patient ID to view Bill: ";
                std::getline(std::cin, patientId);
                hms.viewBill(patientId);
                break;
            }
            case 14: {
                std::string filename;
                std::cout << "Enter filename to save data: ";
                std::getline(std::cin, filename);
                hms.saveToFile(filename);
                break;
            }
            case 15: {
                std::string filename;
                std::cout << "Enter filename to load data: ";
                std::getline(std::cin, filename);
                hms.loadFromFile(filename);
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
