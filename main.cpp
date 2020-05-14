#include<iostream>
#include<string>
#include"recursive.h"

using namespace std;




int main(int argc, char *argv[])
{
    vector<CMOS> deck;
    CMOS decks;
    vector<char> expression; 

    bool flag = false;
    expression.push_back('c');
    expression.push_back('d');
    expression.push_back('`');
    expression.push_back('&');
    expression.push_back('b');
    expression.push_back('`');
    expression.push_back('|');
    expression.push_back('a');
    expression.push_back('`');
    expression.push_back('&');
    run(expression, &deck, "Y", "VDD", PMOS, flag);

    expression.clear();
    flag = false;
    expression.push_back('c');
    expression.push_back('`');
    expression.push_back('d');
    expression.push_back('|');
    expression.push_back('b');
    expression.push_back('&');
    expression.push_back('a');
    expression.push_back('|');
    run(expression, &deck, "Y", "0", NMOS, flag);

    for (int i = 0; i < deck.size(); i++){
        decks = deck[i]; 
        // deck.pop_back();
        cout << decks.m_name << " "<< decks.drain<<" "<<decks.gate<<" "<<decks.source<<" "<< decks.body<<" "<<decks.type<<endl;
    }
    return 0;
}

