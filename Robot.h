#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

#include "Grid.h"

class Robot {
public:
  enum class DiagAffinity { AFFINITY_NONE, AFFINITY_RIGHT, AFFINITY_LEFT };
  Robot(Grid *grid) { m_pGrid = grid; }

  bool place(int x, int y, std::string strfacing) {
    std::vector<std::string>::const_iterator iter =
        std::find(FACINGS.begin(), FACINGS.end(), strfacing);
    int findex = (int)(iter - FACINGS.begin());

    if (findex < 4) {
      if (m_pGrid->canMoveTo(x, y)) {
        m_pGrid->clear(m_currentX, m_currentY);
        m_pGrid->moveTo(x, y);
        m_currentFacing = findex;
        m_currentX = x;
        m_currentY = y;
        return true;
      }
    }

    return false;
  }

  bool move(DiagAffinity dfinity = DiagAffinity::AFFINITY_NONE) {
    bool flag = false;
    int destX = -1, destY = -1;

    switch (m_currentFacing) {
    case 0: // north
      if (dfinity == DiagAffinity::AFFINITY_NONE) {
        destX = m_currentX;
        destY = m_currentY + 1;
      } else if (dfinity == DiagAffinity::AFFINITY_RIGHT) {
        destX = m_currentX + 1;
        destY = m_currentY + 1;
      } else if (dfinity == DiagAffinity::AFFINITY_LEFT) {
        destX = m_currentX - 1;
        destY = m_currentY + 1;
      }
      break;

    case 1: // east
      if (dfinity == DiagAffinity::AFFINITY_NONE) {
        destX = m_currentX + 1;
        destY = m_currentY;
      } else if (dfinity == DiagAffinity::AFFINITY_RIGHT) {
        destX = m_currentX + 1;
        destY = m_currentY - 1;
      } else if (dfinity == DiagAffinity::AFFINITY_LEFT) {
        destX = m_currentX + 1;
        destY = m_currentY + 1;
      }
      break;

    case 2: // south
      if (dfinity == DiagAffinity::AFFINITY_NONE) {
        destX = m_currentX;
        destY = m_currentY - 1;
      } else if (dfinity == DiagAffinity::AFFINITY_RIGHT) {
        destX = m_currentX - 1;
        destY = m_currentY - 1;
      } else if (dfinity == DiagAffinity::AFFINITY_LEFT) {
        destX = m_currentX + 1;
        destY = m_currentY - 1;
      }
      break;

    case 3: // west
      if (dfinity == DiagAffinity::AFFINITY_NONE) {
        destX = m_currentX - 1;
        destY = m_currentY;
      } else if (dfinity == DiagAffinity::AFFINITY_RIGHT) {
        destX = m_currentX - 1;
        destY = m_currentY + 1;
      } else if (dfinity == DiagAffinity::AFFINITY_LEFT) {
        destX = m_currentX - 1;
        destY = m_currentY - 1;
      }
      break;
    }

    if (m_pGrid->canMoveTo(destX, destY)) {
      m_pGrid->clear(m_currentX, m_currentY);
      m_pGrid->moveTo(destX, destY);
      m_currentX = destX;
      m_currentY = destY;
      flag = true;
    }

    return flag;
  }

  bool left() {
    bool flag = false;
    if (m_currentFacing >= 0) {
      m_currentFacing = m_currentFacing - 1 < 0 ? 3 : m_currentFacing - 1;
      flag = true;
    }
    return flag;
  }

  bool right() {
    bool flag = false;
    if (m_currentFacing >= 0) {
      m_currentFacing = (m_currentFacing + 1) % 4;
      flag = true;
    }
    return flag;
  }

  void report() {
    std::cout << "Output: " << m_currentX << "," << m_currentY << ","
              << ((m_currentFacing != -1) ? FACINGS[m_currentFacing] : "?")
              << std::endl;
  }

private:
  Grid *m_pGrid = nullptr;
  const std::vector<std::string> FACINGS = {"NORTH", "EAST", "SOUTH", "WEST"}; // keep order
  int m_currentFacing = -1;
  int m_currentX = -1;
  int m_currentY = -1;
};
