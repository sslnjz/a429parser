#include "a429bitsparsemodel.h"

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
   A429BitsParseModel* q_ptr;
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
   return d_ptr->data.size();
}

int A429BitsParseModel::columnCount(const QModelIndex& parent) const
{
   return d_ptr->horizontalHeaders.size();
}

QVariant A429BitsParseModel::headerData(int section, Qt::Orientation orientation, int role) const
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

QVariant A429BitsParseModel::data(const QModelIndex& index, int role) const
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
            return QString("%1").arg(d_ptr->data[index.row()].label, int(4), int(8), QChar('0'));
         case 1:
            return QString("%1").arg(d_ptr->data[index.row()].SDI, int(2), int(2), QChar('0'));
         case 2:
            return QString("%1").arg(d_ptr->data[index.row()].SSM, int(2), int(2), QChar('0'));
         case 3:
            return d_ptr->data[index.row()].parity;
         case 4:
            return QString("%1").arg(d_ptr->data[index.row()].sig, int(d_ptr->data[index.row()].sigbits), int(2), QChar('0')) ;
         case 5:
            return d_ptr->data[index.row()].value;
         case 6:
            return QString::fromStdString(d_ptr->data[index.row()].code);
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