#pragma once

#include <QAbstractTableModel>

#include "a429bits.h"

class A429BitsSetModelPrivate;
class A429BitsSetModel : public QAbstractTableModel
{
public:
   A429BitsSetModel(QObject* parent);
   ~A429BitsSetModel();

   int rowCount(const QModelIndex& parent = QModelIndex()) const override;
   int columnCount(const QModelIndex& parent = QModelIndex()) const override;
   QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

   QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
   bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
   Qt::ItemFlags flags(const QModelIndex& index) const override;

public slots:
   void setData(const QList<A429BitsValue>& data);
   void appendRow();
   void deleteRow(int row);
   void clear();

private:
   const QScopedPointer<A429BitsSetModelPrivate> d_ptr;
   Q_DECLARE_PRIVATE(A429BitsSetModel)
};