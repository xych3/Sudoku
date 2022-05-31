#include<iostream>
#include<string>
#include<time.h>
using namespace std;

int num[9][9];
bool flag = false;

int main(){
	clock_t be = clock();
//	string newStr = "..8...2...3.8.2.6.7...9...5.5.....1...4...6...2.....7.4...8...6.7.1.3.9...1...8..";
//	string newStr = "..53.....8......2..7..1.5..4....53...1..7...6..32...8..6.5....9..4....3......97..";
	string newStr = "........1.......23..4..5......1.........3.6....7...58.....67....1...4...52.......";
	void input(string Str);
	input(newStr);//存入数据
	
	void print();//输出初始数据 
	print();
	int DFS(int n);
	DFS(0);
	cout<<"解出数独："<<endl;
	print();
	clock_t en = clock();
	cout << en-be << endl;
	system("pause");
	return 0;
}
void input(string Str){//把输入的数独初始化存入num中
	int i=0;//newStr的顺序 
	 int row,col;//用于记录num 
	 for(i=0;i<81;i++){
	 	row = i%9;
	 	col = i/9;
	 	if(Str[i] == '.')	num[row][col] = 0;
	 	else num[row][col] = Str[i] - '0';
	 }
}
void print(){
	for(int j=0;j<9;j++){
		for(int i=0;i<9;i++){
			if(i!=0&&i%3==0){
				cout<<"   ";
			}
			cout<<num[i][j]<<" ";
		}
		cout<<endl;
		if(j!=0&&(j+1)%3==0) cout<<endl;
	}
}
//当我在某个位置n填入某一个数据k时，我要判断对应位置的行、列、九宫格都没有与之重复的 
bool check(int r,int c,int k){
	for (int j = 0; j < 9; j++){//行 
		if(num[r][j] == k)	return false;
	}
	for (int i = 0; i < 9; i++){//列 
		if(num[i][c] == k)	return false;
	}
	//九宫格左上角的数字的坐标
	int x = r/3*3;
	int y = c/3*3 ;
	for (int i = x; i < x + 3; i++) {
		for (int j = y; j < y + 3; j++) {
			if (num[i][j] == k) return false;
		}
	}
	return true;//如果上面都没有重复的，那就说明填入这个数字是可以的 
}
int DFS(int n) {//深度搜索构造数独
	if (n > 80) {//所有的都符合条件
		flag = true;
		return 0;
	}

	if (num[n / 9][n % 9] != 0) {	//如果不为0，跳过
		DFS(n + 1);
	}
	else {
	//反之，对该位置进行填数
		for (int i = 1; i <= 9; i++) {//填入的数字为1~9的其中一个
			if (check(n / 9,n % 9, i) == true) {
				num[n / 9][n % 9] = i;//赋值
				DFS(n + 1);//继续搜索
				if (flag == true)	return 0;//构造成功退出
				else 	num[n / 9][n % 9] = 0;	//构造不成功还原当前位
			}
		}
	}
}
/*int DFS(int r,int c) {
//深度搜索构造数独
	if (r>8&&c>8) {
//所有的都符合条件
		flag = true;
		return 0;
	}

	if (num[r][c] != 0) {
		//如果不为0，跳过
		r = (r+1)%9;
		if(r+1>8)	c++;
		DFS(r,c);
	}
	else {
	//反之，对该位置进行填数
		for (int i = 1; i <= 9; i++) {
		//填入的数字为1~9的其中一个
			if (check( r, c, i) == true) {
				num[r][c] = i;//赋值
				r = (r+1)%9;
				if(r+1>8)	c++;
				DFS(r,c);//继续搜索
				if (flag == true)//构造成功退出
				return 0;
				num[r][c] = 0;//构造不成功还原当前位
			}
		}
	}
}*/
