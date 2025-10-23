#pragma once
#include "Pet.hpp"

class Dog : public Pet {
private:
  int energyLevel; // Độ năng động (1–10)

public:
  Dog() {}
  Dog(string id, const string &name, const string &breed, int age, float price,
      int energyLevel = 5)
      : Pet(id, name, breed, age, price), energyLevel(energyLevel) {}

  int getEnergyLevel() const { return energyLevel; }
  void setEnergyLevel(int value) { energyLevel = value; }

  string getType() const override { return "Dog"; }

  void showInfo() const override {
    cout << "=== DOG INFO ===\n";
    Pet::showInfo();
    cout << "Energy Level: " << energyLevel << "/10\n";
  }
};
