/* đọc ghi file Dog/Cat available/unvailable */
#pragma once
#include "include/domain/entities/Cat.hpp"
#include "include/domain/entities/Dog.hpp"
#include "include/domain/entities/Pet.hpp"
#include "include/ds/LinkedList.hpp"
#include <fstream>
#include <sstream>
#include <string>

class PetRepository {
private:
    const string catFilePath = "../data/Cat.txt";
    const string dogFilePath = "../data/Dog.txt";
    const int petIdLength = 4;
    const string invalid = "";
    string filePath(const string &petCode);
    string readingFile(const string &petCode);
    void writingFile(const string &petCode, const string &writeLine);
    bool isDogId(const string &petCode);

public:
    // GET
    string getPetStatus(const string &petCode);
    Dog getDogInfo(const string &petCode);
    Cat getCatInfo(const string &petCode);
    LinkedList<Cat> *getAllCatInfoAvailable();
    LinkedList<Dog> *getAllDogInfoAvailable();
    // SET
    void setDogInfo(const Dog &dog);
    void setCatInfo(const Cat &cat);
    void setStatusUnavailable(const string &petCode);
    void setStatusAvailable(const string &petCode);
    // OTHERS
    bool isAvailablePet(const string &petCode);
    bool isValidPetId(const string &petCode);
    void deletePet(const string &petCode);
};