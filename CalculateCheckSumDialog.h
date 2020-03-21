//
// Created by chang on 2020-03-21.
//

#ifndef TOOLS_CONVERTDATADIALOG_H
#define TOOLS_CONVERTDATADIALOG_H


#include <QtWidgets/QDialog>

class QLineEdit;
class QLabel;
class QPushButton;

class CalculateCheckSumDialog : public QDialog {
    Q_OBJECT
public:
    explicit CalculateCheckSumDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());



private:
    void createUi();
    void createConnect();

    QString getSumResult(const QByteArray &data);
    QString getXorResult(const QByteArray &data);

    QLineEdit *inputLineEdit;

    QPushButton *calculateButton;
    QLabel *xorResultLabel;
    QLabel *sumResultLabel;


};


#endif //TOOLS_CONVERTDATADIALOG_H
