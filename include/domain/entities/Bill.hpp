#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct BillItem {
  string itemId;   // ID của pet hoặc service
  string itemName; // Tên
  string itemType; // "Pet" hoặc "Service"
  float price;
  int quantity;

  BillItem() : itemId(""), itemName(""), itemType(""), price(0), quantity(1) {}
  BillItem(const string &id, const string &name, const string &type, float p,
           int qty = 1)
      : itemId(id), itemName(name), itemType(type), price(p), quantity(qty) {}
};

class Bill {
private:
  string billId;          // Mã hóa đơn (BILL001)
  string clientId;        // ID khách hàng
  string clientName;      // Tên khách hàng
  vector<BillItem> items; // Danh sách sản phẩm/dịch vụ
  float totalAmount;      // Tổng tiền
  string date;            // Ngày tạo hóa đơn
  string time;            // Giờ tạo hóa đơn

public:
  Bill()
      : billId(""), clientId(""), clientName(""), totalAmount(0), date(""),
        time("") {}

  Bill(const string &id, const string &cId, const string &cName,
       const string &d, const string &t)
      : billId(id), clientId(cId), clientName(cName), totalAmount(0), date(d),
        time(t) {}

  // Getters
  string getBillId() const { return billId; }
  string getClientId() const { return clientId; }
  string getClientName() const { return clientName; }
  vector<BillItem> getItems() const { return items; }
  float getTotalAmount() const { return totalAmount; }
  string getDate() const { return date; }
  string getTime() const { return time; }

  // Setters
  void setBillId(const string &id) { billId = id; }
  void setClientId(const string &id) { clientId = id; }
  void setClientName(const string &name) { clientName = name; }
  void setDate(const string &d) { date = d; }
  void setTime(const string &t) { time = t; }

  // Thêm item vào hóa đơn
  void addItem(const BillItem &item) {
    items.push_back(item);
    totalAmount += item.price * item.quantity;
  }

  // Tính lại tổng tiền
  void recalculateTotal() {
    totalAmount = 0;
    for (const auto &item : items) {
      totalAmount += item.price * item.quantity;
    }
  }

  // Hiển thị hóa đơn
  void display() const {
    cout << "\n========================================\n";
    cout << "           HOA DON BAN HANG             \n";
    cout << "========================================\n";
    cout << "Ma hoa don: " << billId << "\n";
    cout << "Khach hang: " << clientName << " (" << clientId << ")\n";
    cout << "Ngay: " << date << " " << time << "\n";
    cout << "----------------------------------------\n";
    cout << "STT | Ten san pham         | Gia      \n";
    cout << "----------------------------------------\n";

    int stt = 1;
    for (const auto &item : items) {
      cout << stt++ << ".  | " << item.itemName << " (" << item.itemType
           << ") | " << item.price << "\n";
    }

    cout << "----------------------------------------\n";
    cout << "Tong cong: " << totalAmount << " VND\n";
    cout << "========================================\n";
    cout << "      Cam on quy khach!                 \n";
    cout << "========================================\n";
  }
};