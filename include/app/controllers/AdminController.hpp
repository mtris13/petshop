/* AdminController.hpp - Logic xử lý cho Admin (Updated) */

#pragma once
#include "app/Menu.hpp"
#include "domain/entities/Admin.hpp"
#include "domain/entities/Cat.hpp"
#include "domain/entities/Client.hpp"
#include "domain/entities/Dog.hpp"
#include "domain/entities/Staff.hpp"
#include "domain/services/SpaService.hpp"
#include "infra/repositories/AccountRepoFile.hpp"
#include "infra/repositories/BillRepoFile.hpp"
#include "infra/repositories/BookingRepoFile.hpp"
#include "infra/repositories/PetRepoFile.hpp"
#include "infra/repositories/ServiceRepoFile.hpp"
#include <iostream>

using namespace std;

class AdminController {
private:
  Admin *currentAdmin;
  AccountRepository accountRepo;
  PetRepository petRepo;
  SpaService spaService;
  BillRepository billRepo;
  BookingRepository bookingRepo;
  ServiceRepository serviceRepo;

  // ===== ACCOUNT MANAGEMENT =====
  void manageAccounts() {
    int choice;
    do {
      Menu::clearScreen();
      Menu::displayAccountManagementMenu();
      cin >> choice;
      cin.ignore();

      switch (choice) {
      case 1:
        viewAllAccounts();
        break;
      case 2:
        addStaffAccount();
        break;
      case 3:
        updateAccount();
        break;
      case 4:
        deleteAccount();
        break;
      case 5:
        viewAccountDetails();
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

  void viewAllAccounts() {
    Menu::displayHeader("ALL ACCOUNTS");
    cout << "\n--- ADMIN ACCOUNTS ---\n";
    // TODO: Implement list all admin accounts
    cout << "Feature coming soon...\n";

    cout << "\n--- STAFF ACCOUNTS ---\n";
    // TODO: Implement list all staff accounts
    cout << "Feature coming soon...\n";

    cout << "\n--- CLIENT ACCOUNTS ---\n";
    // TODO: Implement list all client accounts
    cout << "Feature coming soon...\n";
  }

  void addStaffAccount() {
    Menu::displayHeader("ADD STAFF ACCOUNT");

    string id, name, password, gender;
    float salary;

    cout << "Enter Staff ID (5 digits): ";
    cin >> id;
    cin.ignore();

    if (accountRepo.isValidId(id)) {
      Menu::displayError("Staff ID already exists!");
      return;
    }

    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Password: ";
    cin >> password;
    cout << "Enter Gender (male/female): ";
    cin >> gender;
    cout << "Enter Salary: ";
    cin >> salary;

    Staff newStaff(id, name, password, gender, salary);
    accountRepo.setStaffInfo(newStaff);

    Menu::displaySuccess("Staff account created successfully!");
  }

  void updateAccount() {
    Menu::displayHeader("UPDATE ACCOUNT");

    string id;
    cout << "Enter Account ID: ";
    cin >> id;
    cin.ignore();

    if (!accountRepo.isValidId(id)) {
      Menu::displayError("Account not found!");
      return;
    }

    int length = id.length();

    if (length == 3) { // Admin
      Admin admin = accountRepo.getAdminInfo(id);
      cout << "\nCurrent Info:\n";
      cout << "Name: " << admin.getName() << "\n";

      string name, password, gender;
      cout << "\nEnter New Name: ";
      getline(cin, name);
      cout << "Enter New Password: ";
      cin >> password;
      cout << "Enter New Gender: ";
      cin >> gender;

      admin.setName(name);
      admin.setPassword(password);
      admin.setGender(gender);
      accountRepo.setAdminInfo(admin);

    } else if (length == 5) { // Staff
      Staff staff = accountRepo.getStaffInfo(id);
      cout << "\nCurrent Info:\n";
      cout << "Name: " << staff.getName() << "\n";
      cout << "Salary: " << staff.getSalary() << "\n";

      string name, password, gender;
      float salary;
      cout << "\nEnter New Name: ";
      getline(cin, name);
      cout << "Enter New Password: ";
      cin >> password;
      cout << "Enter New Gender: ";
      cin >> gender;
      cout << "Enter New Salary: ";
      cin >> salary;

      staff.setName(name);
      staff.setPassword(password);
      staff.setGender(gender);
      staff.setSalary(salary);
      accountRepo.setStaffInfo(staff);

    } else if (length == 10) { // Client
      Client client = accountRepo.getClientInfo(id);
      cout << "\nCurrent Info:\n";
      cout << "Name: " << client.getName() << "\n";
      cout << "Address: " << client.getStreet() << ", " << client.getCity()
           << "\n";

      string name, password, gender, street, city;
      cout << "\nEnter New Name: ";
      getline(cin, name);
      cout << "Enter New Password: ";
      cin >> password;
      cout << "Enter New Gender: ";
      cin >> gender;
      cout << "Enter New Street: ";
      getline(cin, street);
      cout << "Enter New City: ";
      getline(cin, city);

      client.setName(name);
      client.setPassword(password);
      client.setGender(gender);
      client.setStreet(street);
      client.setCity(city);
      accountRepo.setClientInfo(client);
    }

    Menu::displaySuccess("Account updated successfully!");
  }

  void deleteAccount() {
    Menu::displayHeader("DELETE ACCOUNT");

    string id;
    cout << "Enter Account ID to delete: ";
    cin >> id;

    if (!accountRepo.isValidId(id)) {
      Menu::displayError("Account not found!");
      return;
    }

    if (id == currentAdmin->getId()) {
      Menu::displayError("Cannot delete your own account!");
      return;
    }

    char confirm;
    cout << "Are you sure? (y/n): ";
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
      accountRepo.deleteAccount(id);
      Menu::displaySuccess("Account deleted successfully!");
    }
  }

  void viewAccountDetails() {
    Menu::displayHeader("ACCOUNT DETAILS");

    string id;
    cout << "Enter Account ID: ";
    cin >> id;

    if (!accountRepo.isValidId(id)) {
      Menu::displayError("Account not found!");
      return;
    }

    int length = id.length();

    if (length == 3) {
      Admin admin = accountRepo.getAdminInfo(id);
      cout << "\n=== ADMIN ACCOUNT ===\n";
      cout << "ID: " << admin.getId() << "\n";
      cout << "Name: " << admin.getName() << "\n";
      cout << "Gender: " << admin.getGender() << "\n";

    } else if (length == 5) {
      Staff staff = accountRepo.getStaffInfo(id);
      cout << "\n=== STAFF ACCOUNT ===\n";
      cout << "ID: " << staff.getId() << "\n";
      cout << "Name: " << staff.getName() << "\n";
      cout << "Gender: " << staff.getGender() << "\n";
      cout << "Salary: " << staff.getSalary() << "\n";

    } else if (length == 10) {
      Client client = accountRepo.getClientInfo(id);
      cout << "\n=== CLIENT ACCOUNT ===\n";
      cout << "ID: " << client.getId() << "\n";
      cout << "Name: " << client.getName() << "\n";
      cout << "Gender: " << client.getGender() << "\n";
      cout << "Address: " << client.getStreet() << ", " << client.getCity()
           << "\n";
    }
  }

  // ===== PET MANAGEMENT =====
  void managePets() {
    int choice;
    do {
      Menu::clearScreen();
      Menu::displayPetManagementMenu();
      cin >> choice;
      cin.ignore();

      switch (choice) {
      case 1:
        viewAllPets();
        break;
      case 2:
        addNewPet();
        break;
      case 3:
        updatePet();
        break;
      case 4:
        deletePet();
        break;
      case 5:
        searchPet();
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

  void viewAllPets() {
    Menu::displayHeader("ALL PETS");
    cout << "Feature coming soon...\n";
    // TODO: List all dogs and cats
  }

  void addNewPet() {
    Menu::displayHeader("ADD NEW PET");

    int type;
    cout << "Pet Type:\n";
    cout << "1. Dog\n";
    cout << "2. Cat\n";
    cout << "Enter choice: ";
    cin >> type;
    cin.ignore();

    string id, name, breed;
    int age;
    float price;

    cout << "Enter Pet ID: ";
    cin >> id;
    cin.ignore();

    if (petRepo.isValidPetId(id)) {
      Menu::displayError("Pet ID already exists!");
      return;
    }

    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Breed: ";
    getline(cin, breed);
    cout << "Enter Age: ";
    cin >> age;
    cout << "Enter Price: ";
    cin >> price;

    if (type == 1) {
      int energy;
      cout << "Enter Energy Level (1-10): ";
      cin >> energy;

      Dog newDog(id, name, breed, age, price, energy);
      petRepo.setDogInfo(newDog);
    } else {
      string furLength;
      cout << "Enter Fur Length (Short/Medium/Long): ";
      cin >> furLength;

      Cat newCat(id, name, breed, age, price, furLength);
      petRepo.setCatInfo(newCat);
    }

    Menu::displaySuccess("Pet added successfully!");
  }

  void updatePet() {
    Menu::displayHeader("UPDATE PET");
    cout << "Feature coming soon...\n";
  }

  void deletePet() {
    Menu::displayHeader("DELETE PET");

    string id;
    cout << "Enter Pet ID to delete: ";
    cin >> id;

    if (!petRepo.isValidPetId(id)) {
      Menu::displayError("Pet not found!");
      return;
    }

    char confirm;
    cout << "Are you sure? (y/n): ";
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
      petRepo.deletePet(id);
      Menu::displaySuccess("Pet deleted successfully!");
    }
  }

  void searchPet() {
    Menu::displayHeader("SEARCH PET");
    cout << "Feature coming soon...\n";
  }

  // ===== SPA SERVICE MANAGEMENT =====
  void manageSpaServices() {
    int choice;
    do {
      Menu::clearScreen();
      Menu::displaySpaManagementMenu();
      cin >> choice;
      cin.ignore();

      switch (choice) {
      case 1:
        spaService.displayAllSpaServices();
        break;
      case 2:
        addSpaService();
        break;
      case 3:
        updateSpaService();
        break;
      case 4:
        deleteSpaService();
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

  void addSpaService() {
    Menu::displayHeader("ADD SPA SERVICE");

    string id, name, desc;
    float price;
    int duration;

    cout << "Enter Service ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Service Name: ";
    getline(cin, name);
    cout << "Enter Description: ";
    getline(cin, desc);
    cout << "Enter Price: ";
    cin >> price;
    cout << "Enter Duration (minutes): ";
    cin >> duration;

    spaService.addSpaService(id, name, desc, price, duration);
  }

  void updateSpaService() {
    Menu::displayHeader("UPDATE SPA SERVICE");

    string id, name, desc;
    float price;
    int duration;

    cout << "Enter Service ID to update: ";
    cin >> id;
    cin.ignore();
    cout << "Enter New Service Name: ";
    getline(cin, name);
    cout << "Enter New Description: ";
    getline(cin, desc);
    cout << "Enter New Price: ";
    cin >> price;
    cout << "Enter New Duration (minutes): ";
    cin >> duration;

    spaService.updateSpaService(id, name, desc, price, duration);
  }

  void deleteSpaService() {
    Menu::displayHeader("DELETE SPA SERVICE");

    string id;
    cout << "Enter Service ID to delete: ";
    cin >> id;

    char confirm;
    cout << "Are you sure? (y/n): ";
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
      spaService.deleteSpaService(id);
    }
  }

  // ===== BOOKING MANAGEMENT =====
  void manageBookings() {
    int choice;
    do {
      Menu::clearScreen();
      Menu::displayBookingManagementMenu();
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
      case 5:
        cancelBooking();
        break;
      case 6:
        deleteBooking();
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

  void cancelBooking() {
    string bookingId;
    cout << "Enter Booking ID to cancel: ";
    cin >> bookingId;
    spaService.cancelBooking(bookingId);
  }

  void deleteBooking() {
    string bookingId;
    cout << "Enter Booking ID to delete: ";
    cin >> bookingId;

    char confirm;
    cout << "Are you sure? (y/n): ";
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
      spaService.deleteBookingPermanent(bookingId);
    }
  }

  // ===== STATISTICS =====
  void viewStatistics() {
    Menu::displayHeader("SYSTEM STATISTICS");

    // 1. Spa Statistics
    cout << "\n========== SPA SERVICES ==========\n";
    spaService.showStatistics();

    // 2. Pet Sales Statistics
    cout << "\n========== PET SALES ==========\n";
    calculatePetSalesStats();

    // 3. Revenue Statistics
    cout << "\n========== REVENUE STATISTICS ==========\n";
    calculateRevenueStats();

    cout << "\n========================================\n";
  }

  void calculatePetSalesStats() {
    int totalDogs = 0, soldDogs = 0, availableDogs = 0;
    int totalCats = 0, soldCats = 0, availableCats = 0;

    // Count Dogs
    ifstream dogFile("../data/Dog.txt");
    if (dogFile.is_open()) {
      string line;
      while (getline(dogFile, line)) {
        if (line.empty())
          continue;
        totalDogs++;
        if (line[6] == '0')
          soldDogs++;
        else
          availableDogs++;
      }
      dogFile.close();
    }

    // Count Cats
    ifstream catFile("../data/Cat.txt");
    if (catFile.is_open()) {
      string line;
      while (getline(catFile, line)) {
        if (line.empty())
          continue;
        totalCats++;
        if (line[6] == '0')
          soldCats++;
        else
          availableCats++;
      }
      catFile.close();
    }

    cout << "Dogs:\n";
    cout << "  Total: " << totalDogs << "\n";
    cout << "  Sold: " << soldDogs << "\n";
    cout << "  Available: " << availableDogs << "\n\n";

    cout << "Cats:\n";
    cout << "  Total: " << totalCats << "\n";
    cout << "  Sold: " << soldCats << "\n";
    cout << "  Available: " << availableCats << "\n\n";

    cout << "Total Pets Sold: " << (soldDogs + soldCats) << "\n";
  }

  void calculateRevenueStats() {
    // Calculate Spa Revenue from completed bookings
    float spaRevenue = 0;
    LinkedList<Booking> allBookings = bookingRepo.getAllBookings();
    Node<Booking> *current = allBookings.getHead();

    while (current != nullptr) {
      if (current->getData().getStatus() == "Completed") {
        string serviceId = current->getData().getServiceId();
        float price = serviceRepo.getServicePrice(serviceId);
        spaRevenue += price;
      }
      current = current->getNext();
    }

    // Calculate Pet Sales Revenue (from sold pets)
    float petRevenue = 0;

    // Dogs
    ifstream dogFile("../data/Dog.txt");
    if (dogFile.is_open()) {
      string line;
      while (getline(dogFile, line)) {
        if (line.empty())
          continue;
        if (line[6] == '0') { // Sold
          stringstream ss(line);
          string id, status, name, breed, age, price, energy;
          getline(ss, id, '|');
          getline(ss, status, '|');
          getline(ss, name, '|');
          getline(ss, breed, '|');
          getline(ss, age, '|');
          getline(ss, price, '|');
          petRevenue += stof(price);
        }
      }
      dogFile.close();
    }

    // Cats
    ifstream catFile("../data/Cat.txt");
    if (catFile.is_open()) {
      string line;
      while (getline(catFile, line)) {
        if (line.empty())
          continue;
        stringstream ss(line);
        string id, name, breed, age, price, fur;
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, breed, '|');
        getline(ss, age, '|');
        getline(ss, price, '|');
        petRevenue += stof(price);
      }
      catFile.close();
    }

    float totalRevenue = spaRevenue + petRevenue;

    cout << "Spa Service Revenue: " << fixed << setprecision(0) << spaRevenue
         << " VND\n";
    cout << "Pet Sales Revenue: " << petRevenue << " VND\n";
    cout << "----------------------------------------\n";
    cout << "Total Revenue: " << totalRevenue << " VND\n";
  }

public:
  AdminController(Admin *admin) : currentAdmin(admin) {}

  void run() {
    int choice;
    do {
      Menu::clearScreen();
      Menu::displayAdminMenu(currentAdmin->getName());
      cin >> choice;
      cin.ignore();

      switch (choice) {
      case 1:
        manageAccounts();
        break;
      case 2:
        managePets();
        break;
      case 3:
        manageSpaServices();
        break;
      case 4:
        manageBookings();
        break;
      case 5:
        viewStatistics();
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