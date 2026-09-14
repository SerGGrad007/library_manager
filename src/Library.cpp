#include "Library.h"

#include <ranges>

std::string Library::toLower(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
                    [](unsigned char c) { return std::tolower(c); });
    return result;
}

void Library::addBook(const std::string &title, const std::string &author, const std::string &isbn,
                      const std::string &genre) {
    const Book book (title, author, isbn, genre);
    books[isbn] = book;
    genres.emplace(genre);

}

bool Library::removeBook(const std::string &isbn) {
    if (!books.contains(isbn)) return false;
    if (const Book book = books[isbn]; book.isBorrowed() == true) return false;
    books.erase(isbn);
    return true;
}

Book * Library::findBook(const std::string &isbn) {
    return books.contains(isbn) ? &books[isbn] : nullptr;
}

std::vector<Book> Library::searchBooks(const std::string &query) {
    const auto q = toLower(query);
    std::vector<Book> result;
    for (const auto &val : books | std::views::values) {
        if (toLower(val.getAuthor()).find(q) != std::string::npos ||
            toLower(val.getGenre()).find(q) != std::string::npos ||
            toLower(val.getTitle()).find(q) != std::string::npos ||
            toLower(val.getIsbn()).find(q) != std::string::npos)
        {
            result.push_back(val);
        }
    }
    return result;
}

void Library::registerUser(const std::string &name, const std::string &userId, const std::string &email,
    UserType type) {
    auto user = User::createUser(type, name, userId, email);
    users[userId] = std::move(user);
}

User * Library::findUser(const std::string &userId) {
    if (users.contains(userId)) {
        return users[userId].get();
    }
    return nullptr;
}

bool Library::borrowBook(const std::string &userId, const std::string &isbn) {
    if (!findUser(userId)) return false;
    if (!findBook(isbn)) return false;
    auto book = findBook(isbn);
    auto user = findUser(userId);
    if (book->isBorrowed() == true) return false;
    if (user->canBorrow() == false) return false;
    book->setBorrowed(true);
    user->addBorrowedBook(isbn);
    const auto now = std::chrono::system_clock::now();
    const auto expire_day = now +
        std::chrono::hours(24 * user->getBorrowDays());
    borrowingHistory.emplace_back(
        userId,
        isbn,
        now,
        expire_day
    );

    return true;
}

bool Library::returnBook(const std::string &userId, const std::string &isbn) {
    auto book = findBook(isbn);
    auto user = findUser(userId);
    if (book == nullptr || !book->isBorrowed()) return false;
    if (user == nullptr) return false;

    Record* foundRecord = nullptr;

    for (auto & it : std::ranges::reverse_view(borrowingHistory))
    {
        if (it.getUserId() == userId &&
            it.getIsbn() == isbn &&
            !it.isReturned())
        {
            foundRecord = &it;
            break;
        }
    }

    if (foundRecord == nullptr) return false;

    const auto now = std::chrono::system_clock::now();
    foundRecord->markReturned(now);

    book->setBorrowed(false);
    user->removeBorrowedBook(isbn);

    return true;

}

std::vector<Record> Library::getOverdueBooks() {
    std::vector<Record> result;

    for (const auto& record : borrowingHistory)
    {
        if (record.isExpired()) result.push_back(record);
    }

    return result;
}
