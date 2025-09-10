#pragma once

#include "Account.hpp"

class Staff : public Account {
private:
  double Salary;

public:
  Staff() : Account(), Salary(0.0) {}
  Staff(const string &Id, const string &Name, const string &Pass,
        const string &Gen, double Salary)
      : Account(Id, Name, Pass, Gen), Salary(Salary) {}
  double getSalary() const { return Salary; };        // getter
  void setSalary(double salary) { Salary = salary; }; // setter
};