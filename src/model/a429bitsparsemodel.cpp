#include "a429bitsparsemodel.h"

#include <QSize>

class A429BitsParseModelPrivate
{
public:
   A429BitsParseModelPrivate(A429BitsParseModel* parent) : q_ptr(parent)
   {
      horizontalHeaders << QObject::tr("Label") << QObject::tr("SDI") << QObject::tr("SSM") << QObject::tr("Parity")
         << QObject::tr("Significant Bit") << QObject::tr("Value") << QObject::tr("Decode");
   }

   QStringList horizontalHeaders;
   QList<A429BitsValue> data;

private:
   A429BitsParseModel* const q_ptr;
   Q_DECLARE_PUBLIC(A429BitsParseModel);
};

A429BitsParseModel::A429BitsParseModel(QObject* parent)
   : QAbstractTableModel(parent)
   , d_ptr(new A429BitsParseModelPrivate(this))
{

}

A429BitsParseModel::~A429BitsParseModel()
{
}

int A429BitsParseModel::rowCount(const QModelIndex& parent) const
{
   Q_D(const A429BitsParseModel);
   return d->data.size();
}

int A429BitsParseModel::columnCount(const QModelIndex& parent) const
{
   Q_D(const A429BitsParseModel);
   return d->horizontalHeaders.size();
}

QVariant A429BitsParseModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   Q_D(const A429BitsParseModel);
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

QVariant A429BitsParseModel::data(const QModelIndex& index, int role) const
{
   Q_D(const A429BitsParseModel);
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
            return QString("%1").arg(d->data[index.row()].label, int(4), int(8), QChar('0'));
         case 1:
            return QString("%1").arg(d->data[index.row()].SDI, int(2), int(2), QChar('0'));
         case 2:
            return QString("%1").arg(d->data[index.row()].SSM, int(2), int(2), QChar('0'));
         case 3:
            return d->data[index.row()].parity;
         case 4:
            return QString("%1").arg(d->data[index.row()].sig, int(d->data[index.row()].sigbits), int(2), QChar('0')) ;
         case 5:
            return d->data[index.row()].value;
         case 6:
            return QString::fromStdString(d->data[index.row()].code);
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


void A429BitsParseModel::clear()
{
   Q_D(A429BitsParseModel);
   beginResetModel();
   d->data.clear();
   endResetModel();
}

void A429BitsParseModel::setData(const QList<A429BitsValue>& data)
{
   Q_D(A429BitsParseModel);
   beginResetModel();
   d->data.clear();
   d->data.append(data);
   endResetModel();
}