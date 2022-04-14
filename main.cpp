#include <QApplication>
#include <QTranslator>
#include "mainWindow.h"
#include "QDebug"
// 纯C语言的
extern "C" {
#include <libavcodec/avcodec.h>
}

int main(int argc, char *argv[]) {
//    QCoreApplication a(argc, argv);
//    qDebug() << "Hello World";
//    return QCoreApplication::exec();
    // 打印版本号
    qDebug() << av_version_info();
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("hello world");
    w.show();
    return QApplication::exec();
}