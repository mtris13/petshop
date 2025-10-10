#include "domain/services/AuthService.hpp"
#include <iostream>

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
    cout << "Da dang nhap voi vai tro: " << user->getRole() << endl;
  }

  return 0;
}
