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
  string role;

public:
  Account() : accountId(""), accountName(""), password(""), gender(""), role("") {}
  Account(const string &Id, const string &Name, const string &Pass,
          const string &Gen, const string &Role)
      : accountId(Id), accountName(Name), password(Pass), gender(Gen),
        role(Role) {}

  // Getter
  string getAccountId() const { return accountId; }
  string getAccountName() const { return accountName; }
  string getPassword() const { return password; }
  string getGender() const { return gender; }
  string getRole() const { return role; }

  // Setter
  void setAccountId(const string &id) { this->accountId = id; }
  void setAccountName(const string &name) { this->accountName = name; }
  void setPassword(const string &password) { this->password = password; }
  void setGender(const string &gender) { this->gender = gender; }
  void setRole(const string &role) { this->role = role; }
};