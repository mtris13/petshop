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

    string filePath(const string &loginCode) {
        int length = loginCode.length();
        if (length == AdminCodeLength)
            return AdminAccountFilePath;
        if (length == ClientCodeLength)
            return ClientAccountFilePath;
        if (length == StaffCodeLength)
            return StaffAccountFilePath;

        return invalid;
    }

    string readingFile(const string &loginCode) {
        ifstream file(filePath(loginCode));
        if (!file.is_open()) {
            cerr << "Error: Cant open file " << filePath(loginCode) << '\n';
            return invalid;
        }
        string line;
        while (getline(file, line)) {
            if (line.empty())
                continue;
            stringstream ss(line);
            string code;
            getline(ss, code, '|');
            if (code == loginCode) {
                file.close();
                return line;
            }
        }
        return invalid;
    }

    void writingFile(const string &loginCode, const string &writeLine) {
        const string path = filePath(loginCode);
        if (path == invalid) {
            cerr << "Error: Invalid file path for loginCode " << loginCode << '\n';
            return;
        }
        const string tempPath = "../data/temp.txt";

        ifstream in(path);
        ofstream out(tempPath);

        if (!out.is_open()) {
            cerr << "Error: Cant create temp file " << tempPath << '\n';
            in.close();
            return;
        }

        string line;
        bool foundAndUpdated = false;

        if (in.is_open()) {
            while (getline(in, line)) {
                if (line.empty())
                    continue;

                stringstream ss(line);
                string code;
                getline(ss, code, '|');

                if (code == loginCode) {
                    out << writeLine << '\n';
                    foundAndUpdated = true;
                } else
                    out << line << '\n';
            }
        }

        if (!foundAndUpdated) {
            out << writeLine << '\n';
        }

        in.close();
        out.close();
        if (remove(path.c_str()) != 0 && in.is_open())
            cerr << "Error: Could not remove original file " << path << '\n';

        if (rename(tempPath.c_str(), path.c_str()) != 0)
            cerr << "Error: Could not rename temp file to " << path << '\n';
    }

    string getAccountPassword(const string &loginCode) {
        string info = readingFile(loginCode);
        if (info == invalid)
            return invalid;
        string code, username, pw;
        stringstream ss(info);
        getline(ss, code, '|');
        getline(ss, username, '|');
        getline(ss, pw, '|');
        return pw;
    }

public:
    AccountRepository() {}
    // GET
    string getAccountName(const string &loginCode) {
        string info = readingFile(loginCode);
        if (info == invalid)
            return invalid;
        string code, username;
        stringstream ss(info);
        getline(ss, code, '|');
        getline(ss, username, '|');
        return username;
    }

    string getAccountGender(const string &loginCode) {
        string info = readingFile(loginCode);
        if (info == invalid)
            return invalid;
        string dummy, gender;
        stringstream ss(info);
        getline(ss, dummy, '|');
        getline(ss, dummy, '|');
        getline(ss, dummy, '|');
        getline(ss, gender, '|');
        return gender;
    }

    Admin getAdminInfo(const string &loginCode) {
        Admin info;
        string line = readingFile(loginCode);
        if (line == invalid)
            return info; // tra ve thong tin rong
        string code, username, pw, gender;
        stringstream ss(line);
        getline(ss, code, '|');
        getline(ss, username, '|');
        getline(ss, pw, '|');
        getline(ss, gender, '|');
        info = Admin(code, username, pw, gender);
        return info;
    }

    Staff getStaffInfo(const string &loginCode) {
        Staff info;
        string line = readingFile(loginCode);
        if (line == invalid)
            return info; // tra ve thong tin rong
        string code, username, pw, gender, salary;
        stringstream ss(line);
        getline(ss, code, '|');
        getline(ss, username, '|');
        getline(ss, pw, '|');
        getline(ss, gender, '|');
        getline(ss, salary, '|');
        info = Staff(code, username, pw, gender, stof(salary));
        return info;
    }

    Client getClientInfo(const string &loginCode) {
        Client info;
        string line = readingFile(loginCode);
        if (line == invalid)
            return info; // tra ve thong tin rong
        string code, username, pw, gender, street, city;
        stringstream ss(line);
        getline(ss, code, '|');
        getline(ss, username, '|');
        getline(ss, pw, '|');
        getline(ss, gender, '|');
        getline(ss, street, '|');
        getline(ss, city, '|');
        info = Client(code, username, pw, gender, street, city);
        return info;
    }

    // SET
    void setAdminInfo(const Admin &ad) {
        string line = ad.getId() + '|' + ad.getName() + '|' + ad.getPassword() + '|' + ad.getGender();
        writingFile(ad.getId(), line);
    }

    void setStaffInfo(const Staff &st) {
        string line = st.getId() + '|' + st.getName() + '|' + st.getPassword() + '|' + st.getGender() + '|' + to_string(st.getSalary());
        writingFile(st.getId(), line);
    }

    void setClientInfo(const Client &cl) {
        string line = cl.getId() + '|' + cl.getName() + '|' + cl.getPassword() + '|' + cl.getGender() + '|' + cl.getStreet() + '|' + cl.getCity();
        writingFile(cl.getId(), line);
    }

    // ANOTHER
    bool isValidId(const string &loginCode) {
        string info = readingFile(loginCode);
        if (info == invalid)
            return false;
        return true;
    }

    bool isValidPassword(const string &loginCode, const string &attemptPassword) {
        string pw = getAccountPassword(loginCode);
        if (pw == invalid || attemptPassword != pw)
            return false;
        return true;
    }

    void deleteAccount(const string &loginCode) {
        const string path = filePath(loginCode);
        if (path == invalid)
            return;

        const string tempPath = "../data/temp.txt";
        ifstream in(path);
        ofstream out(tempPath);

        if (!in.is_open() || !out.is_open()) {
            cerr << "Error opening files for removal." << endl;
            in.close();
            out.close();
            return;
        }

        string line;
        bool removed = false;
        while (getline(in, line)) {
            if (line.empty())
                continue;

            stringstream ss(line);
            string code;
            getline(ss, code, '|');

            if (code == loginCode)
                removed = true;
            else
                out << line << '\n';
        }

        in.close();
        out.close();

        if (removed) {
            remove(path.c_str());
            rename(tempPath.c_str(), path.c_str());
        } else {
            // Nếu không tìm thấy, không cần làm gì, chỉ cần xóa file temp
            remove(tempPath.c_str());
        }
    }
};