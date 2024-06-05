#include "db_query.h"
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

DB_Query::medstruct DB_Query::meds_return()
{
    meds_array.clear();
    try {
        driver = get_driver_instance();
        conn = driver->connect("tcp://127.0.0.1", "login", "password");
        conn->setSchema("debugging");
        pstmt = conn->prepareStatement("SELECT * FROM `leki`");
        rs = pstmt->executeQuery();
        while (rs->next()) {
            if(debug_mode){
                printf("%s, %s, %s, %s, %s, %s, %s, %s\n", rs->getString(1).c_str(), rs->getString(2).c_str(), rs->getString(3).c_str(), rs->getString(4).c_str(),rs->getString(5).c_str(),rs->getString(6).c_str(),rs->getString(7).c_str(),rs->getString(8).c_str());
            }
            meds_array.id.push_back(std::stoi(rs->getString(1).c_str()));
            meds_array.med_name.push_back(rs->getString(2).c_str());
            meds_array.pill_quantity.push_back(std::stoi(rs->getString(3).c_str()));
            meds_array.dose.push_back(std::stod(rs->getString(4).c_str()));
            meds_array.boxes.push_back(std::stoi(rs->getString(5).c_str()));
            meds_array.expiration_date.push_back(rs->getString(6).c_str());
            meds_array.price.push_back(std::stod(rs->getString(7).c_str()));
            meds_array.active_ingredient.push_back(rs->getString(8).c_str());
        }
        rs->close();
        pstmt->close();
        conn->close();
    } catch (sql::SQLException &e) {
        fprintf(stderr, "Error: %s\n", e.what());
        exit(1);
    }
    return meds_array;
}

DB_Query::content_struct DB_Query::prescription_query(std::string accessKey, std::string pesel)
{
    prescriptionData.clear();
    contentData.clear();
    if (pesel.empty() && accessKey.empty()) {
        qDebug() << "Pesel or kod dostepu pusty!\n";
        return contentData;
    } else
    {
        try {
            driver = get_driver_instance();
            conn = driver->connect("tcp://127.0.0.1", "login", "password");
            conn->setSchema("debugging");
            pstmt = conn->prepareStatement("SELECT * FROM `e-recepty`.`recepty_zbiorcze` WHERE kod_dostepu LIKE ? AND pesel LIKE ?");
            pstmt->setString(1, "%" + accessKey + "%");
            pstmt->setString(2, "%" + pesel + "%");
            rs = pstmt->executeQuery();
            while (rs->next()) {
                prescriptionData.id.push_back(std::stoi(rs->getString(1)));
                if(debug_mode){
                    qDebug() << std::stoi(rs->getString(1)) << "\n";
                }
                prescriptionData.pesel.push_back(rs->getString(2).c_str());
                prescriptionData.patient.push_back(rs->getString(3).c_str());
                prescriptionData.date.push_back(rs->getString(4).c_str());
                prescriptionData.doctor.push_back(rs->getString(5).c_str());
            }
            for(int i : prescriptionData.id)
            {
                pstmt = conn->prepareStatement("SELECT * FROM `e-recepty`.`recepty_jed` WHERE id_recepty_zbiorczej LIKE ?");
                pstmt->setString(1, "%" + std::to_string(i) + "%");
                rs = pstmt->executeQuery();
                while (rs->next()) {
                        contentData.id.push_back(std::stoi(rs->getString(1)));
                        contentData.id_link.push_back(std::stoi(rs->getString(2)));
                        contentData.med_name.push_back(rs->getString(3).c_str());
                        contentData.boxes.push_back(std::stoi(rs->getString(4)));
                        contentData.pill_quantity.push_back(std::stoi(rs->getString(5)));
                        contentData.dose.push_back(std::stod(rs->getString(6)));
                        contentData.discount.push_back(std::stod(rs->getString(7)));
                        if(debug_mode){
                            qDebug() << contentData.med_name.back().c_str() << "\n";
                        }
                }
            }
            rs->close();
            pstmt->close();
            conn->close();
        }
        catch (sql::SQLException &e) {
            fprintf(stderr, "Error: %s\n", e.what());
            exit(1);
        }
    }
    return contentData;
}

