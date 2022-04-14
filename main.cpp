#include <QApplication>
#include <QTranslator>
#include "mainWindow.h"

int main(int argc, char *argv[]) {
//    QCoreApplication a(argc, argv);
//    qDebug() << "Hello World";
//    return QCoreApplication::exec();
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("hello world");
    w.show();
    return QApplication::exec();
}