/*
Write an efficient C function that takes two strings as arguments and removes the characters
from first string which are present in second string (mask string).
 */
void removeDirtyChars(string& s1, const string& s2) {
  const uint32_t len1 = s1.length(), len2 = s2.length();
  if (!len1 || !len2)
    return;

  uint32_t count[26];
  for (auto& i : count)
    i = 0;
  for (uint32_t i = 0; i < len2; ++i)
    ++count[s2[i]-'a'];
}
