// add your imports here
#include <fstream>
#include <iostream>
#include <istream>
#include <unordered_set>
const std::string TEST_FOLDER = "\\tests\\";
unsigned int xorShift(unsigned int seed, int r1, int r2);
//create struct for state and its operator
struct State {
  unsigned int x, y;

  bool operator==(const State& other) const {
    return x == other.x && y == other.y;
  }
};
// set up template and struct for the hash  and operator
namespace std {
template<>
  struct hash<State> {
    std::size_t operator()(const State& state) const { return state.x ^ state.y; }
  };
}

int main(){
  // code here
//variables for phases
  int cycles = 0;
  int warmupPhase = 0;
  int numOfStates = 0;

  //create unordered_set and a state
  std::unordered_set<State> states;
State state = {0,0};

//create variables and get input for them
  unsigned int seed, N, min, max;
  std::cin >> seed >> N >> min >> max;
//create a variable for loop iterations
  unsigned int i;
//assign seed value to state.x
  state.x = seed;


  for(i = N; i >= 1; i--)
  {
    //Run xor shift using state.x as seed and store in state.y
    state.y = xorShift(state.x, min, max);



    //check if state is already in set if not add to warmup counter
    if (!states.contains(state)) {
      warmupPhase++;
      
    }


   //check number of times a state appears in the set
     numOfStates = states.count(state);
    //if we do have a repeating value add to the cycles variable to see how long the cycle lasts
    if (numOfStates == 2) {
      cycles++;
    }
    // add the state into the set
    states.insert({state});
    //set state.x to the value of state.y to be used as the new seed for xorshift
    state.x = state.y;
  }
  //remove the cycle length for the warmups to see how long the warmup is
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
