#include <iostream>
#include "DBAdapter.h"

int main()
{
    DBAdapter db;
    if (!db.open("test.db"))
        return -1;
    std::vector<Record> rec = db.execute("SELECT * FROM worktime;");
//    std::vector<Record> rec = db.execute("insert into worktime (Username, CU, Timestamp) VALUES ('Dima', 18, 12312312);");
    return 0;
}
