#include <iostream>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>

struct Data {
  std::string name;
  int speed;
  int runningTime;
  int restingTime;

  int cycleTime() {
    return runningTime + restingTime;
  }
};

size_t parse_line(const std::string& line);

int main (int argc, char** argv) {
  std::string line;
  std::getline(std::cin, line);
  size_t simulationTime = std::stoi(line);
  std::getline(std::cin, line);  

  std::vector<Data> dataList;

  while(!std::cin.eof()) {
    std::vector<std::string> chunks;
    boost::split(chunks, line, boost::is_any_of(" "));    
    Data d {chunks[0], std::stoi(chunks[3]), std::stoi(chunks[6]), std::stoi(chunks[13])};
    dataList.push_back(d);
    std::getline(std::cin, line);
  }

  int maxDistance = 0;
  for(Data& d : dataList) {
    size_t cycles = simulationTime / d.cycleTime();
    int distance = cycles * d.speed * d.runningTime;
    if((cycles * d.cycleTime()) < simulationTime) {
      int rest = simulationTime - (cycles * d.cycleTime());
      if(d.runningTime < rest) {
	distance += d.speed * d.runningTime;
      } else {
	distance += d.speed * rest;
      }
    }
    if(distance > maxDistance)
      maxDistance = distance;
    std::cout << d.name << ": " << distance << std::endl;
  }

  std::cout << maxDistance << std::endl;

}
