
#include "domain/services/SpaService.hpp"
#include <iostream>

using namespace std;

void displayMenu() {
  cout << "\n========== SPA SERVICE MENU ==========\n";
  cout << "1. View All Spa Services\n";
  cout << "2. View Service Details\n";
  cout << "3. Create Booking\n";
  cout << "4. Cancel Booking\n";
  cout << "5. View My Bookings\n";
  cout << "6. View Booking Details\n";
  cout << "7. View All Bookings (Admin)\n";
  cout << "8. View Bookings by Date\n";
  cout << "9. Confirm Booking (Staff)\n";
  cout << "10. Complete Booking (Staff)\n";
  cout << "11. Add New Service (Admin)\n";
  cout << "12. Update Service (Admin)\n";
  cout << "13. Delete Service (Admin)\n";
  cout << "14. Show Statistics\n";
  cout << "0. Exit\n";
  cout << "======================================\n";
  cout << "Enter your choice: ";
}

int main() {
  SpaService spaService;
  int choice;
  string clientId = "0123456789"; // Demo client ID

  do {
    displayMenu();
    cin >> choice;
    cin.ignore(); // Clear buffer

    switch (choice) {
    case 1: {
      // Xem tất cả dịch vụ spa
      spaService.displayAllSpaServices();
      break;
    }

    case 2: {
      // Xem chi tiết dịch vụ
      string serviceId;
      cout << "Enter Service ID: ";
      cin >> serviceId;
      spaService.displaySpaServiceDetails(serviceId);
      break;
    }

    case 3: {
      // Đặt lịch
      string petId, serviceId, date, time;
      cout << "Enter Pet ID: ";
      cin >> petId;
      cout << "Enter Service ID: ";
      cin >> serviceId;
      cout << "Enter Date (dd/mm/yyyy): ";
      cin >> date;
      cout << "Enter Time (hh:mm): ";
      cin >> time;

      spaService.createBooking(clientId, petId, serviceId, date, time);
      break;
    }

    case 4: {
      // Hủy booking
      string bookingId;
      cout << "Enter Booking ID to cancel: ";
      cin >> bookingId;
      spaService.cancelBooking(bookingId);
      break;
    }

    case 5: {
      // Xem lịch của tôi
      spaService.viewMyBookings(clientId);
      break;
    }

    case 6: {
      // Xem chi tiết booking
      string bookingId;
      cout << "Enter Booking ID: ";
      cin >> bookingId;
      spaService.viewBookingDetails(bookingId);
      break;
    }

    case 7: {
      // Xem tất cả bookings (Admin)
      spaService.viewAllBookings();
      break;
    }

    case 8: {
      // Xem bookings theo ngày
      string date;
      cout << "Enter Date (dd/mm/yyyy): ";
      cin >> date;
      spaService.viewBookingsByDate(date);
      break;
    }

    case 9: {
      // Xác nhận booking (Staff)
      string bookingId;
      cout << "Enter Booking ID to confirm: ";
      cin >> bookingId;
      spaService.confirmBooking(bookingId);
      break;
    }

    case 10: {
      // Hoàn thành booking
      string bookingId;
      cout << "Enter Booking ID to complete: ";
      cin >> bookingId;
      spaService.completeBooking(bookingId);
      break;
    }

    case 11: {
      // Thêm dịch vụ mới (Admin)
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
      break;
    }

    case 12: {
      // Cập nhật dịch vụ (Admin)
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
      break;
    }

    case 13: {
      // Xóa dịch vụ (Admin)
      string id;
      cout << "Enter Service ID to delete: ";
      cin >> id;

      char confirm;
      cout << "Are you sure? (y/n): ";
      cin >> confirm;
      if (confirm == 'y' || confirm == 'Y') {
        spaService.deleteSpaService(id);
      }
      break;
    }

    case 14: {
      // Thống kê
      spaService.showStatistics();
      break;
    }

    case 0: {
      cout << "Thank you for using Spa Service!\n";
      break;
    }

    default: {
      cout << "Invalid choice! Please try again.\n";
      break;
    }
    }

    if (choice != 0) {
      cout << "\nPress Enter to continue...";
      cin.get();
    }

  } while (choice != 0);

  return 0;
}