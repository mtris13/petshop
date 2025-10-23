#pragma once

#include "Account.hpp"

class Staff : public Account {
private:
    float salary;

public:
    Staff() : Account(), salary(0.0) {}
    Staff(const string &Id, const string &Name, const string &Pass, const string &Gen, const float &Salary) : Account(Id, Name, Pass, Gen), salary(Salary) {}
    float getSalary() const { return salary; };              // getter
    void setSalary(float salary) { this->salary = salary; }; // setter
};