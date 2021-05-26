#include "a429bitssetmodel.h"

#include <QMessageBox>

class A429BitsSetModelPrivate
{
public:
   A429BitsSetModelPrivate(A429BitsSetModel* q) : q_ptr(q)
   {
      horizontalHeaders << QObject::tr("LSB") << QObject::tr("Bits Number") << QObject::tr("LSB Res")
         << QObject::tr("Format") << QObject::tr("Value");
   }

   QList<A429BitsSet> data;
   QStringList horizontalHeaders;
private:
   A429BitsSetModel* const q_ptr;
   Q_DECLARE_PUBLIC(A429BitsSetModel)
};

A429BitsSetModel::A429BitsSetModel(QObject* parent)
   : QAbstractTableModel(parent)
   , d_ptr(new A429BitsSetModelPrivate(this))
{
}

A429BitsSetModel::~A429BitsSetModel()
{
}

int A429BitsSetModel::rowCount(const QModelIndex& parent) const
{
   Q_D(const A429BitsSetModel);
   return d->data.size();
}

int A429BitsSetModel::columnCount(const QModelIndex& parent) const
{
   Q_D(const A429BitsSetModel);
   return d->horizontalHeaders.size();
}

QVariant A429BitsSetModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   Q_D(const A429BitsSetModel);
   switch (role)
   {
   case Qt::DisplayRole:
   {
      switch (orientation)
      {
      case Qt::Horizontal:
         return d->horizontalHeaders[section];
         break;
      case Qt::Vertical:
         return section + 1;
         break;
      default:
         break;
      }
   }
   break;
   case Qt::TextAlignmentRole:
      return QVariant(Qt::AlignCenter);
   default:
      break;
   }
   return QVariant();
}

QVariant A429BitsSetModel::data(const QModelIndex& index, int role) const
{
   Q_D(const A429BitsSetModel);
   if (!index.isValid())
   {
      return QVariant();
   }

   switch (role)
   {
   case Qt::DisplayRole:
      if (d->data.count() > 0)
      {
         switch (index.column())
         {
         case 0:
            return d->data[index.row()].lsb;
         case 1:
            return d->data[index.row()].sigbits;
         case 2:
            return QString::number(d->data[index.row()].lsbres, 'g', 10);
         case 3:
            return QString::fromStdString(d->data[index.row()].format);
         case 4:
            return d->data[index.row()].value;
         default:
            break;
         }
      }
      break;
   case Qt::TextAlignmentRole:
      return QVariant(Qt::AlignCenter);
   default:
      break;
   }
   return QVariant();
}

bool A429BitsSetModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
   Q_D(A429BitsSetModel);
   if (role == Qt::EditRole)
   {
      if (!checkIndex(index))
         return false;
      if (d->data.count() > 0)
      {
         switch (index.column())
         {
         case 0:
         {
            int start = value.toUInt();
            if (start + d->data[index.row()].sigbits <= 32)
            {
               bool valid = false;
               if (d->data.size() <= 1)
               {
                  valid = true;
               }
               else if ((index.row() - 1) >= 0)
               {
                  valid = start >= (d->data[index.row() - 1].lsb + d->data[index.row() - 1].sigbits);
               }
               else if ((index.row() + 1) <= d->data.count())
               {
                  valid = (start + d->data[index.row()].sigbits) <= d->data[index.row() + 1].lsb;
               }

               d->data[index.row()].lsb = valid ? start : d->data[index.row()].lsb;
            }
         }
         break;
         case 1:
         {
            int number = value.toUInt();
            if (d->data[index.row()].format == "DIS")
            {
               d->data[index.row()].sigbits = 1;
               d->data[index.row()].lsbres = 1;
            }
            else if (d->data[index.row()].lsb + number <= 32)
            {
               if (!((index.row() + 1) < d->data.count() && ((d->data[index.row()].lsb + number) >= d->data[index.row() + 1].lsb)))
               {
                  d->data[index.row()].sigbits = number;
               }
            }
         }
         break;
         case 2:
         {
            if (d->data[index.row()].format == "DIS")
               d->data[index.row()].lsbres = 1;
            else
               d->data[index.row()].lsbres = value.toDouble();
         }
         break;
         case 3:
         {
            d->data[index.row()].format = value.toString().toStdString();
            if (value.toString() == "DIS")
            {
               d->data[index.row()].sigbits = 1;
               d->data[index.row()].lsbres = 1;
            }
         }
         break;
         case 4:
            d->data[index.row()].value = value.toDouble();
            break;
         default:
            break;
         }
      }
      return true;
   }
   return false;
}

Qt::ItemFlags A429BitsSetModel::flags(const QModelIndex& index) const
{
   return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

void A429BitsSetModel::setData(const QList<A429BitsSet>& data)
{
   Q_D(A429BitsSetModel);
   beginResetModel();
   d->data = data;
   endResetModel();
}

void A429BitsSetModel::appendRow()
{
   Q_D(A429BitsSetModel);
   beginResetModel();
   int lsb = 11;
   int sigbits = 1;
   double sigres = 1.0f;
   for (size_t i = 0; i < d->data.size(); ++i)
   {
      lsb = d->data[i].sigbits + d->data[i].lsb;
   }

   if ((lsb + sigbits) > 30)
   {
      QMessageBox::warning(qobject_cast<QWidget*>(parent()), tr("Warning"), tr("significant bits out of range"));
      return;
   }
   d->data.append(A429BitsSet{ lsb, sigbits, sigres, "BCD", "", 1.0});
   endResetModel();
}

void A429BitsSetModel::deleteRow(int row)
{
   Q_D(A429BitsSetModel);
   beginResetModel();
   d->data.removeAt(row);
   endResetModel();
}

void A429BitsSetModel::clear()
{
   Q_D(A429BitsSetModel);
   beginResetModel();
   d->data.clear();
   endResetModel();
}
