#pragma once

#include <iostream>
#include <string>
using namespace std;

class Account {
protected:
  string accountId;
  string accountName;
  string password;
  string gender;

public:
  Account() : accountId(""), accountName(""), password(""), gender("") {}
  Account(const string &Id, const string &Name, const string &Pass,
          const string &Gen)
      : accountId(Id), accountName(Name), password(Pass), gender(Gen) {}

  // Getter
  string getAccountId() const { return accountId; }
  string getAccountName() const { return accountName; }
  string getPassword() const { return password; }
  string getGender() const { return gender; }

  // Setter
  void setAccountId(const string &id) { this->accountId = id; }
  void setAccountName(const string &name) { this->accountName = name; }
  void setPassword(const string &password) { this->password = password; }
  void setGender(const string &gender) { this->gender = gender; }
};