//
// Created by Alex Balta on 03.07.2024.
//

#pragma once

#include <QString>

class Item {
  private:
    int val;
    int rank;
    int place;
    int swap;
    int cmp;
    int read;

  public:
    Item() : val(0), rank(-1), place(-1), swap(0), cmp(0), read(0) {}
    explicit Item(int v) : val(v), rank(-1), place(-1), swap(0), cmp(0), read(0) {}

    int getVal() const { return val; }
    int getRank() const { return rank; }
    int getPlace() const { return place; }
    int getSwap() const { return swap; }
    int getCmp() const { return cmp; }
    int getRead() const { return read; }

    void setVal(int v) { val = v; }
    void setRank(int r) { rank = r; }
    void setPlace(int p) { place = p; }
    void setSwap(int s) { swap = s; }
    void setCmp(int c) { cmp = c; }
    void setRead(int r) { read = r; }

    bool operator<(const Item &other) const {
        return val < other.val;
    }

    bool operator>(const Item &other) const {
        return val > other.val;
    }

    bool operator==(const Item &other) const {
        return val == other.val;
    }

    QString Tip() const {
        QString s = QString("Item n°%1\nValue: %2\nRank: %3\nRead: %4\nCompared: %5\nMoved: %6");
        return s.arg(QString::number(place),
                     QString::number(val),
                     (rank == -1) ? "???" : QString::number(rank),
                     QString::number(read),
                     QString::number(cmp),
                     QString::number(swap));
    }
};