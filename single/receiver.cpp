//
// Created by bjke on 2022/4/16.
//

#include "receiver.h"
#include "QDebug"
Receiver::Receiver(QObject *parent) : QObject(parent) {

}

// 实现槽函数，编写处理信号的代码
void Receiver::handleExit() {
        qDebug() << "Receiver::handleExit";
}
