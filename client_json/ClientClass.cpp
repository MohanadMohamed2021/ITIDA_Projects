#include "ClientClass.h"
#include "qtextensions.h"
#define MAX_TRIALS 3
#define PORT 12345
#define KEY "Key"
#define SIGNATURE "Signature"

ClientClass::ClientClass(QObject *parent):
    QObject(parent),qin(stdin),qout(stdout),login_flag(false),trials(0),_port(PORT)
{
    //intialize the socket
    _socket = new QTcpSocket(this);

    //********Stablish the network connections with my slots
    connect(_socket,&QTcpSocket::disconnected,this,&ClientClass::onDevice_Disconnected);
    connect(_socket,&QTcpSocket::errorOccurred,this,&ClientClass::onDevice_ErrorOccurred);
    connect(_socket,&QTcpSocket::stateChanged,this,&ClientClass::onDevice_StateChanged);
    connect(_socket,&QTcpSocket::readyRead,this,&ClientClass::onDevice_DataReady);

    //Scan Ip and Port to listen to
    qout<<"enter IP"<<Qt::endl;
    _ip=qin.readLine().trimmed();
    //Connect the socket with the scanned ip & port
    _socket->connectToHost(_ip,_port);

    //wait for connection to stablish with server
    if(_socket->waitForConnected())
    {
        // If client connected to server this message appears
        qDebug() << "---------------------------\n"
                    "|| Client Connected ||\n"
                    "---------------------------";
    }
    else  //in case timeout
    {
        qDebug() << ">> Couldn't connect to Server: " << _socket->errorString();
        exit(EXIT_FAILURE);
    }
}

/**************Slot to handle the comming respond from server**************/
//"jsonSize:84;{\"data\":\"usrpass:mohanad:1234\",\"fileName\":\"null\",\"fileSize\":20,\"fileType\":\"message\"}"
void ClientClass::onDevice_DataReady()
{
    if (_socket->isOpen())
    {
        // Read the available data from the socket
        QByteArray encryptMessage = _socket->readAll();
        QString dataString=decryptMessage(encryptMessage,KEY);

        // Ensure that there is some data to process
        if (!dataString.isEmpty())
        {
            // Extract the JSON size from the header
            qint32 jsonSize = dataString.split(":")[1].split(";")[0].toInt();

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
                    int fileSize = jsonObject.value("fileSize").toInt();
                    QString message = jsonObject.value("data").toString();

                    if(fileSize == message.size())
                    {
                        // Print the message
                        qout << "Received message: " << message << Qt::endl;

                        // Proceed to the messageHandler to forward the message
                        messageHandler(message);
                    }
                    else
                    {
                        qout << "Incomplete data received. Waiting for more." << Qt::endl;
                    }
                }
                else
                {
                    // Failed to parse JSON
                    qout << "Failed to parse JSON. Invalid JSON format." << Qt::endl;
                }
            }
            else
            {
                // Incomplete data, wait for more
                qout << "Incomplete data received. Waiting for more." << Qt::endl;
            }
        }
        else
        {
            // No data received
            qout << "No data received." << Qt::endl;
        }
    }
    else
    {
        qout << "Socket is not open..............." << Qt::endl;
    }
}

/*************Algorithm to decrypt data**********/
QString ClientClass::decryptMessage(const QString &encryptedMessage, const QString &key)
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

/***************Function to handle and forward the comming message***********/
void ClientClass::messageHandler(QString message)
{
    // I will enter ths case when i logout from exsisting session
    if(message.contains("logged out successfully"))
    {
        login_flag=false;   //Reset the flag to make sure if wrong login happens i will try again

        qout<<"\nenter 'login' to login again.....\n"
                "enter anything else to close the application\n"<<Qt::endl;
        qout << "\n >>";
        qout.flush();
        QString choice=qin.readLine().trimmed();
        if(choice=="login")
        {
            login();
        }
        else
        {
            socketDisconnect();
            exit(0);
        }
    }
    // This case will happens after successful login
    else if((message.contains("logged in successfully")) || (login_flag==true))
    {
        login_flag=true; //Flag to make sure i will enter session after every other request
        trials=0;       //Reset numbers of trials
        qout << "\n >>";
        qout.flush();
        operations();   //Proceed to the session
    }
    //This case to make user login before enter the session
    else
    {
        qout<<"\nenter 'login' to login to your account.....\n"
                "enter anything else to close the application\n"<<Qt::endl;
        qout << "\n >>";
        qout.flush();
        QString choice=qin.readLine().trimmed();

        //Giving user choice to login or close programme
        if(choice=="login")
        {
            trials++;
            //Put limit to login trials
            if(trials==MAX_TRIALS)
            {
                qout<<"You have excceded max number of trials........."<<Qt::endl;
                exit(0);
            }
            login();
        }
        else
        {
            socketDisconnect();
            exit(0);
        }
    }

}

