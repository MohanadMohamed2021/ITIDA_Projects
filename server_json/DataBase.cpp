#include "DataBase.h"
#define PATH_DATA "../server_json/DataBase.json"
#define PATH_DATA_TRANS "../server_json/Transaction_DataBase.json"


/*******this the constractor of the DataBase class used to init qin,qout**********/
DataBase::DataBase(QObject *parent)
    : QObject{parent},qin(stdin),qout(stdout),_pathData(PATH_DATA),_pathDataTrans(PATH_DATA_TRANS){}

/*****************this function used to update the vector by the data base file*************/
void DataBase::on_Init_DataBase()
{
    QFile file(_pathData); //create instance of QFile to deal with json file

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))   //open the file in readonly mode
    {
        QByteArray jsonData = file.readAll();   //read the data inside the file
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData); //convert the QByteArray to QJsonDocument

        if (!jsonDoc.isNull() && jsonDoc.isArray())     //check if the converted data is valid
        {
            _dataBase.clear();  // Clear the vector

            QJsonArray jsonArray = jsonDoc.array();     //convert the QJsonDocument to QJsonArray to loop in

            for (int i = 0; i < jsonArray.size(); ++i)
            {
                QJsonObject jsonObj = jsonArray[i].toObject(); //take the object of the array and push it into my vector
                _dataBase.push_back(jsonObj);
            }
        }
        else
        {
            qDebug() << "Invalid JSON format!";
        }
    }
    else
    {
        qDebug() << "Can't open database file....";
    }
}

/*****************this function used to update the vector by the data base Transaction file*************/
void DataBase::on_Init_Transaction_DataBase()
{
    QFile file_Transaction(_pathDataTrans);     //create instance of QFile to deal with json file

    if (file_Transaction.open(QFile::ReadOnly | QFile::Text))   //open the file in readonly mode
    {
        QByteArray jsonData = file_Transaction.readAll();   //read the data inside the file
        file_Transaction.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);  //convert the QByteArray to QJsonDocument

        if (!jsonDoc.isNull() && jsonDoc.isArray()) //check if the converted data is valid
        {
            _dataBase_Transaction.clear();  // Clear the vector

            QJsonArray jsonArray = jsonDoc.array(); //convert the QJsonDocument to QJsonArray to loop in

            for (int i = 0; i < jsonArray.size(); ++i)
            {
                QJsonObject jsonObj = jsonArray[i].toObject(); //take the object of the array and push it into my vector
                _dataBase_Transaction.push_back(jsonObj);
            }
        }
        else
        {
            qDebug() << "Invalid JSON format for transaction data!";
        }
    }
    else
    {
        qDebug() << "Can't open transaction database file....";
    }
}

/************this a getter function to get the data inside data base file************/
QVector<QJsonObject> DataBase::get_DataBase()
{
    on_Init_DataBase(); //ensure the return data us up to date
    if(!_dataBase.empty()) //check if the vector is empty
    {
        return _dataBase;
    }
    else    //return empty string in case vector is empty
    {
        return QVector<QJsonObject>();
    }
}

/************this a getter function to get the data inside data base Transaction file************/
QVector<QJsonObject> DataBase::get_Transaction_DataBase()
{
    on_Init_Transaction_DataBase(); //ensure the return data us up to date

    if(!_dataBase_Transaction.empty())  //check if the vector is empty
    {
        return _dataBase_Transaction;
    }
    else
    {
        return QVector<QJsonObject>();  //return empty string in case vector is empty
    }
}

/************this a function to change the state of log of the user/admin in data base file************/
void DataBase::set_Login(const QString user_name, const QString state)
{
    QFile file(_pathData);      //create instance of QFile to deal with json file

    if (file.open(QFile::ReadWrite | QFile::Text))
    {
        QByteArray fileData = file.readAll();       //read the data inside the file
        QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData); //convert the QByteArray to QJsonDocument

        if (!jsonDoc.isNull() && jsonDoc.isArray()) //check if data is valid
        {
            QJsonArray jsonArray = jsonDoc.array(); //convert QJsonDocument to jsonArray

            for (int i = 0; i < jsonArray.size(); ++i)
            {
                QJsonObject user = jsonArray[i].toObject();
                if (user["usr"].toString() == user_name) //when i get desired user i change log state
                {
                    QString logValue = (state == "on") ? "1" : "0";
                    user["log"] = logValue;
                    jsonArray[i] = user;    //overwrite the old object by the modified one
                    break;
                }
            }

            file.resize(0);

            // Write the updated JSON content back to the file
            file.write(QJsonDocument(jsonArray).toJson());
            file.close();
        }
        else
        {
            qDebug() << "Invalid JSON format!";
            file.close();
        }
    }
    else
    {
        qDebug() << "Can't open the file";
    }
}

