//
// Created by bjke on 2022/4/14.
//

#include "mainWindow.h"
#include "ui_mainwindow.h"
#include "single/sender.h"
#include "single/receiver.h"
#include "audiothread.h"
#include "SDL2/SDL.h"
#include <QFile>
#include "playthread.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui_MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_audioButton_clicked() {
    if (!_audioThread) {
        qDebug() << "开始录音" << QThread::currentThread();
        // 点击了 "开始录音"
        // 开启线程
        _audioThread = new AudioThread(this);
        _audioThread->start();
        connect(_audioThread, &AudioThread::finished, [this]() {
            // 线程结束
            _audioThread = nullptr;
            ui->audioButton->setText("开始录音");
        });
        ui->audioButton->setText("结束录音");
    } else {
        // 结束录音
//        _audioThread->setStop(true);
        _audioThread->requestInterruption();
        _audioThread = nullptr;
        ui->audioButton->setText("开始录音");
    }
}


void MainWindow::on_registerButton_clicked() {
    //    SDL_version version;
    //    SDL_VERSION(&version);
    //    qDebug() <<version.major <<version.minor << version.patch;
    if (_playThread) { // 停止播放
        _playThread->requestInterruption();
        _playThread = nullptr;
        ui->registerButton->setText("开始播放");
    } else { // 开始播放
        _playThread= new PlayThread(this);
        _playThread->start();
        connect(_playThread, &PlayThread::finished, [this]() {
            // 线程结束
            _playThread = nullptr;
            ui->registerButton->setText("开始播放");
        });
        ui->registerButton->setText("停止播放");
    }

}

void MainWindow::slotAndSingle() {
    auto *btn = new QPushButton;
    btn->setText("close");
    btn->setFixedSize(100, 30);
    btn->setParent(this);
//    connect(btn,&QPushButton::clicked,this,&MainWindow::close);
    connect(btn, &QPushButton::clicked, []() {
        qDebug() << "点击了按钮";
    });

    auto *sender = new Sender;
    auto *receiver = new Receiver;
    connect(sender, &Sender::exit, receiver, &Receiver::handleExit);

    // 发出信号
    // 最终会调用Receiver::handleExit函数
    emit sender->exit();

    // 销毁对象
    delete sender;
    delete receiver;
}
