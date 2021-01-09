// Compiler arguments: g++ -std=c++11
#include <iostream>
#include <string>
#include <set>
#include <time.h>
#include <stdio.h>
#include <vector>
using namespace std;

set<string> st;
struct anss{
    string ta;
    int a;
    int b;
};
vector <anss> Record;
/* 
+------------+------------+
|  PLAYER    |    PC      |
+--------A-B-+--------A-B-+
| 1234   1 2 | 1234   0 2 |
| 1243   2 1 |            |
+------------+------------+
*/
void printout() {
    cout << "+------------+------------+\n"
         << "|  PLAYER    |    PC      |\n"
         << "+--------A-B-+--------A-B-+\n";
    for (int i =0; i<Record.size(); i++ ) {
        cout << "| " << Record[i].ta
            << "   " << Record[i].a
            << " "   << Record[i].b
            << " ";
        
        i++;
        if (i == Record.size()) {
            cout <<"|            |\n";
        } else {
            cout << "| " << Record[i].ta
            << "   " << Record[i].a
            << " "   << Record[i].b
            << " |\n";
        }
        
    }

    cout << "+------------+------------+\n";
}


string trueans="abcd";  //定義global：trueans變數則無須回傳值
void gen_trueans(){
    srand(time(0));
    set<int> st;  //set記錄以選到的數並避免重複
    int num;
    for (int i=0; i<4; i++) {
        do {
            num=rand()%10;  //利用rand隨機產出並利用餘數控制範圍
        } while (st.count(num)!=0);
        st.insert(num);
        trueans[i]=num+'0';
    }
}

// 使用遞迴列出來所有可能解
string arr = "abcd";
void gen_allposible(int idx){
    for(int i='0'; i<='9'; i++){ // 產生 char '0' ~ '9'
        if(arr[0] != i && arr[1] != i && arr[2] != i ){
            arr[idx]=i;
            if(idx==3){
                st.insert(arr);  //使用set記錄所有可能的解
            }
            else gen_allposible(idx+1);  //遞迴
            arr[idx]=-1;
        }
    }
}

// 是否答案對
bool check(int a, int b, string trueans, string guess ){
    int A=0, B=0;
    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            if (trueans[i]==guess[j]) {
                if(i==j) A++;
                else B++;
                break;
            }
        }
    }
    if (A == a && B == b) return true;
    else return false;
}

int main(){
    gen_trueans();
    srand(time(0));
    gen_allposible(0);
    int ans[2];
    //cout << "---- "<<trueans << endl;
    cout << "\nHello! Welcome to 1A2B!\n"<< "-----------------------\n";
    while(1){
        // 判斷人猜的結果
        cout <<"\nYour turn. Please guess my number? ";
        string guess;
        cin >> guess;
        int A=0,B=0;
        for (int i=0; i<4; i++){
            for (int j=0; j<4; j++){
                if (trueans[i]==guess[j]) {
                    if(i==j) A++;  //先比較Ａ再比較Ｂ可以避免重複計算
                    else B++;
                    break;
                }
            }
        }
        if(A==4){
            cout << "---- You Win. ----\n";
            break;
        }
        else {
            Record.push_back({guess, A, B});
            printout();
            cout <<"The hint is "<< A << "A" << B << "B\n";
        }
        // 電腦開始猜
        set<string>::iterator it; // 定義一個 iterator
        it = next(st.begin(), rand() % st.size()); // rand 指到set中的一個可能解
        string gs= *it;
        //cout << "------ " << st.size() << endl;
        cout << "\nMy turn. I guess the number is "<< gs << '\n';
        cout << "Please give me a hint. (Input 'A' <space> 'B'  <Enter> ): ";
        for(int i=0; i<2; i++){
            cin >> ans[i];
        }
        if(ans[0]==4) {
            cout << "---- You Lose ----\n";
            break;
        }

        // 參考：https://www.techiedelight.com/remove-elements-set-cpp/
        for(it = st.begin() ;it!=st.end(); ){ // 從第一個元素，到set結束
            bool check_ans= check( ans[0], ans[1], *it, gs); // 檢查是否與Hint相符
            if (check_ans == false) {  
                st.erase(it++); // 避免iterator指到set中已刪除的元素，所以要這樣寫
            } else {
                ++it;
            }
        }
        Record.push_back({gs, ans[0], ans[1]});
        printout();
        if (st.size()==0) {  //沒有可能的解卻未產生答案代表玩家未依照規定輸入
            cout << "---- OH!! You cheated. ----\n";
            break;
        }
    }
    return 0;
}