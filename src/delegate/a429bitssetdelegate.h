#pragma once

#include <QStyledItemDelegate>

#include "a429bitsdelegate.h"

class A429BitsSetDelegate : public A429BitsDelegate
{
   Q_OBJECT
public:
   A429BitsSetDelegate(QObject* parent);
   ~A429BitsSetDelegate();

   QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
      const QModelIndex& index) const override;
};