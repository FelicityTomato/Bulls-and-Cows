#include <iostream>
#include <string>
#include <set>
#include <time.h>
#include <stdio.h>
using namespace std;

string arr = "abcd";
set<string> st;

void may(int idx){
    for(int i= '0'; i<='9'; i++){
        if(arr[0] != i && arr[1] != i && arr[2] != i ){
            arr[idx]= i;
            if(idx==3){
                st.insert(arr);
            }
            else may(idx+1);
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
    srand(time(0));
    may(0);//列出來
    int ans[2];
    while(1){
        cout << "------ " << st.size() << endl;
        // 開始猜
        set<string>::iterator it;
        it = next(st.begin(), rand() % st.size());
        string gs= *it;
        cout << gs << '\n';
        for(int i=0; i<2; i++){
            cin >> ans[i];
        }
        if(ans[0]==4) return 0;
        // 資料來源：https://www.techiedelight.com/remove-elements-set-cpp/
        for(it = st.begin() ;it!=st.end(); ){
            bool check_ans= check( ans[0], ans[1], *it, gs);
            if (check_ans == false) {
                st.erase(it++);
            } else {
                ++it;
            }
        }
        
    }
}