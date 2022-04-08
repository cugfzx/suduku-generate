#include <iostream>
#include<fstream>
#include "sudoku1.h"
int main() 
{
	Sudoku S;
	sudokuDemo test;
	int counts = 1;
	unsigned int avarageTimes = 0;
	unsigned int singleTimes = 0;
	unsigned long int totalTimes=0;
	ofstream writecsv;
	

	cout << "请输入回溯算法运行次数（输入0演示回溯算法，输入-1演示直接填充,输入-2演示简化的直接填充）" << endl;
	while (cin >> counts)
	{
		if (counts==0) {
			test.display_init();
			test.algorithm_stepBystep();
			test.clear();
		}
		else if (counts == -1)
		{
			test.display_init();
			test.algorithm_direct_fill();
			test.clear();
		}
		else if (counts == -2)
		{
			test.display_init();
			test.algorithm_direct_fill_simplified();
			test.clear();
		}
		else{
			writecsv.open("analysis.csv", ios::out);
			writecsv << "number" << ',' << "judgeTimes" << endl;
			for (int i = 0; i < counts; i++)
			{
				S.algorithm_1();
				S.display();
				singleTimes = S.analyze();
				totalTimes += singleTimes;
				writecsv << i << ',' << singleTimes << endl;
				S.clear();
			}
			avarageTimes = totalTimes / counts;
			writecsv.close();
			printf("平均填入数字的次数是：%d\n\n", avarageTimes);
		}
		cout << "请输入回溯算法运行次数（输入0演示回溯算法，输入-1演示直接填充,输入-2演示简化的直接填充）" << endl;
	}	
}