#pragma once
#include "Account.hpp"
using namespace std;

class Client : public Account {
private:
  string Street;
  string District;
  string City;

public:
  Client() : Account(), Street(""), District(""), City("") {}
  Client(const string &id, const string &name, const string &password,
         const string &gender, const string &street, const string &district,
         const string &city)
      : Account(id, name, password, gender), Street(street), District(district),
        City(city) {}

  // Getter
  string getStreet() const { return Street; }
  string getDistrict() const { return District; }
  string getCity() const { return City; }

  // Setter
  void setStreet(const string &street) { Street = street; }
  void setDistrict(const string &district) { District = district; }
  void setCity(const string &city) { City = city; }
};
