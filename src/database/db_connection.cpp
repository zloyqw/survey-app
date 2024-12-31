#include "database/db_connection.h"
#include <iostream>
#include <stdexcept>

DbConnection::DbConnection() {
    try {
        connection = std::make_unique<pqxx::connection>("dbname=survey_app user=postgres password=Zaxscdvfbg14 host=localhost port=5432");
        if (!connection->is_open()) {
            throw std::runtime_error("Connection to database failed.");
        }
        std::cout << "Connected to database successfully!" << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << "Error connecting to database: " << e.what() << std::endl;
         throw;
    }
}

DbConnection::~DbConnection() {
    // No need to disconnect explicitly, the connection will be closed automatically when the object goes out of scope.
}


pqxx::connection& DbConnection::getConnection() {
    return *connection;
}