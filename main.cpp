#include<iostream>
#include<string>
#include"recursive.h"

using namespace std;




int main(int argc, char *argv[])
{
    vector<CMOS> deck;
    CMOS decks;
    vector<char> expression; 

    expression.push_back('C');
    expression.push_back('`');

    run(expression, &deck, "Y", "VDD", PMOS);

    for (int i = 0; i < deck.size(); i++){
        decks = deck[i]; 
        deck.pop_back();
        cout << decks.m_name << " "<< decks.drain<<" "<<decks.gate<<" "<<decks.source<<" "<< decks.body<<" "<<decks.type<<endl;
    }
    return 0;
}

