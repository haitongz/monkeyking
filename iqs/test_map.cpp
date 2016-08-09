#include <iostream>
#include <map>

using namespace std;

struct strCmp
{
   bool operator()(const char* s1, const char* s2) const
   {
      return strcmp(s1, s2) < 0;
   }
};

int main()
{
   typedef map<const char*, unsigned int, strCmp>::iterator Iter;
   map<const char*, unsigned int, strCmp> ages;

   ages["Homer"] = 38;
   ages["Marge"] = 37;
   ages["Lisa"] = 8;
   ages["Maggie"] = 1;
   ages["Bart"] = 11;

   cout << "Bart is " << ages["Bart"] << " years old" << endl;
   cout << "In alphabetical order: " << endl;
   for (Iter iter = ages.begin(); iter != ages.end(); ++iter) {
      cout << (*iter).first << " is " << (*iter).second << " years old" << endl;
   }

   while (!ages.empty()) {
      cout << "testing empty() and erase()... " << (*ages.begin()).first << ", " << (*ages.begin()).second << endl;
      ages.erase(ages.begin());
   }

   cout << "all elements shall have been erased, size is " << ages.size() << endl;

   map<string, int> stringCounts;
   /*
      while (cin >> str)
         stringCounts[str]++;
   */
   string str = "my spoon is too big.";
   stringCounts[str]++;
   str = "my spoon is TOO big!";
   stringCounts[str]++;
   str = "my SPOON is TOO big!";
   stringCounts[str]++;
   str = "I like BANANA REPUBLIC!";
   stringCounts[str]++;
   str = "spoon";
   stringCounts[str]++;
   str = "spoons";
   stringCounts[str]++;

   cout << "testing count()... word 'spoon' repeats " << stringCounts.count("spoon") << " time(s)" << endl;
   map<string, int>::iterator iter = stringCounts.find("spoon");
   if (iter != stringCounts.end()) {
      cout << "testing find()... word '" << iter->first << "' repeats " << iter->second << " time(s)" << endl;
   }

   cout << "testing swap()..." << endl;
   map<string, int> secondMap;
   secondMap["This is second map"]++;
   stringCounts.swap(secondMap);
   for (map<string, int>::iterator iter = stringCounts.begin(); iter != stringCounts.end(); ++iter) {
      cout << "orginal map has " << iter->first << ", value is " << iter->second << endl;
   }
   for (map<string, int>::iterator iter = secondMap.begin(); iter != secondMap.end(); ++iter) {
      cout << "second map has " << iter->first << ", value is " << iter->second << endl;
   }

   cout << "testing clear()..." << endl;
   stringCounts.clear();
   cout << "all elements shall have been erased, size is " << stringCounts.size() << endl;

   stringCounts.insert(make_pair("Key 1", -1 ));
   stringCounts.insert(make_pair("Another key!", 32));
   stringCounts.insert(make_pair("Key the Three", 66667));

   for (iter = stringCounts.begin(); iter != stringCounts.end(); ++iter) {
      cout << "Key: '" << iter->first << "', Value: " << iter->second << endl;
   }
}
