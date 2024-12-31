#ifndef DB_CONNECTION_H
#define DB_CONNECTION_H

#include <pqxx/pqxx>
#include <memory>

class DbConnection {
private:
   std::unique_ptr<pqxx::connection> connection;
public:
    DbConnection();
    ~DbConnection();
    pqxx::connection& getConnection();
};

#endif