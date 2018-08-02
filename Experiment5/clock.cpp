#include<iostream>
#include<string>
using namespace std;

/**
* 页框
*/
class Frame {
public:
	/**
	  * 页号
		   */
	int page;
	/**
		  * 这里用来存储LRU算法中需要用到的某个数据
			   */
	int LRU_index;
	/**
		  * 你可以使用这里来标记Clock算法中这里是否有星号
			   */
	bool Clock_star;
};

/**
* 页框的数组
*/
Frame * frames;
/**
* 页框数量
*/
int frameNum;
/**
* 这是读入的第几个页
*/
int pageSteamIndex;

/**
* 算法类
*/
class Algorithm {
public:
	 /**
		  * 初始化
			   */
	virtual void init() {

	}
	 /**
		  * 需要读入某页
			   * @param page 页号，[1,+∞）
				    */
	virtual void read(int page) {

	}

};

/**
* 当前使用的算法
*/
Algorithm * alg;

/**
* LRU 算法
*/
class LRU :public Algorithm {
public:
	 /**
		  * 初始化
			   */
	void init() {
		pageSteamIndex = 0;
		for (int i = 0; i<frameNum; i++) {
			frames[i].page = 0;
			frames[i].LRU_index = 0;
		}
		print();
	}
	 /**
		  * 需要读入某页
			   * @param page 页号，[1,+∞）
				    */
	void read(int page) {
		pageSteamIndex++;
		if (pageInFrame(page)) {
			//该页已经在页框中
			print();
		}
		else if (putPageToEmpty(page)) {
			//该页被放入空页框
			print();
		}
		else {
			//缺页
			int switchFrame = 0;
			int lru_min = frames[switchFrame].LRU_index;
			for (int i = 1; i<frameNum; i++) {
				if (lru_min > frames[i].LRU_index) {
					lru_min = frames[i].LRU_index;
					switchFrame = i;
				}
			}
			frames[switchFrame].page = page;
			frames[switchFrame].LRU_index = pageSteamIndex;
			print(true);
		}
	}
private:
	 /**
		  * 某页是否在页框中
			   * @param page 页号
				    * @return 是否在页框中
					    */
	bool pageInFrame(int page) {
		for (int i = 0; i<frameNum; i++) {
			if (frames[i].page == page) {
				frames[i].LRU_index = pageSteamIndex;
				return true;
			}
		}
		return false;
	}

	 /**
		  * 如果有空页框，把某页放入空页框，并返回true
			   * 没有空页框时，返回false
				    * @param page 页号
					     * @return 该函数执行前是否有空页框
							  */
	bool putPageToEmpty(int page) {
		for (int i = 0; i<frameNum; i++) {
			if (frames[i].page == 0) {
				frames[i].page = page;
				frames[i].LRU_index = pageSteamIndex;
				return true;
			}
		}
		return false;
	}

	 /**
		  * 打印当前页框状态
			   * @param pageFault 是否发生缺页错误
				    *        如果发生缺页，将会显示记号 “F”
					     */
	void print(int pageFault = false) {
		cout << pageSteamIndex << ":\t";
		for (int i = 0; i<frameNum; i++) {
			if (frames[i].page>0) {
				cout << frames[i].page << "\t";
			}
		}
		if (pageFault) {
			cout << "F";
		}
		cout << endl;
	}

};

