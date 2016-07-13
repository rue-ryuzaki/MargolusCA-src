#include "mysqlconnect.h"
#include <mysql_driver.h>

connectDetails::connectDetails() { }

connectDetails::connectDetails(string server, string user, string password,
        string database, string table) : server(server), user(user),
        password(password), database(database), table(table) { }

MySQLData::MySQLData(uint rows, uint columns) : rows(rows), columns(columns), 
        drows(0), data(nullptr) { }

MySQLData::~MySQLData() {
    ClearData();
}

bool MySQLData::Restruct() {
    ClearData();
    
    if (rows == 0 || columns == 0) {
        return false;
    }
    drows = rows;
    data = new string*[rows];

    for (uint i = 0; i < rows; ++i) {
        data[i] = new string[columns];
        for (uint j = 0; j < columns; ++j) {
            data[i][j] = "";
        }
    }
    for (uint i = 0; i < columns; ++i) {
        head.push_back("");
    }
    return true;
}

void MySQLData::SetRows(uint row) {
    this->rows = row;
}

uint MySQLData::GetRows() const {
    return rows;
}

void MySQLData::SetColumns(uint column) {
    this->columns = column;
}

uint MySQLData::GetColumns() const {
    return columns;
}

void MySQLData::SetData(uint row, uint column, string value) {
    if (row >= rows || column >= columns) {
        return;
    }
    data[row][column] = value;
}

void MySQLData::SetHead(uint column, string value) {
    if (column >= columns) {
        return;
    }
    head[column] = value;
}

