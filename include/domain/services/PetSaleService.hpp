#pragma once
#include "include/infra/repositories/PetRepoFile.hpp"
using namespace std;

class PetSaleService {
private:
    PetRepository petRepo;
    void addtoCart_Cat() {
        LinkedList<Cat> *allCat = petRepo.getAllCatInfoAvailable();
        allCat->printLinkedList();
        LinkedList<string> cart;
        while (true) {
            cout << "=================================\n";
            cout << "Enter 00 to exit\n";
            cout << "Choose your cat you want to add to cart: ";
            string choice;
            cin >> choice;
            if (choice == "00") {
                // ADD CartRepoFile.hpp then add all choice into client file
                return;
            }
            if (petRepo.isAvailablePet(choice)) {
                cart.pushBack(choice);
            } else
                cout << "Your choice is invalid!\n";
        }
    }

    void addToCart_Dog() {
        LinkedList<Dog> *allDog = petRepo.getAllDogInfoAvailable();
        allDog->printLinkedList();
        LinkedList<string> cart;
        while (true) {
            cout << "=================================\n";
            cout << "Enter 00 to exit\n";
            cout << "Choose your cat you want to add to cart: ";
            string choice;
            cin >> choice;
            if (choice == "00") {
                // ADD CartRepoFile.hpp then add all choice into client file
                return;
            }
            if (petRepo.isAvailablePet(choice)) {
                cart.pushBack(choice);
            } else
                cout << "Your choice is invalid!\n";
        }
    }

public:
    void addToCart() {
        while (true) {
            system("cls");
            cout << "==========================";
            cout << "Type of pet:\n1.Cat\n2.Dog";
            cout << "Your choice: ";
            int choice;
            cin >> choice;
            if (choice == 1) {
                addtoCart_Cat();
            } else if (choice == 2) {
                addToCart_Dog();
            } else
                cout << "Your choice is invalid!\n";
        }
    }
};