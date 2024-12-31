#include "models/test.h"
#include <iostream>
#include <stdexcept>
#include "database/db_connection.h"
#include <pqxx/pqxx>
#include <sstream>

Test::Test(int id, const std::string& name, const std::string& description) : id(id), name(name), description(description) {}

int Test::getId() const {
    return id;
}

std::string Test::getName() const {
    return name;
}

std::string Test::getDescription() const {
    return description;
}

Test Test::create(const std::string& name, const std::string& description) {
    DbConnection db;
    pqxx::connection& connection = db.getConnection();
    pqxx::work txn(connection);
    
    pqxx::result res = txn.exec(
        "INSERT INTO tests (name, description) VALUES ('" + name + "', '" + description + "') RETURNING id"
    );
    
    int newId = 0;
    if (!res.empty())
    {
       newId = res[0][0].as<int>();
    }
    
    txn.commit();

    return Test(newId, name, description);
}

std::vector<Test> Test::getAll() {
    DbConnection db;
    pqxx::connection& connection = db.getConnection();
    pqxx::work txn(connection);

    pqxx::result res = txn.exec("SELECT id, name, description FROM tests");

    std::vector<Test> tests;
    for (const auto& row : res) {
        tests.emplace_back(row[0].as<int>(), row[1].as<std::string>(), row[2].as<std::string>());
    }
     txn.commit();
    return tests;
}

Test Test::get(int id) {
    DbConnection db;
    pqxx::connection& connection = db.getConnection();
    pqxx::work txn(connection);

    pqxx::result res = txn.exec(
        "SELECT id, name, description FROM tests WHERE id = " + std::to_string(id)
    );

    if (res.empty()) {
        throw std::runtime_error("Test with id " + std::to_string(id) + " not found");
    }
    txn.commit();
    return Test(res[0][0].as<int>(), res[0][1].as<std::string>(), res[0][2].as<std::string>());
}

Test Test::update(int id, const std::string& name, const std::string& description) {
    DbConnection db;
    pqxx::connection& connection = db.getConnection();
     pqxx::work txn(connection);
    txn.exec(
       "UPDATE tests SET name = '" + name + "', description = '" + description + "' WHERE id = " + std::to_string(id)
    );
    txn.commit();
    return Test(id, name, description);
}

void Test::remove(int id) {
    DbConnection db;
    pqxx::connection& connection = db.getConnection();
     pqxx::work txn(connection);
    txn.exec("DELETE FROM tests WHERE id = " + std::to_string(id));
    txn.commit();
}