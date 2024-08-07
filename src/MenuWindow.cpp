//
// Created by Alex Balta on 03.07.2024.
//

#include "../headers/MenuWindow.hpp"

MenuWindow::MenuWindow(QGraphicsScene *scene, QGraphicsView *view, QWidget *parent)
    : QWidget(parent),
      m_parent(parent),
      m_scene(scene),
      m_view(view),
      playing(false),
      m_link(nullptr),
      m_sort(nullptr) {

    m_chooseAlgorithm = new QComboBox(this);
    m_chooseAlgorithm->addItems({
                                    "Bubble Sort", "Quick Sort", "Merge Sort", "Radix Sort",
                                    "Bucket Sort", "Insertion Sort", "Heap Sort", "Selection Sort",
                                    "Sorting Networks", "Stupid Sorts"
                                });

    m_chooseOption = new QComboBox(this);
    m_optionManager = new OptionManager(m_chooseOption);
    connect(m_chooseAlgorithm, SIGNAL(currentIndexChanged(int)), m_optionManager, SLOT(updateOptions(int)));
    m_chooseAlgorithm->setCurrentIndex(1);
    m_chooseAlgorithm->setCurrentIndex(0); // To force a refresh

    auto delayLayout = new QHBoxLayout;
    m_chooseDelay = new QSlider(Qt::Horizontal);
    m_chooseDelay->setRange(0, 9);
    m_textDelay = new QLabel("0 ms");
    connect(m_chooseDelay, &QSlider::valueChanged, [this]() {
        m_textDelay->setText(QString::number(m_chooseDelay->value()) + " ms");
    });
    delayLayout->addWidget(m_chooseDelay);
    delayLayout->addWidget(m_textDelay);

    m_chooseDistribution = new QComboBox(this);
    m_chooseDistribution->addItems({"Regular", "Uniform", "Centered", "Split", "High", "Low"});

    m_chooseScramble = new QComboBox(this);
    m_chooseScramble->addItems({"Random", "Sorted-ish", "Reversed-ish", "Shuffle"});

    m_chooseSize = new QComboBox(this);
    m_chooseSize->addItems({"8", "16", "32", "64", "128", "256", "512", "1024"});
    m_chooseSize->setCurrentIndex(4);
//    connect(m_chooseSize, SIGNAL(currentIndexChanged(int)), this, SLOT(Resize(int)));

    m_numberCompare = new QLCDNumber(this);
    m_numberCompare->setDigitCount(10);
    m_numberRead = new QLCDNumber(this);
    m_numberRead->setDigitCount(10);
    m_numberWrite = new QLCDNumber(this);
    m_numberWrite->setDigitCount(10);

    m_buttonStart = new QPushButton("Start", this);
    m_buttonPause = new QPushButton("--", this);
    m_buttonPause->setEnabled(false);

    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(new QLabel("Algorithm:", this));
    m_layout->addWidget(m_chooseAlgorithm);
    m_layout->addWidget(new QLabel("Specification:", this));
    m_layout->addWidget(m_chooseOption);
    m_layout->addWidget(new QLabel("Delay:", this));
    m_layout->addLayout(delayLayout);
    m_layout->addWidget(new QLabel("Size:", this));
    m_layout->addWidget(m_chooseSize);
    m_layout->addWidget(new QLabel("Distribution:", this));
    m_layout->addWidget(m_chooseDistribution);
    m_layout->addWidget(new QLabel("Scramble:", this));
    m_layout->addWidget(m_chooseScramble);
    m_layout->addWidget(new QLabel("Comparisons", this));
    m_layout->addWidget(m_numberCompare);
    m_layout->addWidget(new QLabel("Accesses (read)", this));
    m_layout->addWidget(m_numberRead);
    m_layout->addWidget(new QLabel("Accesses (write)", this));
    m_layout->addWidget(m_numberWrite);

    m_layout->addWidget(m_buttonStart);
    m_layout->addWidget(m_buttonPause);

    connect(m_buttonStart, SIGNAL(clicked()), this, SLOT(run()));
}

