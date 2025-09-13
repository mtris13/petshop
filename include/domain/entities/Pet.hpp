#pragma once
#include <iostream>
#include <string>
using namespace std;

class Pet {
private:
  int id;
  string name;
  string species; // Dog, Cat
  string breed;   // Husky, Shiba,...
  int age;
  double price;

public:
  Pet(int id, const string &name, const string &species, const string &breed,
      int age, double price)
      : id(id), name(name), species(species), breed(breed), age(age),
        price(price) {}

  // Getter
  int getId() const { return id; }
  string getName() const { return name; }
  string getSpecies() const { return species; }
  string getBreed() const { return breed; }
  int getAge() const { return age; }
  double getPrice() const { return price; }

  // Setter
  void setName(const string &newName) { name = newName; }
  void setSpecies(const string &newSpecies) { species = newSpecies; }
  void setBreed(const string &newBreed) { breed = newBreed; }
  void setAge(int newAge) { age = newAge; }
  void setPrice(double newPrice) { price = newPrice; }
};
