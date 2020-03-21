//
// Created by chang on 2020-03-21.
//

#ifndef TOOLS_LINESERIALCONTROLLER_H
#define TOOLS_LINESERIALCONTROLLER_H


#include "SerialController.h"

class LineSerialController: public SerialController {
    Q_OBJECT
public:
    explicit LineSerialController();
    explicit LineSerialController(SerialController *serialController);
    QByteArray getNextFrame() override;

    MainWindow::SendType sendType() override;

    int getTotalCount() override;
};


#endif //TOOLS_LINESERIALCONTROLLER_H
