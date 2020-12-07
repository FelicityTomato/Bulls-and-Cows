#include <iostream>
#include <set>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;

int main(){
    srand(time(0));
    int trueans[4];
    set<int> st;
    int num;
    for (int i=0; i<4; i++) {
        do {
            num=rand()%10;
        } while (st.count(num)!=0);
        st.insert(num);
        trueans[i]=num;
    }
    //cout << trueans[0] << trueans[1] << trueans[2] << trueans[3] << endl;
    int A=0, B=0;
    while(A!=4){
        string s;
        cin >> s;
        int guess[4];
        for (int i=0; i<4; i++){
            guess[i] = s[i]-48;
        }
        A=0;
        B=0;
        for (int i=0; i<4; i++){
            for (int j=0; j<4; j++){
                if (trueans[i]==guess[j]) {
                    if(i==j) A++;
                    else B++;
                    break;
                }
            }
        }
        cout << A << "A" << B << "B" << endl;
    }
    cout << "you WIN"  << endl;
    return 0;
}