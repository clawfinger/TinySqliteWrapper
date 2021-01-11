#pragma once
#include <string>
#include <vector>
#include <any>

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
    int execute(const std::string& query);
    int lastResultCode();

private:
    int (*execCallback)(void*,int,char**,char**);
    sqlite3* m_db;
    sqlite3_stmt* m_currentStatement;
    int m_lastResultCode;
};


class Column
{
public:
    const int INTEGER;
    const int FLOAT;
    const int TEXT;
    const int BLOB;
    const int Null;

    Column(const std::any& value);
    Column();
    std::any& getValue();
    void setValue(const std::any& value);
    int getType() const;
    void setType(int type);

private:
    int m_type;
    std::any m_value;
};

class Record
{
public:
    const std::any& getColumn(int index);
    void setColumn(int index, const std::any& value);

private:
    bool checkIndex(int index);

private:
    std::vector<Column> m_columns;
};
