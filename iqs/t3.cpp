#include <iostream>

class String{
        public:
                explicit String(char ch , int n = 1){}
                String(const char *p){}
        private :
                void operator=(const char*){}
};


int main(){
        String x = "aaa";
        return 0;
}
