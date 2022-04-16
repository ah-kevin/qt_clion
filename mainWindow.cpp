//
// Created by bjke on 2022/4/14.
//

#include "mainWindow.h"
#include "ui_mainwindow.h"
#include "single/sender.h"
#include "single/receiver.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui_MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
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