/***************Function to handle desired operation*************/
void ClientClass::operations()
{
    QString choice;
    choice=qin.readLine().trimmed();
    /*****************EXIT the system**************/
    if(choice=="exit")
    {
        qout<<"Please logout first to be able to exit.........\n"
                "the following is the system commands\n"<<Qt::endl;
        sendMessage("help");

    }
    /*****************Send login Request**************/
    else if(choice=="login")
    {
        qout<<"Please logout first to be able to login.........\n"
                "the following is the system commands\n"<<Qt::endl;
        sendMessage("help");
    }
    /*****************Send logout Request**************/
    else if(choice=="logout")
    {
        logout();
    }
    /*****************Send Request to fetch account number**************/
    else if(choice=="acc")
    {
        getAccountNumber();
    }
    /***********Send Request to fetch account number with admin help*******/
    else if(choice=="aacc")
    {
        getAccountNumber_Admin();
    }
    /*****************Send Request to fetch balance**************/
    else if(choice=="bal")
    {
        getAccountBalane();
    }
    /*****************Send Request to fetch Data_Base**************/
    else if(choice=="data")
    {
        getBankData();
    }
    /*****************Send Request to add User**************/
    else if(choice=="add")
    {
        addNewUser();
    }
    /****************send request to delete user*****************/
    else if(choice=="del")
    {
        deleteUser();
    }
    /****************send request to update user*****************/
    else if(choice=="update")
    {
        updateUser();
    }
    /****************send request transfer money*****************/
    else if(choice=="transfer")
    {
        moneyTransfer();
    }
    /****************send request to withdraw money*****************/
    else if(choice=="withdraw")
    {
        moneyWithdraw();
    }
    /****************send request to deposite money*****************/
    else if(choice=="deposit")
    {
        moneyDeposit();
    }
    /**********send request to get transaction history*************/
    else if(choice=="history")
    {
        moneyTransHistory();
    }
    /***********Function to clear terminal***************/
    else if(choice=="clear")
    {
        clearTerminal();
    }
    /*****************Send Request to fetch system commands**************/
    else if(choice=="help")
    {
        sendMessage("help");

    }
    /*****************Invalid command**************/
    else
    {
        //qout<<"Invalid input enter 'help' to print list of command...*_*"<<Qt::endl;
        sendMessage("invalid");

    }
}

/*******Function to send login request**************/
void ClientClass::login()
{
    /*********scan username and passward then append it to the header************/
    qout<<"Enter your name"<<Qt::endl;
    _user_name=qin.readLine().trimmed();
    qout<<"Enter your passward"<<Qt::endl;
    QString passward=qin.readLine().trimmed();
    QString message = QString("usrpass:%1:%2").arg(_user_name).arg(passward);

    sendMessage(message);
}

/********Function to handle logout request**************/
void ClientClass::logout()
{
    /*********scan username then append it to the header************/
    QString message = QString("logout:%1").arg(_user_name);
    sendMessage(message);
}

/********Function to send request to get account number********/
void ClientClass::getAccountNumber()
{
    /*********scan username then append it to the header************/
    QString message = QString("acc:%1").arg(_user_name);
    sendMessage(message);
}

/********Function to send request to get account number with admin help********/
void ClientClass::getAccountNumber_Admin()
{
    qout<<"Enter username"<<Qt::endl;
    QString username=qin.readLine().trimmed();
    QString message = QString("aacc:%1:%2").arg(_user_name).arg(username);

    sendMessage(message);
}

/*************Function to request to get account balance***********/
void ClientClass::getAccountBalane()
{
    /*********scan user account number then append it to the header************/
    qout<<"Enter Account_Number"<<Qt::endl;
    QString Account_Number=qin.readLine().trimmed();
    QString message = QString("bal:%1").arg(Account_Number);

    sendMessage(message);
}

/*************Function to send request to ger bank data***********/
void ClientClass::getBankData()
{
    QString message = QString("data:%1").arg(_user_name);
    sendMessage(message);
}

/*************Function to send request to add new member***********/
void ClientClass::addNewUser()
{
    //scan admin name and data to add for new member

    qout<<"Enter username to add"<<Qt::endl;

    QString username=qin.readLine().trimmed();

    qout<<"Enter passward"<<Qt::endl;

    QString passward=qin.readLine().trimmed();

    qout<<"Enter enter full name"<<Qt::endl;

    QString full_name=qin.readLine().trimmed();

    qout<<"Enter user age"<<Qt::endl;

    QString age=qin.readLine().trimmed();

    QString message = QString("add:%1:%2:%3:%4:%5").arg(_user_name).arg(username).arg(passward).arg(full_name).arg(age);

    sendMessage(message);
}

/*************Function to send request to delete member******************/
void ClientClass::deleteUser()
{
    //scan admin name and account number of the user to erase
    qout<<"Enter account number of user you want to delete"<<Qt::endl;
    QString account_number=qin.readLine().trimmed();

    QString message = QString("del:%1:%2").arg(_user_name).arg(account_number);

    sendMessage(message);
}

