#include "DBAdapter.h"
#include "sqlite/sqlite3.h"
#include <iostream>

DBAdapter::DBAdapter(const std::string& dbPath)
{
    open(dbPath);
}

DBAdapter::~DBAdapter()
{
    close();
}

bool DBAdapter::open(const std::string& dbPath)
{
    m_lastResultCode = sqlite3_open(dbPath.c_str(), &m_db);

    if(m_lastResultCode != SQLITE_OK)
    {
       std::cout << "Can't open database: " << sqlite3_errmsg(m_db) << std::endl;
       return false;
    }
    else
    {
       std::cout << "Opened database successfully" << std::endl;
       return true;
    }
}

void DBAdapter::close()
{
    sqlite3_close(m_db);
}

int DBAdapter::execute(const std::string& query)
{


    m_lastResultCode = sqlite3_prepare_v2(m_db, query.c_str(), query.size(), &m_currentStatement, NULL);

    if(m_lastResultCode != SQLITE_OK)
    {
       std::cout << "SQL prepare error" << std::endl;
       return m_lastResultCode;
    }
    else
    {
       std::cout << "SQL prepare OK" << std::endl;
    }

    while(sqlite3_step(m_currentStatement) != SQLITE_DONE)
    {
        int         id   = sqlite3_column_int(m_currentStatement, 0);
        const unsigned char* name = sqlite3_column_text(m_currentStatement, 1);
        std::cout << "ID: " << id << " (type: " << sqlite3_column_type(m_currentStatement, 0) << ") " <<
                     "Name: " << name << " (type: " << sqlite3_column_type(m_currentStatement, 1) << ") " << std::endl;
    }
    return m_lastResultCode;
}

int DBAdapter::lastResultCode()
{
    return m_lastResultCode;
}

const int Column::INTEGER = SQLITE_INTEGER;
const int Column::FLOAT = SQLITE_FLOAT;
const int Column::TEXT = SQLITE_TEXT;
const int Column::BLOB = SQLITE_BLOB;
const int Column::Null = SQLITE_NULL;

Column::Column(const std::any& value) : m_value(value)
{
}

Column::Column()
{
    m_type = Null;
}

std::any& Column::getValue()
{
    return m_value;
}

void Column::setValue(const std::any& value)
{
    m_value = value;
}

int Column::getType() const
{
    return m_type;
}

void Column::setType(int type)
{
    m_type = type;
}

Column Record::getColumn(int index) const
{
    if (!checkIndex(index))
        return {};

    return m_columns[index];
}

void Record::setColumn(int index, const Column& value)
{
    if (!checkIndex(index))
        return;

    m_columns[index] = value;
}

bool Record::checkIndex(int index) const
{
    if ((index < 0) || (index >= m_columns.size()))
        return false;

    return true;
}
