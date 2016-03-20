#ifndef MYSQLCONNECT_H
#define	MYSQLCONNECT_H

/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>
#include <vector>

#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

enum AuthResult {
    AuthOK,    // all OK
    AuthFalse, // error in authentificaton
    AuthCancel // auth cancel - exit program
};

struct connectDetails {
    connectDetails();
    connectDetails(string server, string user, string password, string database,
        string table = "");
    
    string server   = "";
    string user     = "";
    string password = "";
    string database = "";
    string table    = "";
};

class MySQLData {
public:
    MySQLData(uint rows = 0, uint columns = 0);
    ~MySQLData();
    
    bool Restruct();

    void SetRows(uint);
    uint GetRows();
    void SetColumns(uint);
    uint GetColumns();

    void SetData(uint row, uint column, string value);
    void SetHead(uint column, string value);

    string ** GetData() const;
    string GetData(uint row, uint column) const;
    string GetData(uint row, string column) const;
    vector<string> GetHead() const;
    string GetHead(uint) const;
    
private:
    void ClearData();
    
    uint rows;
    uint columns;
    uint drows;
    string ** data;
    vector<string> head;
};

enum SQLStatus {
    SQL_OK,
    SQL_FALSE,
    SQL_ERROR
};

class SQLResult {
public:
    SQLResult(SQLStatus status, string message, MySQLData data) : status(status),
            message(message), data(data) { }
    
    MySQLData GetData() const { return data; }
    SQLStatus GetStatus() const { return status; };
    string GetMessage() const { return message; }
    
private:
    SQLStatus status;
    string message;
    MySQLData data;
};

class MySQL {
public:
    MySQL(connectDetails);
    MySQL(string server, string user, string password, string database, string table = "");
    ~MySQL();
    
    void PrintQuery(string);
    SQLResult Execute(string);
    SQLResult GetData(string);
    SQLResult ConnectTest();
    string GetTable() const;
    void SetTable(string);
    
private:
    connectDetails mysqlD;
};

#endif	/* MYSQLCONNECT_H */
