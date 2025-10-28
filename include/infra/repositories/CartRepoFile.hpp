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
#include "PetRepoFile.hpp"
#include "domain/entities/Cart.hpp"
#include "ds/LinkedList.hpp"
#include <fstream>
#include <iomanip> // cần cho setw, left, right, setprecision
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class CartRepository {
private:
    const std::string cartFolderPath = "../data/Cart/";

    std::string getCartFilePath(const std::string &clientId) {
        return cartFolderPath + clientId + ".txt";
    }

public:
    CartRepository() {}

    // Thêm pet vào giỏ hàng
    void addToCart(const std::string &clientId, const std::string &petId, const std::string &petName, float price);
    // Lấy tất cả items trong giỏ hàng
    LinkedList<CartItem> getCartItems(const std::string &clientId);
    // Xóa một item khỏi giỏ hàng
    void removeFromCart(const std::string &clientId, const std::string &petId);
    // Xóa toàn bộ giỏ hàng (sau khi thanh toán)
    void clearCart(const std::string &clientId);
    // Kiểm tra giỏ hàng có trống không
    bool isCartEmpty(const std::string &clientId);

    // Tính tổng tiền trong giỏ hàng
    float calculateTotal(const std::string &clientId);
    // Hiển thị giỏ hàng
    void displayCart(const std::string &clientId);
};