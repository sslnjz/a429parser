#include "a429bitsview.h"
#include "model/a429bitsmodel.h"
#include "delegate/a429bitsdelegate.h"

#include <QMenu>
#include <QFile>
#include <QTextStream>
#include <QHeaderView>
#include <QMessageBox>
#include <QFileDialog>
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

void A429BitsView::resizeEvent(QResizeEvent* event)
{
   setColumnWidth(1, 80);
   return QTableView::resizeEvent(event);
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

void A429BitsView::deleteRow()
{
   QAction* action = qobject_cast<QAction*>(sender());
   if (action)
   {
      int row = action->data().toInt();
      m_model->deleteRow(row);
   }
}

void A429BitsView::importTemplate()
{
   QString templatefile = QFileDialog::getOpenFileName(this, tr("Selected Template"), 
      ".", tr("CSV(Comma delimited) (*.csv)"));

   if (!templatefile.isEmpty())
   {
      QFile temp(templatefile);
      if (temp.open(QFile::ReadOnly))
      {
         QList<A429Bits> bits;
         QTextStream  in(&temp);
         while (!in.atEnd())
         {
            QString line = in.readLine();
            QStringList columns = line.split(",", Qt::SkipEmptyParts);
            if (5 == columns.size())
            {
               A429Bits bit{};
               for (size_t i = 0; i < columns.size(); ++i)
               {
                  switch (i)
                  {
                  case 0:
                     bit.lsb = columns[i].toInt();
                     break;
                  case 1:
                     bit.sigbits = columns[i].toInt();
                     break;
                  case 2:
                     bit.lsbres = columns[i].toDouble();
                     break;
                  case 3:
                     bit.format = columns[i].toStdString();
                     break;
                  case 4:
                     bit.codedesc = columns[i].toStdString();
                     break;
                  default:
                     break;
                  }
               }
               bits << bit;
            }
            else
            {
               QMessageBox::warning(this, tr("Warning"),
                  tr("Template format error: column missing"));
            }
         }
         temp.close();
         m_model->setData(bits);
      }
      else
      {
         QMessageBox::warning(this, tr("Warning"),
            tr("Unable to open the file: %1")
            .arg(templatefile));
      }
   }

}

void A429BitsView::exportTemplate()
{
   QList<QStringList> contents;
   for (size_t i = 0; i < m_model->rowCount(); i++)
   {
      QStringList content;
      for (size_t j = 0; j < m_model->columnCount(); j++)
      {
         content << m_model->index(i, j).data().toString();
      }
      contents << content;
   }
   QString templateFile = QFileDialog::getSaveFileName(this, tr("Save Template"), ".", tr("CSV(Comma delimited) (*.csv)"));

   QFile temp(templateFile);
   if (temp.open(QFile::WriteOnly | QFile::Truncate))
   {
      for (auto content : contents)
      {
         QTextStream out(&temp);
         out << content.join(",") << "\n";
      }
      temp.close();
      QMessageBox::information(this, tr("Export"),
         tr("Template export successfully, exported to: %1")
         .arg(templateFile));
   }
   else
   {
      QMessageBox::warning(this, tr("Warning"),
         tr("Unable to open the file: %1")
         .arg(templateFile));
   }
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
      connect(actDel, &QAction::triggered, this, &A429BitsView::deleteRow);
   }

   menu->addSeparator();

   QAction* actImport = menu->addAction(tr("Import"));
   connect(actImport, &QAction::triggered, this, &A429BitsView::importTemplate);

   QAction* actExport= menu->addAction(tr("Export"));
   connect(actExport, &QAction::triggered, this, &A429BitsView::exportTemplate);

   menu->addSeparator();

   QAction* actClear = menu->addAction(tr("Clear"));
   connect(actClear, &QAction::triggered, this, &A429BitsView::clear);

   menu->exec(event->globalPos());
}
