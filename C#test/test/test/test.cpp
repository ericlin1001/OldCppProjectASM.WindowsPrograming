
#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;

void no(){
    cout<<"IMPOSSIBLE"<<endl;
} 

void an(int n){
    cout<<n<<endl;
}

int main(){
    int n;
    vector<int>a;
    int m;
    cin>>n>>m;
    int i;
    for(i=0;i<m;i++){
                    int t;
                    cin>>t;
                    a.push_back(t);
    }
    sort(a.begin(),a.end());
    //
    vector<int>as;
    int minNum=0,maxNum=0;
    int temp;
   
    const int max=(1<<m);
    for(int k=0;k<max;k++){
        temp=0;
        for(i=0;i<m;i++){
            if((k&(1<<i))!=0)temp+=a[i];
        }
        if(temp>=n)as.push_back(temp);
    }
    if(as.size()==0){no();return 0;}
    sort(as.begin(),as.end());
    //
    an(as.front());
    system("pause");
    return 0;
}