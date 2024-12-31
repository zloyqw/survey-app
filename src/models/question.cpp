#include "models/question.h"
#include <iostream>
#include <stdexcept>
#include "database/db_connection.h"
#include <pqxx/pqxx>
#include <sstream>

Question::Question(int id, int testId, const std::string& questionText) : id(id), testId(testId), questionText(questionText) {}

int Question::getId() const {
    return id;
}

int Question::getTestId() const {
    return testId;
}

std::string Question::getQuestionText() const {
    return questionText;
}

Question Question::create(int testId, const std::string& questionText) {
    DbConnection db;
    pqxx::connection& connection = db.getConnection();
     pqxx::work txn(connection);
    
    pqxx::result res = txn.exec(
        "INSERT INTO questions (test_id, question_text) VALUES (" + std::to_string(testId) + ", '" + questionText + "') RETURNING id"
    );
    
    int newId = 0;
    if (!res.empty())
    {
       newId = res[0][0].as<int>();
    }
    
    txn.commit();
    
    return Question(newId, testId, questionText);
}

std::vector<Question> Question::getAll() {
    DbConnection db;
    pqxx::connection& connection = db.getConnection();
     pqxx::work txn(connection);

    pqxx::result res = txn.exec("SELECT id, test_id, question_text FROM questions");

    std::vector<Question> questions;
    for (const auto& row : res) {
        questions.emplace_back(row[0].as<int>(), row[1].as<int>(), row[2].as<std::string>());
    }
    txn.commit();
    return questions;
}

Question Question::get(int id) {
    DbConnection db;
    pqxx::connection& connection = db.getConnection();
    pqxx::work txn(connection);

    pqxx::result res = txn.exec(
        "SELECT id, test_id, question_text FROM questions WHERE id = " + std::to_string(id)
    );

    if (res.empty()) {
        throw std::runtime_error("Question with id " + std::to_string(id) + " not found");
    }
    txn.commit();
    return Question(res[0][0].as<int>(), res[0][1].as<int>(), res[0][2].as<std::string>());
}

Question Question::update(int id, int testId, const std::string& questionText) {
    DbConnection db;
    pqxx::connection& connection = db.getConnection();
    pqxx::work txn(connection);

    txn.exec(
        "UPDATE questions SET test_id = " + std::to_string(testId) + ", question_text = '" + questionText + "' WHERE id = " + std::to_string(id)
    );
     txn.commit();
    return Question(id, testId, questionText);
}

void Question::remove(int id) {
    DbConnection db;
    pqxx::connection& connection = db.getConnection();
     pqxx::work txn(connection);
    txn.exec("DELETE FROM questions WHERE id = " + std::to_string(id));
     txn.commit();
}