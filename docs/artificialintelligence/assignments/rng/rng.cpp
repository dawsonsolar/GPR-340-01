// add your imports here
#include <fstream>
#include <iostream>
#include <istream>
#include <random>
#include <unordered_set>
const std::string TEST_FOLDER = "\\tests\\";
unsigned int xorShift(unsigned int seed, int r1, int r2);
struct State
{
  unsigned int a, b;
  bool operator==(const State& other) const
  {
    return a == other.a && b == other.b;
  }
};

namespace std
{
  template <>
  struct hash<State>
  {
    std::size_t operator()(const State& s) const
    {
      return s.a ^ s.b;
    }
  };
}

int main(){
  std::unordered_set<State> states;
  State state = {1, 2};
  int cycles = 0;
  int warmups = 0;
  int statesCount = 0;



  unsigned int seed, N, min, max;
  std::cin >> seed >> N >> min >> max;
  unsigned int i;
  state.a = seed;

  for(i = N; i >= 1; i--) {
    //Run xor shift
    seed = xorShift(seed, min, max);
    state.b = seed;

    if(!states.contains(state))
    {
      warmups++;
    }
    states.insert({state});
    statesCount = states.count(state);
    if (statesCount == 2)
    {
      cycles++;
    }
  }
  warmups -= cycles;
}
//The purpose of this function is to take the number and xor shift it to output a pseudo-random number
    unsigned int xorShift(unsigned int seed, int r1, int r2)
{
  seed = seed xor (seed << 13);
  seed = seed xor (seed >> 17);
  seed = seed xor (seed << 5);
  int value = r1 + (seed % (r2 - r1 + 1)); //clamps the value to between r1 and r2
          //output the new values
          std::cout << value << std::endl;
  return seed;
}
