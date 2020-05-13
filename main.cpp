#include<iostream>
#include<string>
#include <queue>

using namespace std;

enum Mtype { PMOS , NMOS };
int m_number = 1;
struct CMOS {
    string m_name;
    string drain;
    string gate;
    string source;
    string body;
    Mtype type; 
};

void NOT (string , string , queue<CMOS>);
void OR (string , string , queue<CMOS>);
void AND (string , string , queue<CMOS>);

int main(int argc, char *argv[])
{
    return 0;

}

void NOT (string input, string output, queue<CMOS> deck)
{
    CMOS m1, m2; 

    m1.m_name = "M" + to_string(m_number);
    m1.drain = output;
    m1.gate = input;
    m1.source = "VDD"; 
    m1.body = "VDD";
    m1.type = PMOS;
    m_number++;
    
    m2.m_name = "M" + to_string(m_number);
    m2.drain = output;
    m2.gate = input;
    m2.source = "0"; 
    m2.body = "0";
    m2.type = NMOS;

    deck.push(m1);
    deck.push(m2);
}

void OR (string op1, string op2, queue<CMOS> deck)
{

}

void AND (string op1, string op2, queue<CMOS> deck)
{

}