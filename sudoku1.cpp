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
	int i, j = 0;//l��¼���ݵ�λ��

	this->available = true;

	for (j = 0; j < 9; j++)
	{
		
		if (this->sudokus[y][j] == num || this->sudokus[j][x] == num)		//�Ըõ���������ֵ���м�飬�����������ֵ�����ֵ������ ����������
		{
			this->available = false;
			return;
		}
	}
	for (j = 3 * (x / 3); j < 3 * (x / 3) + 3; j++)//�жϸõ�����3x3�������Ƿ������ͬ��
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
		
		if ((this->notAvailableNum[x * 9 + y] & verification[i]) == 0)		//λ�������0����ʾ��ֵ��ȡ
		{
			this->availableNum.push_back(i + 1);
		}
	}
}


void Sudoku::algorithm_1()
{
	srand(unsigned(time(NULL)) + clock());        /* ���ݵ�ǰʱ���趨����������� */
	int x = 0, y = 0, index = 0;//x,yΪ���������꣬index��¼����λ��
	short num;

	while (!sudokus[8][8]) {
		this->CheckNumUsed(x, y);
		int len = this->availableNum.size();

		
		if (len == 0)		//len==0,��ʾ��ǰ���޿���ֵ����Ҫ����
		{
			this->notAvailableNum[x * 9 + y] = 0;			//�Ե�ǰ�����㣬�ص���һ����
			this->sudokus[y][x] = 0;
			if (y > 0)
				y--;
			else {
				x--;
				y = 8;
			}
			this->notAvailableNum[x * 9 + y] += this->verification[this->sudokus[y][x]];	//�����ݺ�ĵ��ֵ����notAvailableNum����
			continue;
		}
		else {
			index = rand() % len;				//�������һ��0-len-1������
		}

		num = this->availableNum[index];
		this->judgeTimes++;

		this->CheckNumAvailable(x, y, num);			//��֤�������Ƿ��ظ�
		
		if (this->available == false)			//��������ظ�����Ѹ����ּ�¼��
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
			//�����λ�õ�ֵ����ALL_USED	��ʾ1-9�������ϣ���Ҫ������һ��λ��
			this->notAvailableNum[x * 9 + y] = 0;			//�Ե�ǰ�����㣬�ص���һ����
			this->sudokus[y][x] = 0;
			if (y > 0)
				y--;
			else {
				x--;
				y = 8;
			}
			this->notAvailableNum[x * 9 + y] += this->verification[this->sudokus[y][x]];	//�����ݺ�ĵ��ֵ����notAvailableNum����
			continue;
		}
	}
}

