#pragma once
#include <string>
#include <utility>

class Book {
public:
    Book() = default;

    Book(std::string title, std::string author, std::string isbn, std::string genre):
    title(std::move(title)), author(std::move(author)),
    isbn(std::move(isbn)), genre(std::move(genre)), is_borrowed(false){}

    const std::string& getTitle() const {
        return title;
    }

    const std::string& getAuthor() const {
        return author;
    }

    const std::string& getGenre() const {
        return genre;
    }

    const std::string& getIsbn() const {
        return isbn;
    }

    bool isBorrowed() const {
        return is_borrowed;
    }

    void setBorrowed(const bool value) {
        is_borrowed = value;
    }

private:
    std::string title;
    std::string author;
    std::string isbn;
    std::string genre;
    bool is_borrowed = false;
};
