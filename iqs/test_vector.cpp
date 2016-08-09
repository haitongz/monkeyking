#include <iostream>
#include <vector>

using namespace std;

int main()
{
   vector<int> v;
   v.assign(10, 42);

   for (int i = 0; i < v.size(); ++i) {
      cout << v[i] << " ";
   }

   cout << endl;

   vector<int> v1;
   for (int i = 0; i < 10; ++i) {
      v1.push_back(i);
   }

   vector<int> v2;
   v2.assign(v1.begin(), v1.end());
   for (int i = 0; i < v2.size(); ++i) {
      cout << v2[i] << " ";
   }
   cout << endl;

   for (int i = 0; i < 10; ++i) {
      cout << "Element " << i << " is " << v.at(i) << endl;
   }

   for (int i = 0; i < 5; ++i) {
      v.push_back(i);
   }
   cout << "The first element is " << v.front() << " and the last element is " << v.back() << endl;

   /*
   vector<string> words;
   string str;
   while (cin >> str)
      words.push_back(str);

   vector<string>::iterator iter;
   for (iter = words.begin(); iter != words.end(); ++iter)
   {
      cout << *iter << endl;
   }
   */
   vector<int> v3(10);
   cout << "The capacity of v3 is " << v3.capacity() << endl;

   vector<int> v4;
   v4.reserve(20);
   cout << "The capacity of v4 is " << v4.capacity() << endl;

   vector<int> v_i;
   v_i.resize(10);
   cout << "size of v_i is " << v_i.size() << endl;
   cout << "capacity of v_i is " << v_i.capacity() << endl;

   v_i.push_back(1);
   cout << "size of v_i is " << v_i.size() << endl;
   cout << "capacity of v_i is " << v_i.capacity() << endl;
   for (int i = 0; i < v_i.capacity(); ++i) {
      cout << i << "th element is " << v_i[i] << endl;
   }

   vector<int> v5;
   for (int i = 0; i < 5; ++i) {
      v5.push_back(i);
   }

   while (!v5.empty()) {
      cout << v5.back() << endl;
      v5.pop_back();
   }

   vector<int> v6;
   v6.push_back(0);
   v6.push_back(1);
   v6.push_back(2);
   v6.push_back(3);

   int bad_val = *(v6.end());
   cout << "bad_val is " << bad_val << endl;

   int good_val = *(v6.end() - 1);
   cout << "good_val is " << good_val << endl;
   vector<int> v7(5, 789);
   vector<int>::iterator it;

   for (it = v7.begin(); it != v7.end(); ++it) {
      cout << *it << endl;
   }

   // Create a vector, load it with the first ten characters of the alphabet
   vector<char> alphaVector;
   for (int i = 0; i < 10; ++i) {
      alphaVector.push_back(i + 65);
   }

   int size = alphaVector.size();
   vector<char>::iterator startIterator;
   vector<char>::iterator tempIterator;

   for (int i = 0; i < size; ++i) {
      startIterator = alphaVector.begin();
      alphaVector.erase(startIterator);

      // Display the vector
      for (tempIterator = alphaVector.begin(); tempIterator != alphaVector.end(); ++tempIterator) {
         cout << *tempIterator;
      }
      cout << endl;
   }

   // create a vector, load it with the first ten characters of the alphabet
   alphaVector.clear();
   for (int i = 0; i < 10; ++i) {
      alphaVector.push_back(i + 65);
   }

   // display the complete vector
   for (int i = 0; i < alphaVector.size(); ++i) {
      cout << alphaVector[i];
   }
   cout << endl;

   // use erase to remove all but the first two and last three elements
   // of the vector
   alphaVector.erase(alphaVector.begin() + 2, alphaVector.end() - 3);
   // display the modified vector

   for (int i = 0; i < alphaVector.size(); ++i) {
      cout << alphaVector[i];
   }
   cout << endl;

   /*
   words.clear();

   while (cin >> str)
      words.push_back(str);
   std::sort(words.begin(), words.end());

   cout << "In alphabetical order, the first word is '" << words.front() << "'." << endl;
   */
   // Create a vector, load it with the first 10 characters of the alphabet
   vector<char> betaVector;
   for (int i = 0; i < 10; ++i) {
      betaVector.push_back(i+65);
   }

   // Insert four C's into the vector
   vector<char>::iterator theIterator = betaVector.begin();
   betaVector.insert(theIterator, 4, 'C');

   // Display the vector
   for (theIterator = betaVector.begin(); theIterator != betaVector.end(); ++theIterator) {
      cout << *theIterator;
   }

   vector<int> v7_1;
   v7_1.push_back(0);
   v7_1.push_back(1);
   v7_1.push_back(2);
   v7_1.push_back(3);

   vector<int> v8;
   v8.push_back(5);
   v8.push_back(6);
   v8.push_back(7);
   v8.push_back(8);

   cout << "Before, v8 is: ";

   for (int i = 0; i < v8.size(); ++i) {
      cout << v8[i] << " ";
   }
   cout << endl;

   v8.insert(v8.end(), v7_1.begin(), v7_1.end());
   cout << "After, v8 is: ";

   for (int i = 0; i < v8.size(); ++i) {
      cout << v8[i] << " ";
   }
   cout << endl;

   vector<string> v9;
   v9.push_back("I'm in v1!");
   vector<string> v10;
   v10.push_back("And I'm in v2!");
   v9.swap(v10);
   cout << "The first element in v9 is " << v9.front() << endl;
   cout << "The first element in v10 is " << v10.front() << endl;

   /*
   // create a vector of random integers
   cout << "original vector: ";
   vector<int> v11;

   for (int i = 0; i < 10; ++i)
   {
      int num = (int) rand() % 10;
      cout << num << " ";
      v11.push_back(num);
   }

   cout << endl;

   // find the first element of v that is even
   vector<int>::iterator iter1 = v11.begin();
   while (iter1 != v11.end() && *iter1 % 2 != 0)
   {
   ++iter1;
   }

   // find the last element of v that is even

   vector<int>::iterator iter2 = v11.end();
   do
   {
   --iter2;
   }
   while (iter2 != v11.begin() && *iter2 % 2 != 0);

   // only proceed if we find both numbers
   if (iter1 != v11.end() && iter2 != v11.begin())
   {
   cout << "first even number: " << *iter1 << ", last even number: " << *iter2 << endl;
   cout << "new vector: ";
   vector<int> v12(iter1, iter2);
   for (int i = 0; i < v12.size(); ++i)
   {
   cout << v12[i] << " ";
   }
   cout << endl;
   }
   */
}
