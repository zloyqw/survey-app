        cmake_minimum_required(VERSION 3.10)
        project(survey_app)

        set(CMAKE_CXX_STANDARD 17)
        include_directories(include)

        add_executable(${PROJECT_NAME} main.cpp src/models/user.cpp src/models/test.cpp src/models/question.cpp src/models/answer.cpp src/models/result.cpp)
      