bool DB_Query::meds_order(DB_Query::medstruct med_order)
{
    int last_ID = 0;
    int new_ID = 0;
    int boxes_buff = 0;
    try {
        driver = get_driver_instance();
        conn = driver->connect("tcp://127.0.0.1", "login", "passowrd");
        conn->setSchema("debugging");
        pstmt = conn->prepareStatement("SELECT MAX(`id_leku`) FROM `leki`;");
        rs = pstmt->executeQuery();
        while (rs->next()) {
            last_ID = std::stoi(rs->getString(1));
        }
        new_ID = last_ID + 1;
        //qDebug() << std::to_string(last_ID) << " " << std::to_string(new_ID) << "\n";
        pstmt = conn->prepareStatement("SELECT `id_leku`, `Ilosc opakowan` FROM `debugging`.`leki` "
                                       "WHERE `nazwa_leku` LIKE ? "
                                       "AND `Ilosc tabletek` LIKE ? "
                                       "AND `dawka` LIKE ? "
                                       "AND `Waznosc` LIKE ? "
                                       "AND `cena` LIKE ? "
                                       "AND `Substancja_czynna` LIKE ? ;");
        pstmt->setString(1, "%" + med_order.med_name[0] + "%");
        pstmt->setInt(2, med_order.pill_quantity[0]);
        pstmt->setDouble(3, med_order.dose[0]);
        pstmt->setString(4, "%" + med_order.expiration_date[0] + "%");
        pstmt->setDouble(5, med_order.price[0]);
        pstmt->setString(6, "%" + med_order.active_ingredient[0] + "%");
        rs = pstmt->executeQuery();
        if(debug_mode){
            qDebug() << "Result set size: " << rs->rowsCount();
        }
        while (rs->next()) {
            last_ID = std::stoi(rs->getString(1));
            boxes_buff = std::stoi(rs->getString(2));
        }
        if(debug_mode){
            qDebug() << "boxes in db : " << boxes_buff << "boxes in input : " << med_order.boxes[0] << "\n";
        }
        if(boxes_buff != 0){
            qDebug() << "Same meds already exist in DB with ID = " << last_ID << " merging them!\n";
            boxes_buff += med_order.boxes[0];
            if(debug_mode){
                qDebug() << "boxes buff now : " << boxes_buff << "\n";
            }
            pstmt = conn->prepareStatement("UPDATE `debugging`.`leki` "
                                           "SET `Ilosc opakowan` = ? "
                                           "WHERE `id_leku` = ?");
            pstmt->setInt(1, boxes_buff);
            pstmt->setInt(2, last_ID);
            rs = pstmt->executeQuery();
            qDebug() << "Meds merged!\n";
            return true;
        }
        else{
                pstmt = conn->prepareStatement("INSERT INTO `leki` (`id_leku`,`nazwa_leku`, `Ilosc tabletek`, `Dawka`, `Ilosc opakowan`, `Waznosc`, `cena`, `Substancja_czynna`) "
                                                "VALUES (?, ?, ?, ?, ?, ?, ?, ?);");
                pstmt->setInt(1, new_ID);
                pstmt->setString(2, med_order.med_name[0]);
                pstmt->setInt(3, med_order.pill_quantity[0]);
                pstmt->setString(4, std::to_string(med_order.dose[0]));
                pstmt->setInt(5, med_order.boxes[0]);
                pstmt->setString(6, med_order.expiration_date[0]);
                pstmt->setDouble(7, med_order.price[0]);
                pstmt->setString(8, med_order.active_ingredient[0]);
                rs = pstmt->executeQuery();
                qDebug() << "Meds ordered!\n";
                return true;
        }
    }
    catch (sql::SQLException &e) {
        fprintf(stderr, "Error: %s\n", e.what());
        exit(1);
    }
}

