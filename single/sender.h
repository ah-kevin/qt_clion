//
// Created by bjke on 2022/4/16.
//

#ifndef QT_CLION_SENDER_H
#define QT_CLION_SENDER_H

#include <QObject>

class Sender : public QObject{
    Q_OBJECT
public:
    explicit Sender(QObject *parent = nullptr);
     // 自定义新号
    signals:
    void exit();
};
#endif //QT_CLION_SENDER_H
