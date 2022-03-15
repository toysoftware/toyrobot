#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

class Grid {
public:
  struct Cell {
    int ncount;
    int nmax;
    bool valid;
  };

  Grid(std::vector<std::vector<Cell>> *pGridCells) {
    m_pGridCells = pGridCells;
  }

  bool canMoveTo(int x, int y) {
    if (x < 0 || y < 0) {
      return false;
    }

    if (y < m_pGridCells->size() && x < (*m_pGridCells)[y].size()) {
      if ((*m_pGridCells)[y][x].valid) {
        if ((*m_pGridCells)[y][x].ncount < (*m_pGridCells)[y][x].nmax) {
          return true;
        }
      }
    }
    return false;
  }

  void clear(int x, int y) {
    if (x >= 0 && y >= 0) {
      int count = (*m_pGridCells)[y][x].ncount;
      count--;
      (*m_pGridCells)[y][x].ncount = count >= 0 ? count : 0;
    }
  }

  bool moveTo(int x, int y) {
    if (x >= 0 && y >= 0 &&
        (*m_pGridCells)[y][x].ncount < (*m_pGridCells)[y][x].nmax) {
      (*m_pGridCells)[y][x].ncount++;
      return true;
    }
    return false;
  }

  void printgrid() {
    for (int y = 0; y < m_pGridCells->size(); y++) {
      for (int x = 0; x < (*m_pGridCells)[y].size(); x++) {
        std::cout << (*m_pGridCells)[y][x].ncount << " ";
      }
      std::cout << std::endl;
    }
  }

private:
  std::vector<std::vector<Cell>> *m_pGridCells = nullptr;
};
