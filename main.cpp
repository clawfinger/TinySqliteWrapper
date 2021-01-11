#include <iostream>
#include "DBAdapter.h"

int main()
{
    DBAdapter db;
    if (!db.open("test.db"))
        return -1;
    db.execute("SELECT * FROM worktime");
}
