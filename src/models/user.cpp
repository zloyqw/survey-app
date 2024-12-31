#include "models/user.h"
#include <vector>
#include <stdexcept>

std::vector<User> User::users;
int User::nextId = 1;

User::User() : id(0), username(""), email("") {}

User::User(int id, const std::string& username, const std::string& email)
    : id(id), username(username), email(email) {}

int User::getId() const {
    return id;
}

void User::setId(int id) {
    this->id = id;
}

std::string User::getUsername() const {
    return username;
}

void User::setUsername(const std::string& username) {
    this->username = username;
}

std::string User::getEmail() const {
    return email;
}

void User::setEmail(const std::string& email) {
    this->email = email;
}

User User::create(const std::string& username, const std::string& email)
{
    User user(nextId++, username, email);
    users.push_back(user);
    return user;
}

std::vector<User> User::getAll()
{
    return users;
}

User User::get(int id)
{
    for (const auto& user : users)
    {
        if (user.getId() == id)
        {
            return user;
        }
    }
    throw std::runtime_error("User not found");
}

User User::update(int id, const std::string& username, const std::string& email)
{
    for (auto& user : users)
    {
        if (user.getId() == id)
        {
            user.setUsername(username);
            user.setEmail(email);
            return user;
        }
    }
    throw std::runtime_error("User not found");
}

void User::remove(int id)
{
    for (size_t i = 0; i < users.size(); ++i)
    {
        if (users[i].getId() == id)
        {
            users.erase(users.begin() + i);
            return;
        }
    }
    throw std::runtime_error("User not found");
}
