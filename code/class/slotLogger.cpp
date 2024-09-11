// slotLogger.cpp (實現文件)
#include "slotLogger.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

SlotLogger::SlotLogger(QObject* parent) : QObject(parent) {}

bool SlotLogger::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::MetaCall) {
        const QMetaObject* metaObj = obj->metaObject();
        QString functionName = metaObj->className();
        // 使用 spdlog 紀錄槽函數觸發的名稱
        spdlog::info("Function {} triggered", functionName.toStdString());
        spdlog::flush_on(spdlog::level::info);  // 當記錄到 info 級別時強制刷新
        spdlog::default_logger()->flush();  // 手動刷新當前默認日誌器
    }

    return QObject::eventFilter(obj, event);
}
