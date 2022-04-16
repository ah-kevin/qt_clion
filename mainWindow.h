//
// Created by bjke on 2022/4/14.
//

#ifndef QT_CLION_MAINWINDOW_H
#define QT_CLION_MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// MainWindow 继承了QMainWindow
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    struct Ui_MainWindow *ui{};
};
#endif //QT_CLION_MAINWINDOW_H
