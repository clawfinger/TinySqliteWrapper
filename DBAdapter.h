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
    sqlite3* m_db;
    sqlite3_stmt* m_currentStatement;
    int m_lastResultCode;
};


class Column
{
public:
    static const int INTEGER;
    static const int FLOAT;
    static const int TEXT;
    static const int BLOB;
    static const int Null;

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
    Column getColumn(int index) const;
    void setColumn(int index, const Column& value);

private:
    bool checkIndex(int index) const;

private:
    std::vector<Column> m_columns;
};
