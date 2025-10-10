#pragma once
#include "infra/repositories/AccountRepofile.hpp"

class AuthService {
private:
  AccountRepository accountRepo;

public:
  AuthService() {}

  Account *login(const string &username, const string &password) {
    Account *acc = accountRepo.findAccountByNameAndPass(username, password);
    if (acc == nullptr) {
      cout << "Sai ten dang nhap hoac mat khau!\n";
    } else {
      cout << "Dang nhap thanh cong! Xin chao " << acc->getAccountName() << " ("
           << acc->getRole() << ")\n";
    }
    return acc;
  }
};
