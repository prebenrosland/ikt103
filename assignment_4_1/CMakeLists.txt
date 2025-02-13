cmake_minimum_required(VERSION 3.24)
project(assignment_4_1)

set(CMAKE_CXX_STANDARD 17)



add_library(sqlite3 sqlite3/sqlite3.c)



target_include_directories(sqlite3 PUBLIC sqlite3)

add_library(sqlitecpp
        sqlitecpp/src/Backup.cpp
        sqlitecpp/src/Column.cpp
        sqlitecpp/src/Database.cpp
        sqlitecpp/src/Exception.cpp
        sqlitecpp/src/Statement.cpp
        sqlitecpp/src/Transaction.cpp)

if (UNIX)
    target_link_libraries(sqlite3 pthread dl)
endif (UNIX)

target_include_directories(sqlitecpp PUBLIC sqlitecpp/include)
target_link_libraries(sqlitecpp sqlite3)

add_executable(assignment_4_1 main.cpp)
target_link_libraries(assignment_4_1 sqlite3 sqlitecpp)
