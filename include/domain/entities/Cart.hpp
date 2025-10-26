#pragma once

#include <iostream>
#include <string>

class CartItem {
private:
    std::string petId;
    std::string petName;
    std::string price;

public:
    CartItem() : petId(""), petName(""), price(0) {}
    CartItem(const std::string &id, const std::string &name, std::string p) : petId(id), petName(name), price(p) {}
    // GET
    std::string getPetId() { return petId; }
    std::string getPetName() { return petName; }
    std::string getPrice() { return price; }
};