#pragma once
#include <string>
#include <vector>
#include <any>

class Column
{
public:
    enum class Type
    {
        INTEGER,
        FLOAT,
        TEXT,
        BLOB,
        Null
    };

    Column(const std::any& value);
    Column();
    std::any& getValue();
    void setValue(const std::any& value);
    Type getType() const;
    void setType(Type type);
    std::string getName() const;
    void setName(const std::string& name);

private:
    Type m_type;
    std::string m_name;
    std::any m_value;
};

class Record
{
public:
    Column getColumn(int index) const;
    int getColumnCount() const;
    void appendColumn(const Column& column);
    void appendColumn(const std::any& value);
    void setColumn(int index, const Column& value);
    void setColumn(int index, const std::any& value);

private:
    bool checkIndex(int index) const;

private:
    std::vector<Column> m_columns;
};
