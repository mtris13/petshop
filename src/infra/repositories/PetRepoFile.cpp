#include "infra/repositories/PetRepoFile.hpp"
using namespace std;

string PetRepository::filePath(const string &petCode) {
    if (petCode.length() != petIdLength)
        return invalid;
    if (petCode[0] == 'd')
        return dogFilePath;
    return catFilePath;
}

string PetRepository::readingFile(const string &petCode) {
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

void PetRepository::writingFile(const string &petCode, const string &writeLine) {
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

bool PetRepository::isDogId(const string &petCode) {
    if (petCode.length() == petIdLength && petCode[0] == 'd')
        return true;
    return false;
}
string PetRepository::toLowercase(std::string &str) {
    for (int i = 0; i < str.length(); i++)
        str[i] = tolower(str[i]);
    return str;
}

// --- THÊM HÀM HELPER ĐỂ XÓA DẤU NGOẶC KÉP ---
string PetRepository::trimQuotes(string s) {
    if (s.length() >= 2 && s.front() == '"' && s.back() == '"') {
        return s.substr(1, s.length() - 2);
    }
    return s;
}

// GET
string PetRepository::getPetStatus(const string &petCode) {
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

Dog PetRepository::getDogInfo(const string &petCode) {
    Dog dog;
    if (!isDogId(petCode))
        return dog;
    string info = readingFile(petCode);
    if (info == invalid)
        return dog;

    // --- SỬA ĐỔI: Thêm description ---
    string code, status, name, breed, age, price, energy, description;
    stringstream ss(info);
    getline(ss, code, '|');
    getline(ss, status, '|');
    getline(ss, name, '|');
    getline(ss, breed, '|');
    getline(ss, age, '|');
    getline(ss, price, '|');
    getline(ss, energy, '|');
    getline(ss, description); // Đọc phần còn lại của dòng

    description = trimQuotes(description); // Xóa dấu ngoặc kép

    dog = Dog(code, name, breed, stoi(age), stol(price), stoi(status), stoi(energy), description);
    return dog;
}

Cat PetRepository::getCatInfo(const string &petCode) {
    Cat cat;
    if (isDogId(petCode))
        return cat;

    string info = readingFile(petCode);
    if (info == invalid)
        return cat;

    // --- SỬA ĐỔI: Thêm description ---
    string code, status, name, breed, age, price, fur, description;
    stringstream ss(info);
    getline(ss, code, '|');
    getline(ss, status, '|');
    getline(ss, name, '|');
    getline(ss, breed, '|');
    getline(ss, age, '|');
    getline(ss, price, '|');
    getline(ss, fur, '|');
    getline(ss, description); // Đọc phần còn lại của dòng

    description = trimQuotes(description); // Xóa dấu ngoặc kép

    cat = Cat(code, name, breed, stoi(age), stol(price), stoi(status), fur, description);
    return cat;
}

LinkedList<Cat> PetRepository::getAllCatInfo() {
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

        // --- SỬA ĐỔI: Thêm description ---
        string code, status, name, breed, age, price, fur, description;
        stringstream ss(line);
        getline(ss, code, '|');
        getline(ss, status, '|');
        getline(ss, name, '|');
        getline(ss, breed, '|');
        getline(ss, age, '|');
        getline(ss, price, '|');
        getline(ss, fur, '|');
        getline(ss, description); // Đọc phần còn lại

        description = trimQuotes(description); // Xóa dấu ngoặc kép

        Cat cat = Cat(code, name, breed, stoi(age), stol(price), stoi(status), fur, description);
        cats.pushBack(cat);
    }
    file.close();
    return cats;
}

LinkedList<Dog> PetRepository::getAllDogInfo() {
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

        // --- SỬA ĐỔI: Thêm description ---
        string code, status, name, breed, age, price, energy, description;
        stringstream ss(line);
        getline(ss, code, '|');
        getline(ss, status, '|');
        getline(ss, name, '|');
        getline(ss, breed, '|');
        getline(ss, age, '|');
        getline(ss, price, '|');
        getline(ss, energy, '|');
        getline(ss, description); // Đọc phần còn lại

        description = trimQuotes(description); // Xóa dấu ngoặc kép

        Dog dog = Dog(code, name, breed, stoi(age), stol(price), stoi(status), stoi(energy), description);
        dogs.pushBack(dog);
    }
    file.close();
    return dogs;
}

LinkedList<Cat> PetRepository::getAllCatInfoAvailable() {
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

        // --- SỬA ĐỔI: Thêm description ---
        string code, status, name, breed, age, price, fur, description;
        stringstream ss(line);
        getline(ss, code, '|');
        getline(ss, status, '|');
        getline(ss, name, '|');
        getline(ss, breed, '|');
        getline(ss, age, '|');
        getline(ss, price, '|');
        getline(ss, fur, '|');
        getline(ss, description); // Đọc phần còn lại

        description = trimQuotes(description); // Xóa dấu ngoặc kép

        if (status == "1") {
            Cat cat = Cat(code, name, breed, stoi(age), stol(price), stoi(status), fur, description);
            cats.pushBack(cat);
        }
    }
    file.close();
    return cats;
}

