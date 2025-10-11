#pragma once
#include <iostream>
#include <string>
using namespace std;

class Pet {
protected:
  int id;
  string name;
  string breed;
  int age;
  double price;

public:
  Pet(int id, const string &name, const string &breed, int age, double price)
      : id(id), name(name), breed(breed), age(age), price(price) {}

  virtual ~Pet() = default;

  // Getter
  int getId() const { return id; }
  string getName() const { return name; }
  string getBreed() const { return breed; }
  int getAge() const { return age; }
  double getPrice() const { return price; }

  // Setter
  void setName(const string &newName) { name = newName; }
  void setBreed(const string &newBreed) { breed = newBreed; }
  void setAge(int newAge) { age = newAge; }
  void setPrice(double newPrice) { price = newPrice; }

  // Phương thức ảo để biết loại thú
  virtual string getType() const = 0;

  virtual void showInfo() const {
    cout << "ID: " << id << "\n"
         << "Name: " << name << "\n"
         << "Breed: " << breed << "\n"
         << "Age: " << age << "\n"
         << "Price: " << price << "\n";
  }
};
