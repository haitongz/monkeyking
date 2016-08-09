#include <iostream>

using namespace std;

class Mother

{

public:

      Mother(){toPrint();}

      ~Mother(){toPrint();}

      virtual void toPrint (){cout << "Mother" << endl;}

} ;

class Daughter : public Mother

{

public:

      Daughter(){toPrint();}

      ~Daughter(){toPrint();}

      virtual void toPrint() {cout << "Daughter" << endl;}

};

 

int main(int argc, char **argv)

{

      Mother* d= new Daughter();

      delete d;

      return 0;

}
