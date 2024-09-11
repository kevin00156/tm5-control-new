#include "file_selector_widget.h"
#include "ui_file_selector_widget.h"

#include <QFileDialog>
#include <QLineEdit>
#include <QString>

file_selector_widget::file_selector_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::file_selector_widget)
{
    ui->setupUi(this);
}

file_selector_widget::~file_selector_widget()
{
    delete ui;
}



QString file_selector_widget::getPath()
{
    return ui->textFilePath->text();
}

void file_selector_widget::on_buttonFileSelector_clicked(){
    // 打開一個文件選擇對話框，只允許選擇 .yaml 文件
    QString filePath = QFileDialog::getOpenFileName(
        this, 
        tr("選擇 YAML 文件"), 
        "", 
        tr("YAML Files (*.yaml)")  // 過濾條件
    );

    // 如果用戶選擇了一個文件，則將其路徑寫入 textFilePath 中
    if (!filePath.isEmpty()) {
        ui->textFilePath->setText(filePath);
    }
}