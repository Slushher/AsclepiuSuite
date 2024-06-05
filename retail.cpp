#include "retail.h"
#include "ui_retail.h"
#include "global.h"
#include <typeinfo>


retail::retail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::retail)
{
    ui->setupUi(this);
    c_listModel = new QStringListModel(this);
    c_cartModel = new QStringListModel(this);
    Qsearchdrug = ui->Qsearchdrug;
    Qdruglist = ui->Qdruglist;
    Qcartlist = ui->Qcartlist;
    db_medstruct = db1.meds_return();
    db_medstruct_original = db_medstruct;
    db_medcart = db_medstruct;
    for(size_t i = 0; i < db_medcart.id.size(); ++i){
        db_medcart.boxes[i] = 0;
    }
    setMedList(db_medstruct);
    setGradient(this);
    connect(Qsearchdrug, &QLineEdit::textChanged, this, &retail::filterList);
    connect(Qsearchdrug, &QLineEdit::textEdited, this, &retail::filterList);
    backButton = ui->backButton;
    Qclearcart = ui->Qclearcart;
    Qproceed = ui->Qproceed;
    Qdropcart = ui->Qdropcart;
    connect(backButton, &QPushButton::clicked, this, [=]() { goBack(this); });
    QPushButton *Qaddcart = ui->Qaddcart;
    connect(Qaddcart, &QPushButton::clicked, this, &retail::addItemToCart);
    connect(Qdropcart, &QPushButton::clicked, this, &retail::removeItemFromCart);
    connect(Qclearcart, &QPushButton::clicked, this, &retail::resetTransaction);
    connect(Qproceed, &QPushButton::clicked, this, &retail::checkoutCart);
}

retail::~retail()
{
    delete ui;
}

void retail::refreshMeds()
{
    db_medstruct = db1.meds_return();
    setMedList(db_medstruct);
}

void retail::resetTransaction(){
    db_medstruct = db_medstruct_original;
    db_medcart = db_medstruct;
    for(size_t i = 0; i < db_medcart.id.size(); ++i){
        db_medcart.boxes[i] = 0;
    }
    setMedList(db_medstruct);
    setCartList(db_medcart);
}

void retail::filterList(const QString &text) {
    setMedList(db_medstruct);
    QStringListModel *listModel = qobject_cast<QStringListModel*>(Qdruglist->model());
    if (!listModel) {
        return;
    }

    if (text.isEmpty()) {
        Qdruglist->setModel(c_listModel);
        setMedList(db_medstruct);
        //qDebug() << "listModel: " << listModel;
        return;
    }

    QStringList listSearchResult;
    for (const QString &item : c_listModel->stringList()) {
        if (item.contains(text, Qt::CaseInsensitive)) {
            listSearchResult << item;
            //qDebug() << "listSearchResult: " << listSearchResult;
        }
    }

    listModel->setStringList(listSearchResult);
}

void retail::setMedList(DB_Query::medstruct db_medstruct)
{
    QStringList stringList;
    //qDebug() << "size " << db_medstruct.id.size();
    for(size_t i = 0; i < db_medstruct.id.size(); ++i){
        //if(db_medstruct.boxes[i] > 0){
            //stringList<<QString::fromStdString(std::to_string(db_medstruct.id[i])+" "+db_medstruct.med_name[i]+" "+std::to_string(db_medstruct.pill_quantity[i])+" "+QString::number(db_medstruct.dose[i], 'f', 2).toStdString());
            stringList<<QString::fromStdString("'" + db_medstruct.med_name[i]+"', "+QString::number(db_medstruct.dose[i], 'f', 2).toStdString()+"mg"+", "+
                                               std::to_string(db_medstruct.pill_quantity[i])+"szt. " + " x" + std::to_string(db_medstruct.boxes[i])+ ", "+"(EXP): "+
                                               db_medstruct.expiration_date[i] + ", " + QString::number(db_medstruct.price[i], 'f', 2).toStdString()+"zl" + ", " + db_medstruct.active_ingredient[i]);
        //}
    }
    c_listModel->setStringList(stringList);
    ui->Qdruglist->setModel(c_listModel);
}

