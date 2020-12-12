#include <iostream>
#include <string>
#include <set>
#include <time.h>
#include <stdio.h>
using namespace std;

int arr[4] = {-1,-1,-1,-1};
set<string> st;

void may(int idx){
    for(int i=0; i<10; i++){
        if(arr[0] != i && arr[1] != i && arr[2] != i ){
            arr[idx]=i;
            if(idx==3){
                string s = "abcd";
                for(int j=0; j<4; j++)  s[j] = arr[j] + '0';
                st.insert(s);
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
        it = st.end();
        it--;
        for( ;it!=st.begin(); it--){
            bool check_ans= check( ans[0], ans[1], *it, gs);
            if (check_ans == false) {
                it = st.erase(it);
            }
        }
        
    }
}