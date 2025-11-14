#pragma once
#include "Bill_Item.hpp"
#include "ds/LinkedList.hpp"
#include <iostream>
#include <string>

class Bill {
private:
    std::string billId;         // Mã hóa đơn (BILL001)
    std::string clientId;       // ID khách hàng
    std::string clientName;     // Tên khách hàng
    LinkedList<BillItem> items; // Danh sách sản phẩm/dịch vụ
    long totalAmount;           // Tổng tiền
    std::string date;           // Ngày tạo hóa đơn
    std::string time;           // Giờ tạo hóa đơn

public:
    Bill() : billId(""), clientId(""), clientName(""), totalAmount(0), date(""), time("") {}
    ~Bill() {
        std::cout << "Goi ham huy Bill, xoa items..." << std::endl;
    }
    Bill(const std::string &id, const std::string &cId, const std::string &cName, const std::string &d, const std::string &t)
        : billId(id), clientId(cId), clientName(cName), totalAmount(0), date(d), time(t) {}

    // Getters
    std::string getBillId() const { return billId; }
    std::string getClientId() const { return clientId; }
    std::string getClientName() const { return clientName; }
    const LinkedList<BillItem> &getItems() const { return items; }
    long getTotalAmount() const { return totalAmount; }
    std::string getDate() const { return date; }
    std::string getTime() const { return time; }

    // Setters
    void setBillId(const std::string &id) { billId = id; }
    void setClientId(const std::string &id) { clientId = id; }
    void setClientName(const std::string &name) { clientName = name; }
    void setDate(const std::string &d) { date = d; }
    void setTime(const std::string &t) { time = t; }

    // Thêm item vào hóa đơn
    void addItem(const BillItem &item) {
        items.pushBack(item);
        totalAmount += item.getPrice(); // Mỗi item chỉ có số lượng là 1
    }

    // Tính lại tổng tiền
    void recalculateTotal() {
        long total = 0;
        Node<BillItem> *item = items.getHead();
        while (item != nullptr) {
            total += item->getData().getPrice();
            item = item->getNext();
        }
        totalAmount = total;
    }

    // Hiển thị hóa đơn
    void display() const {
        std::cout << "\n========================================\n";
        std::cout << "                       BILL             \n";
        std::cout << "========================================\n";
        std::cout << "Bill ID: " << billId << "\n";
        std::cout << "Client: " << clientName << " (" << clientId << ")\n";
        std::cout << "Date: " << date << " " << time << "\n";
        std::cout << "----------------------------------------\n";
        std::cout << "STT |    Product            | Gia      \n";
        std::cout << "----------------------------------------\n";

        int stt = 1;
        Node<BillItem> *item = items.getHead();
        while (item != nullptr) {
            std::cout << stt++ << ".  | " << item->getData().getItemName() << " (" << item->getData().getItemType() << ") | " << item->getData().getPrice() << "\n";
            item = item->getNext();
        }

        std::cout << "----------------------------------------\n";
        std::cout << "Total: " << totalAmount << " VND\n";
        std::cout << "========================================\n";
        std::cout << "        Thank you for choosing us!      \n";
        std::cout << "========================================\n";
    }
};