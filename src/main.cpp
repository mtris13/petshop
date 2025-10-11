#include "domain/entities/Client.hpp"
#include "domain/entities/Staff.hpp"
#include "domain/services/AuthService.hpp"
#include <iostream>
#include <typeinfo>

using namespace std;

int main() {
  AuthService auth;

  string username, password;
  cout << "Nhap ten dang nhap: ";
  cin >> username;
  cout << "Nhap mat khau: ";
  cin >> password;

  Account *user = auth.login(username, password);

  if (user) {
    cout << "---------------------------------\n";
    cout << "Thong tin tai khoan:\n";
    cout << "ID: " << user->getAccountId() << endl;
    cout << "Ten: " << user->getAccountName() << endl;
    cout << "Gioi tinh: " << user->getGender() << endl;
    cout << "Vai tro: " << user->getRole() << endl;

    // Kiểm tra kiểu thực tế của đối tượng bằng dynamic_cast
    if (auto staff = dynamic_cast<Staff *>(user)) {
      cout << "Luong: " << staff->getSalary() << endl;
    } else if (auto client = dynamic_cast<Client *>(user)) {
      cout << "Dia chi: " << client->getStreet() << ", "
           << client->getDistrict() << ", " << client->getCity() << endl;
    } else {
      cout << "Loai tai khoan khac (Admin hoac khong xac dinh).\n";
    }

    cout << "---------------------------------\n";
  } else {
    cout << "Dang nhap that bai.\n";
  }

  return 0;
}
