#include "a429bitssetdelegate.h"

#include <QLineEdit>
#include <QComboBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

#include "a429bits.h"
#include "aligndelegate.h"

A429BitsSetDelegate::A429BitsSetDelegate(QObject* parent)
   : A429BitsDelegate(parent)
{

}

A429BitsSetDelegate::~A429BitsSetDelegate()
{
}

QWidget* A429BitsSetDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
   Q_UNUSED(option);
   QWidget* editor = Q_NULLPTR;
   switch (index.column())
   {
   case 0:
   case 1:
      {
         QLineEdit* lineedit = new QLineEdit(parent);
         lineedit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9 ]+"), lineedit));
         lineedit->setAlignment(Qt::AlignHCenter);
         connect(lineedit, &QLineEdit::editingFinished, this, &A429BitsSetDelegate::commitAndCloseEditor);
         editor = lineedit;
      }
   break;
   case 2:
      {
         QLineEdit* lineedit = new QLineEdit(parent);
         lineedit->setValidator(new QDoubleValidator(lineedit));
         lineedit->setAlignment(Qt::AlignHCenter);
         connect(lineedit, &QLineEdit::editingFinished, this, &A429BitsSetDelegate::commitAndCloseEditor);
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
   case 4:
      {
         QLineEdit* lineedit = new QLineEdit(parent);
         if("CHR" != index.model()->index(index.row(), 3).data().toString())
            lineedit->setValidator(new QDoubleValidator(lineedit));
         lineedit->setAlignment(Qt::AlignHCenter);
         connect(lineedit, &QLineEdit::editingFinished, this, &A429BitsSetDelegate::commitAndCloseEditor);
         editor = lineedit;
      }
      break;
   default:
      break;
   }
   return editor;
}
