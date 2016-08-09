#include <string>

void log(std::string message)
{
}

class Account
{
   public:
      Account(int id);
      virtual ~Account();
      virtual std::string get_name() { return ""; }
      int get_id() { return 0; }
};

Account::~Account()
{
   log("Destroying: " + get_name());
}

int main()
{
   Account a(0);
   return 0;
}
