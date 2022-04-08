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
	

	cout << "����������㷨���д���������0��ʾ�����㷨������-1��ʾֱ�����,����-2��ʾ�򻯵�ֱ����䣩" << endl;
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
			printf("ƽ���������ֵĴ����ǣ�%d\n\n", avarageTimes);
		}
		cout << "����������㷨���д���������0��ʾ�����㷨������-1��ʾֱ�����,����-2��ʾ�򻯵�ֱ����䣩" << endl;
	}	
}