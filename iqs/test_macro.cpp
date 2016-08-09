#include <iostream>

#define STATE_CREATER( x ) x##State

const char* UN = "Unstarted";

class State
{
   public:
      State() {
         std::cout << "Base State" << std::endl;
      }
};

class UnstartedState : public State
{
   public:
      UnstartedState() {
         std::cout << "Unstarted State!" << std::endl;
      }
};

int main()
{
   State* p = new STATE_CREATER( Unstarted );
   return 0;
}
