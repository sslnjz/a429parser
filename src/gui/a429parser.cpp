#include "a429parser.h"
#include "a4292value.h"
#include "value2a429.h"
#include "a4292valuebatch.h"

#include <qmessagebox.h>

A429Parser::A429Parser(QWidget* parent)
   : QWidget(parent)
{
   setupUi(this);
   gridLayoutA4292Value->addWidget(new A4292Value(this));
   gridLayoutValue2A429->addWidget(new Value2A429(this));
   gridLayoutA4292ValueBatch->addWidget(new A4292ValueBatch(this));

   tabWidget->setCurrentIndex(0);
}

A429Parser::~A429Parser()
{

}

void A429Parser::message(int level, const QString& title, const QString& desc)
{
   switch (level)
   {
   case 0:
      QMessageBox::question(this, title, desc);
      break;
   case 1:
      QMessageBox::information(this, title, desc);
      break;
   case 2:
      QMessageBox::warning(this, title, desc);
      break;
   case 3:
      QMessageBox::critical(this, title, desc);
      break;
   default:
      break;
   }
}
