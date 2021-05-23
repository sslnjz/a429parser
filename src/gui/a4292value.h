#pragma once

#include <QWidget>

#include "ui_a4292value.h"

class A4292ValueData;
class A4292Value: public QWidget, public Ui::A4292Value
{
   Q_OBJECT
public:
   A4292Value(QWidget* parent = Q_NULLPTR);
   ~A4292Value();

protected:
   virtual void timerEvent(QTimerEvent* event) override;


private:
   A4292ValueData* d;
};
