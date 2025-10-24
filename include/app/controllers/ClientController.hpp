/* ClientController.hpp - Logic xử lý cho Client */

#pragma once
#include "app/Menu.hpp"
#include "domain/entities/Client.hpp"
#include "domain/services/SpaService.hpp"
#include "infra/repositories/AccountRepoFile.hpp"
#include "infra/repositories/PetRepoFile.hpp"

#include <iostream>

using namespace std;

class ClientController {
private:
  Client *currentClient;
  SpaService spaService;
  PetRepository petRepo;
  void viewPetsForSale() {
    Menu::displayHeader("PETS FOR SALE");
    cout << "Feature coming soon...\n";
    // TODO: Display available pets for purchase
  }

  void viewSpaServices() {
    Menu::clearScreen();
    spaService.displayAllSpaServices();
  }

  void bookSpaService() {
    Menu::displayHeader("BOOK SPA SERVICE");

    // Show available services first
    spaService.displayAllSpaServices();

    cout << "\n";
    string petId, serviceId, date, time;

    cout << "Enter Pet ID: ";
    cin >> petId;

    // Validate pet exists
    if (!petRepo.isValidPetId(petId)) {
      Menu::displayError("Invalid Pet ID!");
      return;
    }

    cout << "Enter Service ID: ";
    cin >> serviceId;

    cout << "Enter Date (dd/mm/yyyy): ";
    cin >> date;

    cout << "Enter Time (hh:mm): ";
    cin >> time;

    spaService.createBooking(currentClient->getId(), petId, serviceId, date,
                             time);
  }

  void viewMyBookings() {
    Menu::clearScreen();
    Menu::displayHeader("MY BOOKINGS");
    spaService.viewMyBookings(currentClient->getId());
  }

  void cancelMyBooking() {
    Menu::displayHeader("CANCEL BOOKING");

    // Show my bookings first
    spaService.viewMyBookings(currentClient->getId());

    cout << "\n";
    string bookingId;
    cout << "Enter Booking ID to cancel: ";
    cin >> bookingId;

    spaService.cancelBooking(bookingId);
  }

  void viewMyProfile() {
    Menu::displayHeader("MY PROFILE");

    cout << "\n=== CLIENT INFORMATION ===\n";
    cout << "ID: " << currentClient->getId() << "\n";
    cout << "Name: " << currentClient->getName() << "\n";
    cout << "Gender: " << currentClient->getGender() << "\n";
    cout << "Address: " << currentClient->getStreet() << ", "
         << currentClient->getCity() << "\n";
    cout << "==========================\n";

    cout << "\nDo you want to update your profile? (y/n): ";
    char choice;
    cin >> choice;
    cin.ignore();

    if (choice == 'y' || choice == 'Y') {
      updateProfile();
    }
  }

  void updateProfile() {
    Menu::displayHeader("UPDATE PROFILE");

    string name, password, gender, street, city;

    cout << "Enter New Name (or press Enter to keep current): ";
    getline(cin, name);
    if (name.empty())
      name = currentClient->getName();

    cout << "Enter New Password (or press Enter to keep current): ";
    getline(cin, password);
    if (password.empty())
      password = currentClient->getPassword();

    cout << "Enter New Gender (male/female, or press Enter to keep current): ";
    getline(cin, gender);
    if (gender.empty())
      gender = currentClient->getGender();

    cout << "Enter New Street (or press Enter to keep current): ";
    getline(cin, street);
    if (street.empty())
      street = currentClient->getStreet();

    cout << "Enter New City (or press Enter to keep current): ";
    getline(cin, city);
    if (city.empty())
      city = currentClient->getCity();

    // Update client object
    currentClient->setName(name);
    currentClient->setPassword(password);
    currentClient->setGender(gender);
    currentClient->setStreet(street);
    currentClient->setCity(city);

    // Save to file
    AccountRepository accountRepo;
    accountRepo.setClientInfo(*currentClient);

    Menu::displaySuccess("Profile updated successfully!");
  }

public:
  ClientController(Client *client) : currentClient(client) {}

  void run() {
    int choice;
    do {
      Menu::clearScreen();
      Menu::displayClientMenu(currentClient->getName());
      cin >> choice;
      cin.ignore();

      switch (choice) {
      case 1:
        viewPetsForSale();
        Menu::pause();
        break;
      case 2:
        viewSpaServices();
        Menu::pause();
        break;
      case 3:
        bookSpaService();
        Menu::pause();
        break;
      case 4:
        viewMyBookings();
        Menu::pause();
        break;
      case 5:
        cancelMyBooking();
        Menu::pause();
        break;
      case 6:
        viewMyProfile();
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