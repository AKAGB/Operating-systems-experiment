#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string sub, dst;

string replace(string src, string sub, string dst)
{
    if (sub == dst) return src;
    int index = src.find(sub), len = sub.length(), dlen = dst.length();
    while (index != -1) {
        src = src.substr(0, index) + dst + src.substr(index + len);
        index = src.find(sub, index + dlen);
    }
    return src;
}

void file_replace_str(void * filename)
{
    string fpath = *((string *)filename);
    // Open file
    string src;
    fstream file(fpath, ios::in);
    if (file) {
        file >> src;
        file.close();
        file.open(fpath, ios::out);
        file << replace(src, sub, dst) << endl;
        file.close();
    }
    else {
        cout << "No such file." << endl;
    }
}

int main() 
{
    // Input
    string fpath1, fpath2;
    cout << "input file 1 path: ";
    cin >> fpath1;
    cout << "input file 2 path: ";
    cin >> fpath2;
    cout << "input string replace from: ";
    cin >> sub;
    cout << "input string replace to: ";
    cin >> dst;

    file_replace_str(&fpath1);

    return 0;
}