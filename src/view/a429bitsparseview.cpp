#include "a429bitsparseview.h"

#include "model/a429bitsparsemodel.h"

A429BitsParseView::A429BitsParseView(QWidget* parent)
   : QTableView(parent)
   , m_model(new A429BitsParseModel(this))
{
   setModel(m_model);
   resizeColumnToContents(4);
}

A429BitsParseView::~A429BitsParseView()
{
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
