#pragma once

#include <QWidget>

#include "ui_a429parser.h"

class A429Parser : public QWidget, public Ui::A429Parser
{
   Q_OBJECT
public:
   A429Parser(QWidget* parent = Q_NULLPTR);
   ~A429Parser();

};