// slotLogger.h (頭文件)
#ifndef SLOTLOGGER_H
#define SLOTLOGGER_H

#include <QObject>
#include <QEvent>
#include <QDebug>

class SlotLogger : public QObject
{
    Q_OBJECT

public:
    SlotLogger(QObject* parent = nullptr);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
};

#endif // SLOTLOGGER_H
