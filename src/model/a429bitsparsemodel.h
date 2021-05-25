#pragma once

#include <QAbstractTableModel>

#include "a429bits.h"

class A429BitsParseModelPrivate;
class A429BitsParseModel : public QAbstractTableModel
{
   Q_OBJECT
public:
   A429BitsParseModel(QObject* parent = Q_NULLPTR);
   ~A429BitsParseModel();

   int rowCount(const QModelIndex& parent = QModelIndex()) const override;
   int columnCount(const QModelIndex& parent = QModelIndex()) const override;
   QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

   QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

public slots:
   void setData(const QList<A429BitsValue>& data);
   void clear();

private:
   const QScopedPointer<A429BitsParseModelPrivate> d_ptr;
   Q_DECLARE_PRIVATE(A429BitsParseModel)
};