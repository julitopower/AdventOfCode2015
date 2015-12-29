#ifndef COMMAND
#define COMMAND

#include <cstdlib>
#include <string>
#include <boost/algorithm/string.hpp>

enum class CommandType {
  ON, OFF, TOGGLE
    };

struct Command {

  Command(CommandType t, size_t x0,size_t y0, size_t x1, size_t y1)
    : type(t), x0(x0), y0(y0), x1(x1), y1(y1) {}
  
  const CommandType type;
  const size_t x0, y0, x1, y1;
};

Command buildCommand(const std::string& line) {
  std::vector<std::string> chunks;
  boost::split(chunks, line, boost::is_any_of(" "));

  CommandType t;
  size_t from_index, to_index;

  //Determine CommandType
  if(chunks.size() == 4) {
    t = CommandType::TOGGLE;
    from_index = 1;
    to_index = 3;
  } else {
    from_index = 2;
    to_index = 4;
   
    if(chunks[1] == "on") {
      t = CommandType::ON;
    } else {
      t = CommandType::OFF; 
    }
  }

  std::vector<std::string> coord;
  boost::split(coord, chunks[from_index], boost::is_any_of(","));
  size_t x0 = stoi(coord[0]);
  size_t y0 = stoi(coord[1]);

  coord.clear();
  boost::split(coord, chunks[to_index], boost::is_any_of(","));
  size_t x1 = stoi(coord[0]);
  size_t y1 = stoi(coord[1]);
  
  return Command(t, x0, y0, x1, y1);
}

#endif // COMMAND