void MenuWindow::run() {
    m_buttonStart->setText("Abort");
    disconnect(m_buttonStart, SIGNAL(clicked()), this, SLOT(run()));
    connect(m_buttonStart, SIGNAL(clicked()), this, SLOT(abort()));
    connect(m_buttonPause, SIGNAL(clicked()), this, SLOT(pause()));
    m_buttonPause->setText("Pause");
    m_buttonPause->setEnabled(true);
    int size = (1 << (m_chooseSize->currentIndex() + 3));

    m_array.resize(size);
    Distributor distributor(m_array);

    m_chooseAlgorithm->setEnabled(false);
    m_chooseOption->setEnabled(false);
    m_chooseDelay->setEnabled(false);
    m_chooseSize->setEnabled(false);
    m_chooseDistribution->setEnabled(false);
    m_chooseScramble->setEnabled(false);

    switch (m_chooseDistribution->currentIndex()) {
        case 0: distributor.DRegular();
            break;
        case 1: distributor.DUniform();
            break;
        case 2: distributor.DCentered();
            break;
        case 3: distributor.DSplit();
            break;
        case 4: distributor.DHigh();
            break;
        case 5: distributor.DLow();
            break;
    }
    switch (m_chooseScramble->currentIndex()) {
        case 0: distributor.SRandom();
            break;
        case 1: distributor.SSorted();
            break;
        case 2: distributor.SReversed();
            break;
        case 3: distributor.SShuffle();
            break;
    }
    int delay = m_chooseDelay->value() * 1000;

    m_link = new Linker(this, m_array, size, m_scene, delay);
    m_sort = new Sorter(m_link);

    switch (m_chooseAlgorithm->currentIndex()) {
        case OptionManager::BUBBLE_SORT:
            switch (m_chooseOption->currentIndex()) {
                case 0: m_sort->Bubble_upwards();
                    break;
                case 1: m_sort->Bubble_downwards();
                    break;
                case 2: m_sort->Bubble_shaker();
                    break;
                case 3: m_sort->Comb();
                    break;
            }
            break;
        case OptionManager::QUICK_SORT:
            switch (m_chooseOption->currentIndex()) {
                case 0: m_sort->Quick_naive();
                    break;
                case 1: m_sort->Quick_middle();
                    break;
                case 2: m_sort->Quick_optimized();
                    break;
                case 3: m_sort->Quick_median();
                    break;
            }
            break;
        case OptionManager::MERGE_SORT:
            switch (m_chooseOption->currentIndex()) {
                case 0: m_sort->Mergesort_standard();
                    break;
                case 1: m_sort->Mergesort_pack();
                    break;
                case 2: m_sort->Mergesort_weave();
                    break;
            }
            break;
        case OptionManager::RADIX_SORT:
            switch (m_chooseOption->currentIndex()) {
                case 0: m_sort->RadixLSD2();
                    break;
                case 1: m_sort->RadixLSD4();
                    break;
                case 2: m_sort->RadixLSD8();
                    break;
                case 3: m_sort->RadixMSD2();
                    break;
                case 4: m_sort->RadixMSD4();
                    break;
                case 5: m_sort->RadixMSD8();
                    break;
                case 6: m_sort->Counting();
                    break;
            }
            break;
        case OptionManager::BUCKET_SORT:
            switch (m_chooseOption->currentIndex()) {
                case 0: m_sort->Bucket();
                    break;
                case 1: m_sort->Sampler();
                    break;
            }
            break;
        case OptionManager::INSERTION_SORT:
            switch (m_chooseOption->currentIndex()) {
                case 0: m_sort->Insertion();
                    break;
                case 1: m_sort->Shell();
                    break;
                case 2: m_sort->BinInsertion();
                    break;
                case 3: m_sort->Gnomesort();
                    break;
            }
            break;
        case OptionManager::HEAP_SORT:
            switch (m_chooseOption->currentIndex()) {
                case 0: m_sort->Heapsort_max();
                    break;
                case 1: m_sort->Heapsort_sift();
                    break;
                case 2: m_sort->Heapsort_min();
                    break;
                case 3: m_sort->Heapsort_tern();
                    break;
                case 4: m_sort->SmoothSort();
                    break;
            }
            break;
        case OptionManager::SELECTION_SORT:
            switch (m_chooseOption->currentIndex()) {
                case 0: m_sort->Selection_max();
                    break;
                case 1: m_sort->Selection_min();
                    break;
                case 2: m_sort->Selection_dbl();
                    break;
                case 3: m_sort->Cycle();
                    break;
                case 4: m_sort->CycleOpt();
                    break;
                case 5: m_sort->Pancake();
                    break;
            }
            break;
        case OptionManager::SORTING_NETWORKS:
            switch (m_chooseOption->currentIndex()) {
                case 0: m_sort->Bitonic();
                    break;
                case 1: m_sort->OddEven();
                    break;
                case 2: m_sort->BitonicPara();
                    break;
                case 3: m_sort->OddEvenPara();
                    break;
                case 4: m_sort->ShearSort();
                    break;
            }
            break;
        case OptionManager::STUPID_SORTS:
            switch (m_chooseOption->currentIndex()) {
                case 0: m_sort->Slowsort();
                    break;
                case 1: m_sort->Stoogesort();
                    break;
                case 2: m_sort->Bogosort();
                    break;
                case 3: m_sort->LessBogosort();
                    break;
                case 4: m_sort->Randsort();
                    break;
            }
            break;
    }

    m_buttonStart->setText("Clear");
    m_buttonStart->setEnabled(true);
    m_buttonPause->setText("--");
    m_buttonPause->setEnabled(false);
    disconnect(m_buttonStart, SIGNAL(clicked()), this, SLOT(abort()));
    connect(m_buttonStart, SIGNAL(clicked()), this, SLOT(done()));
}

