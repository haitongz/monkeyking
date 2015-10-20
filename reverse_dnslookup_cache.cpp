/*
Reverse DNS look up is using an internet IP address to find a domain name.
For example, if you type 74.125.200.106 in browser, it automatically redirects to google.in.

How to implement Reverse DNS Look Up cache? Following are the operations needed from cache.
1) Add a IP address to URL Mapping in cache.
2) Find URL for a given IP address.
 */
#include <iostream>
#include <cstring>

using namespace std;

// There are atmost 11 different chars in a valid IP address
#define CHARS 11
// Maximum length of a valid IP address
#define MAX 50

// A utility function to find index of child for a given character 'c'
uint8_t getIndex(char c) { return (c == '.') ? 10 : (c-'0'); }

// A utility function to find character for a given child index.
char getCharFromIndex(const uint8_t i) { return (i == 10) ? '.' : ('0'+i); }

// Trie Node.
struct TrieNode {
  bool isLeaf;
  char* URL;
  TrieNode* child[CHARS];
};

// Function to create a new trie node
TrieNode* newTrieNode() {
  TrieNode* newNode = new TrieNode;
  newNode->isLeaf = false;
  newNode->URL = nullptr;

  for (uint8_t i = 0; i < CHARS; ++i)
    newNode->child[i] = nullptr;

  return newNode;
}

// This method inserts an ip address and the corresponding domain name in the trie. The last node in Trie contains the URL.
void insert(TrieNode* root, char* ipAddr, char* URL) {
  const uint32_t len = strlen(ipAddr);
  TrieNode* crawl = root;

  // Traversing over the length of the ip address.
  for (uint32_t level = 0; level < len; ++level) {
    // Get index of child node from current character in ipAddr.
    // Index must be from 0 to 10 where 0 to 9 is used for digits and 10 for dot
    const uint8_t index = getIndex(ipAddr[level]);

    // Create a new child if not exist already
    if (!crawl->child[index])
      crawl->child[index] = newTrieNode();

    // Move to the child
    crawl = crawl->child[index];
  }

  //Below needs to be carried out for the last node. Save the corresponding URL of the ip address in the last node of trie.
  crawl->isLeaf = true;
  crawl->URL = new char[strlen(URL)+1];
  strcpy(crawl->URL, URL);
}

// This function returns URL if given IP address is present in DNS cache.
// Else returns NULL
char* searchDNSCache(TrieNode* root, char* ipAddr) {
  TrieNode* crawl = root;
  const uint32_t len = strlen(ipAddr);

  // Traversal over the length of ip address.
  for (uint32_t level = 0; level < len; ++level) {
    uint8_t index = getIndex(ipAddr[level]);
    if (!crawl->child[index])
      return nullptr;
    crawl = crawl->child[index];
  }

  // If we find the last node for a given ip address, print the URL.
  if (crawl && crawl->isLeaf)
    return crawl->URL;

  return nullptr;
}

int main(int argc, char** argv) {
  char ipAddr[][MAX] = {"107.108.11.123", "107.109.123.255", "74.125.200.106"};
  char URL[][50] = {"www.samsung.com", "www.samsung.net", "www.google.in"};
  const uint32_t n = sizeof(ipAddr)/sizeof(ipAddr[0]);

  TrieNode* root = newTrieNode();
  // Inserts all the ip address and their corresponding domain name after ip address validation.
  for (uint32_t i = 0; i < n; ++i)
    insert(root, ipAddr[i], URL[i]);

  // If reverse DNS look up succeeds print the domain name along with DNS resolved.
  char ip[] = "107.108.11.123";
  char* res_url = searchDNSCache(root, ip);
  if (res_url)
    cout << "Reverse DNS look up resolved in cache: " << endl << ip << " --> " << res_url << endl;
  else
    cout << "Reverse DNS look up not resolved in cache!" << endl;

  return 0;
}
