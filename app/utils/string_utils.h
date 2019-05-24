#ifndef STRING_UTILS_H_INCLUDED
#define STRING_UTILS_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int substr_count(string str, string sub){
    int i = 0;
    int cnt = 0;
    while(str.find(sub, i) != string::npos){
        i = str.find(sub, i)+1;
        cnt++;
    }
    return cnt;
};

vector<int> stot(string str){
    // cout << "enter stot" << endl;
    vector<int> res;
    // if(str.size() <= 0) return res;
    int i = (str[0]=='('?1:0);
    int j = (str[str.size()-1]==')'?str.size()-1:str.size());
    int k = str.find(',', 0);
    string tmp;
    while(k != string::npos){
        tmp = str.substr(i, k-i);
        if(tmp == "None"){
            res.push_back(-1);
        }
        else{
            res.push_back(atoi(tmp.c_str()));
        }
        i = k+1;
        k = str.find(',', k+1);
    }
    k = str.rfind(',') + 1;
    if(k < j){
        tmp = str.substr(k, j-k);
        if(tmp == "None"){
            res.push_back(-1);
        }
        else{
            res.push_back(atoi(tmp.c_str()));
        }
    }
    // cout << "leave stot" << endl;
    return res;
};

string ttos(vector<int> v, bool paranth=false){
    // cout << "enter ttos" << endl;
    string res;
    for(int i=0; i<v.size(); i++){
        if(v[i] == -1){
            res += "None,";
        }
        else{
            res += to_string(v[i]) + ",";
        }
    }
    if(paranth){
        res = "(" + res + ")";
    }
    // cout << "leave ttos" << endl;
    return res;
};

#endif // STRING_UTILS_H_INCLUDED
