#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sqlite3.h>

#include "parameters.h"
#include "utility.h"

using namespace std;

sqlite3* DB;

static int callback(void* data, int argc, char** argv, char** azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char*)data);
  
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
  
    printf("\n");
    return 0;
}

int setup_db_connection() {
    int exit = 0;
    exit = sqlite3_open(DB_NAME.c_str(), &DB);
    if (exit) {
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
        return -1;
    }
    else
        std::cout << "Opened Database Successfully!" << std::endl;
    return 0;
}

int query_db(string sql_query) {
    string data("CALLBACK FUNCTION");
    int rc = sqlite3_exec(DB, sql_query.c_str(), callback, (void*)data.c_str(), NULL);
  
    if (rc != SQLITE_OK)
        cerr << "Error SELECT" << endl;
    else {
        cout << "Operation OK!" << endl;
    }
  
    return 0;
}

void close_db_connection() {
    sqlite3_close(DB);
}