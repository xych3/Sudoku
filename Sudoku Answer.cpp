#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;

/* 全局变量声明 */
int type = 0; // 用于决定输出格式为机器格式或自定格式
bool qu_sort = false; // 是否开启优化
bool flag = false; // 用于判断是否构造完成
int aResult[81]; // 用于接收题目（空白处初始值为0）以及保存最终结果
int aEmpty_size = 0; // 记录当前剩余的未填数字数量
int aEmpty[81]; // 用于记载空白单元格的序号
int aEmpty_cho[81]; // 用于记录当前数字可选的数字多少
int aRow[9][9]; // 标识某行某个数字是否存在，减少判断时间
int aCol[9][9]; // 标识某行某个数字是否存在，减少判断时间
int aNine[9][9]; // 标识九宫格某个数字是否存在，减少判断时间

/* 
    算法设计：
    1. 读入数独问题。
    2. 给数组aResult、aEmpty、aRow、aCol、aNine赋初值。
    3. 按顺序扫描，将未填数字的空格序号乘以10后存入aEmpty数组, 把已填数字或0按序号存入aResult数组, 同时根据序号及已经填的数字给aRow、aCol和aNine数组进行预处理。
    4. 如果aEmpty数组中存在未填写数字的空格序号, 则从aEmpty数组中取出一个未填写数字的空格序号, 否则执行(11)。
    5. 把取出的空格序号进行行号、列号及九宫格序号分解。
    6. 从数字1开始直到数字9尝试填写, 并对其行、列及九宫格进行冲突判断, 若尝试成功执行 (7) , 否则执行 (8) 。
    7. 执行相应标识处理后转到 (4) 。
    8. 退回到上一个填数序号, 若该填数序号存在则执行相应标识处理后执行 (9) , 否则执行 (12) 。
    9. 如果原来填写数字的下一个数字存在, 对原来填写数字的下一个数字尝试填写。
    10. 下一个数字尝试填写成功执行 (7) , 否则执行 (8) 。
    11. 成功找到一个解，退出
    12. 无解，退出
*/

/* 函数声明 */
void inputnum(string);
void quickSort(int*, int*, int, int);
void getanswer_DFS(int);
bool check(int, int, int, int);
void print();

/* 函数定义 */
void inputnum(string Str)
{
    int i=0, row=0, col=0, jno=0; // 用于读入数据以及预处理
    for(i=0; i<81; ++i) {
        if(Str[i]=='.') {
            aResult[i] = 0;
            aEmpty[aEmpty_size++] = i;
        }
        else {
            row = i/9;
            col = i%9;
            jno = row/3*3+col/3;
            aResult[i] = Str[i] - '0';
            aRow[row][aResult[i]-1] = 1;
            aCol[col][aResult[i]-1] = 1;
            aNine[jno][aResult[i]-1] = 1;
        }
    }

    // 此处尝试优化，思想是将可选择较少的位放在前面以增大选择正确的概率
    if(qu_sort) {
        for(i=0; i<aEmpty_size; ++i) {
            aEmpty_cho[i] = 0;
            row = aEmpty[i]/9;
            col = aEmpty[i]%9;
            jno = row/3*3+col/3;
            for(int j=0; j<9; ++j) {
                if(aRow[row][j]||aCol[col][j]||aNine[jno][j]) ++aEmpty_cho[i];
            }
        }
        quickSort(aEmpty, aEmpty_cho, 0, aEmpty_size-1);
    }
}
void quickSort(int* a_empty, int* a_empty_cho, int begin, int end) {
    if(begin>=end) return;
    int l = begin, r = end;
    int base = a_empty_cho[begin];
    int base_c = a_empty[begin];
    while(l<r) {
        while(a_empty_cho[r]<=base && l<r) --r;
        while(a_empty_cho[l]>=base && l<r) ++l;
        if(l<r) {
            int tmp_cho = a_empty_cho[l];
            int tmp = a_empty[l];
            a_empty_cho[l] = a_empty_cho[r];
            a_empty[l] = a_empty[r];
            a_empty_cho[r] = tmp_cho;
            a_empty[r] = tmp;
        }
    }
    a_empty_cho[begin] = a_empty_cho[l];
    a_empty[begin] = a_empty[l];
    a_empty_cho[l] = base;
    a_empty[l] = base_c;
    quickSort(a_empty,a_empty_cho,begin,l-1);
    quickSort(a_empty,a_empty_cho,l+1,end);
}
void getanswer_DFS(int n)
{
    if(n>=aEmpty_size) {
        flag = true;
        return;
    }
    int row = aEmpty[n]/9;
    int col = aEmpty[n]%9;
    int jno = row/3*3+col/3;
    for(int i=1; i<=9; ++i) {
        if(check(row,col,jno,i)) {
            aResult[aEmpty[n]] = i;
            aRow[row][i-1] = 1;
            aCol[col][i-1] = 1;
            aNine[jno][i-1] = 1;
            getanswer_DFS(n+1);
            if(flag) return;
            else {
                aResult[aEmpty[n]] = 0;
                aRow[row][i-1] = 0;
                aCol[col][i-1] = 0;
                aNine[jno][i-1] = 0;
            }
        }
    }
}
bool check(int row, int col, int jno, int num) 
{
    if(aRow[row][num-1] || aCol[col][num-1] || aNine[jno][num-1]) return false;
    else return true;
}
void print() 
{
    if(type==0) {
        for(int i=0; i<81; ++i) {
            cout << aResult[i];
        }
        cout << endl;
    }
    else {
        for(int i=0; i<81; ++i) {
            if(i!=0&&i%3==0) cout << "   ";
            if(i!=0&&i%9==0) cout << endl;
            if(i!=0&&i%27==0) cout << endl;
            cout << aResult[i] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


/* 主函数 */
int main(){
    bool myself = false;
    cout << "请输入输出格式type：'0'-机器格式 / '1'-自定格式" << endl;
    cin >> type;
    cout << "是否开启总体优化：'0'-关闭 / '1'-开启" << endl;
    cin >> qu_sort;
    cout << "使用测试数据或自行输入数据：'0'-测试数据/'1'-输入数据" << endl;
    cin >> myself;
    cout << endl;
    string newStr = "";
    // Test Samples 测试样例
	// newStr = "..8...2...3.8.2.6.7...9...5.5.....1...4...6...2.....7.4...8...6.7.1.3.9...1...8..";
	// newStr = "..53.....8......2..7..1.5..4....53...1..7...6..32...8..6.5....9..4....3......97..";
	if(myself) cin >> newStr;
    else newStr = "........1.......23..4..5......1.........3.6....7...58.....67....1...4...52.......";
    clock_t be = clock();
    for(int i=0; i<9; ++i) {
        for(int j=0; j<9; ++j) {
            aRow[i][j] = 0;
            aCol[i][j] = 0;
            aNine[i][j] = 0;
        }
    }
    inputnum(newStr);
    cout << "The original data is:" << endl;
    print();
    if(aEmpty_size>0) getanswer_DFS(0);
    if(flag) {
        cout << "The answer of the Sudoku is:" << endl;
        print();
    }
    clock_t en = clock();
    cout << "Time:" << en-be << endl;
    system("pause");
    return 0;
}