#include <QLineEdit>
#include <QCheckBox>
#include <QWidget>
#include <QSettings>
#include <QObject>
#include <QProcess>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "header/loadAndSaveFunction.h"

// 檢查 widget 是否包含 QLineEdit 或 QCheckBox
bool hasRelevantChildren(QWidget *widget) {
    for (QObject *child : widget->children()) {
        if (qobject_cast<QLineEdit *>(child) || qobject_cast<QCheckBox *>(child)) {
            return true; // 如果找到符合條件的子元件，返回 true
        }
        if (QWidget *childWidget = qobject_cast<QWidget *>(child)) {
            if (hasRelevantChildren(childWidget)) {
                return true; // 遞迴檢查子元件
            }
        }
    }
    return false; // 沒有符合條件的子元件
}

// 遍歷所有子元件並保存它們的狀態
void saveWidgetState(QWidget *widget, QSettings &settings) {
    if (widget->children().isEmpty() || !hasRelevantChildren(widget)) 
    {
        return;
    }
    spdlog::info("----------save widget state {}----------", widget->objectName().toStdString()); //印出log紀錄
    for (QObject *child : widget->children()) {
        if (QLineEdit *lineEdit = qobject_cast<QLineEdit *>(child)) {
            settings.setValue(lineEdit->objectName(), lineEdit->text());
            spdlog::info("set line_edit : {} = {}", lineEdit->objectName().toStdString(), lineEdit->text().toStdString());
        } else if (QCheckBox *checkBox = qobject_cast<QCheckBox *>(child)) {
            settings.setValue(checkBox->objectName(), checkBox->isChecked());
            spdlog::info("set checkbox : {} = {}", checkBox->objectName().toStdString(), checkBox->isChecked());
        }
        // 遞歸遍歷子元件
        if (QWidget *childWidget = qobject_cast<QWidget *>(child)) {
            saveWidgetState(childWidget, settings);
        }
    }
}

// 遍歷所有子元件並加載它們的狀態
void loadWidgetState(QWidget *widget, QSettings &settings) {
    if (widget->children().isEmpty() || !hasRelevantChildren(widget)) 
    {
        return;
    }
    spdlog::info("----------load widget state {}----------", widget->objectName().toStdString()); //印出log紀錄
    for (QObject *child : widget->children()) {
        if (QLineEdit *lineEdit = qobject_cast<QLineEdit *>(child)) {
            lineEdit->setText(settings.value(lineEdit->objectName(), "").toString());
            spdlog::info("load line_edit : {} = {}", lineEdit->objectName().toStdString(), lineEdit->text().toStdString());
        } else if (QCheckBox *checkBox = qobject_cast<QCheckBox *>(child)) {
            checkBox->setChecked(settings.value(checkBox->objectName(), false).toBool());
            spdlog::info("load checkbox : {} = {}", checkBox->objectName().toStdString(), checkBox->isChecked());
        }
        // 遞歸遍歷子元件
        if (QWidget *childWidget = qobject_cast<QWidget *>(child)) {
            loadWidgetState(childWidget, settings);
        }
    }
}
