#include "a429bitsparseview.h"

#include <QMenu>
#include <QHeaderView>
#include <QContextMenuEvent>

#include "model/a429bitsparsemodel.h"

A429BitsParseView::A429BitsParseView(QWidget* parent)
   : QTableView(parent)
   , m_model(new A429BitsParseModel(this))
{
   setModel(m_model);
   horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);

   connect(horizontalHeader(), &QHeaderView::customContextMenuRequested, 
      this, &A429BitsParseView::horizontalHeaderContextMenuResopnse);
}

A429BitsParseView::~A429BitsParseView()
{
}

void A429BitsParseView::resizeEvent(QResizeEvent* event)
{
   setColumnWidth(4, 85);
   return QTableView::resizeEvent(event);
}

void A429BitsParseView::contextMenuEvent(QContextMenuEvent* event)
{
   QMenu* menu = new QMenu(this);
   QAction* actNew = menu->addAction(tr("Reset"));
   connect(actNew, &QAction::triggered, [&]() {
      for (size_t i = 0; i < m_model->columnCount(); i++)
      {
         setColumnHidden(i, false);
      }
   });

   menu->exec(event->globalPos());
}

void A429BitsParseView::setData(const QList<A429BitsValue>& data)
{
   m_model->setData(data);
   resizeColumnToContents(4);
}

void A429BitsParseView::clear()
{
   m_model->clear();
}

void A429BitsParseView::horizontalHeaderContextMenuResopnse(const QPoint& pos)
{
   QMenu* menu = new QMenu(this);

   for (size_t i = 0; i < m_model->columnCount(); i++)
   {
      QAction* action = menu->addAction(m_model->headerData(i, Qt::Horizontal).toString());
      action->setData(i);
      action->setCheckable(true);
      action->setChecked(!isColumnHidden(i));

      connect(action, &QAction::toggled, 
         [&, action](bool check){

            int section = action->data().toInt();
            setColumnHidden(section, !check);
         });
   }

   menu->exec(this->mapToGlobal(pos));
}
