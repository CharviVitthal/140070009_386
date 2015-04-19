#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;


#ifndef elementary_functions
#define elementary_functions

//code to convert the input variable to "x"
vector<string> convert_variable(vector<string> expr, string var) {
    for(int i=0;i<expr.size();i++) {
        if(expr[i]==var) {
            expr[i]="x";
        }
    }
    return expr;
}

//code to convert { and [ to (, and } and ] to )
string convert_brackets(string s) {
    for(int i=0;i<s.size();i++) {
        if(s[i]=='['||s[i]=='{') {
            s[i]='(';
        }
        if(s[i]==']'||s[i]=='}') {
            s[i]=')';
        }
    }
    return s;
}

//code to remove whitespaces from input
string remove_whitespaces(string s) {
    s.erase( std::remove_if( s.begin(), s.end(), ::isspace ), s.end() );
    return s;
}

//code to convert equation to function
vector<string> equation_to_function(vector<string> input) {
	int i=0;
	for(;i<input.size();i++) {
		if(input[i]=="=") {
			break;
		}
	}
	vector<string> b;
	copy(input.begin(), input.begin()+i, back_inserter(b));
	b.push_back("-");
	b.push_back("(");
	copy(input.begin()+i+1,input.end(), back_inserter(b));
	b.push_back(")");
	return b;
}

//code to replace constants pi and e with their numerical values
vector<string> replace_constants(vector<string> expression) {
	for(int i=0;i<expression.size();i++) {
		if(expression[i]=="pi") {
			expression[i]="3.14159";
		}
		if(expression[i]=="e") {
			expression[i]="2.71828";
		}
	}
	return expression;
}

//code to remove repeated roots from final roots vector
vector<double> remove_repeated_roots(vector<double> roots) {
    sort(roots.rbegin(),roots.rend());
	int size=roots.size();
	for (int i=0; i<size; i++) {
      for (int j=i+1;j<size;) {
         if (abs(roots[j]-roots[i])<=1e-3) {
            for (int k=j; k<size; k++) {
               roots[k]=roots[k+1];
            }
            size--;
         } else
            j++;
      }
   }
	return vector<double>(roots.begin(), roots.begin()+size);
}
#endif
