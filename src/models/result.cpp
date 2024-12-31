#include "models/result.h"
#include <vector>
#include <stdexcept>

std::vector<Result> Result::results;
int Result::nextId = 1;

Result::Result() : id(0), userId(0), testId(0), score(0) {}

Result::Result(int id, int userId, int testId, int score)
    : id(id), userId(userId), testId(testId), score(score) {}

int Result::getId() const {
    return id;
}

void Result::setId(int id) {
    this->id = id;
}

int Result::getUserId() const {
    return userId;
}

void Result::setUserId(int userId) {
    this->userId = userId;
}

int Result::getTestId() const {
    return testId;
}

void Result::setTestId(int testId) {
    this->testId = testId;
}

int Result::getScore() const {
    return score;
}

void Result::setScore(int score) {
    this->score = score;
}
Result Result::create(int userId, int testId, int score)
{
    Result result(nextId++, userId, testId, score);
    results.push_back(result);
    return result;
}

std::vector<Result> Result::getAll()
{
    return results;
}

Result Result::get(int id)
{
    for (const auto& result : results)
    {
        if (result.getId() == id)
        {
            return result;
        }
    }
    throw std::runtime_error("Result not found");
}

Result Result::update(int id, int userId, int testId, int score)
{
     for(auto& result : results)
     {
        if (result.getId() == id)
        {
           result.setUserId(userId);
            result.setTestId(testId);
           result.setScore(score);
           return result;
        }
    }
    throw std::runtime_error("Result not found");
}

void Result::remove(int id)
{
    for (size_t i = 0; i < results.size(); ++i)
    {
        if (results[i].getId() == id)
        {
            results.erase(results.begin() + i);
            return;
        }
    }
    throw std::runtime_error("Result not found");
}
