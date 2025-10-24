/* StaffController.hpp - Logic xử lý cho Staff (Updated) */

#pragma once
#include "app/Menu.hpp"
#include "domain/entities/Staff.hpp"
#include "domain/services/SpaService.hpp"
#include "infra/repositories/AccountRepoFile.hpp"
#include "infra/repositories/PetRepoFile.hpp"
#include <ctime>
#include <iostream>

using namespace std;

class StaffController {
private:
  Staff *currentStaff;
  SpaService spaService;
  PetRepository petRepo;
  AccountRepository accountRepo;

  void viewPets() {
    Menu::displayHeader("PETS AVAILABLE");

    cout << "\n1. View Dogs\n";
    cout << "2. View Cats\n";
    cout << "0. Back\n";
    cout << "Enter choice: ";

    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
      displayDogs();
    } else if (choice == 2) {
      displayCats();
    }
  }

  void displayDogs() {
    Menu::displayHeader("ALL DOGS");

    ifstream file("../data/Dog.txt");
    if (!file.is_open()) {
      Menu::displayError("Cannot open Dog.txt");
      return;
    }

    cout << "\nID    | Status | Name       | Breed              | Age | Price  "
            "    | Energy\n";
    cout << "-----------------------------------------------------------"
            "-------------------\n";

    string line;
    while (getline(file, line)) {
      if (line.empty())
        continue;

      stringstream ss(line);
      string id, status, name, breed, age, price, energy;

      getline(ss, id, '|');
      getline(ss, status, '|');
      getline(ss, name, '|');
      getline(ss, breed, '|');
      getline(ss, age, '|');
      getline(ss, price, '|');
      getline(ss, energy, '|');

      string statusText = (status == "1") ? "Available" : "Sold";

      cout << id << " | " << statusText << " | " << name << " | " << breed
           << " | " << age << " | " << price << " | " << energy << "/10\n";
    }

    file.close();
  }

  void displayCats() {
    Menu::displayHeader("ALL CATS");

    ifstream file("../data/Cat.txt");
    if (!file.is_open()) {
      Menu::displayError("Cannot open Cat.txt");
      return;
    }

    cout << "\nID    | Name   | Breed              | Age | Price      | Fur "
            "Length\n";
    cout << "------------------------------------------------------------"
            "-------------------\n";

    string line;
    while (getline(file, line)) {
      if (line.empty())
        continue;

      stringstream ss(line);
      string id, name, breed, age, price, fur;

      getline(ss, id, '|');
      getline(ss, name, '|');
      getline(ss, breed, '|');
      getline(ss, age, '|');
      getline(ss, price, '|');
      getline(ss, fur, '|');

      cout << id << " | " << name << " | " << breed << " | " << age << " | "
           << price << " | " << fur << "\n";
    }

    file.close();
  }

  void viewSpaServices() {
    Menu::clearScreen();
    spaService.displayAllSpaServices();
  }

  void manageBookings() {
    int choice;
    do {
      Menu::clearScreen();
      Menu::displayStaffBookingMenu();
      cin >> choice;
      cin.ignore();

      switch (choice) {
      case 1:
        spaService.viewAllBookings();
        break;
      case 2:
        viewBookingsByDate();
        break;
      case 3:
        confirmBooking();
        break;
      case 4:
        completeBooking();
        break;
      case 0:
        break;
      default:
        Menu::displayError("Invalid choice!");
      }

      if (choice != 0)
        Menu::pause();
    } while (choice != 0);
  }

  void viewBookingsByDate() {
    string date;
    cout << "Enter Date (dd/mm/yyyy): ";
    cin >> date;
    spaService.viewBookingsByDate(date);
  }

  void confirmBooking() {
    string bookingId;
    cout << "Enter Booking ID to confirm: ";
    cin >> bookingId;
    spaService.confirmBooking(bookingId);
  }

  void completeBooking() {
    string bookingId;
    cout << "Enter Booking ID to complete: ";
    cin >> bookingId;
    spaService.completeBooking(bookingId);
  }

  void viewTodaySchedule() {
    Menu::displayHeader("TODAY'S SCHEDULE");

    // Get current date
    time_t now = time(0);
    tm *ltm = localtime(&now);

    string today = to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) +
                   "/" + to_string(1900 + ltm->tm_year);

    cout << "Date: " << today << "\n";
    spaService.viewBookingsByDate(today);
  }

  void createClientAccount() {
    Menu::displayHeader("CREATE CLIENT ACCOUNT");

    string id, name, password, gender, street, city;

    cout << "Enter Phone Number (10 digits): ";
    cin >> id;

    // Validate phone number
    if (id.length() != 10) {
      Menu::displayError("Phone number must be 10 digits!");
      return;
    }

    // Check if ID already exists
    if (accountRepo.isValidId(id)) {
      Menu::displayError("This phone number is already registered!");
      return;
    }

    cin.ignore();
    cout << "Enter Client Name: ";
    getline(cin, name);

    cout << "Enter Password: ";
    cin >> password;

    cout << "Enter Gender (male/female): ";
    cin >> gender;

    cin.ignore();
    cout << "Enter Street Address: ";
    getline(cin, street);

    cout << "Enter City: ";
    getline(cin, city);

    // Create new client account
    Client newClient(id, name, password, gender, street, city);
    accountRepo.setClientInfo(newClient);

    Menu::displaySuccess("Client account created successfully!");
    cout << "Phone: " << id << "\n";
    cout << "Name: " << name << "\n";
    cout << "Password: " << password << "\n";
  }

public:
  StaffController(Staff *staff) : currentStaff(staff) {}

  void run() {
    int choice;
    do {
      Menu::clearScreen();
      cout << "\n========================================\n";
      cout << "  STAFF PANEL - " << currentStaff->getName() << "\n";
      cout << "========================================\n";
      cout << "1. View Pets\n";
      cout << "2. View Spa Services\n";
      cout << "3. Manage Bookings\n";
      cout << "4. View Today's Schedule\n";
      cout << "5. Create Client Account\n";
      cout << "0. Logout\n";
      cout << "========================================\n";
      cout << "Enter your choice: ";
      cin >> choice;
      cin.ignore();

      switch (choice) {
      case 1:
        viewPets();
        Menu::pause();
        break;
      case 2:
        viewSpaServices();
        Menu::pause();
        break;
      case 3:
        manageBookings();
        break;
      case 4:
        viewTodaySchedule();
        Menu::pause();
        break;
      case 5:
        createClientAccount();
        Menu::pause();
        break;
      case 0:
        Menu::displayInfo("Logging out...");
        break;
      default:
        Menu::displayError("Invalid choice!");
        Menu::pause();
      }
    } while (choice != 0);
  }
};