#include <iostream>
#include <string>
#include <iomanip>

#include <openssl/md5.h>

const size_t BUFFER_SIZE = 16;

int main(int argc, char** argv) {
  std::string input;
  std::cin >> input;

  unsigned char output[BUFFER_SIZE];

  int i = 0;
  bool found = false;
  while(!found) {
    std::string current_string = input + std::to_string(i);
    MD5(reinterpret_cast<const unsigned char*>(current_string.c_str()), current_string.size(), output);

    if(output[0] == 0 && output[1] == 0 && output[2] < 16) {
      found = true;
      break;
    }

    ++i;
  }

  std::cout << i << std::endl;
  return 0;
}
