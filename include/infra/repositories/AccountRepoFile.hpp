/* đọc và ghi các file Accounts:
Service:
    check password
    check available id
    get information from all type of accounts
    set information form all type of accounts
    delete account
    !!: there isn't setting password/name/etc functions for accounts. Only change info via setAdminInfo/setClientInfo/setStaffInfo.
        generate them if needed.
*/

/* một số tính năng có thể bổ sung: mã hóa mật khẩu */
#pragma once
#include "domain/entities/Account.hpp"
#include "domain/entities/Admin.hpp"
#include "domain/entities/Client.hpp"
#include "domain/entities/Staff.hpp"
#include "ds/LinkedList.hpp"
#include <fstream>
#include <sstream>
#include <string>

class AccountRepository {
private:
    const string AdminAccountFilePath = "../data/AdminAccount.txt";
    const string ClientAccountFilePath = "../data/ClientAccount.txt";
    const string StaffAccountFilePath = "../data/StaffAccount.txt";
    const int AdminCodeLength = 3;
    const int ClientCodeLength = 10; // so dien thoai
    const int StaffCodeLength = 5;   // che giấu những const để các file khác không nhìn thấy được
    const string invalid = "";

    string filePath(const string &loginCode);
    string readingFile(const string &loginCode);
    void writingFile(const string &loginCode, const string &writeLine);
    string getAccountPassword(const string &loginCode);

public:
    AccountRepository() {}
    // GET
    string getAccountName(const string &loginCode);
    string getAccountGender(const string &loginCode);
    Admin getAdminInfo(const string &loginCode);
    Staff getStaffInfo(const string &loginCode);
    Client getClientInfo(const string &loginCode);
    // SET
    void setAdminInfo(const Admin &ad);
    void setStaffInfo(const Staff &st);
    void setClientInfo(const Client &cl);

    // ANOTHER
    bool isValidId(const string &loginCode);
    bool isValidPassword(const string &loginCode, const string &attemptPassword);
    void deleteAccount(const string &loginCode);
};