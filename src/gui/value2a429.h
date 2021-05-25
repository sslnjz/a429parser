#pragma once

#include <QWidget>

#include "ui_value2a429.h"

class Value2A429Private;
class Value2A429 : public QWidget, public Ui::Value2A429
{
   Q_OBJECT
public:
   Value2A429(QWidget* parent = Q_NULLPTR);
   ~Value2A429();

protected:
   void timerEvent(QTimerEvent* event) override;

public slots:
   void decode();

private:
   const QScopedPointer<Value2A429Private> d_ptr;
   Q_DECLARE_PRIVATE(Value2A429);
};