void MySQLData::ClearData() {
    if (data != nullptr) {
        for (uint i = 0; i < drows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }
    data = nullptr;
    head.clear();
}

string ** MySQLData::GetData() const {
    return data;
}

string MySQLData::GetData(uint row, uint column) const {
    if (row >= rows || column >= columns) {
        return "";
    }
    return data[row][column];
}

string MySQLData::GetData(uint row, string columnname) const {
    int column = -1;
    for (uint i = 0; i < head.size(); ++i) {
        if (head[i] == columnname) {
            column = i;
            break;
        }
    }
    if (column == -1) {
        return "";
    }
    if (row >= rows || column >= columns) {
        return "";
    }
    return data[row][column];
}

vector<string> MySQLData::GetHead() const {
    return head;
}

string MySQLData::GetHead(uint column) const {
    if (column >= columns) {
        return "";
    }
    return head[column];
}

SQLResult::SQLResult(SQLStatus status, string message, MySQLData data)
    : status(status), message(message), data(data) { }

MySQLData SQLResult::GetData() const {
    return data;
}

SQLStatus SQLResult::GetStatus() const {
    return status;
};

string SQLResult::GetMessage() const {
    return message;
}

MySQL::MySQL(connectDetails details) {
    mysqlD.server   = details.server;     // where the mysql database is
    mysqlD.user     = details.user;       // the root user of mysql
    mysqlD.password = details.password;   // the password of the root user in mysql
    mysqlD.database = details.database;   // the databse to pick
    mysqlD.table    = details.table;
}

MySQL::MySQL(string server, string user, string password, string database, string table) {
    mysqlD.server   = server;   // where the mysql database is
    mysqlD.user     = user;     // the root user of mysql
    mysqlD.password = password; // the password of the root user in mysql
    mysqlD.database = database; // the databse to pick
    mysqlD.table    = table;
}

MySQL::~MySQL() { }

void MySQL::PrintQuery(string query) {
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    try {
        driver = get_driver_instance();
        //con = driver->connect("tcp://127.0.0.1:3306", mysqlD.user, mysqlD.password);
        con = driver->connect(mysqlD.server, mysqlD.user, mysqlD.password);
        /* Connect to the MySQL test database */
        con->setSchema(mysqlD.database);

        stmt = con->createStatement();
        res = stmt->executeQuery(query);

        uint columnCount = res->getMetaData()->getColumnCount();
        if (res->rowsCount() > 0) {
            if (columnCount > 1) {
                cout << res->getMetaData()->getColumnName(1);
            }
            for (uint i = 1; i < columnCount; ++i) {
                cout << "\t" << res->getMetaData()->getColumnName(i + 1);
            }
            cout << endl;
        }
        while (res->next()) {
            if (columnCount > 1) {
                cout << res->getString(1);
            }
            for (uint i = 1; i < columnCount; ++i) {
                cout << "\t" << res->getString(i + 1);
            }
            cout << endl;
        }
        driver->threadEnd();
    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    } catch (...) {
        cout << "Strange MySQL Error!\n";
    }
    delete res;
    delete stmt;
    delete con;
}

SQLResult MySQL::Execute(string query) {
    SQLStatus status = SQL_ERROR;
    string message = "";
    MySQLData data;
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    try {
        driver = get_driver_instance();
        //con = driver->connect("tcp://127.0.0.1:3306", mysqlD.user, mysqlD.password);
        con = driver->connect(mysqlD.server, mysqlD.user, mysqlD.password);
        /* Connect to the MySQL test database */
        con->setSchema(mysqlD.database);

        stmt = con->createStatement();
        stmt->execute(query);
        driver->threadEnd();
        status = SQL_OK;
    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        message = "MySQL error: " + (string)e.what();
        status = SQL_ERROR;
    } catch (...) {
        cout << "Strange MySQL Error!\n";
        message = "Strange MySQL Error!";
        status = SQL_ERROR;
    }
    delete stmt;
    delete con;
    return SQLResult(status, message, data);
}

SQLResult MySQL::GetData(string query) {
    SQLStatus status = SQL_ERROR;
    string message = "";
    MySQLData data;
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    try {
        driver = get_driver_instance();
        //con = driver->connect("tcp://127.0.0.1:3306", mysqlD.user, mysqlD.password);
        con = driver->connect(mysqlD.server, mysqlD.user, mysqlD.password);
        /* Connect to the MySQL test database */
        con->setSchema(mysqlD.database);

        stmt = con->createStatement();
        res = stmt->executeQuery(query);
        if (res->rowsCount() < 1) {
            driver->threadEnd();
            cout << " empty\n";
            message = "Empty result";
            status = SQL_OK;
            delete res;
            delete stmt;
            delete con;
            return SQLResult(status, message, data);
        }
        data.SetRows(res->rowsCount());
        data.SetColumns(res->getMetaData()->getColumnCount());

        if (!data.Restruct()) {
            driver->threadEnd();
            cout << " Some error\n";
            message = "Some error";
            status = SQL_ERROR;
            delete res;
            delete stmt;
            delete con;
            return SQLResult(status, message, data);
        }
        for (uint i = 0; i < data.GetColumns(); ++i) {
            data.SetHead(i, res->getMetaData()->getColumnName(i + 1));
        }
        while (res->next()) {
            for (uint i = 0; i < data.GetColumns(); ++i) {
                data.SetData((res->getRow() - 1), i, res->getString(i + 1));
            }
        }
        driver->threadEnd();
        status = SQL_OK;
    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        message = "MySQL error: " + (string)e.what();
        status = SQL_ERROR;
    } catch (...) {
        cout << "Strange MySQL Error!\n";
        message = "Strange MySQL Error!";
        status = SQL_ERROR;
    }
    delete res;
    delete stmt;
    delete con;
    return SQLResult(status, message, data);
}

SQLResult MySQL::ConnectTest() {
    SQLStatus status = SQL_ERROR;
    string message = "";
    MySQLData data;
    try {
        sql::Driver *driver;
        sql::Connection *con;
        driver = get_driver_instance();
        con = driver->connect(mysqlD.server, mysqlD.user, mysqlD.password);
        driver->threadEnd();
        delete con;
        status = SQL_OK;
    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << ")" << endl;
        message = "MySQL error: " + (string)e.what();
        status = SQL_ERROR;
    } catch (...) {
        cout << "Strange MySQL Error!\n";
        message = "Strange MySQL Error!";
        status = SQL_ERROR;
    }
    return SQLResult(status, message, data);
}

string MySQL::GetTable() const {
    return mysqlD.table;
}

void MySQL::SetTable(string table) {
    mysqlD.table = table;
}
