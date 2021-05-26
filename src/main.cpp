#include <iostream>
#include <qapplication.h>
#include <QStyleFactory>
#include "version.h"
#include "gui/a429parser.h"

int main(int argc, char* argv[])
{
   QApplication a(argc, argv);

   a.setStyle(QStyleFactory::create("Fusion"));

   A429Parser parser;
   parser.show();

   return a.exec();
}