//
// Created by chang on 2020-03-21.
//

#ifndef TOOLS_TCPCLIENTREADWRITER_H
#define TOOLS_TCPCLIENTREADWRITER_H

#include <QTcpSocket>

#include "AbstractReadWriter.h"

class TcpClientReadWriter : public AbstractReadWriter {
Q_OBJECT
public:
    explicit TcpClientReadWriter(QObject *parent = nullptr);

    bool open() override;

    bool isOpen() override;

    bool isConnected() override;

    QString settingsText() const override;

    void setAddress(const QString &address);

    void setPort(int port);

    QByteArray readAll() override;

    qint64 write(const QByteArray &byteArray) const override;

    void close() override;
private:
    QTcpSocket *_tcpSocket{nullptr};
    QString _address{"192.168.1.100"};
    int _port{9000};

};


#endif //TOOLS_TCPCLIENTREADWRITER_H
