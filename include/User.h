#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

enum class UserType {
    STUDENT,
    FACULTY,
    GUEST
};

class User {
public:
    User(std::string name, std::string userId, std::string email):
    name(std::move(name)), userId(std::move(userId)), email(std::move(email)){}

    virtual int getMaxBooks() = 0;
    virtual int getBorrowDays() = 0;
    virtual UserType getType() = 0;

    virtual ~User() = default;

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

    void addBorrowedBook (const std::string& isbn) {
        borrowedBooks.push_back(isbn);
    }

    void removeBorrowedBook (const std::string& isbn) {
        std::erase(borrowedBooks, isbn);
    }

    static std::unique_ptr<User> createUser(UserType type, const std::string& name,
        const std::string& userId, const std::string& email);


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

    UserType getType() override {
        return UserType::STUDENT;
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

    UserType getType() override {
        return UserType::FACULTY;
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

    UserType getType() override {
        return UserType::GUEST;
    }
};