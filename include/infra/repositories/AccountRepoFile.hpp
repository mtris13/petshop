#pragma once
#include "domain/entities/Admin.hpp"
#include "domain/entities/Client.hpp"
#include "domain/entities/Staff.hpp"
#include <fstream>
#include <sstream>
#include <vector>

class AccountRepoFile {
private:
  string filePath;

public:
  AccountRepoFile(const string &path) : filePath(path) {}
  vector<Account *> getAllAccounts() {
    vector<Account *> accounts;
    ifstream file(filePath);
    string line;
    while (getline(file, line)) {
      stringstream ss(line);
      string id, username, password, email, role;
      getline(ss, id, '|');
      getline(ss, username, '|');
      getline(ss, password, '|');
      getline(ss, email, '|');

      // if (role == "ADMIN") {
      //     accounts.push_back( username, password, email));
      // } else if (role == "STAFF") {
      //     string salaryStr;
      //     getline(ss, salaryStr, '|');
      //     double salary = stod(salaryStr);
      //     accounts.push_back(new Staff(stoi(id), username, password, email,
      //     salary));
      // } else if (role == "CLIENT") {
      //     accounts.push_back(new Client(stoi(id), username, password,
      //     email));
      // }
    }
    return accounts;
  }
};
