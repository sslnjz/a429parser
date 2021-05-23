#pragma once

#include <QWidget>

#include "ui_a4292valuebatch.h"

class A4292ValueBatch : public QWidget, public Ui::A4292ValueBatch
{
   Q_OBJECT
public:
   A4292ValueBatch(QWidget* parent = Q_NULLPTR);
   ~A4292ValueBatch();
};