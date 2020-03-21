//
// Created by chang on 2020-03-21.
//

#include "NormalSerialController.h"

QByteArray NormalSerialController::getNextFrame() {
    return _data;
}

MainWindow::SendType NormalSerialController::sendType() {
    return MainWindow::SendType ::Normal;
}

NormalSerialController::NormalSerialController():SerialController() {

}

NormalSerialController::NormalSerialController(SerialController *serialController) : SerialController(
        serialController) {

}

int NormalSerialController::getTotalCount() {
    return _dataList.count();
}
