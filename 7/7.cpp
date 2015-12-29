#include "Element.hpp"
#include <iostream>
#include <boost/algorithm/string.hpp>

const std::string AND = "AND";
const std::string OR = "OR";
const std::string LSHIFT = "LSHIFT";
const std::string RSHIFT = "RSHIFT";

std::shared_ptr<Element> createInput(const std::string& input, Circuit& circuit);
void parse(const std::string& line, Circuit& circuit);

int main(int argc, char** argv) {
  Circuit circuit;

  std::string line;
  std::getline(std::cin, line);

  while(!std::cin.eof()) {
    parse(line, circuit);
    std::getline(std::cin, line);    
  }

  circuit.print();
  std::cout << circuit.getWire("a")->getValue() << std::endl;

}

void parse(const std::string& line, Circuit& circuit) {
  std::vector<std::string> chunks;
  boost::split(chunks, line, boost::is_any_of(" "));
  //Gates have 5 elements in the line
  //Not has 4 elements
  //Signal and wire to wire have 3 elements
  if(chunks.size() == 5) {
    std::cout << "Gate: " << line << std::endl;
    std::shared_ptr<Element> gate;
    auto op = chunks[1];
    if(op == AND)
      gate = circuit.buildAnd();
    else if(op ==  OR)
      gate = circuit.buildOr();
    else if(op == LSHIFT)
      gate = circuit.buildLShift();
    else if(op ==RSHIFT)
      gate = circuit.buildRShift();
    
    auto input1 = createInput(chunks[0], circuit);
    auto input2 = createInput(chunks[2], circuit);
    auto output = createInput(chunks[4], circuit);
    input1->addOutput(gate);
    input2->addOutput(gate);
    gate->addOutput(output);
  } else if(chunks.size() == 4) {
    std::cout << "NOT: " << line << std::endl;
    auto gate = circuit.buildNot();
    auto input = createInput(chunks[1], circuit);
    auto output = createInput(chunks[3], circuit);
    input->addOutput(gate);
    gate->addOutput(output);
  } else {
    std::cout << "Wire|Signal: " << line << std::endl;
    auto input = createInput(chunks[0], circuit);
    auto output = createInput(chunks[2], circuit);
    input->addOutput(output);
  }
}

std::shared_ptr<Element> createInput(const std::string& input, Circuit& circuit) {
  try {
    unsigned short int value = std::stoi(input);
    return circuit.buildSignal(value);
  } catch(...) {
    auto wire = circuit.getWire(input);
    if(wire.get() == nullptr) {
      return circuit.buildWire(input);
    } else {
      return wire;
    }
  }
}