/**
* FIFO 算法
*/
class FIFO :public Algorithm {
public:
	 /**
		  * 初始化
			   */
	void init() {
		pageSteamIndex = 0;
		for (int i = 0; i<frameNum; i++) {
			frames[i].page = 0;
		}
		next = 0;
		print();
	}
	 /**
		  * 需要读入某页
			   * @param page 页号，[1,+∞）
				    */
	void read(int page) {
		pageSteamIndex++;
		if (pageInFrame(page)) {
			//该页已经在页框中
			print();
		}
		else {
			//缺页
			//是否有空页框(决定是否输出“F”)
			bool frameIsEmpty = (frames[next].page == 0);
			frames[next].page = page;
			print(!frameIsEmpty);
			next = (next + 1) % frameNum;
		}
	}
private:
	/**
	  * FIFO算法需要用到的数据，
		   * 它指出下一次缺页错误发生时，
			    * 替换哪一个页框内的页
				     */
	int next;
	 /**
		  * 某页是否在页框中
			   * @param page 页号
				    * @return 是否在页框中
					    */
	bool pageInFrame(int page) {
		for (int i = 0; i<frameNum; i++) {
			if (frames[i].page == page) {
				return true;
			}
		}
		return false;
	}
	 /**
		  * 打印当前页框状态
			   * @param pageFault 是否发生缺页错误
				    *        如果发生缺页，将会显示记号 “F”
					     */
	void print(int pageFault = false) {
		cout << pageSteamIndex << ":\t";
		for (int i = 0; i<frameNum; i++) {
			if (frames[i].page>0) {
				cout << frames[i].page << "\t";
			}
		}
		if (pageFault) {
			cout << "F";
		}
		cout << endl;
	}
};

/**
* Clock 算法
*/
class Clock :public Algorithm {
public:

	 /**
		  * 初始化
			   */
	void init() {
		pageSteamIndex = 0;
		for (int i = 0; i<frameNum; i++) {
			frames[i].page = 0;
			frames[i].Clock_star = false;
		}
		next = 0;
		print();
	}

	 /**
		  * 需要读入某页
			   * @param page 页号，[1,+∞）
				    */
	void read(int page) {
		pageSteamIndex++;
		if (pageInFrame(page)) {
			//该页已经在页框中
			print();
		}
		else {
			//缺页
			//是否有空页框(决定是否输出“F”)
			while (true) {
				if (frames[next].Clock_star == false) {
					frames[next].Clock_star = true;
					break;
				}
				frames[next].Clock_star = false;
				next = (next + 1) % frameNum;
			}
			bool frameIsEmpty = false;
			if (frames[next].page == 0) {
				frameIsEmpty = true;
			}
			frames[next].page = page;
			print(!frameIsEmpty);
			next = (next + 1) % frameNum;
		}
	}

private:
	int next;

	bool pageInFrame(int page) {
		for (int i = 0; i<frameNum; i++) {
			if (frames[i].page == page) {
				frames[i].Clock_star = true;
				return true;
			}
		}
		return false;
	}


	void print(int pageFault = false) {
		cout << pageSteamIndex << ":\t";
		for (int i = 0; i<frameNum; i++) {
			if (frames[i].page>0) {
				cout << frames[i].page;
				if (frames[i].Clock_star)
					cout << "*";
				else
					cout << " ";
				cout << "\t";
			}
		}
		if (pageFault) {
			cout << "F";
		}
		cout << endl;
	}
};

void loop() {
	//输入页框数量
	cout << "frame number:";
	cin >> frameNum;
	//建立页框数组
	frames = new Frame[frameNum]();
	//输入算法名字
	cout << "algorithm:";
	string strAlg;
	cin >> strAlg;
	//大写化
	for (int i = 0; i<strAlg.size(); i++) {
		if (strAlg[i] >= 'a' && strAlg[i] <= 'z') {
			strAlg[i] = strAlg[i] + 'A' - 'a';
		}
	}
	//判别使用的算法
	if (strAlg == "LRU") {
		alg = new LRU();
	}
	else if (strAlg == "FIFO") {
		alg = new FIFO();
	}
	else if (strAlg == "CLOCK") {
		alg = new Clock();
	}
	else {
		alg = new Algorithm();
	}
	//算法初始化
	alg->init();
	//输入页号
	int page;
	for (;;) {
		cout << "page:";
		cin >> page;
		if (page <= 0) {
			break;
		}
		//需要读某页
		alg->read(page);
	}//当页号小于等于0时结束
	 //删除页框的数组
	delete[] frames;
	//删除算法实例
	delete alg;
}

int main() {
	for (;;) {
		loop();
	}
}
