#include "a429bitsmodel.h"

#include <QAction>
#include <QMessageBox>

#include "a429bits.h"

class A429BitsModelPrivate : public QObject
{
public:
   A429BitsModelPrivate(A429BitsModel* q) : q_ptr(q)
   {
      horizontalHeaders << tr("LSB") << tr("SIG Bits") << tr("LSB Res") << tr("Format") << tr("Coded");
   }

public:
   QStringList horizontalHeaders;
   QList<A429Bits> data;
private:
   A429BitsModel* q_ptr;
   Q_DECLARE_PUBLIC(A429BitsModel)
};

A429BitsModel::A429BitsModel(QObject* parent)
   : QAbstractTableModel(parent)
   , d_ptr(new A429BitsModelPrivate(this))
{
}

A429BitsModel::~A429BitsModel()
{
}

int A429BitsModel::rowCount(const QModelIndex& parent) const
{
   return d_ptr->data.size();
}

int A429BitsModel::columnCount(const QModelIndex& parent) const
{
   return d_ptr->horizontalHeaders.size();
}

QVariant A429BitsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   switch (role)
   {
   case Qt::DisplayRole:
      {
         switch (orientation)
         {
         case Qt::Horizontal:
            return d_ptr->horizontalHeaders[section];
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

QVariant A429BitsModel::data(const QModelIndex& index, int role) const
{
   if (!index.isValid())
   {
      return QVariant();
   }

   switch (role)
   {
   case Qt::DisplayRole:
      if (d_ptr->data.count() > 0)
      {
         switch (index.column())
         {
         case 0:
            return d_ptr->data[index.row()].lsb;
         case 1:
            return d_ptr->data[index.row()].sigbits;
         case 2:
            return QString::number(d_ptr->data[index.row()].lsbres);
         case 3:
            return QString::fromStdString(d_ptr->data[index.row()].format);
         case 4:
            return QString::fromStdString(d_ptr->data[index.row()].codedesc);
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

bool A429BitsModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
   Q_D(A429BitsModel);
   if (role == Qt::EditRole)
   {
      if (!checkIndex(index))
         return false;
      if (d_ptr->data.count() > 0)
      {
         switch (index.column())
         {
         case 0:
            {
               int start = value.toUInt();
               if (start + d->data[index.row()].sigbits <= 30)
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
               else if (d->data[index.row()].lsb + number <= 30)
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
            d->data[index.row()].codedesc = value.toString().toStdString();
            break;
         default:
            break;
         }
      }
      return true;
   }
   return false;
}

Qt::ItemFlags A429BitsModel::flags(const QModelIndex& index) const
{
   return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

void A429BitsModel::clear()
{
   Q_D(A429BitsModel);
   beginResetModel();
   d->data.clear();
   endResetModel();
}

void A429BitsModel::appendRow()
{
   Q_D(A429BitsModel);
   beginResetModel();
   int start = 11;
   int numbit = 1;
   double scaled = 1.0f;
   for (size_t i = 0; i < d->data.size(); ++i)
   {
      start = d->data[i].sigbits + d->data[i].lsb;
   }

   if ((start + numbit) > 30)
   {
      QMessageBox::warning(qobject_cast<QWidget*>(parent()), tr("Warning"), tr("Bits number out of range"));
      return;
   }
   d->data.append(A429Bits{start, numbit, scaled, "BCD", ""});
   endResetModel();
}

void A429BitsModel::deleteRow()
{
   Q_D(A429BitsModel);
   beginResetModel();
   QAction* act = qobject_cast<QAction*>(sender());
   if (act)
   {
      int row = act->data().toInt();
      d->data.removeAt(row);
   }
   endResetModel();
}
