// Làm việc với file lưu tài khoản
#pragma once
#include "domain/entities/Account.hpp"
#include "ds/LinkedList.hpp"
#include <fstream>
#include <sstream>

class AccountRepository {
private:
  string filePath;
  LinkedList<Account> accounts;

public:
  AccountRepository(const string &path = "../data/accounts.txt")
      : filePath(path) {
    loadFromFile();
  }

  void loadFromFile() {
    ifstream file(filePath);
    if (!file.is_open()) {
      cout << "Error: Cannot open accounts file.\n";
      return;
    }

    string line;
    while (getline(file, line)) {
      stringstream ss(line);
      string id, name, pass, role, gender;

      // file format: id|username|password|role
      getline(ss, id, '|');
      getline(ss, name, '|');
      getline(ss, pass, '|');
      getline(ss, role, '|');
      getline(ss, gender, '|'); // optional

      Account acc(id, name, pass, gender, role);
      accounts.pushBack(acc);
    }

    file.close();
  }

  Account *findAccountByNameAndPass(const string &name, const string &pass) {
    Node<Account> *current = accounts.getHead();
    while (current != nullptr) {
      Account acc = current->getData();
      if (acc.getAccountName() == name && acc.getPassword() == pass) {
        return &current->getData(); // return pointer to existing Account
      }
      current = current->getNext();
    }
    return nullptr;
  }

  LinkedList<Account> &getAllAccounts() { return accounts; }
};
