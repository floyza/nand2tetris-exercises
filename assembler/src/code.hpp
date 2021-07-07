#ifndef __CODE_H_
#define __CODE_H_

#include <bitset>
#include <string>

std::bitset<3> dest_code(std::string i);
std::bitset<7> comp_code(std::string i);
std::bitset<3> jump_code(std::string i);

#endif // __CODE_H_
