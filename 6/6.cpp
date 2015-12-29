#include "Command.hpp"
#include <iostream>
#include <string>
#include <array>

std::array<bool, 1000000> grid;
const int COLS = 1000;
const int ROWS = 1000;

void init() {
  for(auto& v : grid)
    v = false;
}

void set_value(bool value, size_t x0, size_t y0, size_t x1, size_t y1) {
  for(int row = y0; row <= y1 ; ++row) {
    for(int col = x0 ; col <= x1 ; ++col) {
      grid[COLS * row + col] = value;
    } 
  }
}

void on(size_t x0, size_t y0, size_t x1, size_t y1) {
  set_value(true, x0, y0, x1, y1);
}

void off(size_t x0, size_t y0, size_t x1, size_t y1) {
  set_value(false, x0, y0, x1, y1);
}

void toggle(size_t x0, size_t y0, size_t x1, size_t y1) {
  for(int row = y0; row <= y1 ; ++row) {
    for(int col = x0 ; col <= x1 ; ++col) {
      grid[COLS * row + col] = !grid[COLS * row + col];
    } 
  }
}

void run_command(const Command& c) {
  switch(c.type) {
  case CommandType::ON:
    on(c.x0, c.y0, c.x1, c.y1);
    break;
  case CommandType::OFF:
    off(c.x0, c.y0, c.x1, c.y1);
    break;
  case CommandType::TOGGLE:
    toggle(c.x0, c.y0, c.x1, c.y1);
  }
}

int main(int argc, char** argv) {
  init();
  std::string line;
  std::getline(std::cin, line);

  while(!std::cin.eof()) {
    run_command(buildCommand(line));
    std::getline(std::cin, line);    
  }

  size_t count = 0;
  for(auto& v : grid) {
    if(v == true)
      ++count;
  }

  std::cout << count << std::endl;
  return 0;
}
