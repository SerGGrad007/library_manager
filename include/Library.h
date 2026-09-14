#pragma once

#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "LibraryOperations.h"

class Library : public LibraryOperations {
public:
    Library() = default;

    void addBook(const std::string& title, const std::string& author,
                 const std::string& isbn, const std::string& genre) override;
    bool removeBook(const std::string& isbn) override;
    Book* findBook(const std::string& isbn) override;
    std::vector<Book> searchBooks(const std::string& query) override;

    void registerUser(const std::string& name, const std::string& userId,
                       const std::string& email, UserType type) override;
    User* findUser(const std::string& userId) override;

    bool borrowBook(const std::string& userId, const std::string& isbn) override;
    bool returnBook(const std::string& userId, const std::string& isbn) override;
    std::vector<Record> getOverdueBooks() override;

    const std::set<std::string>& getGenres() const { return genres; }

private:
    std::unordered_map<std::string, Book> books;
    std::unordered_map<std::string, std::unique_ptr<User>> users;
    std::vector<Record> borrowingHistory;
    std::set<std::string> genres;
    static std::string toLower(const std::string& s);
};