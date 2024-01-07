#include "MyThreadClass.h"
#include <QDebug>

//create instance of DataBase class
DataBase _DataBase;

//********the Constructor of MyThreadClass
MyThreadClass::MyThreadClass(int ID, QObject *parent) :
    QThread(parent),qin(stdin),qout(stdout)
{
    //initalize the socketDescriptor with the one come from incommingConnection slot
    this->socketDescriptor = ID;
}

//the function that handle new connection and it's run on different thread
void MyThreadClass::run()
{
    // thread start here
    // each socket within the network has a unique number -> socket descriptor
    qDebug() <<">> the running thread number is "<<currentThreadId();
    qDebug() <<">> client_"<< socketDescriptor << "on the thread";

    socket = new QTcpSocket;

    //Asign socketDescriptor for the new socket
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        qDebug()<<"Failed to connect to the socket";
    }

    //connect the two signals of readyRead & disconnected to specific slots
    connect(socket, SIGNAL(readyRead()), this, SLOT(on_clientDataReady()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(on_clientDisconnected()), Qt::DirectConnection);

    qDebug() << socketDescriptor << "-> client connected.";

    //here i push the new name of socket into my map of sockets
    QString client_name=QString("client_%1").arg(socketDescriptor);
    _socketList.first=client_name;
    _socketList.second=socket;
    //Send welcome message to the new client with his own name
    QString str="Welcome from server.I have named you after your socketDescriptor..>> "+client_name+"....\n";
    server_SendMessage(str);
    //python=new QProcess;
    //start event loop
    exec();
}

/*******slot to handle the new message from the client********/
//"/5RMxMxYe6a41psZJDhxMZWtZ6qw8pFUyJMBRoW1GQKvlRmSnQ98pL
//zbzE4nOSBjwPg98OygnQPPnwoUi7AZU7bPXpyRbiDu7djCHC53Y2LDvz+wsrPdQ9vaWFHB6UwP8cRDkpsHeKa71tgEN2ooaseFP//ts5ISx99VTpD/AwbwyUiglkcstrLQygQ3aihqx58n4u2zkhLEz0pR07REQuQ="
//"f1a73e2204a114077f988c9da98d7f8b604ab250496f25aeb3cbd153f5369c83/jsonSize:84;{\"data\":\"usrpass:mohanad:1234\",\"fileName\":\"null\",\"fileSize\":20,\"fileType\":\"message\"}"
void MyThreadClass::on_clientDataReady()
{
    // Read the available data from the socket
    QByteArray encryptMessage = socket->readAll();
    QString dataString=decryptMessage(encryptMessage,"Key");

    // Ensure that there is some data to process
    if (!dataString.isEmpty())
    {
        //Extract the signature and compare it to the one has been sent to me........
        QByteArray hashed = QCryptographicHash::hash("Signature", QCryptographicHash::Sha256);
        QByteArray signature = hashed.toHex();
        //Extract the signature from the recieved message
        QString Auth=dataString.split("/")[0];
        if(Auth.contains(signature))
        {
            // Extract the JSON size from the header
            int jsonSize = dataString.split(":")[1].split(";")[0].toInt();

            // Check if the data received is complete
            if (dataString.size() >= jsonSize)
            {
                // Extract the JSON message based on the jsonSize
                QString jsonMessage = dataString.right(jsonSize);

                // Parse the JSON message
                QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonMessage.toUtf8());
                if (!jsonDoc.isNull())
                {
                    QJsonObject jsonObject = jsonDoc.object();

                    // Extract the messageType and other relevant fields from the JSON object
                    QString fileType = jsonObject.value("fileType").toString();
                    QString fileName = jsonObject.value("fileName").toString();
                    qint32 fileSize = jsonObject.value("fileSize").toInt();
                    QString message = jsonObject.value("data").toString();

                    // Print the message
                    qDebug() << "Received message: " << message <<"...From client named >> "<<_socketList.first<< Qt::endl;

                    //call the selectOperation function to handle the operation based on message
                    selectOperation(message);
                }
                else
                {
                    // Failed to parse JSON
                    qDebug() << "Failed to parse JSON. Invalid JSON format." << Qt::endl;
                }
            }
            else
            {
                // Incomplete data, wait for more
                qDebug() << "Incomplete data received. Waiting for more." << Qt::endl;
            }
        }
        else
        {
            qDebug() << "Signature refuced from unworthy person......" << Qt::endl;
        }
    }
    else
    {
        // No data received
        qDebug() << "No data received." << Qt::endl;
    }

}
/*************Algorithm to decrypt data**********/
QString MyThreadClass::decryptMessage(const QString &encryptedMessage, const QString &key)
{
    QByteArray keyData = key.toUtf8();
    QByteArray encryptedData = QByteArray::fromBase64(encryptedMessage.toUtf8());

    // Use SHA-256 for better security
    QByteArray hashedKey = QCryptographicHash::hash(keyData, QCryptographicHash::Sha256);

    // XOR the encrypted data with the hashed key to decrypt
    QByteArray decryptedData = encryptedData;
    for (int i = 0; i < encryptedData.size(); ++i)
    {
        decryptedData[i] = decryptedData[i] ^ hashedKey[i % hashedKey.size()];
    }
    // Convert the decrypted data to a string
    QString decryptedMessage = QString(decryptedData);

    return decryptedMessage;
}

