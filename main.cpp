#include<iostream>
#include<string>

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
    return 0;
}

