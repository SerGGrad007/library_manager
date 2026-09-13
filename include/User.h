#pragma once

#define LIBRARY_MANAGER_USER_H

#include <string>
#include <utility>
#include <vector>

class User {
public:
    User(std::string name, std::string userId, std::string email):
    name(std::move(name)), userId(std::move(userId)), email(std::move(email)){
        this->borrowedBooks = std::vector<std::string>();
    }

    virtual int getMaxBooks() = 0;
    virtual int getBorrowDays() = 0;
    virtual double getFinePerDay() = 0;

    virtual ~User();

    bool canBorrow() {
        return borrowedBooks.size() < static_cast<size_t>(getMaxBooks());
    }

    const std::string& getUserId() const {
        return userId;
    }

    const std::string& getName() const {
        return name;
    }

    const std::string& getEmail() const {
        return email;
    }

    const std::vector<std::string>& getBorrowedBooks() const {
        return borrowedBooks;
    }

protected:
    std::string name;
    std::string userId;
    std::string email;
    std::vector<std::string> borrowedBooks;
};

class Student final : public User {
public:
    Student(std::string name, std::string userId, std::string email):
    User(std::move(name), std::move(userId), std::move(email)){}

    int getMaxBooks() override {
        return 3;
    }

    int getBorrowDays() override {
        return 14;
    }

    double getFinePerDay() override {
        return 0.50;
    }
};

class Faculty final : public User {
public:
    Faculty(std::string name, std::string userId, std::string email):
    User(std::move(name), std::move(userId), std::move(email)){}

    int getMaxBooks() override {
        return 10;
    }

    int getBorrowDays() override {
        return 30;
    }

    double getFinePerDay() override {
        return 0.50;
    }
};

class Guest final : public User {
public:
    Guest(std::string name, std::string userId, std::string email):
    User(std::move(name), std::move(userId), std::move(email)){}

    int getMaxBooks() override {
        return 1;
    }

    int getBorrowDays() override {
        return 7;
    }

    double getFinePerDay() override {
        return 0.50;
    }
};