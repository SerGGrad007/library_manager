#pragma once
#include <string>
#include <chrono>

class Record {
public:
    using TimePoint = std::chrono::system_clock::time_point;

    Record(std::string userId, std::string isbn,
        const TimePoint borrowDate, const TimePoint expireDate,
        const double finePerDay = 0.0): userId(std::move(userId)),
    isbn(std::move(isbn)), borrowDate(borrowDate), expireDate(expireDate),
    finePerDay(finePerDay)
    {}

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

private:
    std::string userId;
    std::string isbn;
    TimePoint borrowDate;
    TimePoint expireDate;
    TimePoint returnDate;
    bool returned = false;
    double finePerDay;
};
