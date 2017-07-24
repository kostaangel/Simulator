#include "simulator_test.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Simulator_Test w;
    w.show();

    return a.exec();
}
