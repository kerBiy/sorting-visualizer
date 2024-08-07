// Created by Alex Balta on 03.07.2024.
//

#include "Distributor.hpp"

Distributor::Distributor(std::vector<Item> &list)
    : items(list),
      m_generator(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count())) {}

// DISTRIBUTIONS

void Distributor::DRegular() {
    for (int i = 0; i < items.size(); ++i) {
        items[i] = Item(items.size() <= 512 ? i : i / 2);
    }
}

void Distributor::DUniform() {
    std::uniform_int_distribution<int> distribution(0, std::min((int) items.size(), 512) - 1);

    for (auto &item : items) {
        item = Item(distribution(m_generator));
    }

    std::sort(items.begin(), items.end());
}

void Distributor::DCentered() {
    std::normal_distribution<double> distribution(std::min((int) items.size(), 512) / 2.0,
                                                  (int) std::min((int) items.size(), 512) / 5.0);

    for (int i = 0; i < items.size();) {
        double number = distribution(m_generator);
        if (number >= 0.0 && number < std::min((int) items.size(), 512)) {
            items[i++] = Item(static_cast<int>(number));
        }
    }
    std::sort(items.begin(), items.end());
}

void Distributor::DSplit() {
    DCentered();
    for (auto &item : items) {
        int value = item.getVal();
        int mid = std::min((int) items.size(), 512) / 2;
        item.setVal(value >= mid ? value - mid : value + mid);
    }
    std::sort(items.begin(), items.end());
}

void Distributor::DHigh() {
    std::normal_distribution<double> distribution(std::min((int) items.size(), 512) / 1.0,
                                                  std::min((int) items.size(), 512) / 3.0);

    for (int i = 0; i < items.size();) {
        double number = distribution(m_generator);
        if (number >= 0.0 && number < std::min((int) items.size(), 512)) {
            items[i++] = Item(static_cast<int>(number));
        }
    }
    std::sort(items.begin(), items.end());
}

void Distributor::DLow() {
    std::normal_distribution<double> distribution(0.0, std::min((int) items.size(), 512) / 3.0);

    for (int i = 0; i < items.size();) {
        double number = distribution(m_generator);
        if (number >= 0.0 && number < std::min((int) items.size(), 512)) {
            items[i++] = Item(static_cast<int>(number));
        }
    }
    std::sort(items.begin(), items.end());
}

// SCRAMBLES

void Distributor::SRandom() {
    std::uniform_int_distribution<int> distribution(0, std::min((int) items.size(), 512) - 1);

    for (auto &item : items) {
        std::swap(item, items[distribution(m_generator)]);
    }
}

void Distributor::SSorted() {
    int lg = 0;
    for (int i = 1; i < items.size(); i <<= 1) { lg++; }
    for (int i = 0; i < items.size(); ++i) {
        std::uniform_int_distribution<int> distribution(std::max(0, i - lg), std::min((int) items.size() - 1, i + lg));
        std::swap(items[i], items[distribution(m_generator)]);
    }
}

void Distributor::SReversed() {
    for (int i = 0; i < items.size() / 2; ++i) {
        std::swap(items[i], items[items.size() - 1 - i]);
    }
    SSorted();
}

void Distributor::SShuffle() {
    SSorted();
    for (int i = 0; i < items.size() / 2; i += 2) {
        std::swap(items[i], items[items.size() - 1 - i]);
    }
}
