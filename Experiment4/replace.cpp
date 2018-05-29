#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string replace(string src, string sub, string dst)
{
    int index = src.find(sub), len = sub.length();
    while (index != -1) {
        src = src.substr(0, index) + dst + src.substr(index + len);
        index = src.find(sub);
    }
    return src;
}

int main() 
{
    string src = "abcaabbcabcaucdabc", sub = "abc", dst = "ntr";
    cout << replace(src, sub, dst) << endl;

    return 0;
}