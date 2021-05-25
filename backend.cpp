#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sqlite3.h>

#include "parameters.h"
#include "utility.h"

using namespace std;

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

int main() {
    sqlite3* DB;
    int exit = 0;
    exit = sqlite3_open("example.db", &DB);
    if (exit) {
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
        return (-1);
    }
    else
        std::cout << "Opened Database Successfully!" << std::endl;

    string data("CALLBACK FUNCTION");
    string sql1("SELECT NAME FROM CITIES;");
    string sql2("SELECT POPULATION FROM CITIES;");
    string sql3 = sql1 + sql2;
    int rc = sqlite3_exec(DB, sql3.c_str(), callback, (void*)data.c_str(), NULL);
  
    if (rc != SQLITE_OK)
        cerr << "Error SELECT" << endl;
    else {
        cout << "Operation OK!" << endl;
    }
  
    sqlite3_close(DB);
    return 0;
}