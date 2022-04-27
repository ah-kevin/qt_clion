//
// Created by bjke on 2022/4/27.
//

#include <QtCore/qthread.h>

#ifndef QT_CLION_PLAYTHREAD_H
#define QT_CLION_PLAYTHREAD_H

#endif //QT_CLION_PLAYTHREAD_H

class PlayThread : public QThread {
    Q_OBJECT
private:
    void run() override;
public:
    explicit PlayThread(QObject *parent = nullptr);
    ~PlayThread() override;
//    void setStop(bool stop);
    signals:

};