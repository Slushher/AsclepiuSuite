#ifndef LOGIN_H
#define LOGIN_H
#include <string>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "db_query.h"

class Login{
public:
    Login();
    bool validate(std::string login, std::string password);
private:
    sql::Connection *conn;
    sql::PreparedStatement *pstmt;
    sql::Driver *driver;
    sql::ResultSet *rs;
    bool debug_mode = false;
};

#endif // LOGIN_H
