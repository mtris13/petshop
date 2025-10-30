#include "infra/repositories/AccountRepoFile.hpp"
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

string AccountRepository::filePath(const string &loginCode) {
    int length = loginCode.length();
    if (length == AdminIdLength)
        return AdminAccountFilePath;
    if (length == ClientIdLength)
        return ClientAccountFilePath;
    if (length == StaffIdLength)
        return StaffAccountFilePath;

    return invalid;
}

string AccountRepository::readingFile(const string &loginCode) {
    ifstream file(filePath(loginCode));
    if (!file.is_open()) {
        // cerr << "Error: Cant open file " << filePath(loginCode) << '\n';
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

void AccountRepository::writingFile(const string &loginCode, const string &writeLine) {
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

Account *AccountRepository::findAccountById(const string &loginCode) {
    if (!isValidId(loginCode))
        return nullptr;

    int length = loginCode.length();
    if (length == 3) { // Admin
        Admin ad = getAdminInfo(loginCode);
        return new Admin(ad);
    }
    if (length == 5) { // Staff
        Staff st = getStaffInfo(loginCode);
        return new Staff(st);
    }
    if (length == 10) { // Client
        Client cl = getClientInfo(loginCode);
        return new Client(cl);
    }

    return nullptr;
}

string AccountRepository::getAccountPassword(const string &loginCode) {
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

string AccountRepository::generateAccountId(string &type) {
    int maxId = 0;
    string newId = "";

    if (type == "admin") {
        LinkedList<Admin> allAdmins = getAllAdminInfo();
        Node<Admin> *current = allAdmins.getHead();

        while (current != nullptr) {
            string id = current->getData().getId();
            try {
                maxId = max(maxId, stoi(id));
            } catch (...) { /* Bỏ qua nếu ID bị lỗi */
            }
            current = current->getNext();
        }

        maxId++;
        if (maxId < 10)
            newId += "00";
        else if (maxId < 100)
            newId += "0";
        newId += to_string(maxId);

    } else if (type == "staff") {
        LinkedList<Staff> allStaff = getAllStaffInfo();
        Node<Staff> *current = allStaff.getHead();

        while (current != nullptr) {
            string id = current->getData().getId();
            try {
                int num = stoi(id.substr(2, 3));
                maxId = max(maxId, num);
            } catch (...) { /* Bỏ qua nếu ID bị lỗi */
            }
            current = current->getNext();
        }

        maxId++;
        newId = "SV";
        if (maxId < 10)
            newId += "00"; // Đệm "00"
        else if (maxId < 100)
            newId += "0"; // Đệm "0"
        newId += to_string(maxId);

    } else {
        return "INVALID_TYPE";
    }
    return newId;
}

// GET
string AccountRepository::getAccountName(const string &loginCode) {
    string info = readingFile(loginCode);
    if (info == invalid)
        return invalid;
    string code, username;
    stringstream ss(info);
    getline(ss, code, '|');
    getline(ss, username, '|');
    return username;
}

string AccountRepository::getAccountGender(const string &loginCode) {
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

Admin AccountRepository::getAdminInfo(const string &loginCode) {
    Admin info;
    if (loginCode.length() != AdminIdLength)
        return info;
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

Staff AccountRepository::getStaffInfo(const string &loginCode) {
    Staff info;
    if (loginCode.length() != StaffIdLength)
        return info;
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
    info = Staff(code, username, pw, gender, stol(salary));
    return info;
}

Client AccountRepository::getClientInfo(const string &loginCode) {
    Client info;
    if (loginCode.length() != ClientIdLength)
        return info;
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

LinkedList<Admin> AccountRepository::getAllAdminInfo() {
    ifstream file(AdminAccountFilePath);
    LinkedList<Admin> admin;
    if (!file.is_open()) {
        cerr << "Error: Cant open file " << AdminAccountFilePath << '\n';
        return admin;
    }
    string line;
    while (getline(file, line)) {
        if (line.empty())
            continue;
        stringstream ss(line);
        string code, name, pw, gender;
        getline(ss, code, '|');
        getline(ss, name, '|');
        getline(ss, pw, '|');
        getline(ss, gender, '|');
        Admin ad(code, name, pw, gender);
        admin.pushBack(ad);
    }
    file.close();
    return admin;
}

LinkedList<Staff> AccountRepository::getAllStaffInfo() {
    ifstream file(StaffAccountFilePath);
    LinkedList<Staff> staff;
    if (!file.is_open()) {
        cerr << "Error: Cant open file " << StaffAccountFilePath << '\n';
        return staff;
    }
    string line;
    while (getline(file, line)) {
        if (line.empty())
            continue;
        stringstream ss(line);
        string code, name, pw, gender, sal;
        getline(ss, code, '|');
        getline(ss, name, '|');
        getline(ss, pw, '|');
        getline(ss, gender, '|');
        getline(ss, sal);
        Staff st = Staff(code, name, pw, gender, stol(sal));
        staff.pushBack(st);
    }
    file.close();
    return staff;
}

LinkedList<Client> AccountRepository::getAllClientInfo() {
    ifstream file(ClientAccountFilePath);
    LinkedList<Client> client;
    if (!file.is_open()) {
        cerr << "Error: Cant open file " << ClientAccountFilePath << '\n';
        return client;
    }
    string line;
    while (getline(file, line)) {
        if (line.empty())
            continue;
        stringstream ss(line);
        string code, name, pw, gender, street, city;
        getline(ss, code, '|');
        getline(ss, name, '|');
        getline(ss, pw, '|');
        getline(ss, gender, '|');
        getline(ss, street, '|');
        getline(ss, city);
        Client cl(code, name, pw, gender, street, city);
        client.pushBack(cl);
    }
    file.close();
    return client;
}

// SET
void AccountRepository::setAdminInfo(const Admin &ad) {
    string line = ad.getId() + '|' + ad.getName() + '|' + ad.getPassword() + '|' +
                  ad.getGender();
    writingFile(ad.getId(), line);
}

void AccountRepository::setStaffInfo(const Staff &st) {
    string line = st.getId() + '|' + st.getName() + '|' + st.getPassword() + '|' +
                  st.getGender() + '|' + to_string(st.getSalary());
    writingFile(st.getId(), line);
}

void AccountRepository::setClientInfo(const Client &cl) {
    string line = cl.getId() + '|' + cl.getName() + '|' + cl.getPassword() + '|' +
                  cl.getGender() + '|' + cl.getStreet() + '|' + cl.getCity();
    writingFile(cl.getId(), line);
}

// OTHERS
bool AccountRepository::isValidId(const string &loginCode) {
    string info = readingFile(loginCode);
    if (info == invalid)
        return false;
    return true;
}

bool AccountRepository::isValidPassword(const string &loginCode,
                                        const string &attemptPassword) {
    string pw = getAccountPassword(loginCode);
    if (pw == invalid || attemptPassword != pw)
        return false;
    return true;
}

void AccountRepository::deleteAccount(const string &loginCode) {
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

AccountStats AccountRepository::countAccount() {
    AccountStats stats;
    std::string line;

    std::ifstream adminFile(AdminAccountFilePath);
    if (adminFile.is_open()) {
        while (std::getline(adminFile, line)) {
            if (!line.empty())
                stats.totalAdmin++;
        }
        adminFile.close();
    } else {
        std::cerr << "Error: Cannot open " << AdminAccountFilePath << '\n';
    }

    std::ifstream staffFile(StaffAccountFilePath);
    if (staffFile.is_open()) {
        while (std::getline(staffFile, line)) {
            if (!line.empty())
                stats.totalStaff++;
        }
        staffFile.close();
    } else {
        std::cerr << "Error: Cannot open " << StaffAccountFilePath << '\n';
    }

    std::ifstream clientFile(ClientAccountFilePath);
    if (clientFile.is_open()) {
        while (std::getline(clientFile, line)) {
            if (!line.empty())
                stats.totalClient++;
        }
        clientFile.close();
    } else {
        std::cerr << "Error: Cannot open " << ClientAccountFilePath << '\n';
    }

    return stats;
}