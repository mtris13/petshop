#pragma once
#include "Pet.hpp"

class Cat : public Pet {
private:
    string furLength; // Độ dài lông: Short, Medium, Long

public:
    Cat() {}
    Cat(string id, const string &name, const string &breed, int age, float price,
        const string &furLength = "Short")
        : Pet(id, name, breed, age, price), furLength(furLength) {}

    string getFurLength() const { return furLength; }
    void setFurLength(const string &value) { furLength = value; }

    string getType() const override { return "Cat"; }

    void showInfo() const override {
        cout << "=== CAT INFO ===\n";
        Pet::showInfo();
        cout << "Fur Length: " << furLength << "\n";
    }
};