//**********Function to handle the requests send from client***********/
//usr:mohanad,pass:1234
void MyThreadClass::selectOperation(const QString message)
{
    //Parse the comming message to select the operation
    QStringList parts = message.split(":");

    /******************log in Request*********************/
    if(parts[0]=="usrpass")
    {
        check_Login(parts);
    }
    /******************log out Request*********************/
    else if(parts[0]=="logout")
    {
        check_Logout(parts);
    }
    /******************Get Account_Number Request*********************/
    else if(parts[0]=="acc")
    {
        getAccountNumber(parts);
    }
    /******************Get Account_Number with admin help Request*********************/
    else if(parts[0]=="aacc")
    {
        getAccountNumber_Admin(parts);
    }  
    /******************Get Account_Balance Request*******************/
    else if(parts[0]=="bal")
    {
        getAccountBalance(parts);
    }
    /****************Get Data_Base****************************/
    else if(parts[0]=="data")
    {
        Get_DataBase(parts);
    }
    /**************Add New User Request***************************/
    else if(parts[0]=="add")
    {
        addNewUser(parts);
    }
    /**************Delete user Request***************************/
    else if(parts[0]=="del")
    {
        deleteUser(parts);
    } 
    /**************Update user Request***************************/
    else if(parts[0]=="update")
    {
        updateUser(parts);
    }
    /**************transfer money Request********************/
    else if(parts[0]=="transfer")
    {
        Transfer(parts);
    }
    /**************withdraw money Request********************/
    else if(parts[0]=="withdraw")
    {
        Transaction_WithDraw(parts);
    }
    /**************deposite money Request********************/
    else if(parts[0]=="deposit")
    {
        Transaction_Deposite(parts);
    }
    /**************history of transaction Request********************/
    else if(parts[0]=="history")
    {
        getTransaction_DataBase(parts);
    }
    /*************Clear terminal request*************/
    else if(parts[0]=="clear")
    {
        server_SendMessage("Terminal has been cleared\n"
                           "---------------------------\n"
                           "|| Client Connected ||\n"
                           "|| Start Over||\n"
                           "---------------------------");
    }
    /******************help Request*********************/
    else if(parts[0]=="help")
    {
         server_SendMessage("enter 'exit' to disconnect\n"
                            "enter 'clear' to clear terminal\n"
                            "enter 'login' to login\n"
                            "enter 'aacc' to get account number with admin help\n"
                            "enter 'logout' to logout\n"
                            "enter 'acc' to get account number\n"
                            "enter 'bal' to get balance\n"
                            "enter 'data' to get Data_Base\n"
                            "enter 'del to delete use'\n"
                            "enter 'update' to update user\n"
                            "enter 'transfer' to transfer money\n"
                            "enter 'withdraw' to take money\n"
                            "enter 'deposit' to put money\n"
                            "enter 'history' to get transaction history\n"
                            "enter 'add' to add user\n...\n...\n...\n");
    }
    /******************invalid Request*********************/
    else if(parts[0]=="invalid")
    {
        server_SendMessage("Invalid input enter 'help' to print list of command...*_*");
    }
}

