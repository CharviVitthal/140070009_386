#include <iostream>
using namespace std;
#ifndef operator_check

//function to check whether the input string is a binary operator
bool is_binaryoperator(string input)
{
    if(input=="+"||input=="-"||input=="*"||input=="/"||input=="^")
    {
        return true;
    }
    return false;
}

//function to check whether the input string is a unary operator (function)
bool is_unaryoperator(string input)
{
    if(input=="sin"||input=="cos"||input=="sinh"||input=="cosh"||  input=="tanh"||input=="atan"||input=="asinh"||input=="acosh"  ||input=="atanh"||input=="log"||input=="log10"||input=="e"  ||input=="exp"||input=="sqrt")
    {
        return true;
    }
    return false;
}
#define operator_check
#endif // operator_check
