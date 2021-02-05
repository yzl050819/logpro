#include "widget.h"
#include <QApplication>

#include "hlog.h"

int main(int argc, char *argv[])
{

    qInstallMessageHandler( hMessageOutput );
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
