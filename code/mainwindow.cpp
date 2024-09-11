#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "header/checkRobotConnection.cpp"
#include "header/loadAndSaveFunction.cpp"
#include "header/generateLogFileName.cpp"
#include "class/slotLogger.cpp"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

#define LOG_FUNCTION() spdlog::info("{} triggered", __FUNCTION__);

QSettings settings("NCU", "TM5_Control");



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)   
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 創建並安裝事件過濾器
    //SlotLogger* logger = new SlotLogger(this);
    //qApp->installEventFilter(logger);

    // 創建一個簡單的文件記錄器，日誌將被寫入 logs.txt
    // 動態生成文件名
    std::string logFileName = generateLogFileName();
    // 創建文件記錄器，將日誌寫入基於當前時間命名的文件中
    auto file_logger = spdlog::basic_logger_mt("file_logger", logFileName);

    // 設置 logger 的默認記錄器
    spdlog::set_default_logger(file_logger);
    
    spdlog::info("On mainwindow loading");
    spdlog::flush_on(spdlog::level::info);  // 當記錄到 info 級別時強制刷新
    spdlog::default_logger()->flush();  // 手動刷新當前默認日誌器
    std::cout<<"Initialization";

    // 連接按鈕的 clicked 信號到槽函數  
    //connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    ui->pushButton->setCheckable(false);
    loadWidgetState(this, settings);


    //新增一個label到statusbar中 用以顯示狀態
    messageLabel = new QLabel("檢查連接狀態中...", this);
    statusBar()->addPermanentWidget(messageLabel, 0);
    // 設置定時器
    timerGetSystemStatus = new QTimer(this);
    connect(timerGetSystemStatus, &QTimer::timeout, this, &MainWindow::GetSystemStatus);
    timerGetSystemStatus->start(1000); // 每1000ms執行一次
    refresh_comboBox_PoseSelector();//每次開啟時 刷新一次PoseSelector的表單內容

}

MainWindow::~MainWindow()
{ 
    spdlog::info("On mainwindow disposing");
    saveWidgetState(this, settings);
    delete ui;

}













// 實現槽函數
void MainWindow::GetSystemStatus()
{

    if (checkRobotConnection()) {
        messageLabel->setText("已成功連接 TM5-900");
    } else {
        messageLabel->setText("未能連接到 TM5-900");
    }
}



void MainWindow::on_pushButton_clicked()
{
    LOG_FUNCTION();//對這個函數做LOG

    QProcess* process = new QProcess(this);  // 確保這行代碼已經存在，正確初始化 QProcess 對象
    // 使用 QProcess 在新终端中执行命令
    process->start("gnome-terminal", QStringList() << 
    "--tab" << "--" << "bash" << "-c" << "roscore; exec bash"
    );
    spdlog::info("roscore started");
    if (process->waitForStarted()){
        QThread::sleep(2);//等待2秒
        //啟動roscore後 啟動roslaunch命令 以控制tm5-900
        static QProcess* process_tm5_launch = new QProcess(this);

        // 根據 checkbox 的狀態設置 sim 參數
        
        QString simParam = ui->checkboxLaunchSim->isChecked() ? "sim:=true" : "sim:=false";

        // 獲取用戶輸入的 robot_ip
        QString robotIP = ui->textRobotIP->text().isEmpty() ? "127.0.0.1" : ui->textRobotIP->text();

        // 構建 launchCommand 字串
        QString launchCommand = QString("roslaunch tm5-900-moveit_config tm5-900_moveit_planning_execution.launch %1 robot_ip:=%2")
                                    .arg(simParam)
                                    .arg(robotIP);

        process_tm5_launch->start("gnome-terminal", QStringList() << 
        "--tab" << "--" << "bash" << "-c" << launchCommand + "; exec bash"
        );
    spdlog::info("launchCommand started, {}",launchCommand.toStdString());
    }
}


//控制夾爪夾取的按鈕
void MainWindow::on_buttonSetGripperGrip_clicked()
{
    LOG_FUNCTION();//對這個函數做LOG

    QProcess* process = new QProcess(this);
    // 使用 QProcess 在新终端中执行命令
    process->start("gnome-terminal", QStringList() << 
    "--tab" << "--" << "bash" << "-c" << "python3 ./code/ros_commands/setDO.py on"
    );
    ui->statusbar->showMessage("Gripper grip!");
    spdlog::info("Gripper grip!");


    //process->start("python3", QStringList() << 
    //"./ros_commands/setDO.py on"
    //);
}