/************this a function to add new data of new client of the bank into data base file************/
bool DataBase::add_DataBase(const QString usr,const QString pass,const QString full_name,const QString age)
{
    QString AccountNumber=Generate_AccountNumber();  //Generate unique account number

    //this string represent the new line of data i want to add to the data base file
    QJsonObject newUser;
    newUser["usr"] = usr;
    newUser["pass"] = pass;
    newUser["acc"] = AccountNumber;
    newUser["bal"] = "0";
    newUser["auth"] = "user";
    newUser["log"] = "0";
    newUser["FullName"] = full_name;
    newUser["age"] = age;
    newUser["email"] = "mohamedmohaned012@gmail.com";


    // Initialize the QFile object
    QFile file(_pathData);

    // Check if the file opened in read-write mode
    if (file.open(QFile::ReadWrite | QFile::Text))
    {
        // Read existing data from the database file
        QByteArray fileData = file.readAll();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData); //convert the QByteArray to QJsonDocument

        QJsonArray jsonArray = jsonDoc.array(); //convert QJsonDocument to jsonArray

        jsonArray.append(newUser);

        // Write the updated JSON content back to the file
        file.resize(0);
        file.write(QJsonDocument(jsonArray).toJson());
        file.close();

        // Now, update the transaction file with an empty transaction array
        QFile file_Transaction(_pathDataTrans);

        //create new object with the added user in the dataBase transaction file
        QJsonObject newUserTrans;
        newUserTrans["acc"] = AccountNumber;
        newUserTrans["transactions"] = QJsonArray(); // Empty transaction array for the new user

        // Check if the transaction file opened
        if (file_Transaction.open(QFile::ReadWrite | QFile::Text))
        {

            QByteArray fileDataTrans = file_Transaction.readAll();

            QJsonDocument jsonDocTrans = QJsonDocument::fromJson(fileDataTrans); //convert the QByteArray to QJsonDocument

            QJsonArray jsonArrayTrans = jsonDocTrans.array(); //convert QJsonDocument to jsonArray

            jsonArrayTrans.append(newUserTrans);


            // Write the updated JSON content back to the file
            file_Transaction.resize(0);
            file_Transaction.write(QJsonDocument(jsonArrayTrans).toJson());
            file_Transaction.close();

            return true;
        }
        else
        {
            qDebug() << "Can't open the transaction file";
            return false;
        }
    }
    else
    {
        qDebug() << "Can't open the file";
        return false;
    }
}

/************this a function to erase a user from data base file************/
bool DataBase::deleteUser(const QString accountNumber)
{

    // Initialize the QFile objects to open the two files
    QFile file(_pathData);
    QFile file_Transaction(_pathDataTrans);

    // Check if the two files opened in ReadWrite mode
    if (file.open(QIODevice::ReadWrite) && file_Transaction.open(QIODevice::ReadWrite))
    {
        // Read the JSON data from the main data file
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        QJsonArray jsonArray = doc.array();

        // Iterate over the array and remove the object with the specified account number
        QJsonArray newArray;
        for (const auto& value : jsonArray)
        {
            QJsonObject obj = value.toObject();
            if (obj["acc"].toString() != accountNumber)
            {
                newArray.append(obj);
            }
        }

        // Update the main data file with the modified JSON array
        file.resize(0);
        file.write(QJsonDocument(newArray).toJson());
        file.close();

        // Read the JSON data from the transaction data file
        QJsonDocument docTrans = QJsonDocument::fromJson(file_Transaction.readAll());
        QJsonArray jsonArrayTrans = docTrans.array();

        // Iterate over the array and remove the specified "acc" object
        QJsonArray newArrayTrans;
        for (const auto& valueTrans : jsonArrayTrans)
        {
            QJsonObject obj = valueTrans.toObject();
            if (obj["acc"].toString() != accountNumber)
            {
                newArrayTrans.append(obj);
            }
        }

        // Update the transaction data file with the modified JSON array
        file_Transaction.resize(0);
        file_Transaction.write(QJsonDocument(newArrayTrans).toJson());
        file_Transaction.close();

        return true;
    }
    else
    {
        qDebug() << "Can't open the file";
        return false;
    }
}

