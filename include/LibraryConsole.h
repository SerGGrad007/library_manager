#pragma once

#include <string>

#include "Library.h"

class LibraryConsole {
public:
    void run();

private:
    Library library;

    void showMainMenu();
    void handleBookManagement();
    void handleUserManagement();
    void handleBorrowingOperations();
    void handleViewOverdue();

    static int getIntInput(const std::string& prompt);
    static std::string getStringInput(const std::string& prompt);
    UserType getUserTypeInput();
};