//控制夾爪夾取的按鈕
void MainWindow::on_buttonSetGripperRelease_clicked()
{
    LOG_FUNCTION();//對這個函數做LOG

    QProcess* process = new QProcess(this);
    // 使用 QProcess 在新终端中执行命令
    process->start("gnome-terminal", QStringList() << 
    "--tab" << "--" << "bash" << "-c" << "python3 ./code/ros_commands/setDO.py off"
    );
    ui->statusbar->showMessage("Gripper release!");
    spdlog::info("Gripper release!");

    //process->start("python3", QStringList() << 
    //"./ros_commands/setDO.py off"
    //);
}


void MainWindow::on_buttonRecordPose_clicked()
{
    LOG_FUNCTION();//對這個函數做LOG

    QProcess* process = new QProcess(this);

    QString posePath =ui->file_selector_widget_PoseControl->getPath();
    QString poseCommand = QString("python3 ./code/ros_commands/recordPose.py %1").arg(posePath);
    
    if (posePath.isEmpty() || !QFile::exists(posePath))
    {
        QString stringPoseFileNotExist = "Pose file path is not exist!";
        ui->statusbar->showMessage(stringPoseFileNotExist);
        spdlog::warn(stringPoseFileNotExist.toStdString());
        return;
    }

    // 使用 QProcess 执行脚本
    process->start("gnome-terminal", QStringList() << "--tab" << "--" << "bash" << "-c" 
                   << poseCommand);


    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [=](int exitCode, QProcess::ExitStatus exitStatus) {
        if (exitStatus == QProcess::NormalExit && exitCode == 0) {
            ui->statusbar->showMessage("Pose Record!");
            spdlog::info("Pose record in {}",posePath.toStdString());
        } else {
            ui->statusbar->showMessage("Record failed!");
            spdlog::warn("Record failed");
        }
        process->deleteLater();
        refresh_comboBox_PoseSelector();//每次紀錄以後 刷新一次PoseSelector的表單內容
    });

}


void MainWindow::on_buttonReplayAllPoses_clicked()
{
    LOG_FUNCTION();//對這個函數做LOG

    QProcess* process = new QProcess(this);

    QString posePath =ui->file_selector_widget_PoseControl->getPath();
    QString poseCommand = QString("python3 ./code/ros_commands/replayPose.py %1").arg(posePath);
    
    if (posePath.isEmpty() || !QFile::exists(posePath))
    {
        QString stringPoseFileNotExist = "Pose file path is not exist!";
        ui->statusbar->showMessage(stringPoseFileNotExist);
        spdlog::warn(stringPoseFileNotExist.toStdString());
        return;
    }

    // 使用 QProcess 执行脚本
    process->start("gnome-terminal", QStringList() << "--tab" << "--" << "bash" << "-c" 
                   << poseCommand);



}


void MainWindow::refresh_comboBox_PoseSelector()
{
    LOG_FUNCTION();//對這個函數做LOG

    ui->statusbar->showMessage("comboBox_PoseSelector trigged!");
    // 清空 ComboBox
    ui->comboBox_PoseSelector->clear();

    // 獲取 YAML 檔案的路徑
    QString yamlPath = ui->file_selector_widget_PoseControl->getPath();
    if (yamlPath.isEmpty()) {
        QMessageBox::warning(this, "警告", "請選擇 YAML 檔案");
        return;
    }

    // 打開 YAML 檔案
    QFile file(yamlPath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "錯誤", "無法打開 YAML 檔案");
        return;
    }

    // 讀取 YAML 檔案
    try {
        YAML::Node yamlData = YAML::LoadFile(yamlPath.toStdString());

        // 遍歷 YAML 檔案中的點位名稱
        for (auto it = yamlData.begin(); it != yamlData.end(); ++it) {
            std::string pointName = it->first.as<std::string>();
            ui->comboBox_PoseSelector->addItem(QString::fromStdString(pointName)); // 將點位名稱添加到 ComboBox 中
        }
    } catch (const YAML::Exception& e) {
        QMessageBox::warning(this, "錯誤", "YAML 檔案格式錯誤");
    }
}