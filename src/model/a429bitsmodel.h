#pragma once

#include <QAbstractTableModel>

#include "a429bits.h"

class A429BitsModelPrivate;
class A429BitsModel : public QAbstractTableModel
{
   Q_OBJECT
public:
   A429BitsModel(QObject* parent = Q_NULLPTR);
   ~A429BitsModel();

   int rowCount(const QModelIndex& parent = QModelIndex()) const override;
   int columnCount(const QModelIndex& parent = QModelIndex()) const override;
   QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

   QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
   bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
   Qt::ItemFlags flags(const QModelIndex& index) const override;

public slots:
   void clear();
   void appendRow();
   void deleteRow(int row);
   void setData(const QList<A429Bits>& data);

private:
   const QScopedPointer<A429BitsModelPrivate> d_ptr;
   Q_DECLARE_PRIVATE(A429BitsModel)
};