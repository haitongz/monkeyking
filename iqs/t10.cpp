#include <iostream>

using namespace std;

class Someclass {
public:
	int x;
public :
	Someclass(int xx) : x(xx) { }
	Someclass(const Someclass& a) { x = a.x ; x++;} 
	void operator =(const Someclass& a1) { x = a1.x ; x--;}
};
int main( )
{	
	Someclass a(4);
        Someclass b = a;
        cout << b.x << endl;
return 0;
}
