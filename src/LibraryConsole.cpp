#include "LibraryConsole.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>

void LibraryConsole::run()
{
    while (true)
    {
        showMainMenu();

        const int choice = getIntInput("Enter choice: ");

        switch (choice)
        {
        case 1:
            handleBookManagement();
            break;

        case 2:
            handleUserManagement();
            break;

        case 3:
            handleBorrowingOperations();
            break;

        case 4:
            handleViewOverdue();
            break;

        case 0:
            return;

        default:
            std::cout << "Invalid choice.\n";
            break;
        }
    }
}

void LibraryConsole::showMainMenu()
{
    std::cout << "\n========== Library ==========\n";
    std::cout << "1. Book management\n";
    std::cout << "2. User management\n";
    std::cout << "3. Borrowing operations\n";
    std::cout << "4. View overdue books\n";
    std::cout << "0. Exit\n";
}

void LibraryConsole::handleBookManagement()
{
    while (true)
    {
        std::cout << "\n====== Book Management ======\n";
        std::cout << "1. Add book\n";
        std::cout << "2. Remove book\n";
        std::cout << "3. Search books\n";
        std::cout << "4. Find book by ISBN\n";
        std::cout << "0. Back\n";

        const int choice = getIntInput("Enter choice: ");

        switch (choice)
        {
        case 1:
        {
            const std::string title =
                getStringInput("Enter title: ");

            const std::string author =
                getStringInput("Enter author: ");

            const std::string isbn =
                getStringInput("Enter ISBN: ");

            const std::string genre =
                getStringInput("Enter genre: ");

            library.addBook(title, author, isbn, genre);

            std::cout << "Book added successfully.\n";
            break;
        }

        case 2:
        {
            const std::string isbn =
                getStringInput("Enter ISBN: ");

            if (library.removeBook(isbn))
            {
                std::cout << "Book removed successfully.\n";
            }
            else
            {
                std::cout
                    << "Failed to remove book. "
                    << "It may not exist or may currently be borrowed.\n";
            }

            break;
        }

        case 3:
        {
            const std::string query =
                getStringInput("Enter search query: ");

            const auto books = library.searchBooks(query);

            if (books.empty())
            {
                std::cout << "Nothing found.\n";
                break;
            }

            for (const auto& book : books)
            {
                std::cout << "\n";
                std::cout << "Title: " << book.getTitle() << '\n';
                std::cout << "Author: " << book.getAuthor() << '\n';
                std::cout << "ISBN: " << book.getIsbn() << '\n';
                std::cout << "Genre: " << book.getGenre() << '\n';
                std::cout << "Borrowed: "
                          << (book.isBorrowed() ? "Yes" : "No")
                          << '\n';
            }

            break;
        }

        case 4:
        {
            const std::string isbn =
                getStringInput("Enter ISBN: ");

            Book* book = library.findBook(isbn);

            if (book == nullptr)
            {
                std::cout << "Book not found.\n";
            }
            else
            {
                std::cout << "\n";
                std::cout << "Title: " << book->getTitle() << '\n';
                std::cout << "Author: " << book->getAuthor() << '\n';
                std::cout << "ISBN: " << book->getIsbn() << '\n';
                std::cout << "Genre: " << book->getGenre() << '\n';
                std::cout << "Borrowed: "
                          << (book->isBorrowed() ? "Yes" : "No")
                          << '\n';
            }

            break;
        }

        case 0:
            return;

        default:
            std::cout << "Invalid choice.\n";
            break;
        }
    }
}

void LibraryConsole::handleUserManagement()
{
    while (true)
    {
        std::cout << "\n====== User Management ======\n";
        std::cout << "1. Register user\n";
        std::cout << "2. Find user\n";
        std::cout << "0. Back\n";

        const int choice = getIntInput("Enter choice: ");

        switch (choice)
        {
        case 1:
        {
            const std::string name =
                getStringInput("Enter name: ");

            const std::string userId =
                getStringInput("Enter user ID: ");

            const std::string email =
                getStringInput("Enter email: ");

            const UserType type = getUserTypeInput();

            library.registerUser(name, userId, email, type);

            std::cout << "User registered successfully.\n";
            break;
        }

        case 2:
        {
            const std::string userId =
                getStringInput("Enter user ID: ");

            User* user = library.findUser(userId);

            if (user == nullptr)
            {
                std::cout << "User not found.\n";
            }
            else
            {
                std::cout << "\n";
                std::cout << "Name: " << user->getName() << '\n';
                std::cout << "User ID: " << user->getUserId() << '\n';
                std::cout << "Email: " << user->getEmail() << '\n';
            }

            break;
        }

        case 0:
            return;

        default:
            std::cout << "Invalid choice.\n";
            break;
        }
    }
}