/***************Function to send respond to the client****************/
void MyThreadClass::server_SendMessage(QString data)
{
    auto client_socket = _socketList.second;
    if (client_socket->isOpen())
    {
        // Create a JSON object with your data
        QJsonObject jsonObject;
        jsonObject["fileType"] = "message";
        jsonObject["fileName"] = "null";
        jsonObject["fileSize"] = data.size();
        jsonObject["data"] = data;

        // Convert the JSON object to a QByteArray
        QByteArray jsonByteArray = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact);

        // Prepend the size of the JSON data as a header
        QByteArray header;
        header.prepend(QString("jsonSize:%1;").arg(jsonByteArray.size()).toUtf8());

        // Combine header and JSON data
        QByteArray byteArray = header + jsonByteArray;
        //Function to encrypt data
        QString encryptedMessage=encryptMessage(byteArray,"Key");
        // Send the data over the socket
        client_socket->write(encryptedMessage.toUtf8());
    }
    else
    {
        qDebug() << "Socket is not open........T_T";
    }
}
/***********Function to encrypt data**************/
QString MyThreadClass::encryptMessage(const QString &message, const QString &key)
{
    QByteArray keyData = key.toUtf8();
    QByteArray messageData = message.toUtf8();

    // Use SHA-256 for better security
    QByteArray hashedKey = QCryptographicHash::hash(keyData, QCryptographicHash::Sha256);

    // XOR the message with the hashed key
    QByteArray encryptedData = messageData;
    for (int i = 0; i < messageData.size(); ++i)
    {
        encryptedData[i] = encryptedData[i] ^ hashedKey[i % hashedKey.size()];
    }

    // Convert the encrypted data to a Base64-encoded string
    QString encryptedMessage = QString(encryptedData.toBase64());

    return encryptedMessage;
}
/***********Function to login to server******************/
void MyThreadClass::check_Login(QStringList parts)
{
    bool flag1=false; //some flags to check validation of request
    QVector<QJsonObject> dataBase = _DataBase.get_DataBase(); //initialize vector with dataBase vector

    for(auto obj:dataBase) //loop on every line in the file using vector
    {
        if((obj["usr"].toString() == parts[1]) && (obj["pass"].toString() == parts[2])
            && obj["log"] == "0") //check if user is valid
        {
            flag1=true;
        }
    }

    //when the user is valid
    if(flag1==true)
    {
        //change the 'log' state in data base file
        _DataBase.set_Login(parts[1],"on");

        QString str = QString("logged in successfully..... ^_^\n"
                              "Hello %1.....").arg(parts[1]);
        server_SendMessage(str);
        _user_name=parts[1];
        qDebug() << "This user is on the thread >> "<<_user_name;
        qDebug()<<"\n";
    }
    else //in case never find user or incorrect passward
    {
        server_SendMessage("logged in failed because of wrong passward\n"
                           "or this account is already login..... *_*");
    }
}

/**********function to help user get account number with admin help even if he is not login*************/
void MyThreadClass::getAccountNumber_Admin(QStringList parts)
{
    //some flags to check validation of request
    bool flag1=false,flag2=false;
    //temp account number while looping
    QString account_number;

    //initialize vector with dataBase vector
    QVector<QJsonObject>  dataBase(_DataBase.get_DataBase());

    for(auto obj:dataBase) //loop on every line in the file using vector
    {
        if((obj["usr"].toString() == parts[1]) && (obj["log"].toString() == "1")
            && (obj["auth"].toString() == "admin")) //check if admin is valid
        {
            flag1=true;
        }
        if(obj["usr"].toString() == parts[2]) //check if user exsist
        {
            flag2=true;
            account_number=obj["acc"].toString();
        }
    }

    if(flag1==true && flag2==true) //in case admin and user valid
    {
        QString str=QString("Hello %1 your account number is\n"
                              ".................%2 use it well @_@............").arg(parts[2]).arg(account_number);
        server_SendMessage(str);
    }
    else    //in case admin and user invalid
    {
        server_SendMessage("You don't have the authority for this...... *_*");
    }
    qDebug() << "This user is on the thread >> "<<_user_name;
    qDebug()<<"\n";
}
/*********function to handle logout request****************/
void MyThreadClass::check_Logout(QStringList parts)
{
    bool flag1=false; //some flags to check validation of request
    QVector<QJsonObject> dataBase = _DataBase.get_DataBase(); //initialize vector with dataBase vector

    for(auto obj:dataBase) //loop on every line in the file using vector
    {
        if((obj["usr"].toString() == parts[1])) //check if user is valid
        {
            flag1=true;
        }
    }

    //when the user is valid
    if(flag1==true)
    {
        //change the 'log' state in data base file
        _DataBase.set_Login(parts[1],"off");

        QString str = QString("logged out successfully..... >_<\n"
                              "Bye %1.......").arg(parts[1]);
        server_SendMessage(str);
    }
    else //in case never find user
    {
        server_SendMessage("logged out failed...... *_*");
    }
    qDebug() << "This user is on the thread >> "<<_user_name;
    qDebug()<<"\n";
}

