#pragma once
#include "Account.hpp"
using namespace std;

class Client : public Account {
private:
  string street;
  string district;
  string city;

public:
  Client() : Account(), street(""), district(""), city("") {}
  Client(const string &id, const string &name, const string &password,
         const string &gender, const string &street, const string &district,
         const string &city)
      : Account(id, name, password, gender), street(street), district(district),
        city(city) {}

  // Getter
  string getStreet() const { return street; }
  string getDistrict() const { return district; }
  string getCity() const { return city; }

  // Setter
  void setStreet(const string &street) { this->street = street; }
  void setDistrict(const string &district) { this->district = district; }
  void setCity(const string &city) { this->city = city; }
};