void MenuWindow::done() {
    m_array.clear();
    delete m_link;
    delete m_sort;
    m_link = nullptr;
    m_sort = nullptr;
    m_chooseAlgorithm->setEnabled(true);
    m_chooseOption->setEnabled(true);
    m_chooseDelay->setEnabled(true);
    m_chooseSize->setEnabled(true);
    m_chooseDistribution->setEnabled(true);
    m_chooseScramble->setEnabled(true);
    m_numberCompare->display(0);
    m_numberRead->display(0);
    m_numberWrite->display(0);
    m_buttonStart->setText("Start");
    m_buttonStart->setEnabled(true);
    disconnect(m_buttonStart, SIGNAL(clicked()), this, SLOT(done()));
    connect(m_buttonStart, SIGNAL(clicked()), this, SLOT(run()));
}

void MenuWindow::abort() {
    if (m_sort) {
        m_sort->stop();
    }
    play();
    disconnect(m_buttonStart, SIGNAL(clicked()), this, SLOT(abort()));
}

void MenuWindow::pause() {
    playing = false;
    disconnect(m_buttonPause, SIGNAL(clicked()), this, SLOT(pause()));
    connect(m_buttonPause, SIGNAL(clicked()), this, SLOT(play()));
    m_buttonPause->setText("Play");
    while (!playing) {
        QApplication::processEvents();
    }
}

void MenuWindow::play() {
    playing = true;
    disconnect(m_buttonPause, SIGNAL(clicked()), this, SLOT(play()));
    connect(m_buttonPause, SIGNAL(clicked()), this, SLOT(pause()));
    m_buttonPause->setText("Pause");
}

void MenuWindow::INCRCMP() {
    m_numberCompare->display(int(m_numberCompare->value()) + 1);
}

void MenuWindow::INCRREAD() {
    m_numberRead->display(int(m_numberRead->value()) + 1);
}

void MenuWindow::INCRWRITE() {
    m_numberWrite->display(int(m_numberWrite->value()) + 1);
}

void MenuWindow::Resize(int s) {
    if (s == 7) {
        m_parent->setFixedSize(1310, 620);
        m_view->setFixedSize(1100, 580);
        m_view->setSceneRect(0, 0, 1035, 580);
    } else {
        m_parent->setFixedSize(820, 620);
        m_view->setFixedSize(600, 580);
        m_view->setSceneRect(0, 0, 550, 580);
    }
}
