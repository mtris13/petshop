#include "infra/repositories/BillRepoFile.hpp"
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

string BillRepository::getCurrentDateTime(bool dateOnly) {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    std::stringstream ss;
    ss << setfill('0') << setw(2) << ltm->tm_mday << "/" << setw(2)
       << (1 + ltm->tm_mon) << "/" << (1900 + ltm->tm_year);

    if (!dateOnly) {
        ss << " " << setw(2) << ltm->tm_hour << ":" << setw(2) << ltm->tm_min;
    }

    return ss.str();
}

string BillRepository::generateBillId() {
    int maxNum = 0;

    // Đọc tất cả files trong folder bills để tìm số lớn nhất
    // Simplified: chỉ tăng dần từ BILL001
    std::ifstream checkFile(billFolderPath + "counter.txt");
    if (checkFile.is_open()) {
        checkFile >> maxNum;
        checkFile.close();
    }
    maxNum++;

    // Lưu lại counter
    std::ofstream saveFile(billFolderPath + "counter.txt");
    saveFile << maxNum;
    saveFile.close();

    // Tạo ID
    std::stringstream ss;
    ss << "BILL" << setfill('0') << setw(3) << maxNum;
    return ss.str();
}
// Lưu hóa đơn vào file
void BillRepository::saveBill(const Bill &bill) {
    std::string filePath = billFolderPath + bill.getBillId() + ".txt";
    ofstream file(filePath);

    if (!file.is_open()) {
        cerr << "Error: Cannot create bill file: " << filePath << '\n';
        return;
    }

    // Header
    file << "========================================\n";
    file << "           HOA DON BAN HANG             \n";
    file << "             DUT PETSHOP                \n";
    file << "========================================\n";
    file << "Bill ID: " << bill.getBillId() << "\n";
    file << "Client Name: " << bill.getClientId() << "\n";
    file << "Phone Number: " << bill.getClientId() << "\n";
    file << "Date: " << bill.getDate() << "\n";
    file << "Time: " << bill.getTime() << "\n";
    file << "----------------------------------------\n";
    file << "DETAILS:\n";
    file << "----------------------------------------\n";

    // Items
    int stt = 1;
    Node<BillItem> *item = bill.getItems().getHead();
    while (item != nullptr) {
        file << stt++ << ". " << item->getData().getItemName() << " (" << item->getData().getItemType() << ")\n";
        file << "   ID: " << item->getData().getItemId() << "\n";
        file << "   Gia: " << item->getData().getPrice() << " VND\n";
        file << "   Breed: " << item->getData().getItemType() << "\n";
        file << "\n";
        item = item->getNext();
    }

    // Footer
    file << "----------------------------------------\n";
    file << "TONG CONG: " << bill.getTotalAmount() << " VND\n";
    file << "========================================\n";
    file << "        CAM ON QUY KHACH!               \n";
    file << "    Hen gap lai quy khach lan sau!     \n";
    file << "========================================\n";

    file.close();
    std::cout << "\n[SUCCESS] Hoa don da duoc luu tai: " << filePath << "\n";
}

// Tạo hóa đơn từ giỏ hàng
Bill BillRepository::createBillFromCart(const std::string &clientId, const std::string &clientName,
                                        const LinkedList<BillItem> &items) {
    std::string billId = generateBillId();
    std::string dateTime = getCurrentDateTime();

    // Tách date và time
    size_t spacePos = dateTime.find(' ');
    std::string date = dateTime.substr(0, spacePos);
    std::string time = dateTime.substr(spacePos + 1);

    Bill bill(billId, clientId, clientName, date, time);

    // Thêm items vào bill
    Node<BillItem> *current = items.getHead();
    while (current != nullptr) {
        bill.addItem(current->getData());
        current = current->getNext();
    }

    return bill;
}

// Đọc hóa đơn từ file
Bill BillRepository::loadBill(const std::string &billId) {
    Bill bill;
    std::string filePath = billFolderPath + billId + ".txt";
    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "Error: Cannot open bill file: " << filePath << '\n';
        return bill;
    }

    // Đọc và parse file (simplified)
    // Trong thực tế cần parse chi tiết hơn
    file.close();
    return bill;
}

// Lấy danh sách tất cả bills
LinkedList<std::string> BillRepository::getAllBillIds() {
    LinkedList<std::string> billIds;
    // Cần implement directory listing
    // Đơn giản hóa: đọc từ counter
    return billIds;
}

// Thống kê doanh thu
long BillRepository::calculateTotalRevenue() {
    long total = 0;
    // Đọc tất cả bills và tính tổng
    // Simplified version
    return total;
}

// Thống kê doanh thu từ bán pet
long BillRepository::calculatePetSalesRevenue() {
    long total = 0;
    // Đọc tất cả bills, lọc items có type = "Pet"
    return total;
}

// Thống kê doanh thu từ spa
long BillRepository::calculateSpaRevenue() {
    long total = 0;
    // Đọc tất cả bills, lọc items có type = "Service"
    return total;
}