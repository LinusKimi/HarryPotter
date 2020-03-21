//
// Created by chang on 2020-03-21.
//

#ifndef TOOLS_CALCULATECHECKSUMDIALOG_H
#define TOOLS_CALCULATECHECKSUMDIALOG_H


#include <QtWidgets/QDialog>

class QLineEdit;

class QLabel;

class QPushButton;

class QCheckBox;

class QComboBox;

class QTextEdit;

class ConvertDataDialog : public QDialog {
Q_OBJECT
public:
    explicit ConvertDataDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());


private:
    void createUi();

    void createConnect();

    QTextEdit *inputTextEdit;
    QTextEdit *resultTextEdit;

    QCheckBox *hexCheckBox;

    QComboBox *fromCodecComboBox;
    QComboBox *toCodecComboBox;

    QPushButton *exchangeCodecButton;

    QPushButton *parseButton;
    QPushButton *convertButton;
};


#endif //TOOLS_CALCULATECHECKSUMDIALOG_H
