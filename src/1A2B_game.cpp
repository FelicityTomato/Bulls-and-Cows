#include <iostream>
#include <string>
#include <set>
#include <time.h>
#include <stdio.h>
using namespace std;

int arr[4] = {-1,-1,-1,-1};
set<string> st;

string trueans="abcd";
void gen_trueans(){
    srand(time(0));
    set<int> st;
    int num;
    for (int i=0; i<4; i++) {
        do {
            num=rand()%10;
        } while (st.count(num)!=0);
        st.insert(num);
        trueans[i]=num+'0';
    }
}
//列出來所有可能
void gen_allposible(int idx){
    for(int i=0; i<10; i++){
        if(arr[0] != i && arr[1] != i && arr[2] != i ){
            arr[idx]=i;
            if(idx==3){
                string s = "abcd";
                for(int j=0; j<4; j++)  s[j] = arr[j] + '0';
                st.insert(s);
            }
            else gen_allposible(idx+1);
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
                    if(i==j) A++;
                    else B++;
                    break;
                }
            }
        }
        if(A==4){
            cout << "---- You Win. ----\n";
            break;
        }
        else cout <<"The hint is "<< A << "A" << B << "B\n";

        // 電腦開始猜
        set<string>::iterator it;
        it = next(st.begin(), rand() % st.size());
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
        for(it = st.begin() ;it!=st.end(); ){
            bool check_ans= check( ans[0], ans[1], *it, gs);
            if (check_ans == false) {
                st.erase(it++);
            } else {
                ++it;
            }
        }
        if (st.size()==0) {
            cout << "---- OH!! You cheated. ----\n";
            break;
        }
    }
    return 0;
}