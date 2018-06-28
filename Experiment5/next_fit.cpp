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
		if (flag != 1)
			printf("%6.0f%9.0f%6c\n", address, length, flag);
		else
			printf("%6.0f%9.0f     1\n", address, length);
	}
};

table_item* free_table = new table_item[m];
table_item* used_table = new table_item[n];

// 记录当前分配的地址
float cur_addr = 0;

void allocate(char J, float xk) {
	int k;
	float ad;
	k = -1;
	int m1 = -1, m2 = -1;		// m1 记录cur_addr之后的可用空间最靠前的，m2记录之前的可用空间最靠前的
	for (int ctr = 0; ctr < m; ctr++) {         // next-fit
		if (free_table[ctr].length >= xk && free_table[ctr].flag == 1) {
			if (free_table[ctr].address >= cur_addr) {
				if (m1 == -1 || m1 > free_table[ctr].address)
					m1 = ctr;
			}
			else {
				if (m2 == -1 || m2 > free_table[ctr].address)
					m2 = ctr;
			}
		}
	}
	// 优先选择m1，若m1为-1则选择m2
	k = (m1 == -1) ? m2 : m1;

	if (k == -1) {
		printf("无可用的空闲区\n");
		return;
	}
	int i = 0;
	while (used_table[i].flag != 0 && i < n) i++;
	if (i >= n) {
		cout << "无表目填写以分分区，错误" << endl;
		if (free_table[k].flag == 0) free_table[k].flag = 1;
		else free_table[k].length = free_table[k].length + xk;
		return;
	}
	ad = free_table[k].address;
	if (free_table[k].length - xk <= minisize) {        // 碎片大小小于某个阈值，则全分配这块区域
		free_table[k].flag = 0;
		xk = free_table[k].length;
	}
	else {                                              // 碎片大小大于某个阈值，则部分分配这块区域，且分配到空闲区域的首部
		free_table[k].length = free_table[k].length - xk;
		free_table[k].address = ad + xk;
	}


	used_table[i].address = ad;
	used_table[i].length = xk;
	used_table[i].flag = J;
	// 分配成功后更新cur_addr
	cur_addr = ad + xk;
	return;
}

void reclaim(char J) {
	int i, k, j, t, l;
	float S, L;
	S = 0;
	while ((used_table[int(S)].flag != J || used_table[int(S)].flag == 0) && S < n) S += 1;
	if (S >= n) {
		printf("找不到该作业\n");
		return;
	}
	used_table[int(S)].flag = 0;
	L = used_table[int(S)].length;      // 回收区域的长度
	S = used_table[int(S)].address;     // 回收区域的首地址
	j = -1; k = -1; i = 0; l = -1;
	while (i < m && (j == -1 || k == -1 || l == -1)) {
		if (free_table[i].flag == 0) {              // 当前表项为空
			if (free_table[i].address + free_table[i].length == 0) k = i;           // 表项什么都没填充
		}
		else {
			if (free_table[i].address + free_table[i].length == S) l = i;			// 该表项刚好是回收区域的上一块
			if (free_table[i].address == S + L) j = i;                              // 该表项首地址刚好是回收区域的下一块
		}
		i++;
	}
	if (l != -1) {		// 合并上一块和回收区域
		L = free_table[l].length + L;
		S = free_table[l].address;
		free_table[l].address = free_table[l].length = free_table[l].flag = 0;
	}
	if (k != -1) {          // k为空栏目
		if (j != -1) {       // 存在第j表项的首地址为回收区域的下一块
			free_table[k].length = free_table[j].length + free_table[k].length + L;
			free_table[j].address = free_table[j].length = free_table[j].flag = 0;
		}
		else free_table[k].length = free_table[k].length + L;
		free_table[k].address = S;
		free_table[k].flag = 1;
	}
	else {              // 没有空表项
		if (j != -1) {

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

			free_table[t].address = S;
			free_table[t].length = L;
			free_table[t].flag = 1;
		}
	}
	return;
}

int main() {
	int a;
	float xk;
	char J;
	free_table[0].edit(10240, 102400, 1);
	cur_addr = 10240;
	while (1) {
		cout << "选择功能项（0—退出，1—分配内存，2-回收内存，3-显示内存）" << endl;
		cout << "选择功能(0-3)" << endl;
		cin >> a;
		switch (a) {
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
			for (int ctr = 0; ctr < n; ctr++)
				free_table[ctr].show();
			cout << "输出已分分区表：\n起始地址 分区长度 标志" << endl;
			for (int ctr = 0; ctr < n; ctr++)
				used_table[ctr].show();
			break;
		default: cout << "没有该选项" << endl;

		}
	}
	cout << "ok" << endl;
	return 0;
}
