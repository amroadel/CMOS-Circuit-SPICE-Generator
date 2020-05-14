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

void and (string op1, string op2, string output, vector<CMOS> deck, c_logic logic, int n )
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

void or (string op1, string op2, string output, vector<CMOS> deck, c_logic logic, int n )
{
    CMOS m1, m2; 
    m1.m_name = new_mosfet();
    m1.gate = op1; 
    m2.m_name = new_mosfet();
    m2.gate = op2; 
    CMOS temp; 

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

void runner (vector<char> expression, vector<CMOS> deck, vector<char> temp, c_logic logic, vector<string> nodes)
{
    if (expression.size() == 0)
        return;
    
    if (is_operator(expression.back())){
        temp.push_back(expression.back());
        expression.pop_back();
        runner(expression, deck, temp , logic, nodes); 
    }
    else{
        switch (temp.back())
        {
        case '`':
            nodes.push_back(new_node());
            not(to_string(expression.back()), nodes.back(), deck);
            expression.pop_back();
            temp.pop_back();
            runner(expression, deck, temp , logic, nodes);
            break;
        case '&':

            break;
        default:
            break;
        }
    }

    
}

void trial2(vector<char> expression, vector<CMOS> deck, c_logic logic, vector<string> nodes)
{
    vector<char> temp;
    string op1, op2, temp_node;
    int n_ands = 0;
    int n_ors  = 0; 
    while(!nodes.empty())
    {
        if(!expression.empty()){
            if(is_operator(expression.back())){
                temp.push_back(expression.back());
                expression.pop_back();
            }
            else{
                switch (temp.back())
                {
                case '`':
                    nodes.push_back(new_node());
                    not(to_string(expression.back()), nodes.back(), deck);
                    expression.pop_back();
                    temp.pop_back();
                    break;
                case '&':
                    op1 = expression.back();
                    expression.pop_back();
                    op2 =  expression.back();
                    expression.pop_back();
                    nodes.push_back(new_node());
                    and(op1, op2, nodes.back(), deck, logic, n_ands);
                    temp.pop_back();
                    n_ands++;
                    break;
                case '|':
                    op1 = expression.back();
                    expression.pop_back();
                    op2 =  expression.back();
                    expression.pop_back();
                    nodes.push_back(new_node());
                    or(op1, op2, nodes.back(), deck, logic, n_ors);
                    temp.pop_back();
                    n_ors++;
                    break;
                }

            }
        }
        else {
            op1 = nodes.back();
            nodes.pop_back();
            op2 =  nodes.back();
            nodes.pop_back();
            switch (temp.back())
            {
            case '&':
                temp_node = new_node();
                nodes.insert(nodes.begin(), temp_node); 
                and(op1, op2, temp_node, deck, logic);
                temp.pop_back();
                break;
            
            case '|':
                temp_node = new_node();
                nodes.insert(nodes.begin(), temp_node); 
                or(op1, op2, temp_node, deck, logic);
                temp.pop_back();
                break;
            }
        }
    }

}

void trial3(vector<char> expression, vector<CMOS> deck, c_logic logic, vector<string> nodes)
{
    vector<char> temp;
    string op1, op2, temp_node;
    int n_ands = 0;
    int n_ors  = 0; 
    CMOS m;
    while(!nodes.empty())
    {
        if(!expression.empty()){
            if(is_operator(expression.back())){
                temp.push_back(expression.back());
                expression.pop_back();
            }
            else{
                nodes.push_back(to_string(expression.back()));
                expression.pop_back();
                switch(temp.back())
                {
                case '&':
                    switch (logic)
                    {
                    case PUN:
                        m.gate = nodes.back();
                        nodes.pop_back();
                        m.source = n_ands == 0? "VDD" : (deck.back()).drain;
                        m.body = m.source;
                        m.drain = new_node();
                        nodes.push_back(m.drain);
                        m.type = PMOS;
                        m.m_name = new_mosfet();
                        deck.push_back(m);
                        break;
                    
                    default:
                        nodes.pop_back();
                        m.source = n_ands == 0? "0" : (deck.back()).drain;
                        m.body = m.source;
                        m.drain = new_node();
                        nodes.push_back(m.drain);
                        m.type = NMOS;
                        m.m_name = new_mosfet();
                        deck.push_back(m);
                        break;
                    }                 
                    break;
                case '|':
                    switch (logic)
                    {
                    case PUN:
                        m.gate = nodes.back();
                        nodes.pop_back();
                        m.source = n_ors == 0? "VDD" : (deck.back()).source;
                        m.body = m.source;
                        m.drain =  new_node();
                        nodes.push_back(m.drain);
                        m.type = PMOS;
                        m.m_name = new_mosfet();
                        deck.push_back(m);
                        break;
                    
                    default:
                        nodes.pop_back();
                        m.source = n_ands == 0? "0" : (deck.back()).drain;
                        m.body = m.source;
                        m.drain = new_node();
                        nodes.push_back(m.drain);
                        m.type = NMOS;
                        m.m_name = new_mosfet();
                        deck.push_back(m);
                        break;
                    }                   
                    break;
                }

                
            }
        }
    }

}

