/* PetRepoFile.hpp - đọc và ghi các file Pet (UPDATED) */

#pragma once
#include "domain/entities/Cat.hpp"
#include "domain/entities/Dog.hpp"
#include "domain/entities/Pet.hpp"
#include "ds/LinkedList.hpp"
#include <fstream>
#include <sstream>
#include <string>

class PetRepository {
private:
    const std::string catFilePath = "../data/Cat.txt";
    const std::string dogFilePath = "../data/Dog.txt";
    const int petIdLength = 4;
    const std::string invalid = "";

    std::string filePath(const std::string &petCode);
    std::string readingFile(const std::string &petCode);
    void writingFile(const std::string &petCode, const std::string &writeLine);
    bool isDogId(const std::string &petCode);
    // --- THÊM HÀM HELPER ĐỂ XÓA DẤU NGOẶC KÉP ---
    std::string trimQuotes(std::string s);

public:
    // GET
    std::string getPetStatus(const std::string &petCode);
    Dog getDogInfo(const std::string &petCode);
    Cat getCatInfo(const std::string &petCode);
    LinkedList<Cat> getAllCatInfo();
    LinkedList<Dog> getAllDogInfo();
    LinkedList<Cat> getAllCatInfoAvailable();
    LinkedList<Dog> getAllDogInfoAvailable();
    // SET
    void setDogInfo(const Dog &dog);
    void setCatInfo(const Cat &cat);
    void setStatusUnavailable(const std::string &petCode);
    void setStatusAvailable(const std::string &petCode); // use when pet is restored

    // OTHERS
    bool isAvailablePet(const std::string &petCode);
    bool isValidPetId(const std::string &petCode);
    void deletePet(const std::string &petCode);
};