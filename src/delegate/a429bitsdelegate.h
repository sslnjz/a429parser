#pragma once

#include <QStyledItemDelegate>

class A429BitsDelegate : public QStyledItemDelegate
{
   Q_OBJECT
public:
   A429BitsDelegate(QObject* parent);
   ~A429BitsDelegate();

   QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
      const QModelIndex& index) const override;
   void setEditorData(QWidget* editor, const QModelIndex& index) const override;
   void setModelData(QWidget* editor, QAbstractItemModel* model,
      const QModelIndex& index) const override;

private slots:
   void commitAndCloseEditor();
};