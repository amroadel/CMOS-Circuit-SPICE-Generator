#include<vector>
#include<string>

using namespace std; 

int m_number = 0;
int curr_node = 0;
enum m_type { PMOS , NMOS };
enum c_logic { PUN , PDN };
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

void not (string input, string output, vector<CMOS> deck)
{
    CMOS m1, m2; 

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

    deck.push_back(m1);
    deck.push_back(m2);
}

void and (string op1, string op2, string output, vector<CMOS> deck, c_logic logic )
{
    CMOS m1, m2; 
    m1.m_name = new_mosfet();
    m1.gate = op1; 
    m2.m_name = new_mosfet();
    m2.gate = op2; 

    switch (logic)
    {
    case PUN:
        m1.source = "VDD";
        m1.body = m1.source;
        m1.drain = new_node();
        m2.source = m1.drain;
        m2.body = m2.body;
        m2.drain = output; 
        break;
    
    default:
        m1.source = new_node();
        m1.body = m1.source;
        m1.drain = output;
        m2.source = "0";
        m2.body = m2.body;
        m2.drain = m1.source;
        break;
    }

    deck.push_back(m1);
    deck.push_back(m2);
}

void or (string op1, string op2, string output, vector<CMOS> deck, c_logic logic )
{
    CMOS m1, m2; 
    m1.m_name = new_mosfet();
    m1.gate = op1; 
    m2.m_name = new_mosfet();
    m2.gate = op2; 

    switch (logic)
    {
    case PUN:
        m1.source = "VDD";
        m1.body = m1.source;
        m1.drain = output;
        m2.source = "VDD";
        m2.body = m2.body;
        m2.drain = output; 
        break;
    
    default:
        m1.source = new_node();
        m1.body = m1.source;
        m1.drain = output;
        m2.source = "0";
        m2.body = m2.body;
        m2.drain = m1.source;
        break;
    }
    
    deck.push_back(m1);
    deck.push_back(m2);
}

int is_operand(char c)
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

void runner (vector<char> expression, vector<CMOS> deck, char x, c_logic logic, string node)
{
    if (expression.size() == 0)
        return;
    
    if (is_operand(expression.back())){
        x = expression.back();
        expression.pop_back();
        runner(expression, deck, x , logic, node); 
    }
    else{
        switch (x)
        {
        case '`':
            node = new_node();
            not(to_string(expression.back()), node, deck);
            expression.pop_back();
            runner(expression, deck, x , logic, node);
            break;
        case '&':
            
            break;
        default:
            break;
        }
    }

    
}