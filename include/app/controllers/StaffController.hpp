/* StaffController.hpp - Logic xử lý cho Staff */

#pragma once
#include "app/Menu.hpp"
#include "domain/entities/Staff.hpp"
#include "domain/services/SpaService.hpp"
#include "infra/repositories/PetRepoFile.hpp"
#include <ctime>
#include <iostream>

using namespace std;

class StaffController {
private:
  Staff *currentStaff;
  SpaService spaService;
  PetRepository petRepo;

  void viewPets() {
    Menu::displayHeader("PETS AVAILABLE");
    cout << "Feature coming soon...\n";
    // TODO: Display all available pets
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

public:
  StaffController(Staff *staff) : currentStaff(staff) {}

  void run() {
    int choice;
    do {
      Menu::clearScreen();
      Menu::displayStaffMenu(currentStaff->getName());
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