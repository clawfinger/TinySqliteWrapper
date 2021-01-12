#pragma once
#include "Record.h"

class sqlite3;
class sqlite3_stmt;

class DBAdapter
{
public:
    DBAdapter() = default;
    ~DBAdapter();
    DBAdapter(const std::string& dbPath);
    bool open(const std::string& dbPath);
    void close();
    std::vector<Record> execute(const std::string& query);
    int lastResultCode();

private:
    sqlite3* m_db;
    sqlite3_stmt* m_currentStatement;
    int m_lastResultCode;
};
