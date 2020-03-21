//
// Created by chang on 2020-03-21.
//

#ifndef TOOLS_FIXEDCOUNTSERIALCONTROLLER_H
#define TOOLS_FIXEDCOUNTSERIALCONTROLLER_H


#include "SerialController.h"

class FixedBytesSerialController: public SerialController {
Q_OBJECT
public:
    explicit FixedBytesSerialController();
    explicit FixedBytesSerialController(SerialController *serialController);
    QByteArray getNextFrame() override;
    MainWindow::SendType sendType() override;

    int getTotalCount() override;

    int setFixedCount(int count);

private:
    int _lastIndex = 0;
    int _count = 128;
};


#endif //TOOLS_FIXEDCOUNTSERIALCONTROLLER_H
