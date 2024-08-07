//
// Created by Alex Balta on 03.07.2024.
//

#pragma once

#include <QWidget>
#include <QComboBox>
#include <QLCDNumber>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QVector>
#include <QSlider>
#include <QHBoxLayout>

#include "OptionManager.hpp"
#include "Distributor.hpp"
#include "Linker.hpp"
#include "Sorter.hpp"
#include "Item.hpp"

class MenuWindow : public QWidget {
  Q_OBJECT
  private:
    Linker *m_link;
    Sorter *m_sort;
    std::vector<Item> m_array;
    bool playing;

    QWidget *m_parent;
    QGraphicsScene *m_scene;
    QGraphicsView *m_view;
    QVBoxLayout *m_layout;

    QComboBox *m_chooseAlgorithm;
    QComboBox *m_chooseOption;
    OptionManager *m_optionManager;

    QSlider *m_chooseDelay;
    QLabel *m_textDelay;

    QComboBox *m_chooseDistribution;
    QComboBox *m_chooseScramble;
    QComboBox *m_chooseSize;

    QLCDNumber *m_numberCompare;
    QLCDNumber *m_numberRead;
    QLCDNumber *m_numberWrite;

    QPushButton *m_buttonStart;
    QPushButton *m_buttonPause;

  public slots:
    void run();
    void done();
    void Resize(int);
    void abort();
    void play();
    void pause();

  public:
    MenuWindow(QGraphicsScene *scene, QGraphicsView *view, QWidget *parent = nullptr);
    void INCRCMP();
    void INCRREAD();
    void INCRWRITE();
};
