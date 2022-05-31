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
	input(newStr);//��������
	
	void print();//�����ʼ���� 
	print();
	int DFS(int n);
	DFS(0);
	cout<<"���������"<<endl;
	print();
	clock_t en = clock();
	cout << en-be << endl;
	system("pause");
	return 0;
}
void input(string Str){//�������������ʼ������num��
	int i=0;//newStr��˳�� 
	 int row,col;//���ڼ�¼num 
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
//������ĳ��λ��n����ĳһ������kʱ����Ҫ�ж϶�Ӧλ�õ��С��С��Ź���û����֮�ظ��� 
bool check(int r,int c,int k){
	for (int j = 0; j < 9; j++){//�� 
		if(num[r][j] == k)	return false;
	}
	for (int i = 0; i < 9; i++){//�� 
		if(num[i][c] == k)	return false;
	}
	//�Ź������Ͻǵ����ֵ�����
	int x = r/3*3;
	int y = c/3*3 ;
	for (int i = x; i < x + 3; i++) {
		for (int j = y; j < y + 3; j++) {
			if (num[i][j] == k) return false;
		}
	}
	return true;//������涼û���ظ��ģ��Ǿ�˵��������������ǿ��Ե� 
}
int DFS(int n) {//���������������
	if (n > 80) {//���еĶ���������
		flag = true;
		return 0;
	}

	if (num[n / 9][n % 9] != 0) {	//�����Ϊ0������
		DFS(n + 1);
	}
	else {
	//��֮���Ը�λ�ý�������
		for (int i = 1; i <= 9; i++) {//���������Ϊ1~9������һ��
			if (check(n / 9,n % 9, i) == true) {
				num[n / 9][n % 9] = i;//��ֵ
				DFS(n + 1);//��������
				if (flag == true)	return 0;//����ɹ��˳�
				else 	num[n / 9][n % 9] = 0;	//���첻�ɹ���ԭ��ǰλ
			}
		}
	}
}
/*int DFS(int r,int c) {
//���������������
	if (r>8&&c>8) {
//���еĶ���������
		flag = true;
		return 0;
	}

	if (num[r][c] != 0) {
		//�����Ϊ0������
		r = (r+1)%9;
		if(r+1>8)	c++;
		DFS(r,c);
	}
	else {
	//��֮���Ը�λ�ý�������
		for (int i = 1; i <= 9; i++) {
		//���������Ϊ1~9������һ��
			if (check( r, c, i) == true) {
				num[r][c] = i;//��ֵ
				r = (r+1)%9;
				if(r+1>8)	c++;
				DFS(r,c);//��������
				if (flag == true)//����ɹ��˳�
				return 0;
				num[r][c] = 0;//���첻�ɹ���ԭ��ǰλ
			}
		}
	}
}*/
