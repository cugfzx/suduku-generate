#pragma once
#include <vector>
#include<Windows.h>
#define ALL_USED 511
using namespace std;

//�����࣬ʵ���㷨һ
class Sudoku {
public:
	Sudoku();
	~Sudoku();
	void clear();
	void algorithm_1();
	void display()
	{
		for (int x = 0; x < 9; ++x)
		{
			for (int y = 0; y < 9; ++y)
			{
				cout << sudokus[x][y] << " ";
			
			}
			cout << "\n";
		}
	}
	unsigned int analyze()
	{
		cout << "\n�˴��������������ֵĴ���" << this->judgeTimes<<"��\n\n\n";
		return this->judgeTimes;
	}
protected:
	 short verification[9] = { 1,2,4,8,16,32,64,128,256};		//����һ��У������
	 short notAvailableNum[81];		//�������ּ�¼�����ڻ���
	 short sudokus[10][10];		//����������飬�洢���
	 unsigned int judgeTimes;	//ͳ��������������Ҫ���жϴ���
	 unsigned int basicTimes;	//ͳ��������������Ҫ���жϣ���ֵ�����Ĵ���
	 vector <short> availableNum;
	 bool available;		//�ж�ȡֵ�������
	 
	 void CheckNumAvailable(int x, int y,short num);		//���鵱ǰ�����Ƿ�������λ�ó�ͻ
	 void CheckNumUsed(int x,int y);				//�����ȡֵ	
};


//������
class coordinate
{
public:
	int x;
	int y;

	//���صȺ�
	void operator=(const coordinate& another)
	{
		x = another.x;
		y = another.y;
	}
};

//�����㷨��ʾ��sudokuDemo�������㷨һ���㷨��
class sudokuDemo:public Sudoku
{
public:
	void clear();
	void algorithm_stepBystep();//�㷨һ�����ݷ������붯̬��ʾ
	void algorithm_direct_fill();//�㷨����ֱ�����룬���붯̬��ʾ
	void algorithm_direct_fill_simplified();//�㷨���ļ򻯰棬���붯̬��ʾ
	//����ʾ���������Ϊ0
	void display_init();
	//���ڶ�̬��ʾ�㷨һ����䲽��
	void show_step(int x,int y,short num);
	void fill_color(int index, char direction, int t1, int t2, int color);
	void show_how_to_direct_fill(int source_index, int fill_index,char direction);
	void show_how_to_simplify_direct_fill(int x, int y, int num);
private:
	HANDLE  hStdout;	//���ڿ��ƹ��

////////ֱ����䷨�ĳ�Ա�����ͺ���//////////

	//��Ŵ���˳�������1-9
	int numbers[10];
	//��ѡ�����飬��0��Ԫ���ǳ���
	int candidateNum[10];
	//���(x,y)����������Щ���������ѡ������
	void GetValidValueList(int x, int y);
	//ϴ��
	void shuffle();
	//��ֱ������� source_index��ԭ3*3�����ţ�fill_index����������
	void y_move(const int& source_index, const int& fill_index, const bool& direction);
	//ˮƽ������� source_index��ԭ3*3�����ţ�fill_index����������
	void x_move(const int& source_index, const int& fill_index, const bool& direction);
	//��֪3*3�������������Ͻ�Ԫ������
	coordinate & index2coordinate(const int& index)
	{
		coordinate tmp;
		tmp.x = (index - 1) % 3 * 3;
		tmp.y = (index - 1) / 3 * 3;
		return tmp;
	}
};
