#include "value2a429.h"

#include <bitset>

#include "a429bits.h"
#include "utils.h"

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
   lineEditValueLabel->setValidator(new QRegularExpressionValidator(QRegularExpression("^([0-3][0-7]{2})|([0-7]{2})$"), this));

   connect(pushButtonValueCalc, &QPushButton::clicked, this, &Value2A429::decode);
   connect(pushButtonValueClear, &QPushButton::clicked, 
      [&]{
         lineEditValueInt->clear();
         lineEditValueWord->clear();
         lineEditValueParity->clear();
         groupBoxA429->setEnabled(false);
      });
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
   uint32_t dword = 0;
   bool ok = false;
   uint8_t label = static_cast<uint8_t>(lineEditValueLabel->text().toUInt(&ok, 8) & 0xFF);
   if (radioButtonValueArinc->isChecked())
      label = Utils::reverse_8bit(label);

   dword |= label;
   dword |= comboBoxValueSDI->currentText().toUInt() << 8;
   dword |= comboBoxValueSSM->currentText().toUInt() << 29;

   for (size_t i = 0; i < tableViewValueRegion->model()->rowCount(); ++i)
   {
      int lsb = tableViewValueRegion->model()->index(i, 0).data().toUInt();
      int sigbits = tableViewValueRegion->model()->index(i, 1).data().toUInt();
      double lsbres = tableViewValueRegion->model()->index(i, 2).data().toDouble();
      std::string format = tableViewValueRegion->model()->index(i, 3).data().toString().toStdString();

      double value = tableViewValueRegion->model()->index(i, 4).data().toDouble();

      EFormat eformat;
      switch (eformat.index(format))
      {
      case EFormat::DIS:
         Utils::set_bitsuint(lsb, sigbits, lsbres, value, dword);
         break;
      case EFormat::BCD:
         Utils::set_bitsbcd(lsb, sigbits, lsbres, value, dword);
         break;
      case EFormat::BNR:
         Utils::set_bits2c(lsb, sigbits, lsbres, value, dword);
         break;
      case EFormat::CHR:
          Utils::set_bitschar(lsb, sigbits,
                              tableViewValueRegion->model()->index(i, 4).data().toString().toStdString(), dword);
         break;
      case EFormat::COD:
         Utils::set_bitsuint(lsb, sigbits, lsbres, value, dword);
         break;
      default:
         break;
      }
   }

   Utils::calculate_parity(dword);

   lineEditValueInt->setText(QString::number(dword));
   lineEditValueWord->setText(QString::fromStdString(std::bitset<32>(dword).to_string()));
   lineEditValueParity->setText( (dword >> 30) == 1 ? "Even" : "Odd" );

   groupBoxA429->setEnabled(true);
}
