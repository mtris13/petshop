/* CartRepoFile.hpp - Quản lý giỏ hàng của từng client
 *
 * File format: data/Cart/[clientId].txt
 * Format: petId|petName|price
 * Example: d001|Max|9500000
 */
/*
    Add seeing pet detail after added into cart
*/

#pragma once
#include <PetRepoFile.hpp>
#include <fstream>
#include <include/domain/entities/Cart.hpp>
#include <include/ds/LinkedList.hpp>
#include <iomanip> // cần cho setw, left, right, setprecision
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class CartRepository {
private:
    const string cartFolderPath = "../data/Cart/";

    string getCartFilePath(const string &clientId) {
        return cartFolderPath + clientId + ".txt";
    }

public:
    CartRepository() {}

    // Thêm pet vào giỏ hàng
    void addToCart(const string &clientId, const string &petId, const string &petName, float price) {
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
    LinkedList<CartItem> getCartItems(const string &clientId) {
        LinkedList<CartItem> items;
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

            items.pushBack(CartItem(id, name, stof(priceStr)));
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
        LinkedList<CartItem> items = getCartItems(clientId);
        return items.isEmpty();
    }

    // Tính tổng tiền trong giỏ hàng
    float calculateTotal(const string &clientId) {
        LinkedList<CartItem> items = getCartItems(clientId);
        float total = 0;
        Node<CartItem> *current = items.getHead();
        while (current != nullptr) {
            total += current->getData().getPrice();
            current = current->getNext();
        }
        return total;
    }

    // Hiển thị giỏ hàng
    void displayCart(const string &clientId) {
        LinkedList<CartItem> items = getCartItems(clientId);

        if (items.isEmpty()) {
            cout << "\nGio hang trong!\n";
            return;
        }

        Menu::displayHeader("GIO HANG CUA BAN");

        cout << left << setw(5) << "STT" << setw(10) << "ID Pet" << setw(25) << "Ten Pet" << right << setw(15) << "Gia (VND)\n";
        cout << string(55, '-') << "\n";

        int stt = 1;
        float total = 0;
        PetRepository petRepo;
        Node<CartItem> *current = items.getHead();
        while (current != nullptr) {
            string petId = current->getData().getPetId();
            if (petRepo.isAvailablePet(petId)) {
                cout << left << setw(5) << stt++ << setw(10) << petId << setw(25) << current->getData().getPetName() << right << setw(15) << fixed << setprecision(0)
                     << current->getData().getPrice() << "\n";
                total += current->getData().getPrice();
            }
            current = current->getNext();
        }

        cout << string(55, '-') << "\n";
        cout << right << setw(45) << "Tong cong: " << setw(10) << fixed << setprecision(0) << total << " VND\n";
        cout << string(55, '=') << "\n";
    }
};