bool DB_Query::history_add(DB_Query::medstruct med_order, int database_num)
{
    //std::string db_address[2] = {"`historia_zamowien`", "`historia_sprzedazy_leku`"};
    std::string db_address[2] = {"historia_zamowien", "historia_sprzedazy_leku"};
    int new_ID = 0;
    try {
        driver = get_driver_instance();
        conn = driver->connect("tcp://127.0.0.1", "login", "passowrd");
        conn->setSchema("historia_sprzedaz");
        //pstmt = conn->prepareStatement("SELECT MAX(`id`) FROM ?;");
        //pstmt->setString(1, "`" + db_address[database_num] + "`");
        std::string sqlQuery = "SELECT MAX(`id`) FROM " + db_address[database_num] + ";";
        pstmt = conn->prepareStatement(sqlQuery);
        rs = pstmt->executeQuery();
        while (rs->next()) {
            new_ID = std::stoi(rs->getString(1));
        }
        //for (size_t i = 0; i < med_order.med_name.size(); i++) {
            new_ID++;
            sqlQuery = "INSERT INTO " + db_address[database_num] + " (`id`, `nazwa_leku`, `ilosc_tabletek`, `ilosc_opakowan`, `dawka`, `cena`, `data`) "
                       "VALUES (?, ?, ?, ?, ?, ?, ?);";
            pstmt = conn->prepareStatement(sqlQuery);
            pstmt->setInt(1, new_ID);
            pstmt->setString(2, med_order.med_name[0]);
            pstmt->setInt(3, med_order.pill_quantity[0]);
            pstmt->setInt(4, med_order.boxes[0]);
            pstmt->setDouble(5, med_order.dose[0]);
            pstmt->setDouble(6, med_order.price[0]);
            pstmt->setString(7, med_order.expiration_date[0]);
            rs = pstmt->executeQuery();
            qDebug() << "History added!\n";
        //}
        return true;
    }
    catch (sql::SQLException &e) {
        fprintf(stderr, "Error: %s\n", e.what());
        exit(1);
    }
}

DB_Query::historderstruct DB_Query::history_query()
{
    try {
        driver = get_driver_instance();
        conn = driver->connect("tcp://127.0.0.1", "login", "passowrd");
        conn->setSchema("historia_sprzedaz");
        pstmt = conn->prepareStatement("SELECT * FROM `historia_zamowien`");
        rs = pstmt->executeQuery();
        while (rs->next()) {
            if(debug_mode){
                printf("%s, %s, %s, %s, %s\n", rs->getString(1).c_str(), rs->getString(2).c_str(), rs->getString(3).c_str(), rs->getString(4).c_str(),rs->getString(5).c_str());
            }
            history_array.id.push_back(std::stoi(rs->getString(1).c_str()));
            history_array.med_name.push_back(rs->getString(2).c_str());
            history_array.boxes.push_back(std::stoi(rs->getString(3).c_str()));
            history_array.dose.push_back(std::stod(rs->getString(4).c_str()));
            history_array.order_date.push_back(rs->getString(5).c_str());
        }
        rs->close();
        pstmt->close();
        conn->close();
    } catch (sql::SQLException &e) {
        fprintf(stderr, "Error: %s\n", e.what());
        exit(1);
    }
    return history_array;
}

DB_Query::histsalestruct DB_Query::histsale_return()
{
    try {
        driver = get_driver_instance();
        conn = driver->connect("tcp://127.0.0.1", "login", "passowrd");
        conn->setSchema("historia_sprzedaz");
        pstmt = conn->prepareStatement("SELECT * FROM `historia_sprzedazy_leku`");
        rs = pstmt->executeQuery();
        while (rs->next()) {
            if(debug_mode){
                printf("%s, %s, %s, %s, %s, %s\n", rs->getString(1).c_str(), rs->getString(2).c_str(), rs->getString(3).c_str(), rs->getString(4).c_str(),rs->getString(5).c_str(), rs->getString(6).c_str());
            }
            hists_array.id.push_back(std::stoi(rs->getString(1).c_str()));
            hists_array.med_name.push_back(rs->getString(2).c_str());
            hists_array.boxes.push_back(std::stoi(rs->getString(3).c_str()));
            hists_array.dose.push_back(std::stod(rs->getString(4).c_str()));
            hists_array.order_date.push_back(rs->getString(5).c_str());
            hists_array.receipt_id.push_back(std::stod(rs->getString(6).c_str()));
        }
        rs->close();
        pstmt->close();
        conn->close();
    } catch (sql::SQLException &e) {
        fprintf(stderr, "Error: %s\n", e.what());
        exit(1);
    }
    return hists_array;
}
