#include "models/question.h"
#include <vector>
#include <stdexcept>

std::vector<Question> Question::questions;
int Question::nextId = 1;

Question::Question() : id(0), text(""), type("") {}

Question::Question(int id, const std::string& text, const std::string& type)
    : id(id), text(text), type(type) {}

int Question::getId() const {
    return id;
}

void Question::setId(int id) {
    this->id = id;
}

std::string Question::getText() const {
    return text;
}

void Question::setText(const std::string& text) {
    this->text = text;
}

std::string Question::getType() const {
    return type;
}

void Question::setType(const std::string& type) {
    this->type = type;
}
Question Question::create(const std::string& text, const std::string& type)
{
    Question question(nextId++, text, type);
    questions.push_back(question);
    return question;
}

std::vector<Question> Question::getAll()
{
    return questions;
}

Question Question::get(int id)
{
    for (const auto& question : questions)
    {
        if (question.getId() == id)
        {
            return question;
        }
    }
    throw std::runtime_error("Question not found");
}

Question Question::update(int id, const std::string& text, const std::string& type)
{
     for(auto& question : questions)
    {
        if (question.getId() == id)
        {
             question.setText(text);
            question.setType(type);
            return question;
        }
    }
    throw std::runtime_error("Question not found");
}

void Question::remove(int id)
{
    for (size_t i = 0; i < questions.size(); ++i)
    {
        if (questions[i].getId() == id)
        {
            questions.erase(questions.begin() + i);
            return;
        }
    }
    throw std::runtime_error("Question not found");
}
