#include <iostream>
#include <string>
#include "post-proc.h"
#include "recursive.h"
#include "postfix.h"

using namespace std;

int main(int argc, char *argv[])
{
    vector<CMOS> deck;
    vector<char> pun, pdn;
    vector<char> output_labels;
    vector<string> expressions;

    string input = "y=(a|b&(c|d))`";

    output_labels = extract_output_labels(input);
    cout << output_labels.back() << endl;
    expressions = get_postfix_vec(input);
    cout << expressions.back() << endl;

    post_proc(expressions.back(), pun, pdn);

    for (int i = 0; i < pun.size(); i++)
        cout << pun[i];
    cout << endl;

    for (int i = 0; i < pdn.size(); i++)
        cout << pdn[i];
    cout << endl;


    bool flag = false;
    run(pun, &deck, "Y", "VDD", PMOS, flag);

    flag = false;
    run(pdn, &deck, "Y", "0", NMOS, flag);

    CMOS decks;
    for (int i = 0; i < deck.size(); i++){
        decks = deck[i]; 
        cout << decks.m_name << " "<< decks.drain<<" "<<decks.gate<<" "<<decks.source<<" "<< decks.body<<" "<<decks.type<<endl;
    }

    return 0;
}