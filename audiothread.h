//
// Created by bjke on 2022/4/26.
//

#include <QThread>

#ifndef QT_CLION_AUDIOTHREAD_H
#define QT_CLION_AUDIOTHREAD_H

#endif //QT_CLION_AUDIOTHREAD_H

class AudioThread : public QThread {
    Q_OBJECT
private:
    void run() override;
    bool  _stop{};
public:
    explicit AudioThread(QObject *parent = nullptr);
    ~AudioThread() override;
//    void setStop(bool stop);
signals:

};