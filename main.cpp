#include<iostream>
#include<string>
#include <queue>

using namespace std;

enum Mtype { PMOS , NMOS };
int m_number = 0;
int curr_label = 0;
struct CMOS {
    string m_name;
    string drain;
    string gate;
    string source;
    string body;
    Mtype type; 
};

struct wire {
    string node1;
    string node2;
};

void NOT (string, string, queue<CMOS>);
void NOR (string, string, string, queue<CMOS>);
void NAND (string, string, string, queue<CMOS>);
void OR (string, string, string, queue<CMOS>);
void AND (string, string, string, queue<CMOS>);
string new_label();
string new_mosfet();

int main(int argc, char *argv[])
{
    return 0;

}

void NOT (string input, string output, queue<CMOS> deck)
{
    CMOS m1, m2; 

    m1.m_name = new_mosfet();
    m1.drain = output;
    m1.gate = input;
    m1.source = "VDD"; 
    m1.body = "VDD";
    m1.type = PMOS;
    
    m2.m_name = new_mosfet();
    m2.drain = output;
    m2.gate = input;
    m2.source = "0"; 
    m2.body = "0";
    m2.type = NMOS;

    deck.push(m1);
    deck.push(m2);
}

void NOR (string op1, string op2, string output,  queue<CMOS> deck)
{

}

void NAND (string op1, string op2, string output, queue<CMOS> deck)
{

}

void OR (string op1, string op2, string output,  queue<CMOS> deck)
{

}

void AND (string op1, string op2, string output, queue<CMOS> deck)
{

}

string new_label()
{
    curr_label++;
    return "L" + to_string(curr_label);
}

string new_mosfet()
{
    m_number++;
    return "M" + to_string(m_number);
}