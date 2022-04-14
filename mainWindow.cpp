//
// Created by bjke on 2022/4/14.
//

#include "mainWindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui_MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
}