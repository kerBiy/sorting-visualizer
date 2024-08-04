// Created by Alex Balta on 03.07.2024.
//

#pragma once

#include <algorithm>
#include <random>

#include "Item.hpp"

class Distributor {
  private:
    std::vector<Item> &items;
    std::default_random_engine m_generator;

  public:
    /**
     * @brief The main constructor
     * @param size the size of the array
     * @param array an array with Items
     */
    explicit Distributor(std::vector<Item> &list);

    /**
     * DISTRIBUTIONS
     */
    void DRegular();
    void DUniform();
    void DCentered();
    void DSplit();
    void DHigh();
    void DLow();

    /**
     * SCRAMBLEs
     */
    void SRandom();
    void SSorted();
    void SReversed();
    void SShuffle();
};
