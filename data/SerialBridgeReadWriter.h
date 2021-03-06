//
// Created by chang on 2020-03-21.
//

#ifndef TOOLS_SERIALBRIDGEREADWRITER_H
#define TOOLS_SERIALBRIDGEREADWRITER_H


#include "AbstractReadWriter.h"
#include "SerialReadWriter.h"

class SerialBridgeReadWriter : public AbstractReadWriter {
Q_OBJECT
public:
    explicit SerialBridgeReadWriter(QObject *parent = nullptr);

    void setSettings(SerialSettings serialSettings1, SerialSettings serialSettings2);

    QString settingsText() const override;

    bool open() override;

    bool isOpen() override;

    bool isConnected() override ;

    void close() override;

    QByteArray readAll() override;

    qint64 write(const QByteArray &byteArray) const override;


signals:

    bool serial1DataRead(const QByteArray &byteArray);

    bool serial2DataRead(const QByteArray &byteArray);

private:
    SerialReadWriter *_serialReadWriter1;
    SerialReadWriter *_serialReadWriter2;
};


#endif //TOOLS_SERIALBRIDGEREADWRITER_H
