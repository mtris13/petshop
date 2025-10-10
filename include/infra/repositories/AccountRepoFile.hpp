// Làm việc với file lưu tài khoản
#pragma once
#include "domain/entities/Admin.hpp"
#include "domain/entities/Client.hpp"
#include "domain/entities/Staff.hpp"
#include <fstream>
#include <sstream>
using namespace std;

class AccountRepoFile {
private:
    string filePath;

public:
    AccountRepoFile() {}
    AccountRepoFile(const string &path) : filePath(path) {}

    bool checkAccount(const string &id, const string &password);
    bool checkExitId(const string &id);

    void saveAccount(const string &id, const string &password);
    void changePassword(const string &id, const string &newPassword);
    void changeId(const string &Id);
};
