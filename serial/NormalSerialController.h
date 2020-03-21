//
// Created by chang on 2020-03-21.
//

#ifndef TOOLS_NORMALSERIALCONTROLLER_H
#define TOOLS_NORMALSERIALCONTROLLER_H


#include "SerialController.h"

class NormalSerialController: public SerialController {
   Q_OBJECT
public:
    explicit NormalSerialController();
    explicit NormalSerialController(SerialController *serialController);

    QByteArray getNextFrame() override;

    MainWindow::SendType sendType() override;

    int getTotalCount() override;
};


#endif //TOOLS_NORMALSERIALCONTROLLER_H
