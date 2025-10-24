/* CartRepoFile.hpp - Quản lý giỏ hàng của từng client
 *
 * File format: data/Cart/[clientId].txt
 * Format: petId|petName|price
 * Example: d001|Max|9500000
 */

#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct CartItem {
  string petId;
  string petName;
  float price;

  CartItem() : petId(""), petName(""), price(0) {}
  CartItem(const string &id, const string &name, float p)
      : petId(id), petName(name), price(p) {}
};

class CartRepository {
private:
  const string cartFolderPath = "../data/Cart/";

  string getCartFilePath(const string &clientId) {
    return cartFolderPath + clientId + ".txt";
  }

public:
  CartRepository() {}

  // Thêm pet vào giỏ hàng
  void addToCart(const string &clientId, const string &petId,
                 const string &petName, float price) {
    string filePath = getCartFilePath(clientId);
    ofstream file(filePath, ios::app);

    if (!file.is_open()) {
      cerr << "Error: Cannot open cart file for " << clientId << '\n';
      return;
    }

    file << petId << "|" << petName << "|" << price << "\n";
    file.close();
  }

  // Lấy tất cả items trong giỏ hàng
  vector<CartItem> getCartItems(const string &clientId) {
    vector<CartItem> items;
    string filePath = getCartFilePath(clientId);
    ifstream file(filePath);

    if (!file.is_open()) {
      // Giỏ hàng trống hoặc chưa tồn tại
      return items;
    }

    string line;
    while (getline(file, line)) {
      if (line.empty())
        continue;

      stringstream ss(line);
      string id, name, priceStr;

      getline(ss, id, '|');
      getline(ss, name, '|');
      getline(ss, priceStr, '|');

      items.push_back(CartItem(id, name, stof(priceStr)));
    }

    file.close();
    return items;
  }

  // Xóa một item khỏi giỏ hàng
  void removeFromCart(const string &clientId, const string &petId) {
    string filePath = getCartFilePath(clientId);
    string tempPath = cartFolderPath + "temp.txt";

    ifstream in(filePath);
    ofstream out(tempPath);

    if (!in.is_open()) {
      cerr << "Error: Cart file not found\n";
      return;
    }

    if (!out.is_open()) {
      cerr << "Error: Cannot create temp file\n";
      in.close();
      return;
    }

    string line;
    while (getline(in, line)) {
      if (line.empty())
        continue;

      stringstream ss(line);
      string id;
      getline(ss, id, '|');

      if (id != petId) {
        out << line << "\n";
      }
    }

    in.close();
    out.close();

    remove(filePath.c_str());
    rename(tempPath.c_str(), filePath.c_str());
  }

  // Xóa toàn bộ giỏ hàng (sau khi thanh toán)
  void clearCart(const string &clientId) {
    string filePath = getCartFilePath(clientId);
    ofstream file(filePath, ios::trunc);
    file.close();
  }

  // Kiểm tra giỏ hàng có trống không
  bool isCartEmpty(const string &clientId) {
    vector<CartItem> items = getCartItems(clientId);
    return items.empty();
  }

  // Tính tổng tiền trong giỏ hàng
  float calculateTotal(const string &clientId) {
    vector<CartItem> items = getCartItems(clientId);
    float total = 0;
    for (const auto &item : items) {
      total += item.price;
    }
    return total;
  }

  // Hiển thị giỏ hàng
  void displayCart(const string &clientId) {
    vector<CartItem> items = getCartItems(clientId);

    if (items.empty()) {
      cout << "\nGio hang cua ban dang trong!\n";
      return;
    }

    cout << "\n========== GIO HANG CUA BAN ==========\n";
    cout << "STT | ID Pet | Ten Pet              | Gia\n";
    cout << "---------------------------------------\n";

    int stt = 1;
    float total = 0;
    for (const auto &item : items) {
      cout << stt++ << ".  | " << item.petId << " | " << item.petName << " | "
           << item.price << " VND\n";
      total += item.price;
    }

    cout << "---------------------------------------\n";
    cout << "Tong cong: " << total << " VND\n";
    cout << "=======================================\n";
  }
};