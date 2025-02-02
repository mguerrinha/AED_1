cmake_minimum_required(VERSION 3.26)
project(project_1_schedule)

set(CMAKE_CXX_STANDARD 17)

add_executable(project_1_schedule src/main.cpp
        src/UCSpecificClass.cpp
        src/UCSpecificClass.h
        src/Lesson.cpp
        src/Lesson.h
        src/Student.cpp
        src/Student.h
        src/Class.cpp
        src/Class.h
        src/ScheduleManager.cpp
        src/ScheduleManager.h
        src/Interface.cpp
        src/Interface.h
        src/Requests.cpp
        src/Requests.h
)
