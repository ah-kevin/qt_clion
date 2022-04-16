//
// Created by bjke on 2022/4/16.
//

#ifndef QT_CLION_RECEIVER_H
#define QT_CLION_RECEIVER_H


#include <QObject>

class Receiver : public QObject {
Q_OBJECT
public:
    explicit Receiver(QObject *parent = nullptr);

    // 自定义槽
public slots:
    void handleExit();
};
#endif //QT_CLION_RECEIVER_H
