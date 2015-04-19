#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<sstream>
#include "operator_check.cpp"
using namespace std;
#ifndef rpn_tokenizer
//TOKENIZER
vector<string> tokenizer(string a)
{
    int i;
    string  b ;
    for(i=0;i!= a.size();i++)
   {
       if(a[i]=='('||a[i]==')'||a[i]=='+'|| a[i]=='*'||a[i]=='^'||a[i]=='/'||a[i]=='=' )
    {
       b = b +' ' ;
       b = b + a[i];
       b = b + ' ';
    }
    else if(a[i]=='e'){
        b = b + "2.718281";
    }

    else if((i==0 && a[i]=='-') || (i!=0 && a[i]=='-' && a[i-1]=='(')){
        b=b+' ';
        b=b+'-';
        b=b+'1';
        b=b+' ';
        b=b+'*';
        b=b+' ';
    }
    else if(a[i]=='-'){
        b = b + ' ' + a[i] + ' ';
    }
    else
    {
       b = b + a[i];
    }
}
string word ;
vector<string> input;
istringstream iss(b);
while(iss>>word)
{
    if(word=="pi"){
        input.push_back("3.141592");
    }
    else{
        input.push_back(word);
    }
}
return input;

}

//CHECKING PRECEDENCE
bool precedence(string a,string b)
{
   bool bigger;
   map<string,int>c;
   c["^"] = 1;
   c["*"]=2;
   c["/"]=3;
   c["+"]=4;
   c["-"]=5;
   c["("]=6;
   if(c[a]<c[b]){
        bigger = true;
   }
   else{
     bigger = false;
   }
   return bigger;
}
//PARSER
vector<string> get_rpn_expression(vector<string> token){
    // input from user
    int n=token.size();

    int j=0,k=0;          //final rpn stored in queue
    vector<string> queue(n),operatorStack(n);

    for(int i=0;i<n;i++){
        if(!is_binaryoperator(token[i]) && !is_unaryoperator(token[i]) && token[i]!="(" && token[i]!=")"){
            queue[j]=token[i];
            j++;
        }

        else{
            if(token[i]!=")" && token[i]!="("){
                if(k!=0 && precedence(operatorStack[k-1],token[i])){
                    queue[j]=operatorStack[k-1];
                    operatorStack[k-1]=token[i];
                    j++;
                }
                else{
                    operatorStack[k]=token[i];
                    k++;
                }
            }

            else if(token[i]=="("){
                operatorStack[k]=token[i];
                k++;
            }

            else {  // ")" encountered
                while(operatorStack[k-1]!="("){
                    queue[j]=operatorStack[k-1];
                    operatorStack.erase(operatorStack.begin()+(k-1));
                    j++;
                    k--;        //k changed...now k=the position after (
                }
                operatorStack.erase(operatorStack.begin()+(k-1));
                k--;      //now k=position of (..."(" discarded and its position available/free now
            }
        }
    }
    // now k = next empty in operatorStack[]...want to read now so start from k-1
    k=k-1;
    //if operators left in operatorStack, pop them to queue

    while(k>=0){
        queue[j]=operatorStack[k];
        operatorStack.erase(operatorStack.begin()+k);
        k--;
        j++;
    }
    //operator stack is now empty
    return queue;
}

#define rpn_tokenizer
#endif // rpn_tokenizer
// TOKENIZER
