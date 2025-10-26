#pragma once
#include <iostream>
#include <string>

class BillItem {
private:
    std::string itemId;   // ID của pet hoặc service
    std::string itemName; // Tên
    std::string itemType; // "Pet" hoặc "Service"
    std::string price;

public:
    BillItem() : itemId(""), itemName(""), itemType(""), price("0") {}
    BillItem(const std::string &id, const std::string &name, const std::string &type, const std::string &p)
        : itemId(id), itemName(name), itemType(type), price(p) {}
    BillItem(const BillItem &item) {
        itemId = item.itemId;
        itemName = item.itemName;
        itemType = item.itemType;
        price = item.price;
    }
    // Có thể thêm operator =

    // GETTERS
    const std::string &getItemId() const { return itemId; }
    const std::string &getItemName() const { return itemName; }
    const std::string &getItemType() const { return itemType; }
    const std::string getPrice() const { return price; }

    // SETTERS
    void setItemId(const std::string &id) { itemId = id; }
    void setItemName(const std::string &name) { itemName = name; }
    void setItemType(const std::string &type) { itemType = type; }
    void setPrice(float p) { price = to_string(p); }
    void setPrice(string p) { price = p; }
};