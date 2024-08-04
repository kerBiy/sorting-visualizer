#include <QApplication>
#include "MainWindow.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto scene = new QGraphicsScene;
    auto view = new QGraphicsView(scene);

    auto menu = new MenuWindow(scene, view);
    auto mainWindow = new MainWindow(scene, view, menu);
    mainWindow->show();

    auto result = QApplication::exec();

    delete scene;
    delete view;
    delete menu;
    delete mainWindow;

    return result;
}