LinkedList<Dog> PetRepository::getAllDogInfoAvailable() {
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

        // --- SỬA ĐỔI: Thêm description ---
        string code, status, name, breed, age, price, energy, description;
        stringstream ss(line);
        getline(ss, code, '|');
        getline(ss, status, '|');
        getline(ss, name, '|');
        getline(ss, breed, '|');
        getline(ss, age, '|');
        getline(ss, price, '|');
        getline(ss, energy, '|');
        getline(ss, description); // Đọc phần còn lại

        description = trimQuotes(description); // Xóa dấu ngoặc kép

        if (status == "1") {
            Dog dog = Dog(code, name, breed, stoi(age), stol(price), stoi(status), stoi(energy), description);
            dogs.pushBack(dog);
        }
    }
    file.close();
    return dogs;
}

// SET
void PetRepository::setDogInfo(const Dog &dog) {
    // --- SỬA ĐỔI: Thêm description vào chuỗi, bọc trong dấu " " ---
    string line =
        dog.getId() + "|1|" + dog.getName() + '|' + dog.getBreed() + '|' +
        to_string(dog.getAge()) + '|' + to_string(dog.getPrice()) + '|' +
        to_string(dog.getEnergyLevel()) + "|\"" + dog.getDescription() + "\"";
    writingFile(dog.getId(), line);
}

void PetRepository::setCatInfo(const Cat &cat) {
    // --- SỬA ĐỔI: Thêm description vào chuỗi, bọc trong dấu " " ---
    string line = cat.getId() + "|1|" + cat.getName() + '|' + cat.getBreed() +
                  '|' + to_string(cat.getAge()) + '|' +
                  to_string(cat.getPrice()) + '|' + cat.getFurLength() + "|\"" +
                  cat.getDescription() + "\"";
    writingFile(cat.getId(), line);
}

void PetRepository::setStatusUnavailable(const string &petCode) {
    string info = readingFile(petCode);
    if (info == invalid)
        return;

    stringstream ss(info);
    string code, status, rest;
    getline(ss, code, '|');
    getline(ss, status, '|');
    getline(ss, rest); // 'rest' sẽ tự động chứa cả description

    if (status == "1") {
        string newLine = code + "|0|" + rest;
        writingFile(petCode, newLine);
    }
}

void PetRepository::setStatusAvailable(const string &petCode) {
    string info = readingFile(petCode);
    if (info == invalid)
        return;

    stringstream ss(info);
    string code, status, rest;
    getline(ss, code, '|');
    getline(ss, status, '|');
    getline(ss, rest); // 'rest' sẽ tự động chứa cả description

    if (status == "0") {
        string newLine = code + "|1|" + rest;
        writingFile(petCode, newLine);
    }
}
// use when pet is restored

// OTHERS
bool PetRepository::isAvailablePet(const string &petCode) {
    string info = readingFile(petCode);
    if (info == invalid)
        return false;

    string code, status;
    stringstream ss(info);
    getline(ss, code, '|');
    getline(ss, status, '|');
    return (status == "1");
}

bool PetRepository::isValidPetId(const string &petCode) {
    string info = readingFile(petCode);
    return (info == invalid ? false : true);
}

void PetRepository::deletePet(const string &petCode) {
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

LinkedList<Dog> PetRepository::searchDog(std::string searchType, std::string &keyword) {
    toLowercase(keyword);
    LinkedList<Dog> dogs;
    ifstream file(dogFilePath); // Giả sử bạn có biến thành viên "dogFilePath"
    if (!file.is_open()) {
        cerr << "Error: Cant open file " << dogFilePath << '\n';
        return dogs;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty())
            continue;

        stringstream ss(line);
        string id, statusStr, name, breed;

        // --- Lưu ý: Phải parse đúng thứ tự file .txt của bạn ---
        // (Dựa theo code gốc của bạn)
        getline(ss, id, '|');
        getline(ss, statusStr, '|');
        getline(ss, name, '|');
        getline(ss, breed, '|');
        string searchField = (searchType == "name") ? toLowercase(name) : toLowercase(breed);

        if (searchField.find(keyword) != string::npos) {
            string ageStr, priceStr, energyStr, description;
            getline(ss, ageStr, '|');
            getline(ss, priceStr, '|');
            getline(ss, energyStr, '|');
            getline(ss, description); // Lấy phần còn lại làm description
            Dog dog = Dog(id, name, breed, stoi(ageStr), stol(priceStr), stoi(statusStr), stoi(energyStr), description);
            dogs.pushBack(dog);
        }
    }
    file.close();
    return dogs;
}

LinkedList<Cat> PetRepository::searchCat(string searchType, string &keyword) {
    toLowercase(keyword);
    LinkedList<Cat> cats;
    ifstream file(catFilePath); // Thay đổi: Dùng file Cat
    if (!file.is_open()) {
        cerr << "Error: Cant open file " << catFilePath << '\n';
        return cats;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty())
            continue;

        stringstream ss(line);
        string id, statusStr, name, breed;

        getline(ss, id, '|');
        getline(ss, statusStr, '|');
        getline(ss, name, '|');
        getline(ss, breed, '|');

        // Logic tìm kiếm giống hệt
        string searchField = (searchType == "name") ? toLowercase(name) : toLowercase(breed);

        if (searchField.find(keyword) != string::npos) {
            string ageStr, priceStr, fur, description; // Thay đổi: fur thay vì energyStr

            getline(ss, ageStr, '|');
            getline(ss, priceStr, '|');
            getline(ss, fur, '|');
            getline(ss, description);

            Cat cat = Cat(id, name, breed, stoi(ageStr), stol(priceStr), stoi(statusStr), fur, description);
            cats.pushBack(cat);
        }
    }
    file.close();
    return cats;
}