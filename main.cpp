#include "MainWindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QFile qss("dark_orange.qss");
    qss.open(QFile::ReadOnly);
    QString style = QLatin1String(qss.readAll());
    a.setStyleSheet(style);
    qss.close();

    MainWindow w;
    w.show();
    return a.exec();
}