#pragma once

#include "Account.hpp"

class Staff : public Account {
private:
  double salary;

public:
  Staff() : Account(), salary(0.0) {}
  Staff(const string &Id, const string &Name, const string &Pass,
        const string &Gen, double Salary)
      : Account(Id, Name, Pass, Gen,"S"), salary(Salary) {}
  double getSalary() const { return salary; };              // getter
  void setSalary(double salary) { this->salary = salary; }; // setter
};