/////////////////////////////////////////////////////////////////
//////////////////�����㷨��ʾ��sudokuDemo�ĳ�Ա����/////////////
/////////////////////////////////////////////////////////////////
void sudokuDemo::clear()
{
	memset(sudokus, 0, sizeof(sudokus));
	memset(notAvailableNum, 0, sizeof(notAvailableNum));
	availableNum.clear();
	judgeTimes = 0;
	//���λ��   
	COORD cursorPos;
	cursorPos.X = 0;
	cursorPos.Y = 14;
	SetConsoleCursorPosition(hStdout, cursorPos);//����Ƶ�����
	SetConsoleTextAttribute(hStdout, 7);//������ɫΪ��ɫ
}
void sudokuDemo::algorithm_stepBystep()
{
	srand(unsigned(time(NULL)) + clock());        /* ���ݵ�ǰʱ���趨�����������,clock()Ϊ�������仯�ĸ���һ�� */
	int x = 0, y = 0, index = 0;//x,yΪ���������꣬index��¼����λ��
	short num;

	while (!sudokus[8][8]) {
		this->CheckNumUsed(x, y);
		int len = this->availableNum.size();

		
		if (len == 0)		//len==0,��ʾ��ǰ���޿���ֵ����Ҫ����
		{
			this->notAvailableNum[x * 9 + y] = 0;			//�Ե�ǰ�����㣬�ص���һ����
			this->sudokus[y][x] = 0;
			this->show_step(x, y, 0);
			if (y > 0)
				y--;
			else {
				x--;
				y = 8;
			}
			this->notAvailableNum[x * 9 + y] += this->verification[this->sudokus[y][x]];	//�����ݺ�ĵ��ֵ����notAvailableNum����
			continue;
		}
		else {
			index = rand() % len;				//�������һ��0-len-1������
		}

		num = this->availableNum[index];
		this->show_step(x, y, num);//��̬��ʾ�����
		this->judgeTimes++;

		this->CheckNumAvailable(x, y, num);			//��֤�������Ƿ��ظ�
		
		if (this->available == false)			//��������ظ�����Ѹ����ּ�¼��
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
			//�����λ�õ�ֵ����ALL_USED	��ʾ1-9�������ϣ���Ҫ������һ��λ��
			this->notAvailableNum[x * 9 + y] = 0;			//�Ե�ǰ�����㣬�ص���һ����
			this->sudokus[y][x] = 0;
			this->show_step(x, y, 0);
			if (y > 0)
				y--;
			else {
				x--;
				y = 8;
			}
			this->notAvailableNum[x * 9 + y] += this->verification[this->sudokus[y][x]];	//�����ݺ�ĵ��ֵ����notAvailableNum����
			continue;
		}
	}
}
void sudokuDemo::algorithm_direct_fill()
{
	shuffle();//��1-9����˳��
	int counter = 1;

	//������˳���1-9�����м��3*3����
	for (int i = 3; i <= 5; ++i)
		for (int j = 3; j <= 5; ++j)
		{
			sudokus[i][j] = numbers[counter++];
		}
	y_move(5, 4, 0);//5�ž������¹���������4��
	this->show_how_to_direct_fill(5, 4, 'd');
	y_move(5, 6, 1);//5�ž������Ϲ���������6��
	this->show_how_to_direct_fill(5, 6, 'u');
	x_move(5, 2, 1);//5�ž������ҹ���������2��
	this->show_how_to_direct_fill(5, 2, 'r');
	x_move(5, 8, 0);//5�ž����������������8��
	this->show_how_to_direct_fill(5, 8, 'l');
	y_move(2, 1, 0);//2�ž������¹���������1��
	this->show_how_to_direct_fill(2, 1, 'd');
	y_move(2, 3, 1);//2�ž������Ϲ���������3��
	this->show_how_to_direct_fill(2, 3, 'u');
	y_move(8, 7, 0);//8�ž������¹���������7��
	this->show_how_to_direct_fill(8, 7, 'd');
	y_move(8, 9, 1);//8�ž������Ϲ���������9��
	this->show_how_to_direct_fill(8, 9, 'u');
}
void sudokuDemo::algorithm_direct_fill_simplified()
{
	shuffle();//����1-9

		//�洢ƫ����
	int offset[3][3] = { 0,2,1,
						 1,0,2,
						 2,1,0 };

	//x,y����3*3С�����е����꣬i,j����offset�е�����
	int  x, y, i, j, k = 1, counter = 1;
	for (y = 0; y <= 2; ++y)
		for (x = 0; x <= 2; ++x)
		{//�˲�ѭ��ÿִ��һ�Σ�������һ�����ֱ������С������

			k = 1;//k��3*3С�����ţ�ÿ����һ�˹�һ
			for (i = 0; i <= 2; ++i)//i,j���ڱ���offset��ά����
				for (j = 0; j <= 2; ++j)
				{
					//��С�����ŵõ����Ͻ�����
					coordinate coor = index2coordinate(k++);

					//С�������Ͻ������ƫ�����õ����꣬���ڴ���һ������
					sudokus[coor.y + offset[y][j]][coor.x + offset[x][i]] = numbers[counter];
					this->show_how_to_simplify_direct_fill(coor.x + offset[x][i], coor.y + offset[y][j], numbers[counter]);
					//�����־
					//printf("%d����(%d,%d)\n", numbers[counter], coor.y + offset[y][j], coor.x + offset[x][i]);
				}
			//printf("\n");
			++counter;//�´�ѭ����numbers�е���һ������
		}
}
void sudokuDemo::display_init()
{
	system("cls");
	//��׼������   
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	//���λ��   
	COORD cursorPos;
	cursorPos.X = 0;
	cursorPos.Y = 0;
	SetConsoleCursorPosition(hStdout, cursorPos);
	cout << "*******************�Ź������������ʾ*******************\n";
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
	//���λ��   
	COORD cursorPos;
	//���ù��  
	cursorPos.X = 2 * x;
	cursorPos.Y = 1 + y;//ǰ���Ѿ�����һ��
	SetConsoleCursorPosition(hStdout, cursorPos);
	cout << num << " ";
	//���ù��  
	cursorPos.X = 0;
	cursorPos.Y = 14;
	SetConsoleCursorPosition(hStdout, cursorPos);
	cout << "��ǰ���������� ��";
	for (int i = 0; i < 9; i++)
	{
		if ((this->notAvailableNum[x * 9 + y] & verification[i]) == 0)
		{
			cout << i + 1 << " ";
		}
	}
	//�ȴ�0.5s
	Sleep(500);
	//ɾ����ǰ�У���ֹ��ʾ�ص�
	printf("%c[2K", 27);
}
void sudokuDemo::fill_color(int index, char rowCol, int t1, int t2, int color)
{
	//Ҫ����3*3С���񶥵�����
	coordinate coo = index2coordinate(index);
	//���λ��   
	COORD cursorPos;
	int color_array[3] = { 0,0,0 };//0�ǿ���̨���������ɫ����ɫ��1����ɫ��2����ɫ��4�Ǻ�ɫ
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
	//���λ��   
	COORD cursorPos;
	cursorPos.X = 2 * x;
	cursorPos.Y = 1 + y ;

	SetConsoleTextAttribute(hStdout, color[num-1]);
	SetConsoleCursorPosition(hStdout, cursorPos);
	cout << num;
	Sleep(500);
}

