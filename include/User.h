#pragma once

#ifndef LIBRARY_MANAGER_USER_H
#define LIBRARY_MANAGER_USER_H

#include <string>
// #include <utility>
#include <utility>
#include <vector>

class User {
public:
    User(std::string name, std::string userId, std::string email):
    name(std::move(name)), userId(std::move(userId)), email(std::move(email)){
        this->borrowedBooks = new std::vector<std::string>();
    }

    int getMaxBooks();
    int getBorrowDays();
    double getFinePerDay();

    bool canBorrow() {
        return borrowedBooks->size() < getMaxBooks();
    }

protected:
    std::string name;
    std::string userId;
    std::string email;
    std::vector<std::string>* borrowedBooks;
};

class Student : public User {
    Student(std::string name, std::string userId, std::string email):
    User(std::move(name), std::move(userId), std::move(email)){}

    int getMaxBooks() {
        return 3;
    }

    int getBorrowDays() {
        return 14;
    }

    double getFinePerDay() {
        return 0.50;
    }
};

class Faculty : public User {
    Faculty(std::string name, std::string userId, std::string email):
    User(std::move(name), std::move(userId), std::move(email)){}

    int getMaxBooks() {
        return 10;
    }

    int getBorrowDays() {
        return 30;
    }

    double getFinePerDay() {
        return 0.50;
    }
};

class Guest : public User {
    Guest(std::string name, std::string userId, std::string email):
    User(std::move(name), std::move(userId), std::move(email)){}

    int getMaxBooks() {
        return 1;
    }

    int getBorrowDays() {
        return 7;
    }

    double getFinePerDay() {
        return 0.50;
    }
};
#endif //LIBRARY_MANAGER_USER_H