#include <iostream>

#include <unistd.h>

using namespace std;

const size_t BUFFER_SIZE = 1024;
const int STD_IN = 0;
const char UP = '(';
const char DOWN = ')';

int main(int argc, char** argv) {
  char buffer[1024];
  ssize_t count = read(STD_IN, buffer, BUFFER_SIZE);
  int floor = 0;

  while(count > 0) {
    for(int i = 0 ; i < count ; ++i) {
      if(buffer[i] == UP)
	++floor;
      else if(buffer[i] == DOWN)
	--floor;
    }
    count = read(STD_IN, buffer, BUFFER_SIZE);
  }
  cout << "Final floor is: " << floor << endl;
}
