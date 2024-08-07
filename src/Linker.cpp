// Created by Alex Balta on 03.07.2024.

#include "../headers/Linker.hpp"
#include "../headers/MenuWindow.hpp"
#include <cmath>

Linker::Linker(MenuWindow *parent, std::vector<Item> &array, int size, QGraphicsScene *scene, int delay)
    : m_parent(parent), m_size(size), m_scene(scene), m_delay(delay) {
    m_width = std::max(512 / m_size, 1);
    m_array.resize(m_size);
    for (int i = 0; i < m_size; i++) {
        m_array[i] = &array[i];
        m_array[i]->setPlace(i + 1);
        int height = (m_array[i]->getVal() + 1) * m_width;
        float left = 10 + i * m_width;
        float intleft = std::floor(left);
        if (left - intleft < 0.1) {
            left = intleft;
        } else if (left - intleft < 0.6) {
            left = intleft + 0.5f;
        } else {
            left = intleft + 1;
        }
        int up = 540 - height;
        if (m_size <= 256) {
            QPen pen = QPen(Qt::black);
            QBrush brush = QBrush(WHITE);
            m_rects.push_back(m_scene->addRect(left, up, m_width, height, pen, brush));
            m_rects[i]->setToolTip(m_array[i]->Tip());
        } else {
            QPen pen = QPen(WHITE, 1, Qt::SolidLine);
            m_lines.push_back(m_scene->addLine(left, up, left, 540, pen));
            m_lines[i]->setToolTip(m_array[i]->Tip());
        }
    }
}

void Linker::delay() {
    for (int i = 0; i <= m_delay / 6; i++) {
        QApplication::processEvents();
    }
}

void Linker::render(int i, QColor C) {
    int height = (m_array[i]->getVal() + 1) * m_width;
    int left = 10 + i * m_width;
    int up = 540 - height;
    if (m_size <= 256) {
        QPen pen = QPen(Qt::black);
        QBrush brush = QBrush(C);
        m_rects[i]->setBrush(brush);
        m_rects[i]->setPen(pen);
        m_rects[i]->setRect(QRect(left, up, m_width, height));
    } else {
        QPen pen = QPen(C, 1, Qt::SolidLine);
        m_lines[i]->setPen(pen);
        m_lines[i]->setLine(left, up, left, 540);
    }
}

Linker::~Linker() {
    for (int i = 0; i < m_size; ++i) {
        if (m_size <= 256) {
            m_scene->removeItem(m_rects[i]);
            delete m_rects[i];
        } else {
            m_scene->removeItem(m_lines[i]);
            delete m_lines[i];
        }
    }
}

Item Linker::get(int i) {
    render(i, RED);
    delay();
    m_array[i]->setRead(m_array[i]->getRead() + 1);
    m_parent->INCRREAD();
    render(i, WHITE);
    return *m_array[i];
}

Item *Linker::send(int i) {
    render(i, RED);
    delay();
    m_array[i]->setRead(m_array[i]->getRead() + 1);
    m_array[i]->setSwap(m_array[i]->getSwap() + 1);
    m_parent->INCRREAD();
    render(i, WHITE);
    return m_array[i];
}

bool Linker::cmp_ii(int i, int j) {
    render(i, BLUE);
    render(j, BLUE);
    delay();
    m_array[i]->setCmp(m_array[i]->getCmp() + 1);
    m_array[j]->setCmp(m_array[j]->getCmp() + 1);
    m_parent->INCRCMP();
    m_array[i]->setRead(m_array[i]->getRead() + 1);
    m_array[j]->setRead(m_array[j]->getRead() + 1);
    m_parent->INCRREAD();
    m_parent->INCRREAD();
    render(i, WHITE);
    render(j, WHITE);
    return (*m_array[i] < *m_array[j]);
}

