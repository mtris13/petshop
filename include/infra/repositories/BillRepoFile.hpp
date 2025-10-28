/* BillRepoFile.hpp - Quản lý lưu hóa đơn
 *
 * File format: data/bills/[billId].txt
 * Mỗi hóa đơn là một file txt riêng
 */

#pragma once
#include "domain/entities/Bill.hpp"
#include "ds/LinkedList.hpp"
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;
class BillRepository {
private:
    const std::string billFolderPath = "../data/bills/";

    // Lấy ngày giờ hiện tại
    string getCurrentDateTime(bool dateOnly = false);

public:
    BillRepository() {}

    // Tạo bill ID tự động
    std::string generateBillId();
    // Lưu hóa đơn vào file
    void saveBill(const Bill &bill);
    // Tạo hóa đơn từ giỏ hàng
    Bill createBillFromCart(const std::string &clientId, const std::string &clientName, const LinkedList<BillItem> &items);
    // Đọc hóa đơn từ file
    Bill loadBill(const std::string &billId);
    // Lấy danh sách tất cả bills
    LinkedList<std::string> getAllBillIds();
    // Thống kê doanh thu
    float calculateTotalRevenue();
    // Thống kê doanh thu từ bán pet
    float calculatePetSalesRevenue();
    // Thống kê doanh thu từ spa
    float calculateSpaRevenue();
};