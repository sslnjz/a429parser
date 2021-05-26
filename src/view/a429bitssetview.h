#pragma once

#include <QTableView>

class A429BitsSetModel;
class A429BitsSetView : public QTableView
{
   Q_OBJECT
public:
   A429BitsSetView(QWidget* parent);
   ~A429BitsSetView();

protected:
   void resizeEvent(QResizeEvent* event) override;
   void contextMenuEvent(QContextMenuEvent*) override;

public slots:
   void clear();
   void appendRow();
   void deleteRow();
   void importTemplate();
   void exportTemplate();

private:
   A429BitsSetModel* m_model;

};