#include "DBAdapter.h"
#include "sqlite/sqlite3.h"
#include <experimental/filesystem>
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
//    if (!std::experimental::filesystem::exists(dbPath))
//    {
//        std::cout << "Database file not exist" << std::endl;
//        return false;
//    }

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

std::vector<Record> DBAdapter::execute(const std::string& query)
{
    m_lastResultCode = sqlite3_prepare_v2(m_db, query.c_str(), query.size(), &m_currentStatement, NULL);

    if(m_lastResultCode != SQLITE_OK)
    {
       std::cout << "SQL prepare error" << std::endl;
       sqlite3_reset(m_currentStatement);
       return {};
    }
    else
    {
       std::cout << "SQL prepare OK" << std::endl;
    }

    std::vector<Record> result;
    int columnCount = sqlite3_column_count(m_currentStatement);
    while(true)
    {
        int returnCode = sqlite3_step(m_currentStatement);
        if (returnCode == SQLITE_ROW)
        {
            Record record;
            for (int i = 0; i < columnCount; ++i)
            {
                int type = sqlite3_column_type(m_currentStatement, i);
                Column current;
                switch (type)
                {
                    case SQLITE_INTEGER:
                        current.setValue(sqlite3_column_int(m_currentStatement, i));
                        current.setType(Column::Type::INTEGER);
                        break;
                    case SQLITE_TEXT:
                        current.setValue(sqlite3_column_text(m_currentStatement, i));
                        current.setType(Column::Type::TEXT);
                        break;
                    case SQLITE_FLOAT:
                        current.setValue(sqlite3_column_double(m_currentStatement, i));
                        current.setType(Column::Type::FLOAT);
                        break;
                    case SQLITE_BLOB:
                        current.setValue(sqlite3_column_blob(m_currentStatement, i));
                        current.setType(Column::Type::BLOB);
                        break;
                }
                current.setName(sqlite3_column_name(m_currentStatement, i));
                record.appendColumn(current);
            }
            result.push_back(record);
        }        
        else if (returnCode == SQLITE_BUSY)
        {
            std::cout << "SQL base is busy. Query was not executed!" << std::endl;
            break;
        }
        else if (returnCode == SQLITE_DONE)
        {
            break;
        }
    }
    sqlite3_reset(m_currentStatement);
    return result;
}

int DBAdapter::lastResultCode()
{
    return m_lastResultCode;
}