/******************Function to handle account number request**********/
void MyThreadClass::getAccountNumber(QStringList parts)
{
    //some flags to check validation of request
    bool flag1=false;
    //string will hold the account number
    QString account_number;

    //initialize vector with dataBase vector
    QVector<QJsonObject> dataBase(_DataBase.get_DataBase());

    for(auto obj:dataBase)       //loop on every line in the file using vector
    {
        if((obj["usr"].toString() == parts[1]) && (obj["log"].toString() == "1")
            && (obj["auth"] == "user"))         //check if user is valid
        {
            flag1=true;
            account_number=obj["acc"].toString();   //get the account number
        }
    }

    if(flag1==true) // in case valid user
    {
        QString str=QString("Hello %1 your account number is\n"
                              ".................%2 use it well @_@............").arg(parts[1]).arg(account_number);
        server_SendMessage(str);
    }
    else //in case user not login
    {
        server_SendMessage("You're not even logged in......\n"
                           "or you may don't have authority for this........ *_*");
    }
    qDebug() << "This user is on the thread >> "<<_user_name;
    qDebug()<<"\n";
}

/*******function to handle get account balance request****************/
void MyThreadClass::getAccountBalance(QStringList parts )
{
    //some flags to check validation of request
    bool flag1=false;

    QString User_Name; //string to hold user name

    QString balance; //string to hold the balance

    QVector<QJsonObject> dataBase(_DataBase.get_DataBase());    //initialize vector with dataBase vector

    for(auto obj:dataBase) //loop on every line in the file using vector
    {
        if((obj["acc"].toString() == parts[1])) //check if user is valid
        {
            flag1=true;

            //get the user_name and the balance of this object
            balance=obj["bal"].toString();
            User_Name=obj["usr"].toString();
        }
    }
    if(flag1==true)
    {
        QString str=QString("Hello %1 your balance number is\n"
                                ".................%2 lucky you ^_~............").arg(User_Name).arg(balance);
        server_SendMessage(str);
    }
    else  //in case user not login
    {
        server_SendMessage("Invalid account number try again.... *_*");
    }
    qDebug() << "This user is on the thread >> "<<_user_name;
    qDebug()<<"\n";
}

/****************FUnction to handle data base request**********/
void MyThreadClass::Get_DataBase(QStringList parts)
{
    //some flags to check validation of request
    bool flag1=false;

    //initialize vector with dataBase vector
    QVector<QJsonObject> dataBase(_DataBase.get_DataBase());

    for(auto obj:dataBase) //loop on every line in the file using vector
    {
        if((obj["usr"].toString() == parts[1]) && (obj["log"].toString() == "1")
            && (obj["auth"].toString() == "admin")) //check if admin is valid
        {
            flag1=true;
        }
    }

    if(flag1==true) //in case admin is valid
    {
        //copy the object from vector to QJsonArray
        QJsonArray jsonArray;
        for (const auto &obj : dataBase)
        {
            jsonArray.append(obj);
        }

        //convert QJsonArray to QJsonDocument to make it readable
        QJsonDocument jsonDoc(jsonArray);
        QString jsonString = QString::fromUtf8(jsonDoc.toJson()); //this line to convert QJsonDocument to QString

        server_SendMessage(jsonString);
    }
    else //in case admin is not valid
    {
        server_SendMessage("You don't have the authority for this..... *_*");
    }
    qDebug() << "This user is on the thread >> "<<_user_name;
    qDebug()<<"\n";
}

