#include "a429bitsview.h"
#include "model/a429bitsmodel.h"
#include "delegate/a429bitsdelegate.h"

#include <QMenu>
#include <QHeaderView>
#include <QContextMenuEvent>

A429BitsView::A429BitsView(QWidget* parent)
   : QTableView(parent)
   , m_model(new A429BitsModel(this))
{
   setModel(m_model);
   setItemDelegate(new A429BitsDelegate(this));
}

A429BitsView::~A429BitsView()
{
}

void A429BitsView::clear()
{
   m_model->clear();
}

void A429BitsView::appendRow()
{
   m_model->appendRow();
   scrollToBottom();
}

void A429BitsView::contextMenuEvent(QContextMenuEvent* event)
{
   QMenu* menu = new QMenu(this);
   QAction* actNew = menu->addAction(tr("New region"));
   connect(actNew, &QAction::triggered, this, &A429BitsView::appendRow);

   int currentRow = this->rowAt(event->pos().y());
   if (currentRow >= 0) {
      QAction* actDel = menu->addAction(tr("Delete"));
      actDel->setData(currentRow);
      connect(actDel, &QAction::triggered, m_model, &A429BitsModel::deleteRow);
   }

   menu->exec(event->globalPos());
}
