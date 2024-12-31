#include "models/result.h"
#include <iostream>
#include <stdexcept>
#include "database/db_connection.h"
#include <pqxx/pqxx>
#include <sstream>

Result::Result(int id, int userId, int testId, int score) : id(id), userId(userId), testId(testId), score(score) {}

int Result::getId() const {
    return id;
}

int Result::getUserId() const {
    return userId;
}

int Result::getTestId() const {
    return testId;
}

int Result::getScore() const {
    return score;
}

Result Result::create(int userId, int testId, int score) {
    DbConnection db;
    pqxx::connection& connection = db.getConnection();
    pqxx::work txn(connection);
    
    pqxx::result res = txn.exec(
        "INSERT INTO results (user_id, test_id, score) VALUES (" + std::to_string(userId) + ", " + std::to_string(testId) + ", " + std::to_string(score) + ") RETURNING id"
    );
    
    int newId = 0;
    if (!res.empty())
    {
       newId = res[0][0].as<int>();
    }
    txn.commit();
    
    return Result(newId, userId, testId, score);
}

std::vector<Result> Result::getAll() {
    DbConnection db;
    pqxx::connection& connection = db.getConnection();
    pqxx::work txn(connection);

    pqxx::result res = txn.exec("SELECT id, user_id, test_id, score FROM results");

    std::vector<Result> results;
    for (const auto& row : res) {
        results.emplace_back(row[0].as<int>(), row[1].as<int>(), row[2].as<int>(), row[3].as<int>());
    }
     txn.commit();
    return results;
}

Result Result::get(int id) {
    DbConnection db;
    pqxx::connection& connection = db.getConnection();
     pqxx::work txn(connection);

    pqxx::result res = txn.exec(
        "SELECT id, user_id, test_id, score FROM results WHERE id = " + std::to_string(id)
    );

    if (res.empty()) {
        throw std::runtime_error("Result with id " + std::to_string(id) + " not found");
    }
    txn.commit();
    return Result(res[0][0].as<int>(), res[0][1].as<int>(), res[0][2].as<int>(), res[0][3].as<int>());
}

Result Result::update(int id, int userId, int testId, int score) {
    DbConnection db;
    pqxx::connection& connection = db.getConnection();
    pqxx::work txn(connection);

   txn.exec(
        "UPDATE results SET user_id = " + std::to_string(userId) + ", test_id = " + std::to_string(testId) + ", score = " + std::to_string(score) + " WHERE id = " + std::to_string(id)
    );
    txn.commit();
    return Result(id, userId, testId, score);
}

void Result::remove(int id) {
    DbConnection db;
    pqxx::connection& connection = db.getConnection();
    pqxx::work txn(connection);
    txn.exec("DELETE FROM results WHERE id = " + std::to_string(id));
     txn.commit();
}