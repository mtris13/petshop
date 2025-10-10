#pragma once
#include "include/infra/repositories/AccountRepoFile.hpp"
#include <fstream>
#include <sstream>
#include <string>

#define adminIdLength 3
#define staffIdLength 5
#define clientIdLength 10

bool AccountRepoFile::checkAccount(const string &id, const string &password) {
    fstream accountFile(filePath);
    string line;
    while (getline(accountFile, line)) {
        stringstream ss(line);
        string userId, pass;
        ss >> userId >> pass;
        if (id == userId && password == pass)
            return true;
    }
    return false;
}

bool AccountRepoFile::checkExitId(const string &id) {
    fstream accountFile(filePath);
    string line;
    while (getline(accountFile, line)) {
        stringstream ss(line);
        string userId, pass;
        ss >> userId >> pass;
        if (id == userId)
            return true;
    }
    return false;
}

void saveAccount(const string &id, const string &password);
