# TM5 控制專案
此專案旨在透過基於 Qt 的圖形介面來控制達明機器人 TM5。專案整合了 ROS 指令以管理機器人的動作，並包含選擇檔案、運行 ROS 節點和控制 TM5 機器人移動的功能。

## 專案結構
data/：包含與專案相關的數據檔案，如配置或已保存的狀態。

ui/：存放與 Qt 介面相關的檔案。

code/：專案的核心程式碼，包括機器人控制邏輯和 UI 互動。

    main.cpp：程式的主入口，負責初始化應用程式。

    mainwindow.cpp：定義主視窗的行為和邏輯。

    file_selector_widget.cpp：用於檔案選擇的介面部件。

    ros_commands/：包含與 ROS 指令相關的程式碼和腳本,以python編寫。

    header/：存放專案所需的標頭檔案。

    class/：專案中使用的類別定義。

    moc/：由 Qt 自動生成的編譯文件。

.vscode/：VSCode 的配置文件，包含開發環境設置。

log/：存放專案的日誌檔案。

.git/：Git 版本控制的相關資料。

# 安裝與使用
先決條件
>Ubuntu 20.04 或更高版本  
>ROS Noetic  
>Qt 5 開發環境

達明機器人 TM5 的相關套件  

安裝步驟:
---
複製此專案到本地端：

`git clone https://github.com/kevin00156/tm5-control-new.git`

編譯專案：  
請使用vscode，檔案中已配置好tasks.json，請根據qt的安裝路徑進行修改

執行專案：

`./tm5-control-new`
功能

控制達明機器人 TM5 的基本動作。  
ROS 節點控制及管理。  
透過圖形介面選擇檔案及控制機器人行為。



開發者  
開發者名稱：kevin  
聯絡方式：qazsskevin@gmail.com
