#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QFile>
#include <QProcess>
#include <QSettings>
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QComboBox>
#include <yaml-cpp/yaml.h>
#include <QMessageBox>
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int testCounter = 0;
    void refresh_comboBox_PoseSelector();

private slots:
    void on_pushButton_clicked();  // 添加這一行，聲明槽函數
    void on_buttonSetGripperGrip_clicked();  // 添加這一行，聲明槽函數
    void on_buttonSetGripperRelease_clicked();  // 添加這一行，聲明槽函數
    void GetSystemStatus();//聲明刷新系統狀態用的槽函數
    void on_buttonRecordPose_clicked();  // 添加這一行，聲明槽函數
    void on_buttonReplayAllPoses_clicked();  // 添加這一行，聲明槽函數


private:
    Ui::MainWindow *ui;

    QTimer *timerGetSystemStatus;           // 用於定時執行 ping 的 QTimer
    QLabel *messageLabel;                   // 用於指示目前系統狀態
};

#endif // MAINWINDOW_H
