#ifndef ANSWER_H
#define ANSWER_H

#include <string>
#include <vector>
#include "database/db_connection.h"

class Answer {
private:
    int id;
    int questionId;
    std::string answerText;
    bool isCorrect;
public:
    Answer() = default;
    Answer(int id, int questionId, const std::string& answerText, bool isCorrect);
    int getId() const;
    int getQuestionId() const;
    std::string getAnswerText() const;
    bool isCorrectAnswer() const;
    static Answer create(int questionId, const std::string& answerText, bool isCorrect);
    static std::vector<Answer> getAll();
    static Answer get(int id);
    static Answer update(int id, int questionId, const std::string& answerText, bool isCorrect);
    static void remove(int id);
};

#endif
   
               
