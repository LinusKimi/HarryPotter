//
// Created by chang on 2020-03-21.
//

#ifndef TOOLS_BRIDGEREADWRITER_H
#define TOOLS_BRIDGEREADWRITER_H

class SerialReadWriter;

class TcpServerReadWriter;

#include "AbstractReadWriter.h"
#include "SerialReadWriter.h"

class BridgeReadWriter : public AbstractReadWriter {
Q_OBJECT
public:
    explicit BridgeReadWriter(QObject *parent = nullptr);

    void setSettings(SerialSettings serialSettings, const QString &tcpAddress, qint16 port);

    QString settingsText() const override;

    bool open() override;

    bool isOpen() override;

    bool isConnected() override;

    void close() override;

    QByteArray readAll() override;

    qint64 write(const QByteArray &byteArray) const override;

signals:

    bool serialDataRead(const QByteArray &byteArray);

    bool tcpDataRead(const QByteArray &byteArray);

    void currentSocketChanged(const QString &address, qint16 port);

    void connectionClosed();

private:
    SerialReadWriter *_serialReaderWriter;
    TcpServerReadWriter *_tcpReaderWriter;

};


#endif //TOOLS_BRIDGEREADWRITER_H
