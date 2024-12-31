#ifndef RESULT_H
#define RESULT_H

#include <string>
#include <vector>
#include "database/db_connection.h"

class Result {
private:
    int id;
    int userId;
    int testId;
    int score;
public:
    Result() = default;
    Result(int id, int userId, int testId, int score);
    int getId() const;
    int getUserId() const;
    int getTestId() const;
    int getScore() const;
    static Result create(int userId, int testId, int score);
    static std::vector<Result> getAll();
    static Result get(int id);
    static Result update(int id, int userId, int testId, int score);
    static void remove(int id);
};

#endif