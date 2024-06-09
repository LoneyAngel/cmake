#include<iostream>
#include<graphics.h>
#include<iomanip>
using namespace std;

int map[19][19];//创建列表
int flag = 0;//初始化计数器，偶数黑棋出手
void init();//初始化列表,黑棋是1，白棋是2，棋盘上0是白棋，1是黑棋
int isWin(int x,int y);//判断胜利
int playerMove(int x, int y);//luo棋子
void gameView_ShowMap();//打印棋盘
void menuView();//菜单
void winView();//胜利界面
void gameView();//游戏

int main() {
	menuView();//菜单界面
}

//初始化棋子数据
void init() {
	
	for (size_t i=0; i < 19; i++)
	{
		for (size_t j=0; j < 19; j++)
		{
			if (i == 0)
			{
				for (size_t k = 0; k < 19; k++)
				{
					map[0][k] = k;//坐标轴，x轴
				}
			}else if (j==0)
			{
				map[i][0] = i;//坐标轴，y轴
			}
			else
			{
				map[i][j] = 0;//空地
			}
		}
	}
}

//判断是否胜利，四种,从左到右，从上到下，感觉不用传入数据，最基础的判断
//1是黑棋胜，2是白棋胜
// 判断是否胜利
int isWin(int x, int y) {
	int i, j, k;
	int count;

	// 横向判断
	count = 1;
	for (i = x + 1; i < 19; i++) {
		if (map[i][y] == map[x][y]) {
			count++;
		}
		else {
			break;
		}
	}
	for (i = x - 1; i >= 0; i--) {
		if (map[i][y] == map[x][y]) {
			count++;
		}
		else {
			break;
		}
	}
	if (count >= 5) {
		return map[x][y];
	}

	// 纵向判断
	count = 1;
	for (j = y + 1; j < 19; j++) {
		if (map[x][j] == map[x][y]) {
			count++;
		}
		else {
			break;
		}
	}
	for (j = y - 1; j >= 0; j--) {
		if (map[x][j] == map[x][y]) {
			count++;
		}
		else {
			break;
		}
	}
	if (count >= 5) {
		return map[x][y];
	}

	// 左上到右下判断
	count = 1;
	for (i = x + 1, j = y + 1; i < 19 && j < 19; i++, j++) {
		if (map[i][j] == map[x][y]) {
			count++;
		}
		else {
			break;
		}
	}
	for (i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) {
		if (map[i][j] == map[x][y]) {
			count++;
		}
		else {
			break;
		}
	}
	if (count >= 5) {
		return map[x][y];
	}

	// 左下到右上判断
	count = 1;
	for (i = x + 1, j = y - 1; i < 19 && j >= 0; i++, j--) {
		if (map[i][j] == map[x][y]) {
			count++;
		}
		else {
			break;
		}
	}
	for (i = x - 1, j = y + 1; i >= 0 && j < 19; i--, j++) {
		if (map[i][j] == map[x][y]) {
			count++;
		}
		else {
			break;
		}
	}
	if (count >= 5) {
		return map[x][y];
	}

	return 0; // 没有胜利
}


//棋盘展示
void gameView_ShowMap() {
	system("cls");//清空来显示落子后的棋盘
	for (size_t i = 0; i < 19; i++)
	{
		for (size_t j = 0; j < 19; j++)
		{
			if (i==0||j==0)//输出坐标轴
			{
				cout << setw(3) << setfill(' ') << map[i][j];//控制每个隔间内的字符长度
			}
			else
			{
				if (map[i][j] == 1)
				{
					cout << "1  ";//1表示黑子
				}
				else if (map[i][j] == 2)
				{
					cout << "0  ";//0表示白子
				}
				else if (map[i][j] == 0)//输出空地
				{
					cout << "   ";
				}
			}
			
			cout << "|";
		}
		cout << endl;
		cout << "-----------------------------------------------------------------------------" << endl;
	}
}

//落棋,返回0表示下棋失败
int playerMove(int x, int y) {
	if (x==0||y==0)//不能在坐标轴下棋
	{
		cout << "不能在坐标轴下棋！！！";
		return 0;
	}
	else if (map[x][y]!=0)
	{
		cout << "这个位置已经有棋子了！！！";
		cout << "请重新下";
		return 0;
	}
	else//可以下棋
	{
		if (flag%2==0) {
			map[x][y] = 1;//下黑棋
		}
		else
		{
			map[x][y] = 2;//下白棋
		}
		flag++;//计数器加1
		return 1;
	}

}

