//
// Created by Alex Balta on 05.07.2024.
//

#pragma once

#include <QMainWindow>
#include "MenuWindow.hpp"

class MainWindow : public QMainWindow {
  Q_OBJECT
  private:
    QGraphicsScene *m_scene;
    QGraphicsView *m_view;
    QFrame *m_frame;
    MenuWindow *m_menu;

    QWidget *m_parent;
    QWidget *m_mainWidget;
    QHBoxLayout *m_mainLayout;

  public:
    MainWindow(QGraphicsScene *scene, QGraphicsView *view, MenuWindow *menu, QWidget *parent = nullptr);
};
