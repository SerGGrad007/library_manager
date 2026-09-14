#pragma once
#include <string>
#include <chrono>

class Record {
public:
    using TimePoint = std::chrono::system_clock::time_point;

    Record(std::string userId, std::string isbn,
        const TimePoint borrowDate, const TimePoint expireDate): userId(std::move(userId)),
    isbn(std::move(isbn)), borrowDate(borrowDate), expireDate(expireDate){}

    const std::string& getUserId() const {
        return userId;
    }

    const std::string& getIsbn() const {
        return isbn;
    }

    TimePoint getBorrowDate() const {
        return borrowDate;
    }

    TimePoint getExpireDate() const {
        return expireDate;
    }

    TimePoint getReturnDate() const {
        return returnDate;
    }

    bool isReturned() const {
        return returned;
    }

    void markReturned(TimePoint when) {
        returned = true;
        returnDate = when;
    }

    bool isExpired() const {
        return std::chrono::system_clock::now() > expireDate;
    }

    int countDaysExpired() const {
        const TimePoint reference = returned ? returnDate : std::chrono::system_clock::now();
        if (reference <= expireDate) return 0;
        const auto t_diff = std::chrono::duration_cast<std::chrono::hours>(reference - expireDate);
        return static_cast<int> (t_diff.count() / 24) + 1;
    }

private:
    std::string userId;
    std::string isbn;
    TimePoint borrowDate;
    TimePoint expireDate;
    TimePoint returnDate;
    bool returned = false;
};
