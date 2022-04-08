#pragma once
#include <vector>
#include<Windows.h>
#define ALL_USED 511
using namespace std;

//数独类，实现算法一
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
		cout << "\n此次运行中填入数字的次数" << this->judgeTimes<<"次\n\n\n";
		return this->judgeTimes;
	}
protected:
	 short verification[9] = { 1,2,4,8,16,32,64,128,256};		//设置一个校验数组
	 short notAvailableNum[81];		//数独数字记录，用于回溯
	 short sudokus[10][10];		//数独结果数组，存储结果
	 unsigned int judgeTimes;	//统计填完数独所需要的判断次数
	 unsigned int basicTimes;	//统计填完数独所需要的判断，赋值操作的次数
	 vector <short> availableNum;
	 bool available;		//判断取值可用与否
	 
	 void CheckNumAvailable(int x, int y,short num);		//检验当前坐标是否与其他位置冲突
	 void CheckNumUsed(int x,int y);				//检验可取值	
};


//坐标类
class coordinate
{
public:
	int x;
	int y;

	//重载等号
	void operator=(const coordinate& another)
	{
		x = another.x;
		y = another.y;
	}
};

//数独算法演示类sudokuDemo，整合算法一、算法二
class sudokuDemo:public Sudoku
{
public:
	void clear();
	void algorithm_stepBystep();//算法一，回溯法，加入动态演示
	void algorithm_direct_fill();//算法二，直接填入，加入动态演示
	void algorithm_direct_fill_simplified();//算法二的简化版，加入动态演示
	//将显示的数独填充为0
	void display_init();
	//用于动态演示算法一的填充步骤
	void show_step(int x,int y,short num);
	void fill_color(int index, char direction, int t1, int t2, int color);
	void show_how_to_direct_fill(int source_index, int fill_index,char direction);
	void show_how_to_simplify_direct_fill(int x, int y, int num);
private:
	HANDLE  hStdout;	//用于控制光标

////////直接填充法的成员变量和函数//////////

	//存放打乱顺序的数字1-9
	int numbers[10];
	//候选数数组，第0个元素是长度
	int candidateNum[10];
	//获得(x,y)处可以填哪些数，放入候选数数组
	void GetValidValueList(int x, int y);
	//洗牌
	void shuffle();
	//垂直方向滚动 source_index是原3*3矩阵编号，fill_index是填充矩阵编号
	void y_move(const int& source_index, const int& fill_index, const bool& direction);
	//水平方向滚动 source_index是原3*3矩阵编号，fill_index是填充矩阵编号
	void x_move(const int& source_index, const int& fill_index, const bool& direction);
	//已知3*3矩阵标号求其左上角元素坐标
	coordinate & index2coordinate(const int& index)
	{
		coordinate tmp;
		tmp.x = (index - 1) % 3 * 3;
		tmp.y = (index - 1) / 3 * 3;
		return tmp;
	}
};
