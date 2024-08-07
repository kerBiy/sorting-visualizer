//
// Created by Alex Balta on 05.07.2024.
//

#include "MainWindow.hpp"

MainWindow::MainWindow(QGraphicsScene *scene, QGraphicsView *view, MenuWindow *menu, QWidget *parent)
    : QMainWindow(parent), m_scene(scene), m_view(view), m_menu(menu), m_parent(parent) {
    m_mainWidget = new QWidget(this);
    m_mainLayout = new QHBoxLayout(m_mainWidget);
    setCentralWidget(m_mainWidget);

    m_mainWidget->setFixedSize(820, 620);
    m_menu->setFixedHeight(590);

    m_frame = new QFrame;
    m_frame->setLayout(new QVBoxLayout);
    m_mainLayout->addWidget(m_frame);
    m_mainLayout->addWidget(m_menu);

    m_view->setFixedSize(600, 580);
    m_view->setScene(scene);
//    m_view->fitInView(0, 0, 500, 500, Qt::KeepAspectRatio);
    m_frame->layout()->addWidget(view);
}
