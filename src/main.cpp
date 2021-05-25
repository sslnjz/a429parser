#include <iostream>
#include <qapplication.h>
#include <QStyleFactory>
#include "version.h"
#include "gui/a429parser.h"

int main(int argc, char* argv[])
{
   QApplication a(argc, argv);

#if defined(Q_OS_MACOS)
   a.setStyle(QStyleFactory::create("Fusion"));
#endif

   A429Parser parser;
   parser.show();

   return a.exec();
}