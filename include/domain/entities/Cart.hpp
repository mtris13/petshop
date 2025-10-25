#pragma once

#include <iostream>
#include <string>
using namespace std;

class CartItem {
private:
    string petId;
    string petName;
    float price;

public:
    CartItem() : petId(""), petName(""), price(0) {}
    CartItem(const string &id, const string &name, float p) : petId(id), petName(name), price(p) {}
    // GET
    string getPetId() { return petId; }
    string getPetName() { return petName; }
    float getPrice() { return price; }
};