#include "value2a429.h"

class Value2A429Private
{
public:
   Value2A429Private(Value2A429* q) : q_ptr(q) {}

public:
   int timerId;
private:
   Value2A429* const q_ptr;
   Q_DECLARE_PUBLIC(Value2A429)
};

Value2A429::Value2A429(QWidget* parent)
   : QWidget(parent)
   , d_ptr(new Value2A429Private(this))
{
   Q_D(Value2A429);
   setupUi(this);
   d->timerId = startTimer(100);

   connect(pushButtonValueCalc, &QPushButton::clicked, this, &Value2A429::decode);
}

Value2A429::~Value2A429()
{
}

void Value2A429::timerEvent(QTimerEvent* event)
{
   Q_D(Value2A429);
   if (d->timerId == event->timerId())
   {
      bool enabled = !lineEditValueLabel->text().isEmpty();
      frameValueLabelFmt->setEnabled(enabled);
      comboBoxValueSDI->setEnabled(enabled);
      comboBoxValueSSM->setEnabled(enabled);
      tableViewValueRegion->setEnabled(enabled);

      if (tableViewValueRegion->model()->rowCount() < 0 && !enabled)
         pushButtonValueCalc->setEnabled(false);
      else
         pushButtonValueCalc->setEnabled(true);
   }
}

void Value2A429::decode()
{

}
