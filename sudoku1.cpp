#include <iostream>
#include "sudoku1.h"
#include <vector>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#define ALL_USED 511
using namespace std;

Sudoku::Sudoku() {
	memset(sudokus, 0, sizeof(sudokus));
}

Sudoku::~Sudoku() {

}

void Sudoku::clear() {
	memset(sudokus, 0, sizeof(sudokus));
	memset(notAvailableNum, 0, sizeof(notAvailableNum));
	availableNum.clear();
	judgeTimes = 0;
}

void Sudoku::CheckNumAvailable(int x, int y, short num) {
	int i, j = 0;//l记录数据的位置

	this->available = true;

	for (j = 0; j < 9; j++)
	{
		
		if (this->sudokus[y][j] == num || this->sudokus[j][x] == num)		//对该点所在行列值进行检查，如果存在已有值，则该值不可用 ，结束函数
		{
			this->available = false;
			return;
		}
	}
	for (j = 3 * (x / 3); j < 3 * (x / 3) + 3; j++)//判断该点所在3x3行列中是否存在相同数
	{
		for (i = 3 * (y / 3); i < 3 * (y / 3) + 3; i++)
		{
			
			if (num == sudokus[i][j])
			{
				this->available = false;
				return;

			}
		}
	}
}

void Sudoku::CheckNumUsed(int x, int y) {
	this->availableNum.clear();
	for (short int i = 0; i < 9; i++)
	{
		
		if ((this->notAvailableNum[x * 9 + y] & verification[i]) == 0)		//位运算等于0，表示该值可取
		{
			this->availableNum.push_back(i + 1);
		}
	}
}


void Sudoku::algorithm_1()
{
	srand(unsigned(time(NULL)) + clock());        /* 根据当前时间设定随机数的种子 */
	int x = 0, y = 0, index = 0;//x,y为数独的坐标，index记录数字位置
	short num;

	while (!sudokus[8][8]) {
		this->CheckNumUsed(x, y);
		int len = this->availableNum.size();

		
		if (len == 0)		//len==0,表示当前点无可用值，需要回溯
		{
			this->notAvailableNum[x * 9 + y] = 0;			//对当前点置零，回到上一个点
			this->sudokus[y][x] = 0;
			if (y > 0)
				y--;
			else {
				x--;
				y = 8;
			}
			this->notAvailableNum[x * 9 + y] += this->verification[this->sudokus[y][x]];	//将回溯后的点的值加入notAvailableNum数组
			continue;
		}
		else {
			index = rand() % len;				//随机生成一个0-len-1的数字
		}

		num = this->availableNum[index];
		this->judgeTimes++;

		this->CheckNumAvailable(x, y, num);			//验证该数字是否重复
		
		if (this->available == false)			//如果数字重复，则把该数字记录下
		{
			this->notAvailableNum[x * 9 + y] += this->verification[num - 1];
		}
		else
		{
			this->sudokus[y][x] = num;
			y++;
			x = x + y / 9;
			y %= 9;
		}
		
		if (this->notAvailableNum[x * 9 + y] == ALL_USED)
		{
			//如果该位置的值等于ALL_USED	表示1-9都不符合，需要回溯上一个位置
			this->notAvailableNum[x * 9 + y] = 0;			//对当前点置零，回到上一个点
			this->sudokus[y][x] = 0;
			if (y > 0)
				y--;
			else {
				x--;
				y = 8;
			}
			this->notAvailableNum[x * 9 + y] += this->verification[this->sudokus[y][x]];	//将回溯后的点的值加入notAvailableNum数组
			continue;
		}
	}
}

