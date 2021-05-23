#include "a4292value.h"

#include <QRegularExpression>
#include <QRegularExpressionValidator>

class A4292ValueData
{
public:
   A4292ValueData(A4292Value* parent) : parent(parent)
   {

   }

   int timerId;

private:
   A4292Value* parent = Q_NULLPTR;
};

A4292Value::A4292Value(QWidget* parent)
   : QWidget(parent)
   , d(new A4292ValueData(this))
{
   setupUi(this);

   lineEditA429Word->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9 ]+"), this));
   d->timerId = startTimer(100);
}

A4292Value::~A4292Value()
{
}

void A4292Value::timerEvent(QTimerEvent* event)
{
   if (event->timerId() == d->timerId)
   {
      bool isEnabled = !lineEditA429Word->text().isEmpty();
      groupBoxA429Fmt->setEnabled(isEnabled);
      tableViewA429Region->setEnabled(isEnabled);
      pushButtonA429Calc->setEnabled(isEnabled);
   }
   return QWidget::timerEvent(event);
}
