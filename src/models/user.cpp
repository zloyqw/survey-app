#include "models/user.h"
#include <iostream>
#include <stdexcept>
#include "database/db_connection.h"
#include <pqxx/pqxx>
#include <sstream>

User::User(int id, const std::string& username, const std::string& email) : id(id), username(username), email(email) {}

int User::getId() const {
    return id;
}

std::string User::getUsername() const {
    return username;
}

std::string User::getEmail() const {
    return email;
}

User User::create(const std::string& username, const std::string& email) {
    DbConnection db;
    pqxx::connection& connection = db.getConnection();
    pqxx::work txn(connection);
    
    pqxx::result res = txn.exec(
        "INSERT INTO users (username, email) VALUES ('" + username + "', '" + email + "') RETURNING id"
    );
    
    int newId = 0;
    if (!res.empty())
    {
       newId = res[0][0].as<int>();
    }
    
    txn.commit();

    return User(newId, username, email);
}

std::vector<User> User::getAll() {
    DbConnection db;
    pqxx::connection& connection = db.getConnection();
    pqxx::work txn(connection);

    pqxx::result res = txn.exec("SELECT id, username, email FROM users");

    std::vector<User> users;
    for (const auto& row : res) {
        users.emplace_back(row[0].as<int>(), row[1].as<std::string>(), row[2].as<std::string>());
    }
    txn.commit();
    return users;
}

User User::get(int id) {
    DbConnection db;
    pqxx::connection& connection = db.getConnection();
    pqxx::work txn(connection);

   pqxx::result res = txn.exec(
        "SELECT id, username, email FROM users WHERE id = " + std::to_string(id)
    );

    if (res.empty()) {
        throw std::runtime_error("User with id " + std::to_string(id) + " not found");
    }

    txn.commit();

    return User(res[0][0].as<int>(), res[0][1].as<std::string>(), res[0][2].as<std::string>());
}

User User::update(int id, const std::string& username, const std::string& email) {
    DbConnection db;
    pqxx::connection& connection = db.getConnection();
    pqxx::work txn(connection);

    txn.exec(
       "UPDATE users SET username = '" + username + "', email = '" + email + "' WHERE id = " + std::to_string(id)
    );

    txn.commit();

    return User(id, username, email);
}

void User::remove(int id) {
    DbConnection db;
    pqxx::connection& connection = db.getConnection();
    pqxx::work txn(connection);

    txn.exec("DELETE FROM users WHERE id = " + std::to_string(id));
    txn.commit();
}