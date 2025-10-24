/* PetRepoFile.hpp - đọc và ghi các file Pet (COMPLETED) */

#pragma once
#include "domain/entities/Cat.hpp"
#include "domain/entities/Dog.hpp"
#include "domain/entities/Pet.hpp"
#include "ds/LinkedList.hpp"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

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
    return invalid; // not found
  }

  void writingFile(const string &petCode, const string &writeLine) {
    const string path = filePath(petCode);
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

  bool isDogId(const string &petCode) {
    if (petCode.length() == petIdLength && petCode[0] == 'd')
      return true;
    return false;
  }

public:
  // GET
  string getPetStatus(const string &petCode) {
    string info = readingFile(petCode);
    if (info == invalid)
      return invalid;

    string code, status;
    stringstream ss(info);
    getline(ss, code, '|');
    getline(ss, status, '|');
    if (status == "1")
      return "available";
    return "unavailable";
  }

  Dog getDogInfo(const string &petCode) {
    Dog dog;
    if (!isDogId(petCode))
      return dog;
    string info = readingFile(petCode);
    if (info == invalid)
      return dog;
    string code, status, name, breed, age, price, energy;
    stringstream ss(info);
    getline(ss, code, '|');
    getline(ss, status, '|');
    getline(ss, name, '|');
    getline(ss, breed, '|');
    getline(ss, age, '|');
    getline(ss, price, '|');
    getline(ss, energy, '|');
    dog = Dog(code, name, breed, stoi(age), stof(price), stoi(energy));
    return dog;
  }

  Cat getCatInfo(const string &petCode) {
    Cat cat;
    if (isDogId(petCode))
      return cat;

    string info = readingFile(petCode);
    if (info == invalid)
      return cat;

    string code, status, name, breed, age, price, fur;
    stringstream ss(info);
    getline(ss, code, '|');
    getline(ss, status, '|');
    getline(ss, name, '|');
    getline(ss, breed, '|');
    getline(ss, age, '|');
    getline(ss, price, '|');
    getline(ss, fur, '|');
    cat = Cat(code, name, breed, stoi(age), stof(price), fur);
    return cat;
  }

  LinkedList<Cat> getAllCatInfo() {
    LinkedList<Cat> cats;
    ifstream file(catFilePath);
    if (!file.is_open()) {
      cerr << "Error: Cant open file " << catFilePath << '\n';
      return cats;
    }
    string line;
    while (getline(file, line)) {
      if (line.empty())
        continue;
      string code, status, name, breed, age, price, fur;
      stringstream ss(line);
      getline(ss, code, '|');
      getline(ss, status, '|');
      getline(ss, name, '|');
      getline(ss, breed, '|');
      getline(ss, age, '|');
      getline(ss, price, '|');
      getline(ss, fur, '|');
      Cat cat(code, name, breed, stoi(age), stof(price), fur);
      cats.pushBack(cat);
    }
    file.close();
    return cats;
  }

  LinkedList<Dog> getAllDogInfo() {
    LinkedList<Dog> dogs;
    ifstream file(dogFilePath);
    if (!file.is_open()) {
      cerr << "Error: Cant open file " << dogFilePath << '\n';
      return dogs;
    }
    string line;
    while (getline(file, line)) {
      if (line.empty())
        continue;
      string code, status, name, breed, age, price, energy;
      stringstream ss(line);
      getline(ss, code, '|');
      getline(ss, status, '|');
      getline(ss, name, '|');
      getline(ss, breed, '|');
      getline(ss, age, '|');
      getline(ss, price, '|');
      getline(ss, energy, '|');
      Dog dog(code, name, breed, stoi(age), stof(price), stoi(energy));
      dogs.pushBack(dog);
    }
    file.close();
    return dogs;
  }

  LinkedList<Cat> getAllCatInfoAvailable() {
    LinkedList<Cat> cats;
    ifstream file(catFilePath);
    if (!file.is_open()) {
      cerr << "Error: Cant open file " << catFilePath << '\n';
      return cats;
    }
    string line;
    while (getline(file, line)) {
      if (line.empty())
        continue;
      string code, status, name, breed, age, price, fur;
      stringstream ss(line);
      getline(ss, code, '|');
      getline(ss, status, '|');
      getline(ss, name, '|');
      getline(ss, breed, '|');
      getline(ss, age, '|');
      getline(ss, price, '|');
      getline(ss, fur, '|');
      if (status == "1") {
        Cat cat(code, name, breed, stoi(age), stof(price), fur);
        cats.pushBack(cat);
      }
    }
    file.close();
    return cats;
  }

  LinkedList<Dog> getAllDogInfoAvailable() {
    LinkedList<Dog> dogs;
    ifstream file(dogFilePath);
    if (!file.is_open()) {
      cerr << "Error: Cant open file " << dogFilePath << '\n';
      return dogs;
    }
    string line;
    while (getline(file, line)) {
      if (line.empty())
        continue;
      if (line.length() > 6 && line[6] == '1') { // available pet
        string code, status, name, breed, age, price, energy;
        stringstream ss(line);
        getline(ss, code, '|');
        getline(ss, status, '|');
        getline(ss, name, '|');
        getline(ss, breed, '|');
        getline(ss, age, '|');
        getline(ss, price, '|');
        getline(ss, energy, '|');
        Dog dog(code, name, breed, stoi(age), stof(price), stoi(energy));
        dogs.pushBack(dog);
      }
    }
    file.close();
    return dogs;
  }

  // SET
  void setDogInfo(const Dog &dog) {
    string line = dog.getId() + "|1|" + dog.getName() + '|' + dog.getBreed() +
                  '|' + to_string(dog.getAge()) + '|' +
                  to_string(dog.getPrice()) + '|' +
                  to_string(dog.getEnergyLevel());
    writingFile(dog.getId(), line);
  }

  void setCatInfo(const Cat &cat) {
    string line = cat.getId() + "|1|" + cat.getName() + '|' + cat.getBreed() +
                  '|' + to_string(cat.getAge()) + '|' +
                  to_string(cat.getPrice()) + '|' + cat.getFurLength();
    writingFile(cat.getId(), line);
  }

  void setStatusUnavailable(const string &petCode) {
    string info = readingFile(petCode);
    if (info == invalid)
      return;

    stringstream ss(info);
    string code, status, rest;
    getline(ss, code, '|');
    getline(ss, status, '|');
    getline(ss, rest);

    if (status == "1") {
      string newLine = code + "|0|" + rest;
      writingFile(petCode, newLine);
    }
  }

  void setStatusAvailable(const string &petCode) {
    string info = readingFile(petCode);
    if (info == invalid)
      return;

    stringstream ss(info);
    string code, status, rest;
    getline(ss, code, '|');
    getline(ss, status, '|');
    getline(ss, rest);

    if (status == "0") {
      string newLine = code + "|1|" + rest;
      writingFile(petCode, newLine);
    }
  }
  // use when pet is restored

  // OTHERS
  bool isAvailablePet(const string &petCode) {
    string info = readingFile(petCode);
    if (info == invalid)
      return false;

    string code, status;
    stringstream ss(info);
    getline(ss, code, '|');
    getline(ss, status, '|');
    return (status == "1");
  }

  bool isValidPetId(const string &petCode) {
    string info = readingFile(petCode);
    return (info == invalid ? false : true);
  }

  void deletePet(const string &petCode) {
    const string path = filePath(petCode);
    if (path == invalid)
      return;

    const string tempPath = "../data/temp.txt";
    ifstream in(path);
    ofstream out(tempPath);

    if (!in.is_open() || !out.is_open()) {
      cerr << "Error opening files for removal.\n";
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

      if (code == petCode)
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
      remove(tempPath.c_str());
    }
  }
};