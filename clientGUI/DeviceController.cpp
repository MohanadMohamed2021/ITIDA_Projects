#include "DeviceController.h"

DeviceController::DeviceController(QObject *parent)
    : QObject{parent}
{
    connect(&_socket,&QTcpSocket::connected,this,&DeviceController::connected);
    connect(&_socket,&QTcpSocket::disconnected,this,&DeviceController::disconnected);
    connect(&_socket,&QTcpSocket::errorOccurred,this,&DeviceController::errorOccurred);
    connect(&_socket,&QTcpSocket::stateChanged,this,&DeviceController::socket_stateChanged);
    connect(&_socket,&QTcpSocket::readyRead,this,&DeviceController::socket_readyRead);
}

void DeviceController::connectToDevice(QString ip,qint16 port)
{
    if(_socket.isOpen())
    {
        if(ip==_ip && port==_port)
        {
            return;
        }
        _socket.close();
    }
    _ip = ip;
    _port = port;
    _socket.connectToHost(_ip,_port);
}

void DeviceController::socket_stateChanged(QAbstractSocket::SocketState state)
{
    if(state == QAbstractSocket::SocketState::UnconnectedState)
    {
        _socket.close();
    }
    emit stateChanged(state);
}

QAbstractSocket::SocketState DeviceController::GetState()
{
    return _socket.state();
}
void DeviceController::socketDisconnect()
{
    _socket.close();
}
bool DeviceController::isConnected()
{
    return _socket.state() == QAbstractSocket::SocketState::ConnectedState;
}
void DeviceController::socket_readyRead()
{
    if (_socket.isOpen())
    {
        // Read the available data from the socket
        QByteArray encryptMessage = _socket.readAll();
        QString dataString=decryptMessage(encryptMessage,"Key");

        // Ensure that there is some data to process
        if (!dataString.isEmpty())
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
                    if(fileSize == message.size())
                    {
                        // Proceed to the messageHandler to forward the message
                        messageHandler(message);
                    }
                    else
                    {
                        qDebug() << "Incomplete data received. Waiting for more.";
                    }
                }
                else
                {
                    // Failed to parse JSON
                    qDebug() << "Failed to parse JSON. Invalid JSON format.";
                }
            }
            else
            {
                // Incomplete data, wait for more
                qDebug() << "Incomplete data received. Waiting for more.";
            }
        }
        else
        {
            // No data received
            qDebug() << "No data received.";
        }
    }
    else
    {
        qDebug() << "Socket is not open...............";
    }
}
void DeviceController::messageHandler(QString message)
{
    if(message.contains("logged out successfully"))
    {
        emit dataReady(message.toUtf8(),false,true);
    }
    else if(message.contains("logged in successfully"))
    {
        emit dataReady(message.toUtf8(),true,false);
    }
    else
    {
        emit dataReady(message.toUtf8(),false,false);
    }
}

void DeviceController::socketSendData(QString str)
{
    if (_socket.isOpen())
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

        QByteArray hashed = QCryptographicHash::hash("Signature", QCryptographicHash::Sha256);
        QByteArray signature = hashed.toHex()+"/";

        // Combine header and JSON data
        QByteArray byteArray =signature + header + jsonByteArray;

        QString encryptedMessage=encryptMessage(byteArray,"Key");

        // Send the data over the socket
        _socket.write(encryptedMessage.toUtf8());
    }
    else
    {
        qDebug() << ">> Socket could not be opened!";
    }
}
/*****************Algorithm to encrypt data*************/
QString DeviceController::encryptMessage(const QString &message, const QString &key)
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
/*************Algorithm to decrypt data**********/
QString DeviceController::decryptMessage(const QString &encryptedMessage, const QString &key)
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
