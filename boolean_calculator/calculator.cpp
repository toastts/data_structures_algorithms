#include <iostream>
#include <string>
#include <stack>
#include "tnode.h"
#include "calculator.h"

using namespace std; 

calculator::calculator() {

};

calculator::calculator(std::string inp) {
    input = inp;
    for(int i=0; i < input.length(); i++) {
        if(input[i] == ' ') {
            input.erase(i,1);
        }
    }
    while(input.at(0) == '(' && input.at(input.length() - 1) == ')') {
        input = input.substr(1, input.length() - 2);
    }
} 

int calculator::pre(char data) {
    switch(data) {
        case '&':  
            return 3;
        case '|':  
            return 3;
            break; 
        case '!':  
            return 4;
        case '>':
            return 2;
        case '^':
            return 3;
        case 'T':
            return -1;
        case 'F':
            return -1;
        default:
            return -10000;
    }
};

tnode* calculator::tree(string postfix) {
    stack<tnode*> st;
    tnode *t = nullptr;
    tnode *t1 = nullptr;
    tnode *t2 = nullptr;
    for (int i=0; i< (postfix).length(); i++) 
        { 
        if (!isOp(postfix[i])) 
        { 
            t = new tnode(postfix[i]); 
            st.push(t); 
        } 
        else 
        { 
            t = new tnode(postfix[i]); 
            t1 = st.top();
            st.pop();
            if(!(st.empty())) {    
                t2 = st.top(); 
                st.pop();
            } 
            t -> left = t1; 

            if(t2) {
                t -> right = t2;
            } 
            st.push(t); 
            
        } 
        t1 = nullptr;
        t2 = nullptr;
    } 
    t = st.top();
    st.pop();
    return t;
}

string calculator::unspace(string inp) {
    string out;
    for(int i = 0; i < inp.length(); i++) {
        if(inp[i] != ' ') {
            out += inp[i];
        }
    }
    return out;
}

char calculator::checkPre(char a, char b) {
    int a_prec = pre(a);
    int b_prec = pre(b);
    if(a_prec >= b_prec) {
        return a;
    } else {
        return b;
    }
}

void calculator::to_str(tnode* head) {
    if(head -> left != nullptr) {
        to_str(head -> left);
    }
    std::cout << head -> data << " ";
    if(head -> right != nullptr) {
        to_str(head -> right);
    }
};

string calculator::convExpr(string input) {
    string infix = input;
    for(int i=0; i < infix.length(); i++) {
        if(infix[i] == ' ') {
            infix.erase(i,1);
        }
    }
    while(infix.at(0) == '(' && infix.at(infix.length() - 1) == ')') {
        infix = infix.substr(1, infix.length() - 2);
    }
    std::stack<char> st; 
    st.push('N'); 
    int l = infix.length(); 
    string ns; 
    for(int i = 0; i < l; i++) { 
        if(infix[i] == '!' && infix[i+1] == '!') {
            i++;
            continue;
        }
        if(!isOp(infix[i]))  {
            ns+=infix[i]; 
        }
        else if(infix[i] == '(') {
            st.push('('); 
        }
        else if(infix[i] == ')') { 
            while(st.top() != 'N' && st.top() != '(') { 
                char c = st.top(); 
                st.pop(); 
                ns += c; 
            } 
            if(st.top() == '(') { 
                char c = st.top(); 
                st.pop(); 
            } 
        } 
        else { 
            while(st.top() != 'N' && pre(infix[i]) <= pre(st.top())) { 
                char c = st.top(); 
                st.pop(); 
                ns += c; 
            } 
            st.push(infix[i]); 
        } 
    } 
    while(st.top() != 'N') { 
        char c = st.top(); 
        st.pop(); 
        ns += c; 
    } 
      
    return ns;
}

bool calculator::solve(string inp) {
    return tree(convExpr(unspace(inp))) -> eval();
}