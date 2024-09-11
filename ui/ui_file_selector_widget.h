/********************************************************************************
** Form generated from reading UI file 'file_selector_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILE_SELECTOR_WIDGET_H
#define UI_FILE_SELECTOR_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_file_selector_widget
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *textFilePath;
    QToolButton *buttonFileSelector;

    void setupUi(QWidget *file_selector_widget)
    {
        if (file_selector_widget->objectName().isEmpty())
            file_selector_widget->setObjectName(QString::fromUtf8("file_selector_widget"));
        file_selector_widget->resize(200, 30);
        widget = new QWidget(file_selector_widget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 201, 31));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        textFilePath = new QLineEdit(widget);
        textFilePath->setObjectName(QString::fromUtf8("textFilePath"));

        horizontalLayout->addWidget(textFilePath);

        buttonFileSelector = new QToolButton(widget);
        buttonFileSelector->setObjectName(QString::fromUtf8("buttonFileSelector"));

        horizontalLayout->addWidget(buttonFileSelector);


        retranslateUi(file_selector_widget);

        QMetaObject::connectSlotsByName(file_selector_widget);
    } // setupUi

    void retranslateUi(QWidget *file_selector_widget)
    {
        file_selector_widget->setWindowTitle(QApplication::translate("file_selector_widget", "Form", nullptr));
        buttonFileSelector->setText(QApplication::translate("file_selector_widget", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class file_selector_widget: public Ui_file_selector_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILE_SELECTOR_WIDGET_H
