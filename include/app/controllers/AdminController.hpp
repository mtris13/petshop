/* AdminController.hpp - Logic xử lý cho Admin (COMPLETED) */

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
#include <algorithm>
#include <iomanip>
#include <iostream>

using namespace std;

class AdminController {
private:
    const int AdminIdLength = 3;
    const int StaffIdLength = 5;
    const int ClientIdLength = 10;
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
        int count = 0;

        // Admin accounts
        cout << "\n========== ADMIN ACCOUNTS ==========\n";
        cout << setw(8) << left << "ID" << setw(25) << left << "Name" << setw(10)
             << left << "Gender" << "\n";
        cout << string(43, '-') << "\n";

        LinkedList<Admin> admin = accountRepo.getAllAdminInfo();
        Node<Admin> *ad = admin.getHead();
        while (ad != nullptr) {
            cout << setw(8) << left << ad->getData().getId() << setw(25) << left << ad->getData().getName() << setw(10)
                 << left << ad->getData().getGender() << "\n";
            ad = ad->getNext();
            count++;
        }
        cout << "Total: " << count << " admin(s)\n";
        count = 0;

        // Staff accounts
        cout << "\n========== STAFF ACCOUNTS ==========\n";
        cout << setw(8) << left << "ID" << setw(25) << left << "Name" << setw(10)
             << left << "Gender" << setw(15) << right << "Salary" << "\n";
        cout << string(58, '-') << "\n";

        LinkedList<Staff> staffList = accountRepo.getAllStaffInfo();
        Node<Staff> *staffNode = staffList.getHead();
        while (staffNode != nullptr) {
            cout << setw(8) << left << staffNode->getData().getId()
                 << setw(25) << left << staffNode->getData().getName()
                 << setw(10) << left << staffNode->getData().getGender()
                 << setw(15) << right << fixed << setprecision(0) << staffNode->getData().getSalary() << "\n";
            staffNode = staffNode->getNext();
            count++;
        }
        cout << "Total: " << count << " staff(s)\n";
        count = 0;

        // Client accounts
        cout << "\n========== CLIENT ACCOUNTS ==========\n";
        cout << setw(13) << left << "Phone" << setw(25) << left << "Name"
             << setw(10) << left << "Gender" << setw(30) << left << "Address"
             << "\n";
        cout << string(78, '-') << "\n";

