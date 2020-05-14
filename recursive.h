#include<vector>
#include<string>

using namespace std; 

int m_number = 0;
int curr_node = 0;
enum m_type { PMOS , NMOS };
struct CMOS {
    string m_name;
    string drain;
    string gate;
    string source;
    string body;
    m_type type; 
};

string new_node()
{
    curr_node++;
    return "N" + to_string(curr_node);
}

string new_mosfet()
{
    m_number++;
    return "M" + to_string(m_number);
}

string not_f (string input, vector<CMOS> *deck)
{
    CMOS m1, m2; 
    string output = new_node();

    m1.m_name = new_mosfet();
    m1.drain = output;
    m1.gate = input;
    m1.source = "VDD"; 
    m1.body = m1.source;
    m1.type = PMOS;
    
    m2.m_name = new_mosfet();
    m2.drain = output;
    m2.gate = input;
    m2.source = "0"; 
    m2.body = m2.source;
    m2.type = NMOS;

    deck->push_back(m1);
    deck->push_back(m2);
    return output;
}


int is_operator(char c)
{
    switch (c)
    {
    case '`':
        return 1; 
        break;
    case '|':
        return 1; 
        break;
    case '&':
        return 1; 
        break;
    default:
        return 0;
        break;
    }
 
}

void run (vector<char> expression, vector<CMOS> *deck , string node1 , string node2, m_type type)
{
    if (!is_operator(expression.back())){
        CMOS m; 
        m.gate = expression.back();
        expression.pop_back();
        m.source = node1;
        m.body = node1;
        m.drain = node2;
        m.type = type; 
        m.m_name = new_mosfet();
        deck->push_back(m);
    }
    else
    {
        
        switch (expression.back())
        {
        case '|':
            expression.pop_back();
            run(expression, deck , node1 , node2 , type);
            expression.pop_back();
            run(expression, deck , node1 , node2 , type);           
            break;
        case '&':
            expression.pop_back();
            node2 = new_node();
            run(expression, deck , node1 , node2 , type);
            expression.pop_back();
            run(expression, deck , node2 , type == PMOS? "VDD" : "0" , type); 
            break;
        case '`':
            node1 = not_f(node1, deck);
            expression.pop_back();
            run(expression, deck , node1 , node2 , type);
            break;
        }
    }
}