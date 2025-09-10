#pragma once

#include <iostream>
#include <string>
using namespace std;

class Account {
protected:
  string AccountId;
  string AccountName;
  string Password;
  string Gender;

public:
  Account() : AccountId(""), AccountName(""), Password(""), Gender("") {}
  Account(const string &Id, const string &Name, const string &Pass,
          const string &Gen)
      : AccountId(Id), AccountName(Name), Password(Pass), Gender(Gen) {}

  // Getter
  string getAccountId() const { return AccountId; }
  string getAccountName() const { return AccountName; }
  string getPassword() const { return Password; }
  string getGender() const { return Gender; }

  // Setter
  void setAccountId(const string &id) { AccountId = id; }
  void setAccountName(const string &name) { AccountName = name; }
  void setPassword(const string &password) { Password = password; }
  void setGender(const string &gender) { Gender = gender; }
};