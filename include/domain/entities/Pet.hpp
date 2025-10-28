#pragma once
#include <iostream>
#include <string>
using namespace std;

class Pet {
protected:
    string id;
    string name;
    string breed;
    int age;
    float price;

public:
    Pet() {}
    Pet(string id, const string &name, const string &breed, int age, float price)
        : id(id), name(name), breed(breed), age(age), price(price) {}

    virtual ~Pet() = default;

    // Getter
    string getId() const { return id; }
    string getName() const { return name; }
    string getBreed() const { return breed; }
    int getAge() const { return age; }
    float getPrice() const { return price; }

    // Setter
    void setName(const string &newName) { name = newName; }
    void setBreed(const string &newBreed) { breed = newBreed; }
    void setAge(int newAge) { age = newAge; }
    void setPrice(float newPrice) { price = newPrice; }

    // Phương thức ảo để biết loại thú
    virtual std::string getType() const = 0;

    virtual void showInfo(ostream &out) const {
        out << "ID: " << id << "\n"
            << "Name: " << name << "\n"
            << "Breed: " << breed << "\n"
            << "Age: " << age << "\n"
            << "Price: " << price << "\n";
    }
    friend std::ostream &operator<<(ostream &out, const Pet &pet);
};

inline std::ostream &operator<<(ostream &out, const Pet &pet) {
    pet.showInfo(out);
    return out;
}