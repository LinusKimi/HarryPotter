//
// Created by chang on 2020-03-21.
//

#ifndef TOOLS_ABSTRACTREADWRITER_H
#define TOOLS_ABSTRACTREADWRITER_H


#include <QtCore/QObject>

class AbstractReadWriter : public QObject {
Q_OBJECT
public:
    explicit AbstractReadWriter(QObject *parent = nullptr);

    virtual bool open() = 0;

    virtual bool isOpen() = 0;

    virtual bool isConnected() = 0;

    virtual void close() = 0;

    virtual QByteArray readAll() = 0;

    virtual qint64 write(const QByteArray &byteArray) const = 0;

    virtual QString settingsText() const = 0;

signals:
    void readyRead();
};


#endif //TOOLS_ABSTRACTREADWRITER_H