/***********Function to send request to update user data************/
void ClientClass::updateUser()
{
    //scan admin name and data of user

    qout<<"Enter original account number of user"<<Qt::endl;
    QString account_number=qin.readLine().trimmed();

    qout<<"Enter user to update"<<Qt::endl;
    QString user_name=qin.readLine().trimmed();

    qout<<"Enter new passward of user"<<Qt::endl;
    QString passward=qin.readLine().trimmed();

    qout<<"Enter new full name of user"<<Qt::endl;
    QString full_name=qin.readLine().trimmed();

    qout<<"Enter new age of user"<<Qt::endl;
    QString age=qin.readLine().trimmed();

    QString message=QString("update:%1:%2:%3:%4:%5:%6").arg(_user_name).arg(account_number)
                          .arg(user_name).arg(passward).arg(full_name).arg(age);
    sendMessage(message);
}

/**************Function to send request to transfer money*************/
void ClientClass::moneyTransfer()
{
    //scan some data to handle request

    qout<<"Enter your account number"<<Qt::endl;
    QString myAccountNumber=qin.readLine().trimmed();

    qout<<"Enter account number of user you want to transfer to"<<Qt::endl;
    QString hisAccountNumber=qin.readLine().trimmed();

    qout<<"Enter amount of money to transfer"<<Qt::endl;
    QString amount=qin.readLine().trimmed();

    QString message = QString("transfer:%1:%2:%3").arg(myAccountNumber).arg(hisAccountNumber).arg(amount);

    sendMessage(message);
}

/**************Function to send request to withdraw money*************/
void ClientClass::moneyWithdraw()
{
    //scan some data to handle request

    qout<<"Enter your account number"<<Qt::endl;
    QString myAccountNumber=qin.readLine().trimmed();

    qout<<"Enter amount of money to withdraw"<<Qt::endl;
    QString amount=qin.readLine().trimmed();

    QString message = QString("withdraw:%1:%2").arg(myAccountNumber).arg(amount);

    sendMessage(message);
}

/**************Function to send request to deposite money*************/
void ClientClass::moneyDeposit()
{
    //scan some data to handle request

    qout<<"Enter your account number"<<Qt::endl;
    QString myAccountNumber=qin.readLine().trimmed();

    qout<<"Enter amount of money to deposite"<<Qt::endl;
    QString amount=qin.readLine().trimmed();

    QString message = QString("deposit:%1:%2").arg(myAccountNumber).arg(amount);

    sendMessage(message);
}

/**************Function to send request to deposite money*************/
void ClientClass::moneyTransHistory()
{
    //scan some data to handle request

    qout<<"Enter your account number"<<Qt::endl;
    QString myAccountNumber=qin.readLine().trimmed();

    QString message = QString("history:%1").arg(myAccountNumber);

    sendMessage(message);
}

/***********Slot to handle if device disconnected************/
void ClientClass::onDevice_Disconnected()
{
    qout << "Disconnect from device" << Qt::endl;
    exit(0);
}

/********************Slot to handle when error take place************/
void ClientClass::onDevice_ErrorOccurred(QAbstractSocket::SocketError error)
{
    /*****************next lines convert error enum into string****************/
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketError>();
    qout<< "Error occurred: " << metaEnum.valueToKey(error) << Qt::endl;
}

/*******************Slot to handle any change of the connection state***************/
void ClientClass::onDevice_StateChanged(QAbstractSocket::SocketState state)
{
    /*********************in case state==UnconnectedState close socket**************/
    if(state == QAbstractSocket::SocketState::UnconnectedState)
    {
        _socket->close();
    }
    /****************next lines convert state enum into string***********/
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    qout << "Socket state changed: " << metaEnum.valueToKey(state) << Qt::endl;
}

/*****************Function to send requests**************/
void ClientClass::sendMessage(const QString &str)
{
    if (_socket->isOpen())
    {
        // Create a JSON object with your data
        QJsonObject jsonObject;
        jsonObject["fileType"] = "message";
        jsonObject["fileName"] = "null";
        jsonObject["fileSize"] = str.size();
        jsonObject["data"] = str;

        // Convert the JSON object to a QByteArray
        QByteArray jsonByteArray = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact);

        // Prepend the size of the JSON data as a header
        QByteArray header;
        header.prepend(QString("jsonSize:%1;").arg(jsonByteArray.size()).toUtf8());

        //Create signature to verify i am worthy person
        QByteArray hashed = QCryptographicHash::hash(SIGNATURE, QCryptographicHash::Sha256);
        QByteArray signature = hashed.toHex()+"/";

        // Combine header and JSON data
        QByteArray byteArray = signature + header + jsonByteArray;
        //Algorithm to encrypt data
        QString encryptedMessage=encryptMessage(byteArray,KEY);
        // Send the data over the socket
        _socket->write(encryptedMessage.toUtf8());
    }
    else
    {
        qDebug() << ">> Socket could not be opened!";
    }
}
/*****************Algorithm to encrypt data*************/
QString ClientClass::encryptMessage(const QString &message, const QString &key)
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

//Function to break connection when needed
void ClientClass::socketDisconnect()
{
    _socket->close();
}

//function to clear terminal
void ClientClass::clearTerminal()
{
    system("clear");
    sendMessage("clear");
}











