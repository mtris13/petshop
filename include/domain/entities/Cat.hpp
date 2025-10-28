#pragma once
#include "Pet.hpp"
#include <iostream> // Cần cho ostream
#include <string>   // Nên include string

class Cat : public Pet {
private:
  std::string furLength; // Độ dài lông: Short, Medium, Long

  // --- BỔ SUNG THÔNG TIN MÔ TẢ ---
  std::string description; // Mô tả chi tiết

public:
  Cat() {}
  Cat(std::string id, const std::string &name, const std::string &breed,
      int age, float price, const std::string &furLength = "Short",
      const std::string &desc = "No description available.") // Thêm desc
      : Pet(id, name, breed, age, price), furLength(furLength),
        description(desc) {} // Khởi tạo description

  // --- Getter/Setter cho thuộc tính cũ và mới ---
  std::string getFurLength() const { return furLength; }
  void setFurLength(const std::string &value) { furLength = value; }

  std::string getDescription() const { return description; }
  void setDescription(const std::string &d) { description = d; }

  // --- Hàm getType() ---
  std::string getType() const override { return "Cat"; }

  // --- Hàm showInfo() (cho console hoặc file) ---
  void showInfo(std::ostream &out) const override {
    // SỬA LỖI: Dùng 'out' thay vì 'cout'
    out << "=== CAT INFO ===\n";
    Pet::showInfo(out); // Gọi hàm của class cha
    out << "Fur Length: " << furLength << "\n";

    // --- Hiển thị description ---
    out << "Description: " << description << "\n";
  }
};