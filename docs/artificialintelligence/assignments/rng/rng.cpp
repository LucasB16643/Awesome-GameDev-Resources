// add your imports here
#include <fstream>
#include <iostream>
#include <istream>
#include <unordered_set>
const std::string TEST_FOLDER = "\\tests\\";
unsigned int xorShift(unsigned int seed, int r1, int r2);

struct State {
  unsigned int x, y;

  bool operator==(const State& other) const {
    return x == other.x && y == other.y;
  }
};

namespace std {
template<>
  struct hash<State> {
    std::size_t operator()(const State& state) const { return state.x ^ state.y; }
  };
}

int main(){
  // code here

  int cycles = 0;
  int warmupPhase = 0;
  int numOfStates = 0;

  std::unordered_set<State> states;
State state = {0,0};


  unsigned int seed, N, min, max;
  std::cin >> seed >> N >> min >> max;
  unsigned int i;
unsigned int newSeed;
  state.x = seed;


  for(i = N; i >= 1; i--)
  {
    //Run xor shift
    state.y = xorShift(state.x, min, max);




    if (!states.contains(state)) {
      warmupPhase++;
    }

    states.insert({state});


     numOfStates = states.count(state);
    if (numOfStates == 2) {
      cycles++;
    }
    state.x = state.y;
  }
  warmupPhase -= cycles;
  std::cout << "the warmup period is: " << warmupPhase << std::endl;
  std::cout << "the cycle period is: " << cycles << std::endl;
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