void retail::setCartList(DB_Query::medstruct db_medcart)
{
    QStringList stringList;
    //qDebug() << "size " << db_medstruct.id.size();
    for(size_t i = 0; i < db_medcart.id.size(); ++i){
        //if(db_medcart.boxes[i] > 0){
            //stringList<<QString::fromStdString(std::to_string(db_medstruct.id[i])+" "+db_medstruct.med_name[i]+" "+std::to_string(db_medstruct.pill_quantity[i])+" "+QString::number(db_medstruct.dose[i], 'f', 2).toStdString());
            stringList<<QString::fromStdString("'" + db_medcart.med_name[i]+"', "+QString::number(db_medcart.dose[i], 'f', 2).toStdString()+"mg"+", "+
                                               std::to_string(db_medcart.pill_quantity[i])+"szt. " + " x" + std::to_string(db_medcart.boxes[i])+ ", "+"(EXP): "+
                                               db_medcart.expiration_date[i] + ", " + QString::number(db_medcart.price[i], 'f', 2).toStdString()+"zl" + ", " + db_medcart.active_ingredient[i]);
        //}
    }
    c_cartModel->setStringList(stringList);
    ui->Qcartlist->setModel(c_cartModel);
}

void retail::addItemToCart()
{
    int med_list_row = -1;
    QModelIndexList selectedIndexes = Qdruglist->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        return;
    }
    QModelIndex selectedIndex = selectedIndexes.first();
    QString selectedItem = c_listModel->data(selectedIndex, Qt::DisplayRole).toString();
    med_list_row = int(selectedIndex.row());
    if(med_list_row >= 0){
           if(db_medstruct.boxes[med_list_row] > 0){
                db_medstruct.boxes[med_list_row]--;
                db_medcart.boxes[med_list_row]++;
                setMedList(db_medstruct);
                setCartList(db_medcart);
        }
    }
    //qDebug() << QString::fromStdString(db_medstruct.med_name[med_list_row]) << db_medstruct.boxes[med_list_row] << "\n";

    /*QStringListModel *cartModel = qobject_cast<QStringListModel*>(Qcartlist->model());
    if (!cartModel) {
        cartModel = new QStringListModel(this);
        Qcartlist->setModel(cartModel);
    }
    QStringList cartItems = cartModel->stringList();
    cartItems << selectedItem;
    cartModel->setStringList(cartItems);*/
}

void retail::removeItemFromCart()
{
    int med_list_row = -1;
    QModelIndexList selectedIndexes = Qcartlist->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        return;
    }
    QModelIndex selectedIndex = selectedIndexes.first();
    QString selectedItem = c_cartModel->data(selectedIndex, Qt::DisplayRole).toString();
    med_list_row = int(selectedIndex.row());
    if(med_list_row >= 0){
            if(db_medcart.boxes[med_list_row] > 0){
                db_medstruct.boxes[med_list_row]++;
                db_medcart.boxes[med_list_row]--;
                setMedList(db_medstruct);
                setCartList(db_medcart);
        }
    }
    //qDebug() << QString::fromStdString(db_medstruct.med_name[med_list_row]) << db_medstruct.boxes[med_list_row] << "\n";

    /*QStringListModel *cartModel = qobject_cast<QStringListModel*>(Qcartlist->model());
    if (!cartModel) {
        cartModel = new QStringListModel(this);
        Qcartlist->setModel(cartModel);
    }
    QStringList cartItems = cartModel->stringList();
    cartItems << selectedItem;
    cartModel->setStringList(cartItems);*/
}

double retail::castToDouble(std::string num)
{
    std::string currentLocale = std::setlocale(LC_NUMERIC, nullptr);
    std::setlocale(LC_NUMERIC, "C");
    double value = std::stod(num);
    std::setlocale(LC_NUMERIC, currentLocale.c_str());
    return value;
}

void retail::checkoutCart(){
    DB_Query::medstruct cart_buff;
    for(int i = 0; i < int(db_medstruct.id.size()); i++){
        std::string item = c_cartModel->data(c_cartModel->index(i, 0)).toString().toStdString();
        if (item.find("x0") == std::string::npos) {
            cart_buff.clear();
            qDebug() << c_cartModel->data(c_cartModel->index(i, 0)).toString();
            std::smatch match;
            cart_buff.id.push_back(i);
            if (std::regex_search(item, match, rx[0])) {
                cart_buff.med_name.push_back(match[1].str());
            }
            if(std::regex_search(item, match, rx[1])) {
                cart_buff.dose.push_back(castToDouble(match[1].str()));
            }
            if(std::regex_search(item, match, rx[2])) {
                cart_buff.pill_quantity.push_back(std::stoi(match[1].str()));
            }
            if(std::regex_search(item, match, rx[3])) {
                cart_buff.boxes.push_back(std::stoi(match[1].str()));
            }
            if(std::regex_search(item, match, rx[4])) {
                cart_buff.price.push_back(castToDouble(match[1].str()));
            }
            QDateTime currentDate = QDateTime::currentDateTime();
            QString dateStr = currentDate.toString("yyyy-MM-dd");
            cart_buff.expiration_date.push_back(dateStr.toStdString());
            db1.history_add(cart_buff,1);
        }
    }
    cart_buff.qDebugPrint();
}
