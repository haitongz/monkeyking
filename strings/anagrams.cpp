#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

bool checkAnagram(const string& s1, const string& s2) {
  if (s1.length() != s2.length())
    return false;

  map<char,uint> mem;

  for (const auto c : s1) {
    ++mem[c];
  }
  for (const auto c : s2) {
    --mem[c];
  }
  for (const auto& iter : mem) {
    if (iter.second) { // for cases like "abcd" and "aacd"
      return false;
    }
  }

  return true;
}

bool checkAnagram2(string s1, string s2) {
  sort(s1.begin(), s1.end());
  sort(s2.begin(), s2.end());
  return s1 == s2;
}

/*
Given an array of strings, return all groups of strings that are anagrams.
Note: All inputs will be in lower-case.
 */
vector<string> anagrams(vector<string>& strs) {
  if (strs.size() < 2) {
    return {};
  }

  map<string,vector<string>> mem;

  for (const auto& s : strs) {
    string cp = s;
    sort(cp.begin(), cp.end());
    mem[cp].push_back(s);
  }

  vector<string> ret;
  for (const auto& iter : mem) {
    if (iter.second.size() > 1) {
      for (const auto& s : iter.second) {
        ret.push_back(s);
      }
    }
  }

  return ret;
}

// sort an array of strings so that anagrams are next to each other
struct ListNode {
  ListNode(const string& s)
    : value(s)
    , next(nullptr)
    , lastAnagram(nullptr) {
  }

  string value;
  ListNode* next;
  ListNode* lastAnagram;
};

void anagramInsert(ListNode** head, ListNode* nd) {
  if (!head) {
#ifdef _DEBUG_
    cerr << "Invalid argument!" << endl;
#endif
    return;
  } else if (!(*head)) {
    *head = nd;
    return;
  }

  auto curr = *head;
  ListNode* prev = nullptr;

  while (curr) {
    if (checkAnagram(curr->value, nd->value)) { // insert new node after lastAnagram
      ListNode* pos = curr->lastAnagram ? curr->lastAnagram : curr;
      ListNode* next = pos->next;
      pos->next = nd;
      nd->next = next;
      curr->lastAnagram = nd;
      return;
    } else {
      prev = curr->lastAnagram ? curr->lastAnagram : curr;
      curr = prev->next;
    }
  }

  curr = *head;
  prev = nullptr;
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
      prev = curr->lastAnagram ? curr->lastAnagram : curr;
      if (!prev->next) { // end of list
        prev->next = nd;
        prev = nd;
      }

      curr = (ListNode*)prev->next;
    }
  }
}

void anagramSort(const vector<string>& strs) {
  ListNode dummy("");
  auto head = &dummy;

  for (const auto& s : strs) {
    ListNode* nd = new ListNode(s);
    anagramInsert(&head, nd);
  }

  auto curr = head->next;
  while (curr) {
    cout << curr->value << std::endl;
    auto next = curr->next;
    delete curr;
    curr = next;
  }
}

int main(int argc, char** argv) {
  string s1("123");
  string s2("321");
  cout << "Strings are " << (checkAnagram(s1, s2) ? "" : "not ") << "anagrams!" << endl;

  vector<string> strs;
  strs.push_back("zbc");
  strs.push_back("cvjlafoqwer");
  strs.push_back("opqwuqoildnzcvn");
  strs.push_back("cvoermpdfmladf");
  strs.push_back("cmvnqweroqsdlvzm");
  strs.push_back("bzc");
  strs.push_back("ccccc");
  strs.push_back("cvnzcmveoqru");
  strs.push_back("abmntyiewqozc");

  anagramSort(strs);
  return 0;
}
