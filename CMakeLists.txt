cmake_minimum_required(VERSION 3.10)
project(survey_app)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)

add_executable(${PROJECT_NAME} main.cpp
               src/models/user.cpp
               src/models/test.cpp
               src/models/question.cpp
               src/models/answer.cpp
               src/models/result.cpp
               src/database/db_connection.cpp
               )

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBPQXX REQUIRED libpqxx)
include_directories(${LIBPQXX_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} /opt/homebrew/Cellar/libpqxx/7.10.0/lib/libpqxx.dylib)