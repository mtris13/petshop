/* đọc ghi file Dog/Cat available/unvailable */
#pragma once
#include "include/domain/entities/Cat.hpp"
#include "include/domain/entities/Dog.hpp"
#include "include/domain/entities/Pet.hpp"
#include <fstream>
#include <sstream>
#include <string>

class PetRepository {
private:
    const string catFilePath = "../data/Cat.txt";
    const string dogFilePath = "../data/Dog.txt";
    const int petIdLength = 4;
    const string invalid = "";
    string filePath(const string &petCode) {
        if (petCode.length() != petIdLength)
            return invalid;
        if (petCode[0] == 'd')
            return dogFilePath;
        return catFilePath;
    }

    string readingFile(const string &petCode) {
        ifstream file(filePath(petCode));
        if (!file.is_open()) {
            cerr << "Error: Cant open file " << filePath(petCode) << '\n';
            return invalid;
        }
        string line;
        while (getline(file, line)) {
            if (line.empty())
                continue;
            stringstream ss(line);
            string code;
            getline(ss, code, '|');
            if (code == petCode) {
                file.close();
                return line;
            }
        }
        return invalid;
    }

    void PetRepoFile::writingFile(const string &petCode, const string &writeLine) {
        const string path = getPetFilePath(petCode);
        if (path == invalid) {
            cerr << "Error: Invalid file path for petCode " << petCode << '\n';
            return;
        }
        const string tempPath = "../data/temp.txt";

        ifstream in(path);
        bool originalFileExisted = in.is_open();

        ofstream out(tempPath);
        if (!out.is_open()) {
            cerr << "Error: Cant create temp file " << tempPath << '\n';
            if (originalFileExisted)
                in.close();
            return;
        }

        string line;
        bool foundAndUpdated = false;

        if (originalFileExisted) {
            while (getline(in, line)) {
                if (line.empty())
                    continue;

                stringstream ss(line);
                string code;
                getline(ss, code, '|');

                if (code == petCode) {
                    out << writeLine << '\n';
                    foundAndUpdated = true;
                } else
                    out << line << '\n';
            }
        }

        if (!foundAndUpdated) {
            out << writeLine << '\n';
        }

        if (originalFileExisted)
            in.close();
        out.close();

        if (originalFileExisted && remove(path.c_str()) != 0)
            cerr << "Error: Could not remove original file " << path << '\n';

        if (rename(tempPath.c_str(), path.c_str()) != 0)
            cerr << "Error: Could not rename temp file to " << path << '\n';
    }

public:
};