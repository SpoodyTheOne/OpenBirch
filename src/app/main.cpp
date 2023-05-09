#include <QApplication>
#include <QPushButton>

#include "gui/mainwindow.h"
#include "base/expression_parser/mathengine.h"

int main(int argc, char **argv)
{
    MathEngine::Init();
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