bool Linker::cmp_ee(Item *a, Item *b) {
    a->setRead(a->getRead() + 1);
    b->setRead(b->getRead() + 1);
    a->setCmp(a->getCmp() + 1);
    b->setCmp(b->getCmp() + 1);
    m_parent->INCRCMP();
    return (*a < *b);
}

bool Linker::cmp_ie(int i, Item *a) {
    render(i, BLUE);
//    std::this_thread::sleep_for(std::chrono::microseconds(m_delay));
    delay();
    m_parent->INCRREAD();
    a->setRead(a->getRead() + 1);
    m_array[i]->setCmp(m_array[i]->getCmp() + 1);
    a->setCmp(a->getCmp() + 1);
    m_parent->INCRCMP();
    render(i, WHITE);
    return (*m_array[i] < *a);
}

bool Linker::cmp_ei(Item *a, int i) {
    render(i, BLUE);
    delay();
    m_array[i]->setRead(m_array[i]->getRead() + 1);
    m_parent->INCRREAD();
    a->setRead(a->getRead() + 1);
    m_array[i]->setCmp(m_array[i]->getCmp() + 1);
    a->setCmp(a->getCmp() + 1);
    m_parent->INCRCMP();
    render(i, WHITE);
    return (*a < *m_array[i]);
}

void Linker::set(int i, Item val) {
    *m_array[i] = val;
    render(i, PURPLE);
    delay();
    m_array[i]->setSwap(m_array[i]->getSwap() + 1);
    m_parent->INCRWRITE();
    render(i, WHITE);
}

void Linker::receive(int i, Item *val) {
    m_array[i] = val;
    render(i, PURPLE);
    delay();
    m_array[i]->setSwap(m_array[i]->getSwap() + 1);
    m_parent->INCRWRITE();
    render(i, WHITE);
}

void Linker::flip(int i, int j) {
    Item *tmp = m_array[i];
    m_array[i] = m_array[j];
    m_array[j] = tmp;
    m_parent->INCRREAD();
    m_parent->INCRREAD();
    render(i, PURPLE);
    render(j, PURPLE);
    delay();
    m_array[i]->setSwap(m_array[i]->getSwap() + 1);
    m_array[j]->setSwap(m_array[j]->getSwap() + 1);
    m_parent->INCRWRITE();
    m_parent->INCRWRITE();
    render(i, WHITE);
    render(j, WHITE);
}

void Linker::solved(int i) {
    m_array[i]->setRank(i + 1);
    render(i, GREEN);
    QApplication::processEvents();
}

void Linker::tmpsolve(int i) {
    render(i, APPLE);
    QApplication::processEvents();
}

int Linker::getSize() const {
    return m_size;
}

void Linker::setBinHeapLv(int idx) {
    setHeapLv(idx, 2);
}

void Linker::setTerHeapLv(int idx) {
    setHeapLv(idx, 3);
}

void Linker::setHeapLv(int idx, int base) {
    int lv = std::floor(std::log(idx + 1) / std::log(base) + 0.001);
    QColor c;
    c.setHsv(lv * 255 / 8, 100, 255);
    render(idx, c);
    QApplication::processEvents();
}

void Linker::flip_ifn_cmp(int i, int j) {
    render(i, BLUE);
    render(j, BLUE);
    m_array[i]->setCmp(m_array[i]->getCmp() + 1);
    m_array[j]->setCmp(m_array[j]->getCmp() + 1);
    m_parent->INCRREAD();
    m_parent->INCRREAD();
    m_parent->INCRCMP();
    if (*m_array[i] > *m_array[j]) {
        Item *tmp = m_array[i];
        m_array[i] = m_array[j];
        m_array[j] = tmp;
        m_array[i]->setSwap(m_array[i]->getSwap() + 1);
        m_array[j]->setSwap(m_array[j]->getSwap() + 1);
        m_parent->INCRWRITE();
        m_parent->INCRWRITE();
    }
    delay();
    render(i, WHITE);
    render(j, WHITE);
}
