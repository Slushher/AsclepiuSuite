#ifndef DB_QUERY_H
#define DB_QUERY_H
#include <vector>
#include <string>
#include <tuple>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <QDate>
#include <QDebug>

class DB_Query{
public:
    sql::Connection *conn;
    struct medstruct{
        std::vector<unsigned int> id;
        std::vector<std::string> med_name;
        std::vector<int> pill_quantity;
        std::vector<double> dose;
        std::vector<int> boxes;
        std::vector<std::string> expiration_date;
        std::vector<double> price;
        std::vector<std::string> active_ingredient;
        void clear() {
            id.clear();
            med_name.clear();
            pill_quantity.clear();
            dose.clear();
            boxes.clear();
            expiration_date.clear();
            price.clear();
            active_ingredient.clear();
        }
        void qDebugPrint() const {
            qDebug() << "id:";
            for (const auto& value : id) {
                qDebug() << value;
            }
            qDebug() << "med_name:";
            for (const auto& value : med_name) {
                qDebug() << QString::fromStdString(value);
            }
            qDebug() << "pill_quantity:";
            for (const auto& value : pill_quantity) {
                qDebug() << QString::fromStdString(std::to_string(value));
            }
            qDebug() << "dose:";
            for (const auto& value : dose) {
                qDebug() << QString::fromStdString(std::to_string(value));
            }
            qDebug() << "boxes:";
            for (const auto& value : boxes) {
                qDebug() << QString::fromStdString(std::to_string(value));
            }
            qDebug() << "expiration_date:";
            for (const auto& value : expiration_date) {
                qDebug() << QString::fromStdString(value);
            }
            qDebug() << "price:";
            for (const auto& value : price) {
                qDebug() << QString::fromStdString(std::to_string(value));
            }
            qDebug() << "active_ingredient:";
            for (const auto& value : active_ingredient) {
                qDebug() << QString::fromStdString(value);
            }
        }
    };
    struct prescription_struct{
        std::vector<int> id;
        std::vector<std::string> pesel;
        std::vector<std::string> patient;
        std::vector<std::string> date;
        std::vector<std::string> doctor;
        void clear() {
            id.clear();
            pesel.clear();
            patient.clear();
            date.clear();
            doctor.clear();
        }
        void qDebugPrint() const {
            qDebug() << "id:";
            for (const auto& value : id) {
                qDebug() << value;
            }
            qDebug() << "pesel:";
            for (const auto& value : pesel) {
                qDebug() << QString::fromStdString(value);
            }
            qDebug() << "patient:";
            for (const auto& value : patient) {
                qDebug() << QString::fromStdString(value);
            }
            qDebug() << "date:";
            for (const auto& value : date) {
                qDebug() << QString::fromStdString(value);
            }
            qDebug() << "doctor:";
            for (const auto& value : doctor) {
                qDebug() << QString::fromStdString(value);
            }
        }
    };
    struct content_struct{
        std::vector<int> id;
        std::vector<int> id_link;
        std::vector<std::string> med_name;
        //std::vector<std::string> active_ingredient;
        std::vector<int> boxes;
        std::vector<int> pill_quantity;
        std::vector<double> dose;
        std::vector<double> discount;
        void clear() {
            id.clear();
            id_link.clear();
            med_name.clear();
            //active_ingredient.clear();
            boxes.clear();
            pill_quantity.clear();
            dose.clear();
            discount.clear();
        }
        void qDebugPrint() const {
            qDebug() << "Content Struct:";
            qDebug() << "id:";
            for (const auto& value : id) {
                qDebug() << value;
            }
            qDebug() << "id_link:";
            for (const auto& value : id_link) {
                qDebug() << value;
            }
            qDebug() << "med_name:";
            for (const auto& value : med_name) {
                qDebug() << QString::fromStdString(value);
            }
            //qDebug() << "active_ingredient:";
            //for (const auto& value : active_ingredient) {
            //    qDebug() << QString::fromStdString(value);
            //}
            qDebug() << "boxes:";
            for (const auto& value : boxes) {
                qDebug() << value;
            }
            qDebug() << "pill_quantity:";
            for (const auto& value : pill_quantity) {
                qDebug() << value;
            }
            qDebug() << "dose:";
            for (const auto& value : dose) {
                qDebug() << value;
            }
            qDebug() << "discount:";
            for (const auto& value : discount) {
                qDebug() << value;
            }
        }
    };
    struct historderstruct{
       std::vector<unsigned int> id;
       std::vector<std::string> med_name;
       std::vector<double> dose;
       std::vector<int> boxes;
       std::vector<std::string> order_date;
    };
    struct histsalestruct{
           std::vector<unsigned int> id;
           std::vector<std::string> med_name;
           std::vector<double> dose;
           std::vector<int> boxes;
           std::vector<std::string> order_date;
           std::vector<int> receipt_id;
    };

    medstruct meds_return();
    histsalestruct histsale_return();
    content_struct prescription_query(std::string accessKey, std::string pesel);
    bool meds_order(DB_Query::medstruct med_order);
    bool history_add(DB_Query::medstruct med_order, int database_num);
    historderstruct history_query();
    sql::PreparedStatement *pstmt;
    prescription_struct prescriptionData;
    content_struct contentData;
private:
    sql::Driver *driver;
    sql::ResultSet *rs;
    medstruct meds_array;
    historderstruct history_array;
    histsalestruct hists_array;
    bool debug_mode = false;
};

#endif // DB_QUERY_H
