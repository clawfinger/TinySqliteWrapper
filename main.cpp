#include <iostream>
#include "DBAdapter.h"

int main()
{
    DBAdapter db;
    if (!db.open("test.db"))
        return -1;
    std::vector<Record> rec = db.execute("SELECT * FROM worktime;");
    return 0;
}
