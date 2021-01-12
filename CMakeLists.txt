cmake_minimum_required(VERSION 3.5)
set(PROJECT sqliteWrapper)
project(${PROJECT} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    DBAdapter.cpp
    Record.cpp
    )

set(HEADERS
    sqlite/sqlite3.h
    DBAdapter.h
    Record.h
    )

add_executable(${PROJECT} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT} ${PROJECT_SOURCE_DIR}/sqlite/sqlite3.lib)
