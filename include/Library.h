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
    std::vector<BorrowingRecord> getOverdueBooks() override;

    const std::set<std::string>& getGenres() const { return genres; }

private:
    std::unordered_map<std::string, Book> books;
    std::unordered_map<std::string, std::unique_ptr<User>> users;
    std::vector<Record> borrowingHistory;
    std::set<std::string> genres;
    static std::string toLower(const std::string& s);

    /* ==================== КОНТРАКТЫ МЕТОДОВ ====================

    addBook(title, author, isbn, genre):
        1. Создать Book(title, author, isbn, genre).
        2. Положить в `books` по ключу isbn.
           Подумай: что если такой isbn уже есть — перезаписать
           молча, или это должно считаться ошибкой? Интерфейс
           возвращает void, так что решение — на твой вкус, но
           будь готов объяснить его на ревью.
        3. Добавить genre в `genres` (std::set сам уберёт дубликаты).

    removeBook(isbn):
        1. Найти книгу в `books` по isbn.
        2. Если не найдена -> return false.
        3. Подумай: должна ли операция быть заблокирована, если книга
           сейчас на руках (book.isBorrowed() == true)? В README это не
           прописано явно, но это ровно тот случай, который проверяющие
           хотят видеть в разделе "Handles invalid input gracefully" —
           продуманное поведение на граничный случай.
        4. Удалить из `books`, return true.

    findBook(isbn):
        1. Найти в `books`.
        2. Найдена -> вернуть указатель на неё (&iterator->second).
           Не найдена -> вернуть nullptr.

    searchBooks(query):
        1. Привести query к нижнему регистру через toLower().
        2. Пройтись по всем книгам в `books`.
        3. Для каждой книги проверить: содержится ли query (в нижнем
           регистре) в title, author, genre или isbn (тоже приведённых
           к нижнему регистру через toLower()).
        4. Совпавшие — скопировать в результирующий vector<Book>.
        5. Вернуть результат.

    registerUser(name, userId, email, type):
        1. Вызвать уже готовую фабрику: createUser(type, name, userId, email)
           -> получаешь std::unique_ptr<User>.
        2. Положить в `users` по ключу userId (используй operator[] или
           emplace/insert — unique_ptr сам по себе default-конструируем
           как nullptr, так что operator[] сработает даже без
           default-конструктора у самого User).
        3. Подумай: что если userId уже занят? Аналогично addBook —
           решение твоё, но должно быть осознанным.

    findUser(userId):
        1. Найти в `users`.
        2. Найден -> вернуть iterator->second.get() (сырой указатель
           из unique_ptr, Library остаётся владельцем).
        3. Не найден -> nullptr.

    borrowBook(userId, isbn):
        Порядок проверок важен — каждая должна привести к return false,
        как только сработала:
        1. Найти пользователя (findUser-логика) — не найден -> false.
        2. Найти книгу (findBook-логика) — не найдена -> false.
        3. book->isBorrowed() == true -> false (книга занята).
        4. user->canBorrow() == false -> false (пользователь на лимите).
        5. Если все проверки прошли:
             - book->setBorrowed(true)
             - user->addBorrowedBook(isbn)
             - посчитать now = текущее время
               (std::chrono::system_clock::now())
             - посчитать due = now + user->getBorrowDays() дней
               (не забудь перевести дни в часы/секунды для chrono)
             - добавить BorrowingRecord(userId, isbn, now, due)
               в `borrowingHistory`
        6. return true.

    returnBook(userId, isbn):
        1. Найти книгу — не найдена или book->isBorrowed() == false
           -> false (нечего возвращать).
        2. Найти в `borrowingHistory` ПОСЛЕДНЮЮ ещё не возвращённую
           запись с совпадающими userId и isbn. Совет: искать с конца
           (rbegin()/rend()), т.к. интересует самый недавний займ, а
           одна и та же пара userId+isbn может повторяться в истории.
        3. Не нашли такую запись -> false (данные не согласованы,
           либо пользователь никогда не брал эту книгу).
        4. Нашли:
             - record.markReturned(текущее время)
             - book->setBorrowed(false)
             - user->removeBorrowedBook(isbn)
               (find user через users, как в findUser)
        5. return true.

    getOverdueBooks():
        1. Пройтись по `borrowingHistory`.
        2. Собрать в vector<BorrowingRecord> все записи, для которых
           record.isOverdue() == true.
        3. Вернуть результат.

    ============================================================= */
};