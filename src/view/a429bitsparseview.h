#pragma once

#include <QTableView>

#include "a429bits.h"

class A429BitsParseModel;
class A429BitsParseView : public QTableView
{
   Q_OBJECT
public:
   A429BitsParseView(QWidget* parent = Q_NULLPTR);
   ~A429BitsParseView();

protected:
   void resizeEvent(QResizeEvent* event) override;
   void contextMenuEvent(QContextMenuEvent* event)override;

public slots:
   void horizontalHeaderContextMenuResopnse(const QPoint& pos);
   void setData(const QList<A429BitsValue>& data);
   void clear();

private:
   A429BitsParseModel* m_model;
};