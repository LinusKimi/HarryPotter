//
// Created by chang on 2020-03-21.
//

#ifndef TOOLS_FRAMEINFODIALOG_H
#define TOOLS_FRAMEINFODIALOG_H


#include <QtWidgets/QDialog>

class QLineEdit;

class QComboBox;

class QPushButton;

typedef struct {
    QString frame;
    unsigned char head;
    unsigned char end;
    int lenIndex;
    int lenCount;
    int headLen;
    int endLen;
} FrameInfo;


class FrameInfoDialog : public QDialog {
Q_OBJECT
public:
    explicit FrameInfoDialog(const FrameInfo &frameInfo, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

signals:
    void frameInfoChanged(FrameInfo info);

private:
    void createUi();

    void initUiValue(FrameInfo info);

    void createConnect();

    FrameInfo info;

    QLineEdit *frameLineEdit;
    QLineEdit *frameHeadLineEdit;
    QLineEdit *frameEndLineEdit;
    QLineEdit *frameLenIndexLineEdit;
    QComboBox *frameLenCountComboBox;

    QLineEdit *frameHeadLenLineEdit;
    QLineEdit *frameEndLenLineEdit;

    QPushButton *okButton;
    QPushButton *cancelButton;

};


#endif //TOOLS_FRAMEINFODIALOG_H