void gameView() {
	//初始化并展示
	init();
	gameView_ShowMap();
	//开始落子并判断是否胜利
	int result = 0;
	while (!result)//没人胜利则一直循环
	{
		if (flag % 2 == 0) {
			cout<<"落黑子" << endl;
		}
		else
		{
			cout <<"落白子" << endl;
		}
		int x, y;
		cout << "请输入坐标x和y，用空格分隔：";
		cin >> x >> y; // 这里使用空格作为分隔符
		int a = playerMove(x, y);
		if (a)//落子正确
		{
			gameView_ShowMap();//开始游戏
			result = isWin(x,y);
			if (result)
			{
				break;//有人胜利则结束
			}
			else
			{
				continue;
			}
		}
		else
		{
			continue;
		}
		
	}
	//结束画面
	if (result==1)//黑棋胜
	{
		system("cls");
		cout << "-----------------"<<endl;
		cout << "-----黑棋胜------" << endl;
		cout << "-----------------" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
	}
	else
	{
		system("cls");
		cout << "-----------------" << endl;
		cout << "-----白棋胜------" << endl;
		cout << "-----------------" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
	}
	
}
void winView() {
	//结束画面
	if (flag%2 == 1)//黑棋胜
	{
		system("cls");
		cout << "-----------------";
		cout << "-----黑棋胜------";
		cout << "-----------------";
		cout << "|";
		cout << "|";
		cout << "|";
		cout << "|";
		cout << "|";
	}
	else//白棋胜
	{
		system("cls");
		cout << "-----------------";
		cout << "-----白棋胜------";
		cout << "-----------------";
		cout << "|";
		cout << "|";
		cout << "|";
		cout << "|";
		cout << "|";
	}
}

void menuView() {//菜单展示
	while (true) {
		cout << "                                                       " << endl;
		cout << "                                                       " << endl;
		cout << "                                                       " << endl;
		cout << "                                                       " << endl;
		cout << "                                                       " << endl;
		cout << "                                                       " << endl;
		cout << "                 -------------------------------------------------" << endl;
		cout << "                 -------------------------------------------------" << endl;
		cout << "                 ************************* ***********************" << endl;
		cout << "                 ***********************    **********************" << endl;
		cout << "                 ******************              *****************" << endl;
		cout << "                 **********         进入游戏（2）       **********" << endl;
		cout << "                 ****                设置（1）               *****" << endl;
		cout << "                 /                   退出（0）                   /" << endl;
		cout << "                 ******************              *****************" << endl;
		cout << "                 ***********************    **********************" << endl;
		cout << "                 ************************* ***********************" << endl;
		cout << "                 -------------------------------------------------" << endl;
		cout << "                 -------------------------------------------------" << endl;
		int number;
		cin>>number;
		if (number == 2)//开始游戏
		{
			gameView();
		}
		else if (number == 1)//进入设置界面
		{
			system("cls");
			cout << "                                                       " << endl;
			cout << "                                                       " << endl;
			cout << "                                                       " << endl;
			cout << "                                                       " << endl;
			cout << "                                                       " << endl;
			cout << "                                                       " << endl;
			cout << "                 -------------------------------------------------" << endl;
			cout << "                 -------------------------------------------------" << endl;
			cout << "                 ************************* ***********************" << endl;
			cout << "                 ***********************    **********************" << endl;
			cout << "                 ******************              *****************" << endl;
			cout << "                                       敬请期待                   " << endl;
			cout << "                 ***********************    **********************" << endl;
			cout << "                 ************************* ***********************" << endl;
			cout << "                 -------------------------------------------------" << endl;
			cout << "                 -------------------------------------------------" << endl;
			char k;
			cout << "退出设置界面请输入（Y），否则直接退出游戏";
			k = getchar();
			if (k=='Y')
			{
				continue;
			}
			else
			{
				exit(0);
			}
		}
		else if (number==0)//选择退出
		{
			exit(0);
		}
	}
}





