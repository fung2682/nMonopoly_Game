#include <string>
using namespace std;

#ifndef TOKEN_H
#define TOKEN_H
const int token_size = 10;
const string token_[token_size] = {"\xE2\x99\x9a", "\xe2\x99\x9b", "\xe2\x99\x9c", "\xe2\x99\x9d", "\xe2\x99\x9e", "\xe2\x99\x9f", "\xE2\x99\xA0", "\xE2\x99\xA3", "\xE2\x99\xA5", "\xE2\x99\xA6"};
string token(int n);
#endif