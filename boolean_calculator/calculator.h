#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include "tnode.h"

#include <string>

class calculator {
    public:
        std::string post_order;
        std::string input;
        void to_str(tnode*);
        calculator();
        calculator(std::string);
        tnode* tree(std::string);
        bool isOp(char);
        std::string convExpr(std::string);
        char checkPre(char, char);
        int pre(char);
        std::string unspace(std::string);
        bool solve(std::string);
};

#endif