/////////////////////////////////////////////////////////////////
//////////////////数独算法演示类sudokuDemo的成员函数/////////////
/////////////////////////////////////////////////////////////////
void sudokuDemo::clear()
{
	memset(sudokus, 0, sizeof(sudokus));
	memset(notAvailableNum, 0, sizeof(notAvailableNum));
	availableNum.clear();
	judgeTimes = 0;
	//光标位置   
	COORD cursorPos;
	cursorPos.X = 0;
	cursorPos.Y = 14;
	SetConsoleCursorPosition(hStdout, cursorPos);//光标移到下面
	SetConsoleTextAttribute(hStdout, 7);//设置颜色为白色
}
void sudokuDemo::algorithm_stepBystep()
{
	srand(unsigned(time(NULL)) + clock());        /* 根据当前时间设定随机数的种子,clock()为了让它变化的更快一点 */
	int x = 0, y = 0, index = 0;//x,y为数独的坐标，index记录数字位置
	short num;

	while (!sudokus[8][8]) {
		this->CheckNumUsed(x, y);
		int len = this->availableNum.size();

		
		if (len == 0)		//len==0,表示当前点无可用值，需要回溯
		{
			this->notAvailableNum[x * 9 + y] = 0;			//对当前点置零，回到上一个点
			this->sudokus[y][x] = 0;
			this->show_step(x, y, 0);
			if (y > 0)
				y--;
			else {
				x--;
				y = 8;
			}
			this->notAvailableNum[x * 9 + y] += this->verification[this->sudokus[y][x]];	//将回溯后的点的值加入notAvailableNum数组
			continue;
		}
		else {
			index = rand() % len;				//随机生成一个0-len-1的数字
		}

		num = this->availableNum[index];
		this->show_step(x, y, num);//动态显示填充结果
		this->judgeTimes++;

		this->CheckNumAvailable(x, y, num);			//验证该数字是否重复
		
		if (this->available == false)			//如果数字重复，则把该数字记录下
		{
			this->notAvailableNum[x * 9 + y] += this->verification[num - 1];
		}
		else
		{
			this->sudokus[y][x] = num;
			y++;
			x = x + y / 9;
			y %= 9;
		}
		
		if (this->notAvailableNum[x * 9 + y] == ALL_USED)
		{
			//如果该位置的值等于ALL_USED	表示1-9都不符合，需要回溯上一个位置
			this->notAvailableNum[x * 9 + y] = 0;			//对当前点置零，回到上一个点
			this->sudokus[y][x] = 0;
			this->show_step(x, y, 0);
			if (y > 0)
				y--;
			else {
				x--;
				y = 8;
			}
			this->notAvailableNum[x * 9 + y] += this->verification[this->sudokus[y][x]];	//将回溯后的点的值加入notAvailableNum数组
			continue;
		}
	}
}
void sudokuDemo::algorithm_direct_fill()
{
	shuffle();//把1-9打乱顺序
	int counter = 1;

	//将打乱顺序的1-9填入中间的3*3矩阵
	for (int i = 3; i <= 5; ++i)
		for (int j = 3; j <= 5; ++j)
		{
			sudokus[i][j] = numbers[counter++];
		}
	y_move(5, 4, 0);//5号矩阵向下滚动，填入4号
	this->show_how_to_direct_fill(5, 4, 'd');
	y_move(5, 6, 1);//5号矩阵向上滚动，填入6号
	this->show_how_to_direct_fill(5, 6, 'u');
	x_move(5, 2, 1);//5号矩阵向右滚动，填入2号
	this->show_how_to_direct_fill(5, 2, 'r');
	x_move(5, 8, 0);//5号矩阵向左滚动，填入8号
	this->show_how_to_direct_fill(5, 8, 'l');
	y_move(2, 1, 0);//2号矩阵向下滚动，填入1号
	this->show_how_to_direct_fill(2, 1, 'd');
	y_move(2, 3, 1);//2号矩阵向上滚动，填入3号
	this->show_how_to_direct_fill(2, 3, 'u');
	y_move(8, 7, 0);//8号矩阵向下滚动，填入7号
	this->show_how_to_direct_fill(8, 7, 'd');
	y_move(8, 9, 1);//8号矩阵向上滚动，填入9号
	this->show_how_to_direct_fill(8, 9, 'u');
}
void sudokuDemo::algorithm_direct_fill_simplified()
{
	shuffle();//打乱1-9

		//存储偏移量
	int offset[3][3] = { 0,2,1,
						 1,0,2,
						 2,1,0 };

	//x,y是在3*3小矩阵中的坐标，i,j是在offset中的坐标
	int  x, y, i, j, k = 1, counter = 1;
	for (y = 0; y <= 2; ++y)
		for (x = 0; x <= 2; ++x)
		{//此层循环每执行一次，都会有一个数字被填入各小矩阵中

			k = 1;//k是3*3小矩阵编号，每填完一趟归一
			for (i = 0; i <= 2; ++i)//i,j用于遍历offset二维数组
				for (j = 0; j <= 2; ++j)
				{
					//由小矩阵编号得到左上角坐标
					coordinate coor = index2coordinate(k++);

					//小矩阵左上角坐标加偏移量得到坐标，再在此填一个数字
					sudokus[coor.y + offset[y][j]][coor.x + offset[x][i]] = numbers[counter];
					this->show_how_to_simplify_direct_fill(coor.x + offset[x][i], coor.y + offset[y][j], numbers[counter]);
					//输出日志
					//printf("%d填入(%d,%d)\n", numbers[counter], coor.y + offset[y][j], coor.x + offset[x][i]);
				}
			//printf("\n");
			++counter;//下次循环填numbers中的下一个数字
		}
}
void sudokuDemo::display_init()
{
	system("cls");
	//标准输出句柄   
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	//光标位置   
	COORD cursorPos;
	cursorPos.X = 0;
	cursorPos.Y = 0;
	SetConsoleCursorPosition(hStdout, cursorPos);
	cout << "*******************九宫格数独填充演示*******************\n";
	for (int x = 0; x < 9; ++x)
	{
		for (int y = 0; y < 9; ++y)
		{
			cout << 0 << " ";
		}
		cout << "\n";
	}
	cout << "********************************************************\n";
}
void sudokuDemo::show_step(int x, int y, short num)
{
	//光标位置   
	COORD cursorPos;
	//设置光标  
	cursorPos.X = 2 * x;
	cursorPos.Y = 1 + y;//前面已经用了一行
	SetConsoleCursorPosition(hStdout, cursorPos);
	cout << num << " ";
	//设置光标  
	cursorPos.X = 0;
	cursorPos.Y = 14;
	SetConsoleCursorPosition(hStdout, cursorPos);
	cout << "当前格点可用数字 ：";
	for (int i = 0; i < 9; i++)
	{
		if ((this->notAvailableNum[x * 9 + y] & verification[i]) == 0)
		{
			cout << i + 1 << " ";
		}
	}
	//等待0.5s
	Sleep(500);
	//删除当前行，防止显示重叠
	printf("%c[2K", 27);
}
void sudokuDemo::fill_color(int index, char rowCol, int t1, int t2, int color)
{
	//要填充的3*3小方格顶点坐标
	coordinate coo = index2coordinate(index);
	//光标位置   
	COORD cursorPos;
	int color_array[3] = { 0,0,0 };//0是控制台输出字体颜色，黑色，1是蓝色，2是绿色，4是红色
	int temp = color;
	for (int i = 2; i >= 0; i--)
	{
		color_array[i] = temp % 10;
		temp = temp / 10;
	}
	switch (rowCol)
	{
	case 'r':
		for (int row = 0; row < 3; row++)
		{
			for (int col = 0; col < 3; col++)
			{
				cursorPos.X = 2 * coo.x + 2 * col;
				cursorPos.Y = 1 + coo.y + row;

				SetConsoleTextAttribute(hStdout, color_array[row]);
				SetConsoleCursorPosition(hStdout, cursorPos);
				cout << sudokus[coo.y + row][coo.x + col];
			}
			Sleep(t1);
		}
		Sleep(t2);
		break;
	case 'c':
		for (int col = 0; col < 3; col++)
		{
			for (int row = 0; row < 3; row++)
			{
				cursorPos.X = 2 * coo.x + 2 * col;
				cursorPos.Y = 1 + coo.y + row;

				SetConsoleTextAttribute(hStdout, color_array[col]);
				SetConsoleCursorPosition(hStdout, cursorPos);
				cout << sudokus[coo.y + row][coo.x + col];
			}
			Sleep(t1);
		}
		Sleep(t2);
		break;
	default:
		break;
	}
	
}
void sudokuDemo::show_how_to_direct_fill(int source_index,int fill_index, char direction)
{
	switch (direction)
	{
	case 'u':
		this->fill_color(source_index, 'r', 0, 1000, 124);
		this->fill_color(fill_index, 'r', 500, 1500, 412);
		this->fill_color(source_index, 'r', 0, 0, 777);
		this->fill_color(fill_index, 'r', 0, 0, 777);
		break;
	case 'd':
		this->fill_color(source_index, 'r', 0, 1000, 124);
		this->fill_color(fill_index, 'r', 500, 1500, 241);
		this->fill_color(source_index, 'r', 0, 0, 777);
		this->fill_color(fill_index, 'r', 0, 0, 777);
		break;
	case 'r':
		this->fill_color(source_index, 'c', 0, 1000, 124);
		this->fill_color(fill_index, 'c', 500, 1500, 241);
		this->fill_color(source_index, 'c', 0, 0, 777);
		this->fill_color(fill_index, 'c', 0, 0, 777);
		break;
	case 'l':
		this->fill_color(source_index, 'c', 0, 1000, 124);
		this->fill_color(fill_index, 'c', 500, 1500, 412);
		this->fill_color(source_index, 'c', 0, 0, 777);
		this->fill_color(fill_index, 'c', 0, 0, 777);
	default:
		break;
	}	
}
void sudokuDemo::show_how_to_simplify_direct_fill(int x, int y, int num)
{
	int color[9] = { 1,2,3,4,5,6,7,8,11 };
	//光标位置   
	COORD cursorPos;
	cursorPos.X = 2 * x;
	cursorPos.Y = 1 + y ;

	SetConsoleTextAttribute(hStdout, color[num-1]);
	SetConsoleCursorPosition(hStdout, cursorPos);
	cout << num;
	Sleep(500);
}

