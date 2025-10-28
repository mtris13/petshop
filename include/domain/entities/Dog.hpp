#pragma once
#include "Pet.hpp"
#include <string> // Đảm bảo có string

class Dog : public Pet {
private:
  int energyLevel; // Độ năng động (1–10)

  // --- BỔ SUNG THÔNG TIN MÔ TẢ ---
  std::string description; // Mô tả chi tiết (tính cách, sức khỏe, thói quen...)

public:
  Dog() {}
  Dog(std::string id, const std::string &name, const std::string &breed,
      int age, float price, int energyLevel = 5,
      const std::string &desc = "No description available.")
      : Pet(id, name, breed, age, price), energyLevel(energyLevel),
        description(desc) {} // Thêm description vào hàm khởi tạo

  // --- Getter/Setter cho thuộc tính cũ và mới ---
  int getEnergyLevel() const { return energyLevel; }
  void setEnergyLevel(int value) { energyLevel = value; }

  std::string getDescription() const { return description; }
  void setDescription(const std::string &d) { description = d; }

  // --- Hàm getType() ---
  std::string getType() const override { return "Dog"; }

  // --- Hàm showInfo() (cho console) ---
  // Sửa dòng này
  void showInfo(std::ostream &out) const override {
    cout << "=== DOG INFO ===\n";
    Pet::showInfo(out); // Tên, giống, tuổi, giá
    cout << "Energy Level: " << energyLevel << "/10\n";

    // --- Hiển thị description ---
    cout << "Description: " << description << "\n";
  }
};