/************this a function to update the data inside data base  file************/
bool DataBase::update_DataBase(const QString account_number,const QString usr,const QString pass,
                               const QString full_name,const QString age)
{
    // Initialize the QFile objects to open the two files
    QFile file(_pathData);

    // Check if the two files opened in ReadWrite mode
    if (file.open(QIODevice::ReadWrite))
    {
        // Read the JSON data from the main data file
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        QJsonArray jsonArray = doc.array();

        for (int i = 0; i < jsonArray.size(); ++i)
        {
            QJsonObject obj = jsonArray[i].toObject();
            if (obj["acc"].toString() == account_number)
            {
                obj["usr"]=usr;
                obj["pass"]=pass;
                obj["FullName"]=full_name;
                obj["age"]=age;
                jsonArray[i]=obj;
            }
        }

        // Update the main data file with the modified JSON array
        file.resize(0);
        file.write(QJsonDocument(jsonArray).toJson());
        file.close();

        return true;
    }
    else
    {
        qDebug() << "Can't open the file";
        return false;
    }
}

/************this a function to update the data inside data base Transaction file and data base file************/
bool DataBase::moneyTransfer(const QString accountNumberFrom,const QString accountNumberTo,
                             const QString amount_InFrom,const QString amount_InTo,const QString amount)
{
    if(amount_InFrom.toInt() > amount.toInt())
    {
        //calcaulate my money after transfer
        qint32 amount_InFrom_Updated = amount_InFrom.toInt() - amount.toInt();
        QString amount_InFrom_Updated_String=QString::number(amount_InFrom_Updated);

        //calculate the other person money after transfer
        qint32 amount_InTo_Updated = amount.toInt() + amount_InTo.toInt();
        QString amount_InTo_Updated_String=QString::number(amount_InTo_Updated);

        //Open File to update
        QFile file(_pathData);
        if(file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            // Read the JSON data from the main data file
            QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
            QJsonArray jsonArray = doc.array();

            for (int i = 0; i < jsonArray.size(); ++i)
            {
                QJsonObject obj = jsonArray[i].toObject();

                if(obj["acc"].toString() == accountNumberFrom)
                {
                    obj["bal"]=amount_InFrom_Updated_String;
                    jsonArray[i]=obj;
                }

                else if(obj["acc"].toString() == accountNumberTo)
                {
                    obj["bal"]=amount_InTo_Updated_String;
                    jsonArray[i]=obj;
                }
            }

            file.resize(0);
            file.write(QJsonDocument(jsonArray).toJson());
            file.close();

            //update the transaction file
            update_Transaction(accountNumberFrom,amount,"-");
            update_Transaction(accountNumberTo,amount,"+");
            return true;
        }
        else
        {
            qout<<"can't open the file"<<Qt::endl;
            return false;
        }
    }
    else
    {
        return false;
    }
}


/************this a function to update the data inside data base Transaction file and data base file************/
bool DataBase::moneyTransaction_WithDraw(const QString accountNumber,const QString myMoney,const QString transaction)
{
    //check if i have enough money for withdraw operation
    if(myMoney.toInt() > transaction.toInt())
    {
        //calculate my money after the operation
        qint32 myMoney_Updated = myMoney.toInt() - transaction.toInt();
        QString myMoney_Updated_String=QString::number(myMoney_Updated);

        QFile file(_pathData);

        //open the file
        if(file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            // Read the JSON data from the main data file
            QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
            QJsonArray jsonArray = doc.array();

            for (int i = 0; i < jsonArray.size(); ++i)
            {
                QJsonObject obj = jsonArray[i].toObject();

                if(obj["acc"].toString() == accountNumber)
                {
                    obj["bal"]=myMoney_Updated_String;  //update the money in the file
                    jsonArray[i]=obj;
                }

            }

            // Close and reopen the file in WriteOnly mode to clear its content
            file.resize(0);
            file.write(QJsonDocument(jsonArray).toJson());
            file.close();

            //update the transaction file
            update_Transaction(accountNumber,transaction,"-");
            return true;
        }
        else
        {
            qout<<"can't open the file........"<<Qt::endl;
            return false;
        }
    }
    else
    {
        return false;
    }
}

