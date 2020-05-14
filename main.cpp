#include<iostream>
#include<string>
#include "post-proc.h"

using namespace std;

enum Mtype { PMOS , NMOS };
struct CMOS {
    string m_name;
    string drain;
    string gate;
    string source;
    string body;
    Mtype type; 
};


int main(int argc, char *argv[])
{
    vector<char> pun, pdn;
    post_proc("ab|`cd|`&", pun, pdn);

    for (int i = 0; i < pun.size(); i++)
        cout << pun[i];
    cout << endl;

    for (int i = 0; i < pdn.size(); i++)
        cout << pdn[i];
    cout << endl;
    return 0;
}

