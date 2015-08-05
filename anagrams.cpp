/*
Given an array of strings, return all groups of strings that are anagrams.
Note: All inputs will be in lower-case.
*/
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
//#include <cstring> // for bzero
#include "../linked_lists/list_node.h"

using namespace std;

bool areAnagrams(const string& s1, const string& s2) {
  if (s1.length() != s2.length())
    return false;

  map<char,size_t> m;

  for (auto& c : s1) {
    ++m[/*toupper*/(c)];
  }
  for (auto& c : s2) {
    --m[/*toupper*/(c)];
  }
  for (auto& c : s2) {
    if (m[/*toupper*/(c)] != 0)
      return false;
  }

  return true;
}

bool areAnagrams2(string s1, string s2) {
  sort(s1.begin(), s1.end());
  sort(s2.begin(), s2.end());
  return s1 == s2;
}
/*
bool isAnagram(const string& s1, const string& s2) {
  if (s1.length() != s2.length())
    return false;

  // Works well for ASCII strings with length less than 2^16
  // For longer string, overflow might happen
  uint32_t count[256];
  bzero(count, sizeof(count)*sizeof(uint32_t));

  int32_t index = -1;
  char c = '\0';

  // Scan s1, get its letters' distribution
  while (c = s1[++index]) {
    ++count[(uint32_t)c];
  }

  // Scan s2, and compare its letters' distribution with str1
  index = -1;
  while (c = s2[++index]) {
    --count[(uint32_t)c];
  }

  index = -1;
  while (++index < 256) {
    if (count[index] != 0)
      return false;
  }

  return true;
}
*/
vector<string> anagrams(vector<string>& strs) {
  map<string,vector<string>> recs;

  for (uint32_t i = 0; i < strs.size(); ++i) {
    string s = strs[i];
    sort(s.begin(), s.end());
    recs[s].push_back(strs[i]);
  }

  vector<string> res;
  for (map<string,vector<string>>::const_iterator iter = recs.begin();
       iter != recs.end(); ++iter) {
    if (iter->second.size() > 1) {
      for (uint32_t i = 0; i < iter->second.size(); ++i) {
        res.push_back(iter->second[i]);
      }
    }
  }

  return res;
}

// sort an array of strings so that anagrams are next to each other
struct ListNode2 : public ListNodeT<string> {
  ListNode2(const string& v)
      : ListNodeT<string>(v), last_ana(NULL) {
  }

  ListNode2* last_ana;
};

void anaInsert(ListNode2** head, ListNode2* nd) {
  if (!head) {
#ifdef _DEBUG_
    //cerr << "Null head!" << endl;
#endif
    return;
  } else if (!(*head)) {
    *head = nd;
    return;
  }

  ListNode2* curr = *head;
  ListNode2* prev = NULL;

  while (curr) {
    if (areAnagrams(curr->value, nd->value)) { // insert new node after last_ana
      ListNode2* pos = curr->last_ana ? curr->last_ana : curr;
      ListNodeT<string>* next = pos->next;
      pos->next = nd;
      nd->next = next;
      curr->last_ana = nd;
      return;
    } else {
      prev = curr->last_ana ? curr->last_ana : curr;
      curr = (ListNode2*)prev->next;
    }
  }

  curr = *head;
  prev = NULL;
  while (curr) {
    if (less<string>()(nd->value, curr->value)) {
      nd->next = curr;
      if (!prev) { // head
        *head = nd;
      } else {
        prev->next = nd;
      }

      break;
    } else {
      prev = curr->last_ana ? curr->last_ana : curr;
      if (!prev->next) { // end of list
        prev->next = nd;
        prev = nd;
      }

      curr = (ListNode2*)prev->next;
    }
  }
}

void anaSort(const vector<string>& array) {
  ListNode2* head = new ListNode2(array[0]);

  for (uint32_t i = 1; i < array.size(); ++i) {
    ListNode2* nd = new ListNode2(array[i]);
    anaInsert(&head, nd);
  }

  ListNode2* curr = head;
  while (curr) {
    cout << "Attention: " << curr->value << std::endl;
    ListNodeT<string>* next = curr->next;
    delete curr;
    curr = (ListNode2*)next;
  }
}

int main(int argc, char** argv) {
/*  if (argc < 3 || argc > 3) {
    cerr << "Illegal Arguments!" << endl;
    return -1;
  }
*/
  string s1("123");
  string s2("321");
  cout << "Strings are " << (areAnagrams(s1, s2) ? "" : "not ") << "anagrams!" << endl;

  vector<std::string> strs;
  strs.push_back("zbc");
  strs.push_back("cvjlafoqwer");
  strs.push_back("opqwuqoildnzcvn");
  strs.push_back("cvoermpdfmladf");
  strs.push_back("cmvnqweroqsdlvzm");
  strs.push_back("bzc");
  strs.push_back("ccccc");
  strs.push_back("cvnzcmveoqru");
  strs.push_back("abmntyiewqozc");

  anaSort(strs);
  return 0;
}
