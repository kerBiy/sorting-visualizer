// Created by Alex Balta on 03.07.2024.

#pragma once

#include <QApplication>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QColor>

#include <vector>
#include <sstream>
#include <iostream>
#include <chrono>
#include <thread>

#include "Item.hpp"

#define WHITE QColor(255, 255, 255)
#define GREEN QColor(55, 200, 0)
#define BLUE QColor(11, 97, 164)
#define RED QColor(255, 57, 0)
#define APPLE QColor(165, 255, 0)
#define PURPLE QColor(124, 7, 169)

class MenuWindow;

class Linker {
  private:
    std::vector<Item *> m_array;
    int m_size;

    int m_width;
    int m_delay;

    QGraphicsScene *m_scene;
    MenuWindow *m_parent;

    std::vector<QGraphicsRectItem *> m_rects;
    std::vector<QGraphicsLineItem *> m_lines;

    void render(int i, QColor C);
    void setHeapLv(int idx, int base);

  public:
    Linker(MenuWindow *parent, std::vector<Item> &array, int size, QGraphicsScene *scene, int delay);
    ~Linker();

    void delay();
    Item get(int i);
    Item *send(int i);

    bool cmp_ii(int i, int j);
    bool cmp_ei(Item *a, int i);
    bool cmp_ie(int i, Item *a);
    bool cmp_ee(Item *a, Item *b);

    void set(int i, Item val);
    void receive(int i, Item *val);
    void flip(int i, int j);
    void solved(int i);
    void tmpsolve(int i);

    int getSize() const;
    void setBinHeapLv(int idx);
    void setTerHeapLv(int idx);
    void flip_ifn_cmp(int i, int j);

};