/************this a function to update the data inside data base Transaction file and data base file************/
bool DataBase::moneyTransactionPut(const QString accountNumber,const QString myMoney,const QString transaction)
{
    //check if the money user send i valid number
    if(transaction.toInt() > 0)
    {
        //My money after the operation
        qint32 myMoney_Updated = myMoney.toInt() + transaction.toInt();
        QString myMoney_Updated_String=QString::number(myMoney_Updated);

        //open the file
        QFile file(_pathData);
        if(file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            // Read the JSON data from the main data file
            QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
            QJsonArray jsonArray = doc.array();

            for (int i = 0; i < jsonArray.size(); ++i)
            {
                QJsonObject obj = jsonArray[i].toObject();

                if(obj["acc"].toString() == accountNumber)
                {
                    obj["bal"]=myMoney_Updated_String;         //update the money in the file
                    jsonArray[i]=obj;
                }
            }

            // Close and reopen the file in WriteOnly mode to clear its content
            file.resize(0);
            file.write(QJsonDocument(jsonArray).toJson());
            file.close();

            //update the vector and transaction file
            update_Transaction(accountNumber,transaction,"+");
            return true;
        }
        else
        {
            qout<<"can't open the file........"<<Qt::endl;
            return false;
        }
    }
    else
    {
        return false;
    }
}

/************this a function to update the data inside data base Transaction file************/
bool DataBase::update_Transaction(const QString accountNumber, const QString transaction, QString state)
{
    //extract the date of the system to add it to the json file
    QDate currentDate = QDate::currentDate();
    QString currentDateString = currentDate.toString("dd.MM.yyyy");

    // Open the transaction database file
    QFile file_Transaction(_pathDataTrans);
    if (file_Transaction.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QByteArray fileData = file_Transaction.readAll();

        QJsonDocument doc = QJsonDocument::fromJson(fileData);

        if (doc.isArray() && !doc.isNull())  //if QJsonDocument is in valid format
        {
            QJsonArray jsonArray = doc.array();  //convert QJsonDocument into jsonArray to loop in

            for (int i = 0; i < jsonArray.size(); ++i)
            {
                QJsonObject obj = jsonArray[i].toObject();

                if (obj["acc"].toString() == accountNumber)
                {
                    QJsonArray transactions = obj["transactions"].toArray();

                    // Create a new transaction object
                    QJsonObject newTransaction;
                    if (state == "+")
                    {
                        newTransaction["amount"] = "+" + transaction;
                    }
                    else if (state == "-")
                    {
                        newTransaction["amount"] = "-" + transaction;
                    }
                    else
                    {
                        qDebug() << "Invalid state";
                        return false;
                    }
                    newTransaction["date"] = currentDateString;

                    // Append the new transaction to the array
                    transactions.append(newTransaction);

                    // Update the transactions array in the object
                    obj["transactions"] = transactions;
                    jsonArray[i] = obj;
                }
            }

            // Reopen the file in WriteOnly mode to clear its contents
            file_Transaction.resize(0);
            file_Transaction.write(QJsonDocument(jsonArray).toJson());
            file_Transaction.close();

            // Update the vector
            on_Init_Transaction_DataBase();
            return true;
        }
        else
        {
            qDebug() << "Invalid json format...";
            return false;
        }
    }
    else
    {
        qDebug() << "Can't open the file...";
        return false;
    }
}

//Generate unique account number.................
QString DataBase::Generate_AccountNumber()
{
    bool flag=false;    //flag to ensure unique account number
    while(true)
    {
        flag=false;
        //in these line i generate random number synchronized with system clock to act as account number

        qint32 seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator(seed);

        //these represent the two value which i get account number betwwen them
        qint32 minValue = 1024;
        qint32 maxValue = 65535;

        std::uniform_int_distribution<int> distribution(minValue, maxValue);
        qint32 account_number = distribution(generator);
        QString AccountNumber=QString::number(account_number);
        for(auto obj:_dataBase)
        {
            if(obj["acc"].toInt()==account_number)
            {
                flag=true;
            }
        }
        if(flag==false)
        {
            return AccountNumber;
        }
    }
}