/**************function to handle add new user/admin request************/
void MyThreadClass::addNewUser(QStringList parts)
{
    //some flags to check validation of request
    bool flag1=false;

    //initialize vector with dataBase vector
    QVector<QJsonObject> dataBase(_DataBase.get_DataBase());

    for(auto obj:dataBase) //loop on every line in the file using vector
    {
        if((obj["usr"].toString() == parts[1]) && (obj["log"].toString() == "1")
            && (obj["auth"].toString() == "admin")) //check if admin is valid
        {
            flag1=true;
        }
    }
    if(flag1==true) //check if admin is valid
    {
        //check if new user added successfully
        if(_DataBase.add_DataBase(parts[2],parts[3],parts[4],parts[5]))
        {
            QString str=QString("Congratulation new user '%1'\n"
                                    "........has been added welcome aboard ^_^").arg(parts[2]);
            server_SendMessage(str);
        }
        else //in case the new user not added to data base file
        {
            QString str=QString("Sadly new user '%1'\n"
                                    "........couldn't join us @_@").arg(parts[2]);
            server_SendMessage(str);
        }
    }
    else// in case not valid admin
    {
        server_SendMessage("You don't have the authority for this..... *_*");
    }
    qDebug() << "This user is on the thread >> "<<_user_name;
    qDebug()<<"\n";
}


/*************function to handle delete user request****************/
void MyThreadClass::deleteUser(QStringList parts)
{
    //some flags to check validation of request
    bool flag1=false,flag2=false;

    //initialize vector with dataBase vector
    QVector<QJsonObject> dataBase(_DataBase.get_DataBase());

    for(auto obj:dataBase) //loop on every line in the file using vector
    {
        if((obj["usr"].toString() == parts[1]) && (obj["log"].toString() == "1")
            && (obj["auth"].toString() == "admin")) //check if admin is valid
        {
            flag1=true;
        }
        if(obj["acc"].toString() == parts[2])  //check if account number of user is exsist
        {
            flag2=true;
        }
    }

    if(flag1==true && flag2==true) //check if admin is valid
    {
       //check if new user deleted successfully
        if(_DataBase.deleteUser(parts[2]))
        {
            QString str=QString("Congratulation user '%1'\n"
                                    "........has been deleted ^_^").arg(parts[2]);
            server_SendMessage(str);
        }
        else    //in case the new user not deleted from data base file
        {
            QString str=QString("Sadly user '%1'\n"
                                    "........failed to be deleted @_@").arg(parts[2]);
            server_SendMessage(str);
        }
    }
    else   // in case not valid admin
    {
        server_SendMessage("You don't have the authority for this or \n"
                           "the account number doesn't exsist..... *_*");
    }
    qDebug() << "This user is on the thread >> "<<_user_name;
    qDebug()<<"\n";
}


/******************function to handle update user request******************/
void MyThreadClass::updateUser(QStringList parts)
{
    //some flags to check validation of request
    bool flag1=false,flag2=false;

    //initialize vector with dataBase vector
    QVector<QJsonObject> dataBase(_DataBase.get_DataBase());

    for(auto obj:dataBase) //loop on every line in the file using vector
    {
        if((obj["usr"].toString() == parts[1]) && (obj["log"].toString() == "1")
            && (obj["auth"].toString() == "admin")) //check if admin is valid
        {
            flag1=true;
        }
        if(obj["acc"].toString() == parts[2])   //check if account number of user is exsist
        {
            flag2=true;
        }
    }

    if(flag1==true && flag2==true) //check if admin is valid one
    {
        //check if new user updated successfully
        if(_DataBase.update_DataBase(parts[2],parts[3],parts[4],parts[5],parts[6]))
        {
            QString str=QString("Congratulation user '%1'\n"
                                    "........has been updated ^_^").arg(parts[2]);
            server_SendMessage(str);
        }
        else    //in case the new user not updated on data base file
        {
            QString str=QString("Sadly user '%1'\n"
                                    "........failed to be updated @_@").arg(parts[2]);
            server_SendMessage(str);
        }
    }
    else  // in case not valid admin
    {
        server_SendMessage("You don't have the authority for this or \n"
                           "the account number doesn't exsist..... *_*");
    }
    qDebug() << "This user is on the thread >> "<<_user_name;
    qDebug()<<"\n";
}


