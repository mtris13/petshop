#pragma once
#include "domain/entities/Account.hpp"
#include "domain/entities/Client.hpp"
#include "domain/entities/Staff.hpp"

#include "ds/LinkedList.hpp"
#include <fstream>
#include <sstream>

class AccountRepository {
private:
  string filePath;
  LinkedList<Account *> accounts;

public:
  AccountRepository(const string &path = "../data/accounts.txt")
      : filePath(path) {
    loadFromFile();
  }

  void loadFromFile() {
    ifstream file(filePath);
    if (!file.is_open()) {
      cerr << "Error: Cannot open accounts file.\n";
      return;
    }

    string line;
    while (getline(file, line)) {
      stringstream ss(line);
      string id, name, pass, gender, role;
      getline(ss, id, '|');
      getline(ss, name, '|');
      getline(ss, pass, '|');
      getline(ss, gender, '|');
      getline(ss, role, '|');

      Account *acc = nullptr;

      if (role == "C") {
        string street, district, city;
        getline(ss, street, '|');
        getline(ss, district, '|');
        getline(ss, city, '|');
        acc = new Client(id, name, pass, gender, street, district, city);
      } else if (role == "S") {
        double salary;
        ss >> salary;
        acc = new Staff(id, name, pass, gender, salary);
      } else {
        acc = new Account(id, name, pass, gender, role);
      }

      accounts.pushBack(acc);
    }

    file.close();
  }

  Account *findAccountByNameAndPass(const string &name, const string &pass) {
    Node<Account *> *current = accounts.getHead();
    while (current != nullptr) {
      Account *acc = current->getData();
      if (acc->getAccountName() == name && acc->getPassword() == pass) {
        return acc;
      }
      current = current->getNext();
    }
    return nullptr;
  }

  LinkedList<Account *> &getAllAccounts() { return accounts; }
};
