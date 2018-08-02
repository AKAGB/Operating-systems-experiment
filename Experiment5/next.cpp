#include <iostream>
#include <cstdio>
using namespace std;
#define n 10
#define m 10
#define minisize 100

class table_item {
    public:
        float address;
        float length;
        int flag;
        void edit(float ad, float ln, int fg) {
            address = ad;
            length = ln;
            flag = fg;
        }
        table_item(float ad, float ln, int fg) {
            address = ad;
            length = ln;
            flag = fg;
        }
        table_item() {
            address = length = flag = 0;
        }
        void show() {
            printf("%6.0f%9.0f%6c\n", address, length, flag);
        }
}; 

table_item* free_table = new table_item[m];
table_item* used_table = new table_item[n];

void allocate(char J, float xk) {
    int k;
    float ad;
    k = -1;
    for (int ctr = 0; ctr < m; ctr++)
        if (free_table[ctr].length >= xk && free_table[ctr].flag == 1)
            if ( k == -1 || free_table[ctr].length < free_table[k].length)
                k = ctr;
    if (k == -1) {
        printf("无可用的空闲区\n");   
        return;
    }
    if (free_table[k].length - xk <= minisize) {
        free_table[k].flag = 0;
        ad = free_table[k].address;
        xk = free_table[k].length;
    }
    else {
        free_table[k].length = free_table[k].length - xk;
        ad = free_table[k].address + free_table[k].length;
    }  
    int i = 0;
    while (used_table[i].flag != 0 && i < n) i++;
    if (i >= n) {
        cout << "无表目填写以分分区，错误" << endl;
        if (free_table[k].flag == 0) free_table[k].flag = 1;
        else free_table[k].length = free_table[k].length + xk;
        return;
    }
    else {
        used_table[i].address = ad;
        used_table[i].length = xk;
        used_table[i].flag = J;
    }
    return;
}

void reclaim(char J) {
    int i, k, j, s, t;
    float S, L;
    S = 0;
    while ((used_table[int(S)].flag != J || used_table[int(S)].flag == 0) && S < n) S++;
    if (S >= n) {    
        printf("找不到该作业\n");
        return;
    }
    used_table[int(S)].flag = 0; 
    S = used_table[int(S)].address;
    L = used_table[int(S)].length;
    j = -1; k = -1; i = 0;  
    while (i < m && (j == -1 || k == -1)) {
        if (free_table[i].flag == 0) {   
            if (free_table[i].address + free_table[i].length == 0) k = i;
                if (free_table[i].address == S + L) j = 1;
            }
        i++;
    }
    if (k != -1)
        if(j != -1) {    
            free_table[k].length = free_table[j].length + free_table[k].length + L;
            free_table[j].flag + 0;
        }
        else free_table[k].length = free_table[k].length + L;
    else
        if(j!=-1) {  
            free_table[j].address = S;
            free_table[j].length = free_table[j].length + L;
        }
        else {
            t = 0;
            while (free_table[t].flag == 1 && t < m) t++;
            if (t >= m) {   
                cout << "内存空闲表没有空间，回收空间失败\n" << endl;
                used_table[int(S)].flag = J;
                return;
            }
           free_table[t].address=s;
           free_table[t].length=L;
           free_table[t].flag=1;
        }
    return;
}

int main() {
    int a;
    float xk;
    char J;
    free_table[0].edit(10240, 102400, 1);
    while (1) {
        cout << "选择功能项（0—退出，1—分配内存，2-回收内存，3-显示内存）" << endl;
        cout << "选择功能(0-3)" << endl;
        cin >> a; 
        switch(a) {
            case 0: exit(0);
            case 1:
                cout << "输入作业名J和作业所需要长度XK:" << endl;
                cin >> J >> xk;
                allocate(J, xk);
                break;
            case 2:
                cout << "输入要回放分区的作业名:" << endl;
                cin >> J;
                reclaim(J);
                break;
            case 3:
                cout << "输出空闲区表：\n起始地址 分区长度 标志" << endl;
                for(int ctr = 0; ctr < n; ctr++)
                    free_table[ctr].show();
                cout << "输出已分分区表：\n起始地址 分区长度 标志" << endl;
                for(int ctr = 0; ctr < n; ctr++)
                    used_table[ctr].show();
                break;
            default: cout << "没有该选项" << endl;

        }
    }
    cout << "ok" << endl;  
    return 0;
}