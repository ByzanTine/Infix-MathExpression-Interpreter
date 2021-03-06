#include "mathExpression.h"

#include <stack>
#include <ctype.h>
#include <cstdlib>
mathExpression::mathExpression()
{}
mathExpression::mathExpression(std::string expression)
{
    this->expression = expression;
}
mathExpression::mathExpression(const char* expression)
{
    this->expression = expression;
}

int mathExpression::evaluate()
{
    
    std::string post_expression = infixToPostfix(expression);
    int retval = evaluatePostfix(post_expression);
    return retval;
}

int mathExpression::evaluate(std::string expression_)
{
	  std::string post_expression = infixToPostfix(expression_);
	  int retval = evaluatePostfix(post_expression);
	  return retval;
}


std::string mathExpression::infixToPostfix(std::string in_expression)
{
    
    // This is a more than "hacking solution", since it's not a particular general expression of postfix
    return toPostfix(in_expression);
}

int mathExpression::evaluatePostfix(std::string post_expression)
{
    std::stack<int> calculator_stack;
    
    int i = 0; 
    while(i < (int) post_expression.length())
    {
        //read a integer
        while(post_expression[i] == ' ')
            i++;
        if (isdigit(post_expression[i]))
        {
            std::string number = "";
            while(isdigit(post_expression[i])) 
            {
                
                number.push_back(post_expression[i]);
                i++;
            }
            calculator_stack.push(atoi(number.c_str()));
            
        }
        // read a operator
        else if (isOperator(post_expression[i]))
        {
            // do operation
            int operand1 = calculator_stack.top();
            calculator_stack.pop();
            int operand2 = calculator_stack.top();
            calculator_stack.pop();
            switch (post_expression[i]) 
            {
            case '+': calculator_stack.push(operand2 + operand1);break;
            case '-': calculator_stack.push(operand2 - operand1);break;
            case '*': calculator_stack.push(operand2 * operand1);break;
            case '/': calculator_stack.push(operand2 / operand1);break;
            default: /*do nothing*/;
            }
            i++;
        }
    }
    return calculator_stack.top();
}



 

bool mathExpression::isOperator(char a) 
{
    switch (a) 
    {
        case '+': return true;
        case '-': return true;
        case '*': return true;
        case '/': return true;
        case '(': return true;
        case ')': return true;
        default: return false;
    }
}
 
int mathExpression::order(char op) 
{
    switch (op)
    {
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
        default: return 0;
    }
}
 
bool mathExpression::isHigher(char a, char b) 
{
    if(order(a)>=order(b)) return true;
    else return false;
}
 
std::string mathExpression::pop(std::string s) 
{
    return s.substr(0,s.size()-1);
}
 
// It can work with a single digit
// we simply make each token seperate by a space
// So as a demo, "23+45" will be interpret as "23 45 + "as  a postfix notation
// There will always be a space after each number for the postfix notation to read
// NOTE: this part of the code is in Github git but without a license, so I simply adopt
std::string mathExpression::toPostfix(std::string infix) 
{
    std::string postfix;
    std::stack<char> operator_stack;
    for(size_t i = 0; i < infix.length(); ) 
    {
       
        //if operand
        if (isdigit(infix[i]))
        {
            while(isdigit(infix[i])) 
            {
                
                postfix.push_back(infix[i]);
                i++;
            }
            postfix += " ";
            
        }
 
        //if operator
        else if(isOperator(infix[i])) 
        {
            
            //if stack is empty
            if(operator_stack.empty()) 
                operator_stack.push(infix[i]);
            //if stack not empty
            else
            {
 
                //if (
                if(infix[i]=='(') 
                {
                   operator_stack.push(infix[i]);
                }
 
                //if ) is encountered pop till ( to postfix
                else if(infix[i]==')') 
                {
										// push the highest precedence first 
                    while(operator_stack.top() != '(') 
                    {
                        postfix.push_back(operator_stack.top());
                        operator_stack.pop();
                    }
                    operator_stack.pop();
                }
 
                else 
                {
                    //pop until tos has lesser precedence or tos is null.
                    while(!operator_stack.empty() && isHigher(operator_stack.top(),infix[i])) 
                    {
                        postfix.push_back(operator_stack.top());
                        operator_stack.pop();
                    }
										// result in stack empty or the precedence is higher than stack top 
                    operator_stack.push(infix[i]);
                }
            }

            i++;

        }
       
    }
 
    while(!operator_stack.empty()) 
    {
        postfix.push_back(operator_stack.top());
        operator_stack.pop();
    }
 
    return postfix;
}