/*****************function to handle transfer money request*********************/
void MyThreadClass::Transfer(QStringList parts)
{
    //some flags to check validation of request
    bool flag1=false,flag2=false;
    //balance of owner
    QString amount_InFrom;
    //balance of the other person
    QString amount_InTo;
    QString email;
    //initialize vector with dataBase vector
    QVector<QJsonObject> dataBase(_DataBase.get_DataBase());

    for(auto obj:dataBase) //loop on every line in the file using vector
    {
        if((obj["acc"].toString() == parts[1]) && (obj["log"].toString() == "1")
            && (obj["auth"] == "user"))                 //check if the owner is valid
        {
            flag1=true;
            amount_InFrom=obj["bal"].toString();
            email=obj["email"].toString();
        }
        if(obj["acc"].toString() == parts[2])   //check if the other person  is valid
        {
            flag2=true;
            amount_InTo=obj["bal"].toString();
        }
    }

    //check if money transfered and file updated successfully
    if(flag1==true && flag2==true)
    {
        if((_DataBase.moneyTransfer(parts[1],parts[2],amount_InFrom,amount_InTo,parts[3])))
        {
            QString str=QString("Transfer amount of money %1 from %2 to %3\n"
                                  "...........use it well @_@............").arg(parts[3]).arg(parts[1]).arg(parts[2]);
            server_SendMessage(str);
            /*python->start("python3", QStringList() << "/home/mohanad/send_email.py" << email << str);
            if(python->waitForFinished())
            {
                QString output=python->readAllStandardOutput();
                QString outputError=python->readAllStandardError();
                qDebug()<<output;
                qDebug()<<outputError;
            }
            else
            {
                qDebug()<<"Can't send email";
            }*/
        }
        else //in case any error occured in the process
        {
            QString str=QString(" Failed to Transfer amount of money %1 from %2 to %3\n"
                                  "...........hard luck next time@_@............").arg(parts[3]).arg(parts[1]).arg(parts[2]);
            server_SendMessage(str);
        }
    }
    else //invalid account numbers
    {
        server_SendMessage("You don't have the authority for this or \n"
                           "the account number doesn't exsist..... *_*");

    }
    qDebug() << "This user is on the thread >> "<<_user_name;
    qDebug()<<"\n";
}

/****************function to handle withdraw request*******************/
void MyThreadClass::Transaction_WithDraw(QStringList parts )
{
    //some flags to check validation of request
    bool flag1=false;
    //the owner money
    QString Owner_Money;
    QString email;
    //initialize vector with dataBase vector
    QVector<QJsonObject> dataBase(_DataBase.get_DataBase());
    for(auto obj:dataBase) //loop on every line in the file using vector
    {
        if((obj["acc"].toString() == parts[1]) && (obj["log"].toString() == "1")
            && (obj["auth"] == "user")) //the owner is valid
        {
            flag1=true;
            Owner_Money=obj["bal"].toString();
            email=obj["email"].toString();
        }
    }
    if(flag1==true)
    {
        //check if user withdraw and file updated successfully
        if(_DataBase.moneyTransaction_WithDraw(parts[1],Owner_Money,parts[2]))
        {
            QString str=QString("Withdraw amount of money %1 from %2\n"
                                    "...........use it well @_@............").arg(parts[2]).arg(parts[1]);
            server_SendMessage(str);
            /*python->start("python3", QStringList() << "/home/mohanad/send_email.py" << email << str);
            if(python->waitForFinished())
            {
                QString output=python->readAllStandardOutput();
                QString outputError=python->readAllStandardError();
                qDebug()<<output;
                qDebug()<<outputError;
            }
            else
            {
                qDebug()<<"Can't send email";
            }*/
        }
        else    //check if user couldn't withdraw or file not updated successfully
        {
            QString str=QString("Failed to withdraw amount of money %1 from %2\n"
                                    "...........hard luck next try @_@............").arg(parts[2]).arg(parts[1]);
            server_SendMessage(str);
        }
    }
    else//in case user not login
    {
        server_SendMessage("You are not login or invalid account number\n"
                           "or you don't have authority for this......... *_*");
    }
    qDebug() << "This user is on the thread >> "<<_user_name;
    qDebug()<<"\n";
}

