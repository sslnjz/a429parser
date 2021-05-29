#include "a4292value.h"

#include <QRegularExpression>
#include <QRegularExpressionValidator>

#include "a429bits.h"
#include "utils.h"

class A4292ValuePrivate
{
public:
   A4292ValuePrivate(A4292Value* parent) : q_ptr(parent)
   {

   }

   uint32_t qstring2uint(const QString& str)
   {
      uint32_t dword = 0;
      try
      {
         dword = std::stoull(str.toStdString(), nullptr, QRegularExpression("\\b[01]+\\b").match(str).hasMatch() ? 2 : 10);
      }
      catch (const std::exception& e)
      {
         qDebug() << e.what();
      }

      return dword;
   }

   QHash<uint32_t, QString> codesplit(const QString& codedesc)
   {
      QHash<uint32_t, QString> codemap;
      QStringList codes = codedesc.split(";", Qt::SkipEmptyParts);
      for (auto code : codes)
      {
         QStringList c = code.split("=", Qt::SkipEmptyParts);
         if (c.size() == 2)
         {
            bool Ok = false;
            QString identify = c[0];
            uint32_t icode = identify.toInt(&Ok, 2); 
            if (Ok)
            {
               codemap[icode] = c[1];
            }
            else
            {
               icode = identify.toInt(&Ok, 10);
               codemap[icode] = c[1];
            }
         }
      }

      return codemap;
   }

   QString code(const QString& codedesc, double value)
   {
      QHash<uint32_t, QString> codehash = codesplit(codedesc);
      if (codehash.find(value) != codehash.end())
      {
         return QString("%1").arg(codehash[value]);
      }
      else
      {
         return QString("%1").arg(value);
      }
   }

   int timerId;

private:
   A4292Value* q_ptr = Q_NULLPTR;
   Q_DECLARE_PUBLIC(A4292Value)
};

A4292Value::A4292Value(QWidget* parent)
   : QWidget(parent)
   , d_ptr(new A4292ValuePrivate(this))
{
   Q_D(A4292Value);
   setupUi(this);

   lineEditA429Word->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9 ]+"), this));
   d->timerId = startTimer(100);

   connect(pushButtonA429Calc, &QPushButton::clicked, this, &A4292Value::calculate);
   connect(pushButtonA429Clear, &QPushButton::clicked, 
      [this]() {
         tableWidgetA429Value->clear();
         lineEditA429Parity->clear();
         lineEditA429Label->clear();
         lineEditA429SDI->clear();
         lineEditA429SSM->clear();
         groupBoxA429Value->setEnabled(false);
      });
}

A4292Value::~A4292Value()
{
}

void A4292Value::timerEvent(QTimerEvent* event)
{
   Q_D(A4292Value);
   if (event->timerId() == d->timerId)
   {
      bool isEnabled = !lineEditA429Word->text().isEmpty();
      frameA429Fmt->setEnabled(isEnabled);
      tableViewA429Region->setEnabled(isEnabled);
      pushButtonA429Calc->setEnabled(tableViewA429Region->model()->rowCount() > 0 && isEnabled);
   }
   return QWidget::timerEvent(event);
}

void A4292Value::calculate()
{
   Q_D(A4292Value);
   QString sword = lineEditA429Word->text().remove(QRegularExpression("\\s"));
   uint32_t dword = d->qstring2uint(sword);

   QList<A429BitsValue> data;
   for (size_t i = 0; i < tableViewA429Region->model()->rowCount(); ++i)
   {
      A429BitsValue bitsValue;
      uint32_t lsb = 0, sigbits = 0;
      double lsbres = 0.0;
      QString format;
      QString codedesc;
      for (size_t j = 0; j < tableViewA429Region->model()->columnCount(); ++j)
      {
         switch (j)
         {
         case 0:
            lsb = tableViewA429Region->model()->index(i, j).data().toInt();
            break;
         case 1:
            sigbits = tableViewA429Region->model()->index(i, j).data().toInt();
            break;
         case 2:
            lsbres = tableViewA429Region->model()->index(i, j).data().toDouble();
            break;
         case 3:
            format = tableViewA429Region->model()->index(i, j).data().toString();
            break;
         case 4:
            codedesc = tableViewA429Region->model()->index(i, j).data().toString();
            break;
         default:
            break;
         }
      }

      bitsValue.lsb = lsb;
      bitsValue.sigbits = sigbits;
      bitsValue.lsbres = lsbres;
      bitsValue.codedesc = codedesc.toStdString();
      bitsValue.format = format.toStdString();

      uint32_t sig = 0;
      double value = 0;
      if (Utils::get_selected_bits(dword, lsb, sigbits, sig))
      {
         bitsValue.sig = sig;
         EFormat fmt;
         switch (fmt.index(format.toStdString()))
         {
         case EFormat::DIS:
            {
               Utils::get_bitsuint(dword, lsb, sigbits, lsbres, value);
               bitsValue.sigValue.value = value;
               bitsValue.code = d->code(codedesc, value).toStdString();
            }
            break;
         case EFormat::BCD:
            {
               Utils::get_bitsbcd(dword, lsb, sigbits, lsbres, value);
               bitsValue.sigValue.value = value;
               bitsValue.code = d->code(codedesc, value).toStdString();
               
            }
            break;
         case EFormat::BNR:
            {
               Utils::get_bits2c(dword, lsb, sigbits, lsbres, value);
               bitsValue.sigValue.value = value;
               bitsValue.code = d->code(codedesc, value).toStdString();
            }
            break;
         case EFormat::CHR:
            {
                std::string str;
                Utils::get_bitschar(dword, lsb, sigbits, str);
                bitsValue.sigValue.str = str;
            }
            break;
         case EFormat::COD:
            {
               Utils::get_bitsuint(dword, lsb, sigbits, lsbres, value);
               bitsValue.sigValue.value = value;
               bitsValue.code = d->code(codedesc, value).toStdString();
            }
            break;
         default:
            break;
         }
      }

      bitsValue.label = radioButtonA429Reverse->isChecked() ? static_cast<uint8_t>(dword & 0xFF) : Utils::reverse_8bit(dword & 0xFF);
      bitsValue.SDI = static_cast<uint8_t>((dword >> 8) & 0x03);
      bitsValue.SSM = static_cast<uint8_t>((dword >> 29) & 0x03);
      bitsValue.parity = static_cast<uint8_t>((dword >> 31) & 0x1);

      data.append(bitsValue);
   }

   if(radioButtonA429Reverse->isChecked())
      lineEditA429Label->setText(QString("%1").arg(short(dword & 0xFF), int(4), int(8), QChar('0')));
   else
      lineEditA429Label->setText(QString("%1").arg(short(Utils::reverse_8bit(dword & 0xFF)), int(4), int(8), QChar('0')));

   lineEditA429Parity->setText(((dword >> 31) & 0x1) == 0 ? "Odd" : "Even");
   lineEditA429SDI->setText(QString("%1").arg(short((dword >> 8) & 0x03), int(2), int(2), QChar('0')));
   lineEditA429SSM->setText(QString("%1").arg(short((dword >> 29) & 0x03), int(2), int(2), QChar('0')));

   tableWidgetA429Value->setData(data);
   groupBoxA429Value->setEnabled(true);
}