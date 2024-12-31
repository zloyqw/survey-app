#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "database/db_connection.h"

class User {
private:
    int id;
    std::string username;
    std::string email;
public:
    User() = default;
    User(int id, const std::string& username, const std::string& email);
    int getId() const;
    std::string getUsername() const;
    std::string getEmail() const;
    static User create(const std::string& username, const std::string& email);
    static std::vector<User> getAll();
    static User get(int id);
    static User update(int id, const std::string& username, const std::string& email);
    static void remove(int id);
};

#endif