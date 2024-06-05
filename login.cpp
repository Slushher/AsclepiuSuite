#include "login.h"
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

Login::Login(){

}

bool Login::validate(std::string login, std::string password){
    bool valid_login = false, valid_password = false;
    try {
        driver = get_driver_instance();
        conn = driver->connect("tcp://127.0.0.1", "login", "password");
        conn->setSchema("debugging");
        pstmt = conn->prepareStatement("SELECT id_apteki FROM `API_VALIDATION` WHERE id_apteki LIKE ?");
        pstmt->setString(1, "%" + login + "%");
        rs = pstmt->executeQuery();
        while (rs->next()) {
            if(debug_mode){
                std::cout<<rs->getString(1).c_str()<<"\n";
            }
            if(login == rs->getString(1).c_str()){
                valid_login = true;
                if(debug_mode){
                    std::cout<<"Login validity : "<<valid_login<<"\n";
                }
            }
        }
        pstmt = conn->prepareStatement("SELECT password FROM `API_VALIDATION` WHERE password LIKE ?");
        pstmt->setString(1, "%" + password + "%");
        rs = pstmt->executeQuery();
        while (rs->next()) {
            if(debug_mode){
                std::cout<<rs->getString(1).c_str()<<"\n";
            }
            if(password == rs->getString(1).c_str()){
                valid_password = true;
                if(debug_mode){
                    std::cout<<"Password validity : "<<valid_password<<"\n";
                }
            }
        }
        rs->close();
        pstmt->close();
        conn->close();
        if(valid_login && valid_password){
            return true;
        }
        return false;
    } catch (sql::SQLException &e) {
        std::cerr << "SQL Exception: " << e.what() << std::endl;
        return false;
    }
}
