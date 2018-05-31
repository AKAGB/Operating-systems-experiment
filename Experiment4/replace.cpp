#include <iostream>
#include <string>
#include <fstream>
#include <pthread.h>

using namespace std;

string sub, dst;
// 计数器
struct File_data {
    string filename;
    int cnt;
};

string replace(string src, string sub, string dst, int *cnt)
{
    *cnt = 0;
    if (sub == dst) return src;
    int index = src.find(sub), len = sub.length(), dlen = dst.length();
    while (index != -1) {
        (*cnt)++;
        src = src.substr(0, index) + dst + src.substr(index + len);
        index = src.find(sub, index + dlen);
    }
    return src;
}

void *file_replace_str(void * filedata)
{
    File_data *fd = (File_data *)filedata;
    // Open file
    string src;
    fstream file(fd->filename, ios::in);
    if (file) {
        file >> src;
        file.close();
        file.open(fd->filename, ios::out);
        file << replace(src, sub, dst, &(fd->cnt)) << endl;
        file.close();
    }
    else {
        cout << "No such file." << endl;
    }
    return NULL;
}

int main() 
{
    // Input

    File_data f1, f2;
    cout << "input file 1 path: ";
    cin >> f1.filename;
    cout << "input file 2 path: ";
    cin >> f2.filename;
    cout << "input string replace from: ";
    cin >> sub;
    cout << "input string replace to: ";
    cin >> dst;

    pthread_t t1, t2;

    pthread_create(&t1, NULL, file_replace_str, (void *)(&f1));
    pthread_create(&t2, NULL, file_replace_str, (void *)(&f2));

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    cout << "replace number in file 1 : " << f1.cnt << endl;
    cout << "replace number in file 2 : " << f2.cnt << endl; 
    cout << "replace total number : " << f1.cnt + f2.cnt << endl;

    return 0;
}