#ifndef FILE_SELECTOR_WIDGET_H
#define FILE_SELECTOR_WIDGET_H

#include <QWidget>
#include <QString>
namespace Ui {
class file_selector_widget;
}

class file_selector_widget : public QWidget
{
    Q_OBJECT

public:
    explicit file_selector_widget(QWidget *parent = nullptr);
    ~file_selector_widget();
    QString getPath(); 

private slots:
    void on_buttonFileSelector_clicked();


private:
    Ui::file_selector_widget *ui;
};

#endif // FILE_SELECTOR_WIDGET_H
