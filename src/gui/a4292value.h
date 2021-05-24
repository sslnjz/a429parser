#pragma once

#include <QWidget>

#include "ui_a4292value.h"

class A4292ValuePrivate;
class A4292Value: public QWidget, public Ui::A4292Value
{
   Q_OBJECT
public:
   A4292Value(QWidget* parent = Q_NULLPTR);
   ~A4292Value();

protected:
   void timerEvent(QTimerEvent* event) override;

private slots:
   void calculate();

private:
   A4292ValuePrivate* d_ptr;
   Q_DECLARE_PRIVATE(A4292Value)
};
