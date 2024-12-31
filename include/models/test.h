#ifndef TEST_H
#define TEST_H

#include <string>
#include <vector>
#include "database/db_connection.h"

class Test {
private:
    int id;
    std::string name;
    std::string description;
public:
    Test() = default;
    Test(int id, const std::string& name, const std::string& description);
    int getId() const;
    std::string getName() const;
    std::string getDescription() const;
    static Test create(const std::string& name, const std::string& description);
    static std::vector<Test> getAll();
    static Test get(int id);
    static Test update(int id, const std::string& name, const std::string& description);
    static void remove(int id);
};

#endif