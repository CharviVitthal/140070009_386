#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <list>
#include "operator_check.cpp"
using namespace std;

#ifndef syntax_checker
#define syntax_checker

//function to check whether input string is a number
bool is_number(string s) {
	for(int i=0;i<s.size();i++) {
		if(!isdigit(s[i])&&s[i]!='.') {
			return false;
		}
	}
	return true;
}

//function to check whether invalid tokens are input by the user
bool not_valid_tokens(vector<string> input) {
	for(int i=0;i<input.size();i++) {
		if(input[i]!="pi"&&!is_number(input[i])&&input[i]!="="&&input[i]!="x"&&input[i]!="("&&input[i]!=")"&&input[i]!="+"&&input[i]!="-"&&input[i]!="*"&&input[i]!="/"&&input[i]!="^"&&input[i]!="sin"&&input[i]!="cos"&&input[i]!="sinh"&&input[i]!="cosh"&&input[i]!="tanh"&&input[i]!="atan"&&input[i]!="asinh"&&input[i]!="acosh"&&input[i]!="atanh"&&input[i]!="log"&&input[i]!="log10"&&input[i]!="e"&&input[i]!="exp"&&input[i]!="sqrt"&&input[i]!="pow") {
			return true;
		}
	}
	return false;
}

//function to check whether balanced brakcets are input by the user
bool brackets_unbalanced(vector<string> input) {
	int l=0, r=0;
	for(int i=0;i<input.size();i++) {
		if(input[i]=="(") {
			l++;
		}
		else if(input[i]==")") {
			r++;
		}
	}
	return l!=r;
}

//function to check for mismatched brackets
bool mismatched_brackets(vector<string> input) {
	int rad=0;
	for(int i=0;i<input.size();i++) {
		if(input[i]=="(") {
			rad++;
		}
		else if(input[i]==")") {
			rad--;
		}
	}
	if(rad!=0)
		return true;
	else
		return false;
}

//function to check for invalid tokens around brackets
bool invalid_tokens_around_brackets(vector<string> input) {
	for(int i=0;i<input.size();i++) {
		if(input[i]=="(") {
			if(i!=0&&i!=input.size()-1) {
				string l=input[i-1], r=input[i+1];
				if(!is_binaryoperator(l)&&!is_unaryoperator(l)&&l!="(") {
					return true;
				}
				if(!is_unaryoperator(r)&&r!="-"&&!is_number(r)&&r!="x"&&r!="(") {
					return true;
				}
			}
			else if(i==0) {
				string r=input[i+1];
				if(!is_unaryoperator(r)&&r!="-"&&!is_number(r)&&r!="x"&&r!="(") {
					return true;
				}
			}
			else if(i==input.size()-1) {
				return true;
			}
		}
		else if(input[i]==")") {
			if(i!=0&&i!=input.size()-1) {
				string l=input[i-1], r=input[i+1];
				if(!is_binaryoperator(r)&&r!=")") {
					return true;
				}
				if(!is_number(l)&&l!="x"&&l!=")") {
					return true;
				}
 			}
			else if(i==0) {
				return true;
			}
			else if(i==input.size()-1) {
				string l=input[i-1];
				if(!is_number(l)&&l!="x"&&l!=")") {
					return true;
				}
			}
		}
	}
	return false;
}

//function to check for invalid tokens around operators
bool invalid_tokens_around_operators(vector<string> input) {
	for(int i=0;i<input.size();i++) {
		if(is_binaryoperator(input[i])) {
            if(i==0&&input[i]!="-") {
                return true;
            }
            else if(i==0&&input[i]=="-") {
                if(!is_unaryoperator(input[i+1])&&input[i+1]!="x"&&!is_number(input[i+1])&&input[i+1]!="(")
                    return true;
            }
            if(i==input.size()-1) {
                return true;
            }
            if(i!=0&&i!=input.size()-1) {
                if(!is_unaryoperator(input[i+1])&&input[i+1]!="x"&&!is_number(input[i+1])&&input[i+1]!="(")
                    return true;
                if(input[i-1]!="x"&&!is_number(input[i-1])&&input[i-1]!=")")
                    return true;
            }
		}
		else if(is_unaryoperator(input[i])) {
            if(i==input.size()-1) {
                return true;
            }
            if(input[i+1]!="(") {
                return true;
            }
            if(i!=0) {
                if(input[i-1]!="("&&!is_binaryoperator(input[i-1])) {
                    return true;
                }
            }
		}
	}
	return false;
}

//function to check for invalid tokens around variables and digits
bool invalid_tokens_around_variables_and_digits(vector<string> input) {
	for(int i=0;i<input.size();i++) {
		if(input[i]=="x"||is_number(input[i])) {
			if(i!=0&&i!=input.size()-1) {
				string l=input[i-1], r=input[i+1];
				if(l!="("&&!is_binaryoperator(l)) {
					return true;
				}
				if(r!=")"&&!is_binaryoperator(r)) {
					return true;
				}
	 		}
			if(i==0) {
				string r=input[i+1];
				if(r!=")"&&!is_binaryoperator(r)) {
					return true;
				}
			}
			if(i==input.size()-1) {
				string l=input[i-1];
				if(l!="("&&!is_binaryoperator(l)) {
					return true;
				}
			}
		}
	}
	return false;
}

//function to check whether the user has input a variable or not
bool x_hona_chahiye(vector<string> input) {
	for(int i=0;i<input.size();i++) {
		if(input[i]=="x")
			return true;
	}
	return false;
}

//main syntax checker
bool check_syntax(vector<string> input) {
	if(!x_hona_chahiye(input)) {
		return false;
	}
	//invalid tokens
	if(not_valid_tokens(input)) {
		return false;
	}
	//checking for number of brackets
	if(brackets_unbalanced(input)) {
		return false;
	}
	//mismatched brackets
	if(mismatched_brackets(input)) {
		return false;
	}
	//invalid tokens around brakcets
	if(invalid_tokens_around_brackets(input)) {
		return false;
	}
	//invalid tokens around operators
	if(invalid_tokens_around_operators(input)) {
		return false;
	}
	//invalid tokens around variables and digits
	if(invalid_tokens_around_variables_and_digits(input)) {
		return false;
	}
	//has = sign
	return true;
}
#endif // syntax_checker
//syntax checker