//生成只包括1-9的乱序序列
void sudokuDemo::shuffle()
{
	//随机数种子
	srand((unsigned)time(NULL));

	//顺序填入，第0个不用
	for (int i = 1; i <= 9; ++i)
	{
		numbers[i] = i;
	}

	//随机交换9次位置，打乱顺序
	for (int i = 1; i <= 9; ++i)
	{
		swap(numbers[rand() % 9 + 1], numbers[rand() % 9 + 1]);
	}
}

//                              源矩阵编号             目标填充矩阵编号            滚动方向
void sudokuDemo::y_move(const int& source_index, const int& fill_index, const bool& direction)
{
	//标号和坐标转换
	coordinate source_coo = index2coordinate(source_index);
	coordinate fill_coo = index2coordinate(fill_index);

	//滚动之后的行偏移量
	int new_index_up[3] = { 1,2,0 };//旧矩阵的第0行是新矩阵的第1行，旧的第一行是新的第二行，第二行是新的第0行
	int new_index_down[3] = { 2,0,1 };

	if (direction)//向上滚动
	{
		for (int row = 0; row <= 2; ++row)//在这里col和row都是偏移量
		{
			int row_new = new_index_up[row];//得到第row行滚动之后成了第几行
			for (int col = 0; col <= 2; ++col)
			{
				sudokus[fill_coo.y + row_new][fill_coo.x + col] = sudokus[source_coo.y + row][source_coo.x + col];
			}
		}
	}
	else //向下滚动
	{
		for (int row = 0; row <= 2; ++row)
		{
			int row_new = new_index_down[row];//得到第row行滚动之后成了第几行
			for (int col = 0; col <= 2; ++col)
			{
				sudokus[fill_coo.y + row_new][fill_coo.x + col] = sudokus[source_coo.y + row][source_coo.x + col];
			}
		}
	}
}
//                              源矩阵编号             目标填充矩阵编号            滚动方向
void sudokuDemo::x_move(const int& source_index, const int& fill_index, const bool& direction)
{
	//标号和坐标转换
	coordinate source_coo = index2coordinate(source_index);
	coordinate fill_coo = index2coordinate(fill_index);

	//滚动之后的列偏移量
	int new_index_right[3] = { 2,0,1 };
	int new_index_left[3] = { 1,2,0 };

	if (direction)//向右滚动
	{
		for (int col = 0; col <= 2; ++col)
		{
			int col_new = new_index_right[col];//得到第col列滚动之后在第几列
			for (int row = 0; row <= 2; ++row)
			{
				sudokus[fill_coo.y + row][fill_coo.x + col_new] = sudokus[source_coo.x + row][source_coo.x + col];
			}
		}
	}
	else //向左滚动
	{
		for (int col = 0; col <= 2; ++col)//在这里col和row都是偏移量
		{
			int col_new = new_index_left[col];//得到第col列滚动之后在第几列
			for (int row = 0; row <= 2; ++row)
			{
				sudokus[fill_coo.y + row][fill_coo.x + col_new] = sudokus[source_coo.x + row][source_coo.x + col];
			}
		}
	}
}