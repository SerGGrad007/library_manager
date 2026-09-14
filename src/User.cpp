#include "User.h"

std::unique_ptr<User> User::createUser(UserType type, const std::string& name,
                                        const std::string& userId, const std::string& email) {
    switch (type) {
        case UserType::STUDENT:
            return std::make_unique<Student>(name, userId, email);
        case UserType::FACULTY:
            return std::make_unique<Faculty>(name, userId, email);
        case UserType::GUEST:
            return std::make_unique<Guest>(name, userId, email);
    }
    return nullptr;
}
