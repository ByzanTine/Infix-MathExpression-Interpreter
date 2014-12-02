#ifndef __MATH_EXPRESSION_PARSER__
#define __MATH_EXPRESSION_PARSER__

#include <string>

class mathExpression
{
public:
    // Input is a infix notation, just a normal (2+3)*4
    mathExpression(std::string expression);
    // Evalute, return the numeric result
    int evaluate();
    
private:
    // infix to postfix
    std::string infixToPostfix(std::string in_expression);
    // postfix to number
    int evaluatePostfix(std::string post_expression);
    // Private helper function
    std::string toPostfix(std::string infix);
    std::string pop(std::string s);
    bool isHigher(char a, char b);
    int order(char op);
    bool isOperator(char a);
private:
    // vars
    std::string expression;
};


#endif
