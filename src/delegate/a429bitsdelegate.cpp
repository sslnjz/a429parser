#include "a429bitsdelegate.h"

#include <QLineEdit>
#include <QComboBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

#include "a429bits.h"
#include "aligndelegate.h"

A429BitsDelegate::A429BitsDelegate(QObject* parent)
   : QStyledItemDelegate(parent)
{

}

A429BitsDelegate::~A429BitsDelegate()
{
}

QWidget* A429BitsDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
   Q_UNUSED(option)
   QWidget* editor = Q_NULLPTR;
   switch (index.column())
   {
   case 0:
   case 1:
   case 2:
   case 4:
      {
         QLineEdit* lineedit = new QLineEdit(parent);
         lineedit->setAlignment(Qt::AlignHCenter);
         connect(lineedit, &QLineEdit::editingFinished, this, &A429BitsDelegate::commitAndCloseEditor);
         editor = lineedit;
      }
      break;
   case 3:
      {
         EFormat format;
         QComboBox* combo = new QComboBox(parent);
         combo->setStyle(new AlignProxyStyle());
         for (int i = 0; i < EFormat::eRange; ++i)
         {
            combo->addItem(QString::fromStdString(format.name(i)));
         }
         combo->setItemDelegate(new AlignDelegate(Qt::AlignCenter));
         editor = combo;
      }
      break;
   default:
      break;
   } 
   return editor;
}

void A429BitsDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
   if (3 == index.column())
   {
      QComboBox* combo = qobject_cast<QComboBox*>(editor);
      combo->setCurrentText(index.data().toString());
   }
   else
   {
      QLineEdit* starEditor = qobject_cast<QLineEdit*>(editor);
      starEditor->setText(index.data().toString());
   }
}

void A429BitsDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
   if (3 == index.column())
   {
      QComboBox* combo = qobject_cast<QComboBox*>(editor);
      model->setData(index, combo->currentText());
   }
   else
   {
      QLineEdit* myeditor = qobject_cast<QLineEdit*>(editor);
      model->setData(index, QVariant::fromValue(myeditor->text()));
   }
}

void A429BitsDelegate::commitAndCloseEditor()
{
   QLineEdit* editor = qobject_cast<QLineEdit*>(sender());
   emit commitData(editor);
   emit closeEditor(editor);
}