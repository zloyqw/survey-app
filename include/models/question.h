#ifndef QUESTION_H
#define QUESTION_H

#include <string>
#include <vector>
#include "database/db_connection.h"

class Question {
private:
    int id;
    int testId;
    std::string questionText;
public:
    Question() = default;
    Question(int id, int testId, const std::string& questionText);
    int getId() const;
    int getTestId() const;
    std::string getQuestionText() const;
    static Question create(int testId, const std::string& questionText);
    static std::vector<Question> getAll();
    static Question get(int id);
    static Question update(int id, int testId, const std::string& questionText);
    static void remove(int id);
};

#endif