        LinkedList<Client> clients = accountRepo.getAllClientInfo();
        Node<Client> *clientNode = clients.getHead();
        while (clientNode != nullptr) {
            cout << setw(13) << left << clientNode->getData().getId() // Giả sử Id là Phone
                 << setw(25) << left << clientNode->getData().getName()
                 << setw(10) << left << clientNode->getData().getGender()
                 << setw(30) << left << clientNode->getData().getAddress() << "\n";
            clientNode = clientNode->getNext();
            count++;
        }
        cout << "Total: " << count << " client(s)\n";
    }

    void addStaffAccount() {
        Menu::displayHeader("ADD STAFF ACCOUNT");

        string id, name, password, gender;
        long salary;

        cout << "Enter Staff ID (5 characters, e.g., SV001): ";
        cin >> id;
        cin.ignore();

        if (id.length() != StaffIdLength) {
            Menu::displayError("Staff ID must be exactly 5 characters!");
            return;
        }

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
        string name, password, gender;

        if (length == AdminIdLength) { // Admin
            Admin admin = accountRepo.getAdminInfo(id);
            cout << "\nCurrent Info:\n"
                 << "Name: " << admin.getName() << "\n"
                 << "Gender: " << admin.getGender() << "\n";

            cout << "\nEnter New Name (or press Enter to keep): ";
            getline(cin, name);
            if (!name.empty())
                admin.setName(name);

            cout << "Enter New Password (or press Enter to keep): ";
            getline(cin, password);
            if (!password.empty())
                admin.setPassword(password);

            cout << "Enter New Gender (or press Enter to keep): ";
            getline(cin, gender);
            if (!gender.empty())
                admin.setGender(gender);

            accountRepo.setAdminInfo(admin);

        } else if (length == StaffIdLength) { // Staff
            Staff staff = accountRepo.getStaffInfo(id);
            cout << "\nCurrent Info:\n"
                 << "Name: " << staff.getName() << "\n"
                 << "Gender: " << staff.getGender() << "\n"
                 << "Salary: " << staff.getSalary() << "\n";

            cout << "\nEnter New Name (or press Enter to keep): ";
            getline(cin, name);
            if (!name.empty())
                staff.setName(name);

            cout << "Enter New Password (or press Enter to keep): ";
            getline(cin, password);
            if (!password.empty())
                staff.setPassword(password);

            cout << "Enter New Gender (or press Enter to keep): ";
            getline(cin, gender);
            if (!gender.empty())
                staff.setGender(gender);

            string salaryStr;
            while (true) {
                cout << "Enter New Salary (or press Enter to keep): ";
                getline(cin, salaryStr);

                if (salaryStr.empty()) {
                    break;
                }
                try {
                    long number = stol(salaryStr);
                    staff.setSalary(number);
                    break;
                } catch (const std::invalid_argument &e) {
                    std::cerr << "Error: Input is not a number. Please try again.\n";
                } catch (const std::out_of_range &e) {
                    std::cerr << "Error: Number is too large or too small. Please try again.\n";
                }
            }
            accountRepo.setStaffInfo(staff);

        } else if (length == ClientIdLength) { // Client
            Client client = accountRepo.getClientInfo(id);
            cout << "\nCurrent Info:\n"
                 << "Name: " << client.getName() << "\n"
                 << "Gender: " << client.getGender() << "\n"
                 << "Address: " << client.getStreet() << ", " << client.getCity() << "\n";

            cout << "\nEnter New Name (or press Enter to keep): ";
            getline(cin, name);
            if (!name.empty())
                client.setName(name);

            cout << "Enter New Password (or press Enter to keep): ";
            getline(cin, password);
            if (!password.empty())
                client.setPassword(password);

            cout << "Enter New Gender (or press Enter to keep): ";
            getline(cin, gender);
            if (!gender.empty())
                client.setGender(gender);

            string street, city;
            cout << "Enter New Street (or press Enter to keep): ";
            getline(cin, street);
            if (!street.empty())
                client.setStreet(street);

            cout << "Enter New City (or press Enter to keep): ";
            getline(cin, city);
            if (!city.empty())
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

        if (id.length() == AdminIdLength) {
            Menu::displayError("Cannot delete admin accounts!");
            return;
        }

        char confirm;
        cout << "Are you sure you want to delete this account? (y/n): ";
        cin >> confirm;

        if (confirm == 'y' || confirm == 'Y') {
            accountRepo.deleteAccount(id);
            Menu::displaySuccess("Account deleted successfully!");
        } else {
            Menu::displayInfo("Deletion cancelled.");
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

        if (length == AdminIdLength) {
            Admin admin = accountRepo.getAdminInfo(id);
            cout << "\n========== ADMIN ACCOUNT ==========\n";
            cout << "ID: " << admin.getId() << "\n";
            cout << "Name: " << admin.getName() << "\n";
            cout << "Gender: " << admin.getGender() << "\n";
            cout << "===================================\n";

        } else if (length == StaffIdLength) {
            Staff staff = accountRepo.getStaffInfo(id);
            cout << "\n========== STAFF ACCOUNT ==========\n";
            cout << "ID: " << staff.getId() << "\n";
            cout << "Name: " << staff.getName() << "\n";
            cout << "Gender: " << staff.getGender() << "\n";
            cout << "Salary: " << fixed << setprecision(0) << staff.getSalary() << " VND\n";
            cout << "===================================\n";

        } else if (length == ClientIdLength) {
            Client client = accountRepo.getClientInfo(id);
            cout << "\n========== CLIENT ACCOUNT ==========\n";
            cout << "ID (Phone): " << client.getId() << "\n";
            cout << "Name: " << client.getName() << "\n";
            cout << "Gender: " << client.getGender() << "\n";
            cout << "Address: " << client.getAddress() << "\n";
            cout << "====================================\n";
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

        // ======== DOGS ========
        cout << "\n========== DOGS ==========\n";
        cout << setw(6) << left << "ID" << setw(6) << left << "Sold" << setw(15)
             << left << "Name" << setw(20) << left << "Breed" << setw(5) << right
             << "Age" << setw(12) << right << "Price" << setw(8) << right
             << "     Energy"
             << "\n";
        cout << string(75, '-') << "\n";

        ifstream dogFile("../data/Dog.txt");
        int dogCount = 0;
        if (dogFile.is_open()) {
            string line;
            while (getline(dogFile, line)) {
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

                string soldStatus = (status == "0") ? "Yes" : "No";

                cout << setw(6) << left << id << setw(6) << left << soldStatus
                     << setw(15) << left << name << setw(20) << left << breed << setw(5)
                     << right << age << setw(12) << right << fixed << setprecision(0)
                     << stof(price) << setw(8) << right << energy << "/10\n";
                dogCount++;
            }
            dogFile.close();
        }
        cout << "Total Dogs: " << dogCount << "\n";

        // ======== CATS ========
        cout << "\n========== CATS ==========\n";
        cout << setw(6) << left << "ID" << setw(6) << left << "Sold" << setw(15)
             << left << "Name" << setw(20) << left << "Breed" << setw(5) << right
             << "Age" << setw(12) << right << "Price" << setw(10) << left
             << "          Fur"
             << "\n";
        cout << string(80, '-') << "\n";

        ifstream catFile("../data/Cat.txt");
        int catCount = 0;
        if (catFile.is_open()) {
            string line;
            while (getline(catFile, line)) {
                if (line.empty())
                    continue;
                stringstream ss(line);
                string id, status, name, breed, age, price, fur;
                getline(ss, id, '|');
                getline(ss, status, '|');
                getline(ss, name, '|');
                getline(ss, breed, '|');
                getline(ss, age, '|');
                getline(ss, price, '|');
                getline(ss, fur, '|');

                string soldStatus = (status == "0") ? "Yes" : "No";

                cout << setw(6) << left << id << setw(6) << left << soldStatus
                     << setw(15) << left << name << setw(20) << left << breed << setw(5)
                     << right << age << setw(12) << right << fixed << setprecision(0)
                     << stof(price) << setw(10) << left << "" << fur << "\n";
                catCount++;
            }
            catFile.close();
        }
        cout << "Total Cats: " << catCount << "\n";

        cout << "\nGrand Total: " << (dogCount + catCount) << " pets\n";
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
        long price;

        cout << "Enter Pet ID (e.g., d011 or c011): ";
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
        cout << "Enter Age (years): ";
        cin >> age;
        cout << "Enter Price (VND): ";
        cin >> price;
        string desc;
        cout << "Enter description: ";
        cin.ignore();
        getline(cin, desc);

        if (type == 1) {
            int energy;
            cout << "Enter Energy Level (1-10): ";
            cin >> energy;

            if (energy < 1 || energy > 10) {
                Menu::displayError("Energy level must be between 1 and 10!");
                return;
            }

            Dog newDog(id, name, breed, age, price, 1, energy, desc);
            petRepo.setDogInfo(newDog);
            Menu::displaySuccess("Dog added successfully!");

        } else if (type == 2) {
            string furLength;
            cout << "Enter Fur Length (Short/Medium/Long): ";
            cin >> furLength;

            Cat newCat = Cat(id, name, breed, age, price, 1, furLength, desc);
            petRepo.setCatInfo(newCat);
            Menu::displaySuccess("Cat added successfully!");

        } else {
            Menu::displayError("Invalid pet type!");
        }
    }

    void updatePet() {
        Menu::displayHeader("UPDATE PET");

        string id;
        cout << "Enter Pet ID to update: ";
        cin >> id;
        cin.ignore();

        if (!petRepo.isValidPetId(id)) {
            Menu::displayError("Pet not found!");
            return;
        }

        if (id[0] == 'd') {
            // Update Dog
            Dog dog = petRepo.getDogInfo(id);
            cout << "\nCurrent Info:\n";
            cout << "Name: " << dog.getName() << "\n";
            cout << "Breed: " << dog.getBreed() << "\n";
            cout << "Age: " << dog.getAge() << "\n";
            cout << "Price: " << dog.getPrice() << "\n";
            cout << "Energy: " << dog.getEnergyLevel() << "\n";

            string name, breed, ageStr, priceStr, energyStr;

            cout << "\nEnter New Name (or press Enter to keep): ";
            getline(cin, name);
            if (name.empty())
                name = dog.getName();

            cout << "Enter New Breed (or press Enter to keep): ";
            getline(cin, breed);
            if (breed.empty())
                breed = dog.getBreed();

            cout << "Enter New Age (or press Enter to keep): ";
            getline(cin, ageStr);
            int age = ageStr.empty() ? dog.getAge() : stoi(ageStr);

            cout << "Enter New Price (or press Enter to keep): ";
            getline(cin, priceStr);
            long price = priceStr.empty() ? dog.getPrice() : stof(priceStr);

            cout << "Enter New Energy Level (or press Enter to keep): ";
            getline(cin, energyStr);
            int energy = energyStr.empty() ? dog.getEnergyLevel() : stoi(energyStr);

            dog.setName(name);
            dog.setBreed(breed);
            dog.setAge(age);
            dog.setPrice(price);
            dog.setEnergyLevel(energy);

            petRepo.setDogInfo(dog);
            Menu::displaySuccess("Dog updated successfully!");

        } else {
            // Update Cat
            Cat cat = petRepo.getCatInfo(id);
            cout << "\nCurrent Info:\n";
            cout << "Name: " << cat.getName() << "\n";
            cout << "Breed: " << cat.getBreed() << "\n";
            cout << "Age: " << cat.getAge() << "\n";
            cout << "Price: " << cat.getPrice() << "\n";
            cout << "Fur Length: " << cat.getFurLength() << "\n";

            string name, breed, ageStr, priceStr, fur;

            cout << "\nEnter New Name (or press Enter to keep): ";
            getline(cin, name);
            if (name.empty())
                name = cat.getName();

            cout << "Enter New Breed (or press Enter to keep): ";
            getline(cin, breed);
            if (breed.empty())
                breed = cat.getBreed();

            cout << "Enter New Age (or press Enter to keep): ";
            getline(cin, ageStr);
            int age = ageStr.empty() ? cat.getAge() : stoi(ageStr);

            cout << "Enter New Price (or press Enter to keep): ";
            getline(cin, priceStr);
            long price = priceStr.empty() ? cat.getPrice() : stof(priceStr);

            cout << "Enter New Fur Length (or press Enter to keep): ";
            getline(cin, fur);
            if (fur.empty())
                fur = cat.getFurLength();

            cat.setName(name);
            cat.setBreed(breed);
            cat.setAge(age);
            cat.setPrice(price);
            cat.setFurLength(fur);

            petRepo.setCatInfo(cat);
            Menu::displaySuccess("Cat updated successfully!");
        }
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
        cout << "Are you sure you want to delete this pet? (y/n): ";
        cin >> confirm;

        if (confirm == 'y' || confirm == 'Y') {
            petRepo.deletePet(id);
            Menu::displaySuccess("Pet deleted successfully!");
        } else {
            Menu::displayInfo("Deletion cancelled.");
        }
    }

    void searchPet() {
        Menu::displayHeader("SEARCH PET");

        cout << "Search by:\n";
        cout << "1. Pet ID\n";
        cout << "2. Name\n";
        cout << "3. Breed\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string id;
            cout << "Enter Pet ID: ";
            cin >> id;

            if (!petRepo.isValidPetId(id)) {
                Menu::displayError("Pet not found!");
                return;
            }

            if (id[0] == 'd') {
                Dog dog = petRepo.getDogInfo(id);
                cout << "\n=== DOG FOUND ===\n";
                cout << "ID: " << dog.getId() << "\n";
                cout << "Name: " << dog.getName() << "\n";
                cout << "Breed: " << dog.getBreed() << "\n";
                cout << "Age: " << dog.getAge() << "\n";
                cout << "Price: " << dog.getPrice() << "\n";
                cout << "Energy: " << dog.getEnergyLevel() << "/10\n";
            } else {
                Cat cat = petRepo.getCatInfo(id);
                cout << "\n=== CAT FOUND ===\n";
                cout << "ID: " << cat.getId() << "\n";
                cout << "Name: " << cat.getName() << "\n";
                cout << "Breed: " << cat.getBreed() << "\n";
                cout << "Age: " << cat.getAge() << "\n";
                cout << "Price: " << cat.getPrice() << "\n";
                cout << "Fur Length: " << cat.getFurLength() << "\n";
            }

        } else if (choice == 2 || choice == 3) {
            string keyword;
            cout << "Enter search keyword: ";
            getline(cin, keyword);

            // Convert to lowercase for case-insensitive search
            transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);

            bool found = false;

            // Search in Dogs
            ifstream dogFile("../data/Dog.txt");
            if (dogFile.is_open()) {
                string line;
                while (getline(dogFile, line)) {
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

                    string searchField = (choice == 2) ? name : breed;
                    transform(searchField.begin(), searchField.end(), searchField.begin(),
                              ::tolower);

                    if (searchField.find(keyword) != string::npos) {
                        if (!found) {
                            cout << "\n=== SEARCH RESULTS ===\n";
                            found = true;
                        }
                        cout << "\n[DOG] " << id << " - " << name << "\n";
                        cout << "Breed: " << breed << ", Age: " << age
                             << ", Price: " << price << ", Energy: " << energy << "/10\n";
                    }
                }
                dogFile.close();
            }

            // Search in Cats
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
                    getline(ss, fur, '|');

                    string searchField = (choice == 2) ? name : breed;
                    transform(searchField.begin(), searchField.end(), searchField.begin(),
                              ::tolower);

                    if (searchField.find(keyword) != string::npos) {
                        if (!found) {
                            cout << "\n=== SEARCH RESULTS ===\n";
                            found = true;
                        }
                        cout << "\n[CAT] " << id << " - " << name << "\n";
                        cout << "Breed: " << breed << ", Age: " << age
                             << ", Price: " << price << ", Fur: " << fur << "\n";
                    }
                }
                catFile.close();
            }

            if (!found) {
                Menu::displayInfo("No pets found matching your search.");
            }

        } else {
            Menu::displayError("Invalid choice!");
        }
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
        long price;
        int duration;

        cout << "Enter Service ID (e.g., SP011): ";
        cin >> id;
        cin.ignore();
        cout << "Enter Service Name: ";
        getline(cin, name);
        cout << "Enter Description: ";
        getline(cin, desc);
        cout << "Enter Price (VND): ";
        cin >> price;
        cout << "Enter Duration (minutes): ";
        cin >> duration;

        spaService.addSpaService(id, name, desc, price, duration);
    }

    void updateSpaService() {
        Menu::displayHeader("UPDATE SPA SERVICE");

        string id, name, desc;
        long price;
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
        int choice;
        do {
            system("cls");
            Menu::displayHeader("SYSTEM STATISTICS");
            cout << "1. Account Statistics\n";
            cout << "2. Pet Inventory Statistics\n";
            cout << "3. Spa Service Statistics\n";
            cout << "4. Revenue Statistics\n";
            cout << "0. Back\n";
            cout << "==============================\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore(); // tránh lỗi khi nhập chuỗi sau đó

            switch (choice) {
            case 1: {
                cout << "\n========== ACCOUNTS ==========\n";
                int adminCount = 0, staffCount = 0, clientCount = 0;

                ifstream adminFile("../data/AdminAccount.txt");
                if (adminFile.is_open()) {
                    string line;
                    while (getline(adminFile, line))
                        if (!line.empty())
                            adminCount++;
                    adminFile.close();
                }

                ifstream staffFile("../data/StaffAccount.txt");
                if (staffFile.is_open()) {
                    string line;
                    while (getline(staffFile, line))
                        if (!line.empty())
                            staffCount++;
                    staffFile.close();
                }

                ifstream clientFile("../data/ClientAccount.txt");
                if (clientFile.is_open()) {
                    string line;
                    while (getline(clientFile, line))
                        if (!line.empty())
                            clientCount++;
                    clientFile.close();
                }

                cout << "Admins: " << adminCount << "\n";
                cout << "Staff: " << staffCount << "\n";
                cout << "Clients: " << clientCount << "\n";
                cout << "Total Users: " << (adminCount + staffCount + clientCount)
                     << "\n";
                break;
            }

            case 2:
                cout << "\n========== PET INVENTORY ==========\n";
                calculatePetSalesStats();
                break;

            case 3:
                cout << "\n========== SPA SERVICES ==========\n";
                spaService.showStatistics();
                break;

            case 4:
                cout << "\n========== REVENUE STATISTICS ==========\n";
                calculateRevenueStats();
                break;

            case 0:
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
            }

            if (choice != 0) {
                cout << "\nPress Enter to continue...";
                cin.ignore();
            }

        } while (choice != 0);
    }

    void calculatePetSalesStats() {
        int totalDogs = 0, soldDogs = 0, availableDogs = 0;
        int totalCats = 0, soldCats = 0, availableCats = 0;

        // ===== DOGS =====
        ifstream dogFile("../data/Dog.txt");
        if (dogFile.is_open()) {
            string line;
            while (getline(dogFile, line)) {
                if (line.empty())
                    continue;

                totalDogs++;

                // Tách dữ liệu bằng delimiter '|'
                stringstream ss(line);
                string id, status, name, breed, age, price, energy;
                getline(ss, id, '|');
                getline(ss, status, '|');
                getline(ss, name, '|');
                getline(ss, breed, '|');
                getline(ss, age, '|');
                getline(ss, price, '|');
                getline(ss, energy, '|');

                if (status == "1")
                    availableDogs++;
                else if (status == "0")
                    soldDogs++;
            }
            dogFile.close();
        } else {
            cout << "Error: Cannot open Dog.txt\n";
        }

        // ===== CATS =====
        ifstream catFile("../data/Cat.txt");
        if (catFile.is_open()) {
            string line;
            while (getline(catFile, line)) {
                if (line.empty())
                    continue;

                totalCats++;

                // Tách dữ liệu bằng delimiter '|'
                stringstream ss(line);
                string id, status, name, breed, age, price, fur;

                getline(ss, id, '|');
                getline(ss, status,
                        '|'); // Nếu Cat.txt chưa có status, thêm xử lý dự phòng

                if (status == "0")
                    soldCats++;
                else
                    availableCats++;
            }
            catFile.close();
        } else {
            cout << "Error: Cannot open Cat.txt\n";
        }

        cout << "\n========== PET SALES STATISTICS ==========\n";
        cout << "Dogs:\n";
        cout << "  Total: " << totalDogs << "\n";
        cout << "  Available: " << availableDogs << "\n";
        cout << "  Sold: " << soldDogs << "\n\n";

        cout << "Cats:\n";
        cout << "  Total: " << totalCats << "\n";
        cout << "  Available: " << availableCats << "\n";
        cout << "  Sold: " << soldCats << "\n\n";

        cout << "Overall:\n";
        cout << "  Total Pets: " << (totalDogs + totalCats) << "\n";
        cout << "  Total Available: " << (availableDogs + availableCats) << "\n";
        cout << "  Total Sold: " << (soldDogs + soldCats) << "\n";
        cout << "==========================================\n";
    }

    void calculateRevenueStats() {
        // ===== SPA REVENUE =====
        long spaRevenue = 0;
        LinkedList<Booking> allBookings = bookingRepo.getAllBookings();
        Node<Booking> *current = allBookings.getHead();

        while (current != nullptr) {
            const Booking &booking = current->getData();
            if (booking.getStatus() == "Completed") {
                string serviceId = booking.getServiceId();
                long price = serviceRepo.getServicePrice(serviceId);
                spaRevenue += price;
            }
            current = current->getNext();
        }

        // ===== PET SALES REVENUE =====
        long petRevenue = 0;
        int soldPetsCount = 0;

        // --- Dogs ---
        ifstream dogFile("../data/Dog.txt");
        if (dogFile.is_open()) {
            string line;
            while (getline(dogFile, line)) {
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

                if (status == "0") { // sold
                    try {
                        petRevenue += stof(price);
                        soldPetsCount++;
                    } catch (...) {
                        cerr << "Warning: Invalid price for dog " << id << "\n";
                    }
                }
            }
            dogFile.close();
        } else {
            cerr << "Error: Cannot open Dog.txt\n";
        }

        // --- Cats ---
        ifstream catFile("../data/Cat.txt");
        if (catFile.is_open()) {
            string line;
            while (getline(catFile, line)) {
                if (line.empty())
                    continue;

                stringstream ss(line);
                string id, status, name, breed, age, price, fur;

                getline(ss, id, '|');
                getline(ss, status, '|'); // nếu chưa có status thì vẫn đọc rỗng
                getline(ss, name, '|');
                getline(ss, breed, '|');
                getline(ss, age, '|');
                getline(ss, price, '|');
                getline(ss, fur, '|');

                if (status == "0") { // sold
                    try {
                        petRevenue += stof(price);
                        soldPetsCount++;
                    } catch (...) {
                        cerr << "Warning: Invalid price for cat " << id << "\n";
                    }
                }
            }
            catFile.close();
        } else {
            cerr << "Error: Cannot open Cat.txt\n";
        }

        // ===== TOTAL =====
        long totalRevenue = spaRevenue + petRevenue;

        cout << "\n========== REVENUE REPORT ==========\n";
        cout << "Pet Sales:\n";
        cout << "  Pets Sold: " << soldPetsCount << "\n";
        cout << "  Revenue: " << fixed << setprecision(0) << petRevenue
             << " VND\n\n";

        cout << "Spa Services:\n";
        cout << "  Revenue: " << spaRevenue << " VND\n\n";

        cout << "----------------------------------------\n";
        cout << "TOTAL REVENUE: " << totalRevenue << " VND\n";
        cout << "----------------------------------------\n";

        // Breakdown percentages
        if (totalRevenue > 0) {
            cout << "\nRevenue Breakdown:\n";
            cout << "  Pet Sales: " << fixed << setprecision(1)
                 << (petRevenue / totalRevenue * 100) << "%\n";
            cout << "  Spa Services: " << (spaRevenue / totalRevenue * 100) << "%\n";
        }

        cout << "========================================\n";
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