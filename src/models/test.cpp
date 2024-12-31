#include "models/test.h"
#include <vector>
#include <stdexcept>

std::vector<Test> Test::tests;
int Test::nextId = 1;

Test::Test() : id(0), name(""), description("") {}

Test::Test(int id, const std::string& name, const std::string& description)
    : id(id), name(name), description(description) {}

int Test::getId() const {
    return id;
}

void Test::setId(int id) {
    this->id = id;
}

std::string Test::getName() const {
    return name;
}

void Test::setName(const std::string& name) {
    this->name = name;
}

std::string Test::getDescription() const {
    return description;
}

void Test::setDescription(const std::string& description) {
    this->description = description;
}
Test Test::create(const std::string& name, const std::string& description)
{
    Test test(nextId++, name, description);
    tests.push_back(test);
    return test;
}

std::vector<Test> Test::getAll()
{
    return tests;
}

Test Test::get(int id)
{
    for (const auto& test : tests)
    {
        if (test.getId() == id)
        {
            return test;
        }
    }
    throw std::runtime_error("Test not found");
}

Test Test::update(int id, const std::string& name, const std::string& description)
{
    for (auto& test : tests)
    {
        if (test.getId() == id)
        {
            test.setName(name);
            test.setDescription(description);
            return test;
        }
    }
    throw std::runtime_error("Test not found");
}

void Test::remove(int id)
{
    for (size_t i = 0; i < tests.size(); ++i)
    {
        if (tests[i].getId() == id)
        {
            tests.erase(tests.begin() + i);
            return;
        }
    }
    throw std::runtime_error("Test not found");
}
