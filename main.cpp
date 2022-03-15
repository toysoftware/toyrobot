#include <iostream>
#include <sstream>

#include "Grid.h"
#include "Robot.h"

std::vector<std::string> parseInput(const std::string &s, char delim = ' ') {
  std::stringstream ss(s);
  std::string item;
  std::vector<std::string> tokens;
  while (getline(ss, item, delim)) {
    tokens.push_back(item);
  }
  return tokens;
}

int main(int argc, char *argv[]) {
  // 5x5 dimensions
  std::vector<std::vector<Grid::Cell>> gridmap = {
      {{0, 1, true}, {0, 1, true}, {0, 1, true}, {0, 1, true}, {0, 1, true}},
      {{0, 1, true}, {0, 1, true}, {0, 1, true}, {0, 1, true}, {0, 1, true}},
      {{0, 1, true}, {0, 1, true}, {0, 1, true}, {0, 1, true}, {0, 1, true}},
      {{0, 1, true}, {0, 1, true}, {0, 1, true}, {0, 1, true}, {0, 1, true}},
      {{0, 1, true}, {0, 1, true}, {0, 1, true}, {0, 1, true}, {0, 1, true}},
  };

  Grid grid(&gridmap);
  Robot robot(&grid);

  while (true) {
    bool flag;
    std::string input;
    getline(std::cin, input);

    if (input.size() == 0) {
      break;
    }

    std::vector<std::string> cmd = parseInput(input);

    if (cmd[0] == "PLACE") {
      std::vector<std::string> params = parseInput(cmd[1], ',');
      int x = std::stoi(params[0]);
      int y = std::stoi(params[1]);
      std::string facing = params[2];
      flag = robot.place(x, y, facing);
      if (!flag)
        std::cout << "Error: " << std::endl;
    } else if (cmd[0] == "MOVE") {
      flag = robot.move();
      if (!flag)
        std::cout << "Error: " << std::endl;
    } else if (cmd[0] == "LEFT") {
      flag = robot.left();
      if (!flag)
        std::cout << "Error: " << std::endl;
    } else if (cmd[0] == "RIGHT") {
      flag = robot.right();
      if (!flag)
        std::cout << "Error: " << std::endl;
    } else if (cmd[0] == "REPORT") {
      robot.report();
    }
  }

  return 0;
}
