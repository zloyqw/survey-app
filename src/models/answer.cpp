#include "models/answer.h"
#include <iostream>
#include <stdexcept>
#include "database/db_connection.h"
#include <pqxx/pqxx>
#include <sstream>

Answer::Answer(int id, int questionId, const std::string& answerText, bool isCorrect) : id(id), questionId(questionId), answerText(answerText), isCorrect(isCorrect) {}

int Answer::getId() const {
    return id;
}

int Answer::getQuestionId() const {
    return questionId;
}

std::string Answer::getAnswerText() const {
    return answerText;
}

bool Answer::isCorrectAnswer() const {
    return isCorrect;
}

Answer Answer::create(int questionId, const std::string& answerText, bool isCorrect) {
    DbConnection db;
    pqxx::connection& connection = db.getConnection();
     pqxx::work txn(connection);
    
    pqxx::result res = txn.exec(
        "INSERT INTO answers (question_id, answer_text, is_correct) VALUES (" + std::to_string(questionId) + ", '" + answerText + "', " + (isCorrect ? "TRUE" : "FALSE") + ") RETURNING id"
    );
    
     int newId = 0;
    if (!res.empty())
    {
       newId = res[0][0].as<int>();
    }
    txn.commit();

    return Answer(newId, questionId, answerText, isCorrect);
}

std::vector<Answer> Answer::getAll() {
    DbConnection db;
    pqxx::connection& connection = db.getConnection();
     pqxx::work txn(connection);

    pqxx::result res = txn.exec("SELECT id, question_id, answer_text, is_correct FROM answers");

    std::vector<Answer> answers;
    for (const auto& row : res) {
        answers.emplace_back(row[0].as<int>(), row[1].as<int>(), row[2].as<std::string>(), row[3].as<bool>());
    }
     txn.commit();
    return answers;
}

Answer Answer::get(int id) {
    DbConnection db;
    pqxx::connection& connection = db.getConnection();
     pqxx::work txn(connection);

    pqxx::result res = txn.exec(
        "SELECT id, question_id, answer_text, is_correct FROM answers WHERE id = " + std::to_string(id)
    );

    if (res.empty()) {
        throw std::runtime_error("Answer with id " + std::to_string(id) + " not found");
    }
    txn.commit();
    return Answer(res[0][0].as<int>(), res[0][1].as<int>(), res[0][2].as<std::string>(), res[0][3].as<bool>());
}

Answer Answer::update(int id, int questionId, const std::string& answerText, bool isCorrect) {
    DbConnection db;
    pqxx::connection& connection = db.getConnection();
    pqxx::work txn(connection);

   txn.exec(
        "UPDATE answers SET question_id = " + std::to_string(questionId) + ", answer_text = '" + answerText + "', is_correct = " + (isCorrect ? "TRUE" : "FALSE") + " WHERE id = " + std::to_string(id)
    );
    txn.commit();
    return Answer(id, questionId, answerText, isCorrect);
}

void Answer::remove(int id) {
    DbConnection db;
    pqxx::connection& connection = db.getConnection();
    pqxx::work txn(connection);
    txn.exec("DELETE FROM answers WHERE id = " + std::to_string(id));
    txn.commit();
}