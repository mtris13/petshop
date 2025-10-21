/* Chức năng đăng nhập */
#include "domain/entities/Admin.hpp"
#include "domain/entities/Client.hpp"
#include "domain/entities/Staff.hpp"
#include "infra/repositories/AccountRepoFile.hpp"
// #include <conio.h>
#include <iostream>

using namespace std;

class AuthService {
private:
    AccountRepository accountRepo;
    const int AdminIdLength = 3;
    const int ClientIdLength = 10; // so dien thoai
    const int StaffIdLength = 5;

public:
    AuthService() = default;
    Account *login() {
        string id, pass;
        do {
            cout << "Enter your ID: ";
            cin >> id;
            cout << "Enter your password: ";
            cin >> pass;

            if (accountRepo.isValidPassword(id, pass)) {
                cout << "Login successfully! Welcome to PETSHOP.\n";
                return accountRepo.findAccountById(id);
            }

            cout << "Your ID or password is not correct!\n";
            cin.get();
            system("cls");
        } while (true);
    }

    Client *createClientAccount() {
        Client client;
        string id, name, pw, gender, street, city;
        do {
            cout << "Enter your phone number (ID): ";
            cin >> id;
            if (id.length() != ClientIdLength) {
                cout << "Unvalid phone number!\n";
                continue;
            }
            cout << "Enter your name: ";
            cin >> name;
            cout << "Enter your password: ";
            cin >> pw;
            cout << "1. Male\n2. Female\nEnter your gender: ";
            cin >> gender;
            gender = (gender == "1") ? "male" : "female"; // rcm chuyển thành ấn nút trong QT
            cout << "Enter your address: ";
            cin >> street;
            cout << "Enter your city: ";
            cin >> city;
            break;
        } while (true);
    }

    // WILL REMAKE

    // Account *login(const string &username, const string &password) {
    //   Account *acc = accountRepo.findAccountByNameAndPass(username, password);
    //   if (acc == nullptr) {
    //     cout << "Sai ten dang nhap hoac mat khau!\n";
    //     return nullptr;
    //   }

    //   cout << "Dang nhap thanh cong! Xin chao " << acc->getAccountName() << " ("
    //        << acc->getRole() << ")\n";

    //   // displayAccountInfo(acc);
    //   return acc;
    // }

    // void displayAccountInfo(Account *acc) {
    //   if (acc == nullptr) {
    //     cout << "Khong co tai khoan de hien thi.\n";
    //     return;
    //   }

    //   cout << "\n--- Thong tin tai khoan ---\n";
    //   cout << "ID: " << acc->getAccountId() << "\n";
    //   cout << "Ten dang nhap: " << acc->getAccountName() << "\n";
    //   cout << "Gioi tinh: " << acc->getGender() << "\n";
    //   cout << "Vai tro: " << acc->getRole() << "\n";

    //   // Kiem tra xem co phai Client hoac Staff khong
    //   if (acc->getRole() == "C") {
    //     Client *c = dynamic_cast<Client *>(acc);
    //     if (c != nullptr) {
    //       cout << "Dia chi: " << c->getStreet() << ", " << c->getDistrict()
    //            << ", " << c->getCity() << "\n";
    //     }
    //   } else if (acc->getRole() == "S") {
    //     Staff *s = dynamic_cast<Staff *>(acc);
    //     if (s != nullptr) {
    //       cout << "Luong: " << s->getSalary() << "\n";
    //     }
    //   }

    //   cout << "---------------------------\n";
    // }
};