/****************function to handle deposite request*******************/
void MyThreadClass::Transaction_Deposite(QStringList parts)
{
    //some flags to check validation of request
    bool flag1=false;
    //the owner money
    QString Owner_Money;
    QString email;
    //initialize vector with dataBase vector
    QVector<QJsonObject> dataBase(_DataBase.get_DataBase());
    for(auto obj:dataBase) //loop on every line in the file using vector
    {
        if((obj["acc"].toString() == parts[1]) && (obj["log"].toString() == "1")
            && (obj["auth"] == "user")) //the owner is valid
        {
            flag1=true;
            Owner_Money=obj["bal"].toString();
            email=obj["email"].toString();
        }
    }
    if(flag1==true)  //In case user is valid
    {
        //check if user withdraw and file updated successfully
        if(_DataBase.moneyTransactionPut(parts[1],Owner_Money,parts[2]))
        {
            QString str=QString("Deposit amount of money %1 to %2\n"
                                  "...........Keep investing in our bank @_@............").arg(parts[2]).arg(parts[1]);
            server_SendMessage(str);
            //to use this feature adjust path to send_email.py
            /*python->start("python3", QStringList() << "/home/mohanad/send_email.py" << email << str);
            if(python->waitForFinished())
            {
                QString output=python->readAllStandardOutput();
                QString outputError=python->readAllStandardError();
                qDebug()<<output;
                qDebug()<<outputError;
            }
            else
            {
                qDebug()<<"Can't send email";
            }*/
        }
        else    //check if user couldn't withdraw or file not updated successfully
        {
            QString str=QString("Failed to Deposit amount of money %1 to %2\n"
                                  "...........hard luck next try @_@............").arg(parts[2]).arg(parts[1]);
            server_SendMessage(str);
        }
    }
    else//in case user not login
    {
        server_SendMessage("You are not login or invalid account number\n"
                           "or you don't have authority for this......... *_*");
    }
    qDebug() << "This user is on the thread >> "<<_user_name;
    qDebug()<<"\n";
}

/****************Function to handle transaction data base history request**********/
void MyThreadClass::getTransaction_DataBase(QStringList parts)
{
    //some flags to check validation of request
    bool flag1=false;

    //update the vector with Transaction_DataBase
    QVector<QJsonObject> dataBaseTrans(_DataBase.get_Transaction_DataBase());
    for(auto obj:dataBaseTrans) //loop on every object in the file using vector
    {
        if(obj["acc"].toString() == parts[1]) //the owner is valid
        {
            flag1=true;
            QJsonArray transactions = obj["transactions"].toArray(); //extract QJsonArray

            for (int i = 0; i < transactions.size() / 2; ++i)   //here i reverse QJsonArray before handling it
            {
                QJsonValue temp = transactions[i];
                transactions[i] = transactions[transactions.size() - 1 - i];
                transactions[transactions.size() - 1 - i] = temp;
            }
            QJsonDocument jsonDoc(transactions); //to make the QJsonArray readable
            QString jsonString = QString::fromUtf8(jsonDoc.toJson()); //this line to convert QJsonDocument to QString
            server_SendMessage(jsonString);
            break;
        }
    }
    if(flag1==false)    //in case not log in
    {
        server_SendMessage("Invalid account number try again...... *_*");
    }
    qDebug() << "This user is on the thread >> "<<_user_name;
    qDebug()<<"\n";
}

/********************Slot to handle client disconnection**************/
void MyThreadClass::on_clientDisconnected()
{
    QString temp=_socketList.first+" Disconnected....";
    qout<<temp<<" his username was >> "<<_user_name<<Qt::endl;
}

/****Function to handle data base in case server crashed********/
void MyThreadClass::signal_helper()
{
    QVector<QJsonObject> dataBase(_DataBase.get_DataBase());

    for(auto obj:dataBase) //loop on every object in the file using vector
    {
        QString user=obj["usr"].toString();
        _DataBase.set_Login(user,"off");
    }
}

