//
// Created by Alex Balta on 03.07.2024.
//

#pragma once

#include <QComboBox>

class OptionManager : public QObject {
  Q_OBJECT
  public:
    enum Algorithms {
        BUBBLE_SORT = 0,
        QUICK_SORT,
        MERGE_SORT,
        RADIX_SORT,
        BUCKET_SORT,
        INSERTION_SORT,
        HEAP_SORT,
        SELECTION_SORT,
        SORTING_NETWORKS,
        STUPID_SORTS
    };

  private:
    QComboBox *m_menu;

  public slots:
    /**
     * @brief It updates the specification option for each sorting type
     * @param algorithm the algorithm you want (must be from the OptionManager::Algorithms enum
     */
    void updateOptions(int algorithm);

  public:
    /**
     * @brief This is the main constructor
     * @param menu the combo box you want to manage
     */
    explicit OptionManager(QComboBox *menu);
};