void LibraryConsole::handleBorrowingOperations()
{
    while (true)
    {
        std::cout << "\n====== Borrowing Operations ======\n";
        std::cout << "1. Borrow book\n";
        std::cout << "2. Return book\n";
        std::cout << "0. Back\n";

        const int choice = getIntInput("Enter choice: ");

        switch (choice)
        {
        case 1:
        {
            const std::string userId =
                getStringInput("Enter user ID: ");

            const std::string isbn =
                getStringInput("Enter ISBN: ");

            User* user = library.findUser(userId);

            if (user == nullptr)
            {
                std::cout << "Borrow failed: user not found.\n";
                break;
            }

            Book* book = library.findBook(isbn);

            if (book == nullptr)
            {
                std::cout << "Borrow failed: book not found.\n";
                break;
            }

            if (book->isBorrowed())
            {
                std::cout << "Borrow failed: book is already borrowed.\n";
                break;
            }

            if (!user->canBorrow())
            {
                std::cout << "Borrow failed: borrowing limit exceeded.\n";
                break;
            }

            if (library.borrowBook(userId, isbn))
            {
                std::cout << "Book borrowed successfully.\n";
            }
            else
            {
                std::cout << "Failed to borrow book.\n";
            }

            break;
        }

        case 2:
        {
            const std::string userId =
                getStringInput("Enter user ID: ");

            const std::string isbn =
                getStringInput("Enter ISBN: ");

            if (library.returnBook(userId, isbn))
            {
                std::cout << "Book returned successfully.\n";
            }
            else
            {
                std::cout
                    << "Return failed: invalid user/book "
                    << "or the book is not borrowed by this user.\n";
            }

            break;
        }

        case 0:
            return;

        default:
            std::cout << "Invalid choice.\n";
            break;
        }
    }
}

void LibraryConsole::handleViewOverdue()
{
    const auto overdueBooks = library.getOverdueBooks();

    if (overdueBooks.empty())
    {
        std::cout << "\nNo overdue books.\n";
        return;
    }

    std::cout << "\n========== Overdue Books ==========\n";

    for (const auto& record : overdueBooks)
    {
        std::cout << "\nUser ID: "
                  << record.getUserId() << '\n';

        std::cout << "ISBN: "
                  << record.getIsbn() << '\n';

        std::cout << "Days overdue: "
                  << record.getExpireDate() << '\n';
    }
}

int LibraryConsole::getIntInput(const std::string& prompt)
{
    while (true)
    {
        std::cout << prompt;

        std::string input;
        std::getline(std::cin, input);

        try
        {
            std::size_t pos = 0;

            const int value = std::stoi(input, &pos);

            // Запрещаем ввод вроде "123abc".
            if (pos != input.size())
            {
                throw std::invalid_argument("extra characters");
            }

            return value;
        }
        catch (const std::invalid_argument&)
        {
            std::cout
                << "Please enter a valid number.\n";
        }
        catch (const std::out_of_range&)
        {
            std::cout
                << "Please enter a valid number.\n";
        }
    }
}

std::string LibraryConsole::getStringInput(const std::string& prompt)
{
    while (true)
    {
        std::cout << prompt;

        std::string input;
        std::getline(std::cin, input);

        if (!input.empty())
            return input;

        std::cout << "Input cannot be empty.\n";
    }
}

UserType LibraryConsole::getUserTypeInput()
{
    while (true)
    {
        std::cout << "\nSelect user type:\n";
        std::cout << "1. Student\n";
        std::cout << "2. Faculty\n";
        std::cout << "3. Guest\n";

        const int choice =
            getIntInput("Enter choice: ");

        switch (choice)
        {
        case 1:
            return UserType::STUDENT;

        case 2:
            return UserType::FACULTY;

        case 3:
            return UserType::GUEST;

        default:
            std::cout
                << "Invalid user type. "
                << "Please choose 1, 2 or 3.\n";
        }
    }
}