//����ֻ����1-9����������
void sudokuDemo::shuffle()
{
	//���������
	srand((unsigned)time(NULL));

	//˳�����룬��0������
	for (int i = 1; i <= 9; ++i)
	{
		numbers[i] = i;
	}

	//�������9��λ�ã�����˳��
	for (int i = 1; i <= 9; ++i)
	{
		swap(numbers[rand() % 9 + 1], numbers[rand() % 9 + 1]);
	}
}

//                              Դ������             Ŀ����������            ��������
void sudokuDemo::y_move(const int& source_index, const int& fill_index, const bool& direction)
{
	//��ź�����ת��
	coordinate source_coo = index2coordinate(source_index);
	coordinate fill_coo = index2coordinate(fill_index);

	//����֮�����ƫ����
	int new_index_up[3] = { 1,2,0 };//�ɾ���ĵ�0�����¾���ĵ�1�У��ɵĵ�һ�����µĵڶ��У��ڶ������µĵ�0��
	int new_index_down[3] = { 2,0,1 };

	if (direction)//���Ϲ���
	{
		for (int row = 0; row <= 2; ++row)//������col��row����ƫ����
		{
			int row_new = new_index_up[row];//�õ���row�й���֮����˵ڼ���
			for (int col = 0; col <= 2; ++col)
			{
				sudokus[fill_coo.y + row_new][fill_coo.x + col] = sudokus[source_coo.y + row][source_coo.x + col];
			}
		}
	}
	else //���¹���
	{
		for (int row = 0; row <= 2; ++row)
		{
			int row_new = new_index_down[row];//�õ���row�й���֮����˵ڼ���
			for (int col = 0; col <= 2; ++col)
			{
				sudokus[fill_coo.y + row_new][fill_coo.x + col] = sudokus[source_coo.y + row][source_coo.x + col];
			}
		}
	}
}
//                              Դ������             Ŀ����������            ��������
void sudokuDemo::x_move(const int& source_index, const int& fill_index, const bool& direction)
{
	//��ź�����ת��
	coordinate source_coo = index2coordinate(source_index);
	coordinate fill_coo = index2coordinate(fill_index);

	//����֮�����ƫ����
	int new_index_right[3] = { 2,0,1 };
	int new_index_left[3] = { 1,2,0 };

	if (direction)//���ҹ���
	{
		for (int col = 0; col <= 2; ++col)
		{
			int col_new = new_index_right[col];//�õ���col�й���֮���ڵڼ���
			for (int row = 0; row <= 2; ++row)
			{
				sudokus[fill_coo.y + row][fill_coo.x + col_new] = sudokus[source_coo.x + row][source_coo.x + col];
			}
		}
	}
	else //�������
	{
		for (int col = 0; col <= 2; ++col)//������col��row����ƫ����
		{
			int col_new = new_index_left[col];//�õ���col�й���֮���ڵڼ���
			for (int row = 0; row <= 2; ++row)
			{
				sudokus[fill_coo.y + row][fill_coo.x + col_new] = sudokus[source_coo.x + row][source_coo.x + col];
			}
		}
	}
}