#include "infra/repositories/ServiceRepoFile.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
// ===== Private Helper Methods =====

string ServiceRepository::readingFile(const string &serviceId) {
    ifstream file(serviceFilePath);
    if (!file.is_open()) {
        cerr << "Error: Cannot open file " << serviceFilePath << '\n';
        return invalid;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty())
            continue;

        stringstream ss(line);
        string id;
        getline(ss, id, '|');

        if (id == serviceId) {
            file.close();
            return line;
        }
    }

    file.close();
    return invalid;
}

void ServiceRepository::writingFile(const string &serviceId,
                                    const string &writeLine) {
    const string tempPath = "../data/temp.txt";

    ifstream in(serviceFilePath);
    bool originalFileExisted = in.is_open();

    ofstream out(tempPath);
    if (!out.is_open()) {
        cerr << "Error: Cannot create temp file " << tempPath << '\n';
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
            string id;
            getline(ss, id, '|');

            if (id == serviceId) {
                out << writeLine << '\n';
                foundAndUpdated = true;
            } else {
                out << line << '\n';
            }
        }
    }

    if (!foundAndUpdated) {
        out << writeLine << '\n';
    }

    if (originalFileExisted)
        in.close();
    out.close();

    if (originalFileExisted && remove(serviceFilePath.c_str()) != 0) {
        cerr << "Error: Could not remove original file " << serviceFilePath << '\n';
    }

    if (rename(tempPath.c_str(), serviceFilePath.c_str()) != 0) {
        cerr << "Error: Could not rename temp file to " << serviceFilePath << '\n';
    }
}

// ===== GET Operations =====

Service ServiceRepository::getServiceInfo(const string &serviceId) {
    Service service;
    string info = readingFile(serviceId);

    if (info == invalid)
        return service;

    string id, name, desc, priceStr, durationStr;
    stringstream ss(info);

    getline(ss, id, '|');
    getline(ss, name, '|');
    getline(ss, desc, '|');
    getline(ss, priceStr, '|');
    getline(ss, durationStr, '|');

    long price = stof(priceStr);
    int duration = stoi(durationStr);

    service = Service(id, name, desc, price, duration);
    return service;
}

LinkedList<Service> ServiceRepository::getAllServices() {
    LinkedList<Service> services;
    ifstream file(serviceFilePath);

    if (!file.is_open()) {
        cerr << "Error: Cannot open file " << serviceFilePath << '\n';
        return services;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty())
            continue;

        stringstream ss(line);
        string id, name, desc, priceStr, durationStr;

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, desc, '|');
        getline(ss, priceStr, '|');
        getline(ss, durationStr, '|');

        Service service(id, name, desc, stof(priceStr), stoi(durationStr));
        services.pushBack(service);
    }

    file.close();
    return services;
}

long ServiceRepository::getServicePrice(const string &serviceId) {
    Service service = getServiceInfo(serviceId);
    return service.getPrice();
}

int ServiceRepository::getServiceDuration(const string &serviceId) {
    Service service = getServiceInfo(serviceId);
    return service.getDuration();
}

// ===== SET Operations =====

void ServiceRepository::setServiceInfo(const Service &service) {
    string line = service.getId() + "|" + service.getName() + "|" +
                  service.getDescription() + "|" + to_string(service.getPrice()) +
                  "|" + to_string(service.getDuration());

    writingFile(service.getId(), line);
}

void ServiceRepository::updatePrice(const string &serviceId, long newPrice) {
    Service service = getServiceInfo(serviceId);
    if (service.getId().empty()) {
        cerr << "Error: Service not found " << serviceId << '\n';
        return;
    }

    service.setPrice(newPrice);
    setServiceInfo(service);
}

// ===== CHECK Operations =====

bool ServiceRepository::isValidServiceId(const string &serviceId) {
    string info = readingFile(serviceId);
    return (info != invalid);
}

// ===== DELETE Operations =====

void ServiceRepository::deleteService(const string &serviceId) {
    const string tempPath = "../data/temp.txt";

    ifstream in(serviceFilePath);
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
        string id;
        getline(ss, id, '|');

        if (id == serviceId) {
            removed = true;
        } else {
            out << line << '\n';
        }
    }

    in.close();
    out.close();

    if (removed) {
        remove(serviceFilePath.c_str());
        rename(tempPath.c_str(), serviceFilePath.c_str());
    } else {
        remove(tempPath.c_str());
    }
}

// ===== SEARCH Operations =====

LinkedList<Service> ServiceRepository::searchByName(const string &keyword) {
    LinkedList<Service> results;
    LinkedList<Service> allServices = getAllServices();

    string lowerKeyword = keyword;
    transform(lowerKeyword.begin(), lowerKeyword.end(), lowerKeyword.begin(),
              ::tolower);

    Node<Service> *current = allServices.getHead();
    while (current != nullptr) {
        string serviceName = current->getData().getName();
        transform(serviceName.begin(), serviceName.end(), serviceName.begin(),
                  ::tolower);

        if (serviceName.find(lowerKeyword) != string::npos) {
            results.pushBack(current->getData());
        }
        current = current->getNext();
    }

    return results;
}

LinkedList<Service> ServiceRepository::searchByPriceRange(long minPrice,
                                                          long maxPrice) {
    LinkedList<Service> results;
    LinkedList<Service> allServices = getAllServices();

    Node<Service> *current = allServices.getHead();
    while (current != nullptr) {
        long price = current->getData().getPrice();
        if (price >= minPrice && price <= maxPrice) {
            results.pushBack(current->getData());
        }
        current = current->getNext();
    }

    return results;
}

int ServiceRepository::countServices() {
    LinkedList<Service> allServices = getAllServices();
    return allServices.getSize();
}