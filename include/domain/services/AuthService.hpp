#include "domain/entities/Client.hpp"
#include "domain/entities/Staff.hpp"
#include "infra/repositories/AccountRepoFile.hpp"
#include <iostream>

using namespace std;

class AuthService {
private:
  AccountRepository accountRepo;

public:
  AuthService() = default;

  Account *login(const string &username, const string &password) {
    Account *acc = accountRepo.findAccountByNameAndPass(username, password);
    if (acc == nullptr) {
      cout << "Sai ten dang nhap hoac mat khau!\n";
      return nullptr;
    }

    cout << "Dang nhap thanh cong! Xin chao " << acc->getAccountName() << " ("
         << acc->getRole() << ")\n";

    // displayAccountInfo(acc);
    return acc;
  }

  void displayAccountInfo(Account *acc) {
    if (acc == nullptr) {
      cout << "Khong co tai khoan de hien thi.\n";
      return;
    }

    cout << "\n--- Thong tin tai khoan ---\n";
    cout << "ID: " << acc->getAccountId() << "\n";
    cout << "Ten dang nhap: " << acc->getAccountName() << "\n";
    cout << "Gioi tinh: " << acc->getGender() << "\n";
    cout << "Vai tro: " << acc->getRole() << "\n";

    // Kiem tra xem co phai Client hoac Staff khong
    if (acc->getRole() == "C") {
      Client *c = dynamic_cast<Client *>(acc);
      if (c != nullptr) {
        cout << "Dia chi: " << c->getStreet() << ", " << c->getDistrict()
             << ", " << c->getCity() << "\n";
      }
    } else if (acc->getRole() == "S") {
      Staff *s = dynamic_cast<Staff *>(acc);
      if (s != nullptr) {
        cout << "Luong: " << s->getSalary() << "\n";
      }
    }

    cout << "---------------------------\n";
  }
};
