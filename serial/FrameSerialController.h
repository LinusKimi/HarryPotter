//
// Created by chang on 2020-03-21.
//

#ifndef TOOLS_FRAMESERIALCONTROLLER_H
#define TOOLS_FRAMESERIALCONTROLLER_H

#include "FrameInfoDialog.h"
#include "SerialController.h"


class FrameSerialController : public SerialController{
Q_OBJECT
public:
    explicit FrameSerialController();
    explicit FrameSerialController(SerialController *serialController);
    QByteArray getNextFrame() override;

    MainWindow::SendType sendType() override;

    int getTotalCount() override;

    void setFrameInfo(const FrameInfo &frameInfo);

private:
    FrameInfo *_frameInfo;
    int _lastIndex = 0;
};


#endif //TOOLS_FRAMESERIALCONTROLLER_H
