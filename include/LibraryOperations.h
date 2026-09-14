#pragma once

#include <string>
#include <vector>

#include <Book.h>
#include <Record.h>
#include <User.h>

class LibraryOperations {
public:
    virtual ~LibraryOperations() = default;

    virtual void addBook(const std::string& title, const std::string& author,
                          const std::string& isbn, const std::string& genre) = 0;
    virtual bool removeBook(const std::string& isbn) = 0;
    virtual Book* findBook(const std::string& isbn) = 0;
    virtual std::vector<Book> searchBooks(const std::string& query) = 0;

    virtual void registerUser(const std::string& name, const std::string& userId,
                               const std::string& email, UserType type) = 0;
    virtual User* findUser(const std::string& userId) = 0;

    virtual bool borrowBook(const std::string& userId, const std::string& isbn) = 0;
    virtual bool returnBook(const std::string& userId, const std::string& isbn) = 0;
    virtual std::vector<Record> getOverdueBooks() = 0;
};