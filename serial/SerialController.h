//
// Created by chang on 2020-03-21.
//

#ifndef TOOLS_SERIALCONTROLLER_H
#define TOOLS_SERIALCONTROLLER_H


#include <QtCore/QObject>
#include <mainwindow.h>

class SerialController : public QObject {
Q_OBJECT
public:

    explicit SerialController();

    explicit SerialController(SerialController *serialController);

    ~SerialController() override;

    void setData(QString data);

    void setIsHex(bool isHex);

    virtual QByteArray getNextFrame() = 0;

    virtual int getTotalCount() = 0;

    int getCurrentCount();

    void setCurrentCount(int count);

    void setAutoSend(bool autoSend);

    void setLoopSend(bool loopSend);

    void setAutoSendInterval(int interval);

    bool isHex();

    bool autoSend();

    bool loopSend();

    int autoSendInterval();

    QByteArray data();

    QStringList dataList();

    virtual MainWindow::SendType sendType() = 0;

protected:
    bool _isHex{false};
    bool _isAutoSend{false};
    bool _isLoopSend{false};
    int _autoSendInterval{1000};

    QByteArray _data;
    QStringList _dataList;

    int _currentCount{0};
};


#endif //TOOLS_SERIALCONTROLLER_H
