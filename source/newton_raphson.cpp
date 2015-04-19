#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include "operator_check.cpp"
using namespace std;
#ifndef newton_raphsonh
#define newton_raphsonh
vector<double> roots;
double root;

//function to calculate absolute value of a double
double abs1(double x) {
    if(x<0) x*=-1;
    return x;
}

//code to evaluate an expression in its RPN form at a given x
double evaluate(vector<string> v, double x)
{
	ostringstream iss;
	iss<<x;
	string x1=iss.str();
	for(int i=0;i<v.size();i++) {
		if(v[i]=="x") {
			v[i]=x1;
		}
	}
    for(int i=0;
    i<v.size();
    i++)
    {
        if(is_binaryoperator(v[i]))
        {
            if(v[i]=="+")
            {
                double y=atof((v[i-2].c_str()))+atof((v[i-1].c_str()));
                ostringstream iss;
                iss<<y;
                v[i-2]=iss.str();
            }
            else if (v[i]=="-")
            {
                double y=atof((v[i-2].c_str()))-atof((v[i-1].c_str()));
                ostringstream iss;
                iss<<y;
                v[i-2]=iss.str();
            }
            else if (v[i]=="*")
            {
                double y=atof((v[i-2].c_str()))*atof((v[i-1].c_str()));
                ostringstream iss;
                iss<<y;
                v[i-2]=iss.str();
            }
            else if(v[i]=="/" )
            {
                double y=atof((v[i-2].c_str()))/atof((v[i-1].c_str()));
                ostringstream iss;
                iss<<y;
                v[i-2]=iss.str();
            }
            else if(v[i]=="^")
            {
                double y=pow(atof((v[i-2].c_str())),atof((v[i-1].c_str())));
                ostringstream iss;
                iss<<y;
                v[i-2]=iss.str();
            }
            v.erase(v.begin()+i);
            v.erase(v.begin()+i-1);
            i=i-2;
        }
        else if(is_unaryoperator(v[i]))
        {
            if(v[i]=="cos")
            {
                double y=cos(atof((v[i-1].c_str())));
                ostringstream iss;
                iss<<y;
                v[i-1]=iss.str();
            }
            else if(v[i]=="sin" )
            {
                double y=sin(atof((v[i-1].c_str())));
                ostringstream iss;
                iss<<y;
                v[i-1]=iss.str();
            }
            else if(v[i]=="tan" )
            {
                double y=tan(atof((v[i-1].c_str())));
                ostringstream iss;
                iss<<y;
                v[i-1]=iss.str();
            }

            else if(v[i]=="sinh")
            {
                double y=sinh(atof((v[i-1].c_str())));
                ostringstream iss;
                iss<<y;
                v[i-1]=iss.str();
            }
            else if(v[i]=="cosh")
            {
                double y=cosh(atof((v[i-1].c_str())));
                ostringstream iss;
                iss<<y;
                v[i-1]=iss.str();
            }
            else if(v[i]=="tanh")
            {
                double y=tanh(atof((v[i-1].c_str())));
                ostringstream iss;
                iss<<y;
                v[i-1]=iss.str();
            }
            else if(v[i]=="atan")
            {
                double y=atan(atof((v[i-1].c_str())));
                ostringstream iss;
                iss<<y;
                v[i-1]=iss.str();
            }
            else if(v[i]=="acos")
            {
                double y=acos(atof((v[i-1].c_str())));
                ostringstream iss;
                iss<<y;
                v[i-1]=iss.str();
            }
            else if(v[i]=="asin")
            {
                double y=asin(atof((v[i-1].c_str())));
                ostringstream iss;
                iss<<y;
                v[i-1]=iss.str();
            }
            else if(v[i]=="atanh")
            {
                double y=atanh(atof((v[i-1].c_str())));
                ostringstream iss;
                iss<<y;
                v[i-1]=iss.str();
            }
            else if(v[i]=="log")
            {
                double y=log(atof((v[i-1].c_str())));
                ostringstream iss;
                iss<<y;
                v[i-1]=iss.str();
            }
            else if(v[i]=="log10")
            {
                double y=log10(atof((v[i-1].c_str())));
                ostringstream iss;
                iss<<y;
                v[i-1]=iss.str();
            }
            else if(v[i]=="exp")
            {
                double y=exp(atof((v[i-1].c_str())));
                ostringstream iss;
                iss<<y;
                v[i-1]=iss.str();
            }
            else if(v[i]=="sqrt")
            {
                double y=sqrt(atof((v[i-1].c_str())));
                ostringstream iss;
                iss<<y;
                v[i-1]=iss.str();
            }
            v.erase(v.begin()+i);
            i=i-1;
        }
    }
    return atof(v[0].c_str());
}

//function to numerically calculate derivative of function
double df(const vector<string> expression, double x, double h=10e-5) {
	double dy=evaluate(expression, x+h)-evaluate(expression, x-h);
	double dx=h*2;
	double d=dy/dx;
	return d;

}

//function for the newton raphson method in range l to r
double newton_raphson(vector<string> expression, double x, double l, double r) {
	int num_of_iterations=105;
	double x1=1e10;
	while(abs1(x-x1)>10e-5 || num_of_iterations>=0) {
		x1=x;
		if(df(expression, x)!=0){
            x=x-(evaluate(expression, x)/df(expression, x));
		}
        num_of_iterations--;
	}
	if(abs1(evaluate(expression, x))>1e-3) {
		for(int i=0;i<10;i++) {
			x=x-(evaluate(expression, x)/df(expression, x));
		}
		if(abs1(evaluate(expression, x))>1e-3) {
            ostringstream oss;
            //oss<<"1no root in interval "<<l<<" "<<r;
            const char* a=oss.str().c_str();
			throw a;
		}
	}
	if(x<r && x>l && abs1(evaluate(expression, x))<1e-3){
        //w++;
        //cout<<"valid x(root) found after newton raphson "<<w<<" is "<<x<<endl;
        return x;
	}
	else{
        //cases included in else-- NR diverges
        //root outside domain is obtained
        //nan etc
        // same root as l/r is obtained...these corner points if roots-already stored and if original l & r-explicitly checked
        ostringstream oss;
            //oss<<"2no root in interval "<<l<<" "<<r;
            const char* a=oss.str().c_str();
			throw a;
	}
}

//code for storing roots
void storing_roots(vector<double> &rs,double r){
    bool not_exist_already=true;
    for(int i=0;i<rs.size();i++){
        if(abs1(rs[i]-r)<1e-4){
            not_exist_already=false;
            break;
        }
    }
    if(not_exist_already){
        rs.push_back(r);
    }
    return;
}

//main algorithm for finding roots using newton raphson method
void recursive_solve(vector<string> expression, double l, double r) {
	double a=l!=0?l:r;
	double b=r-l;
	if(abs1(b/a)<10e-4)
	{
	    //t++;
	    //cout<<"stopped solving "<<t<<endl;
		return;
	}
	if((r-l)<1e-3){
        return;
    }
	double m=(l+r)/2;
	double val=evaluate(expression, m);
	if(abs1(val)>1e-4) {                    //val != 0
		if(abs1(df(expression, m))>1e-5) {   //df != 0
			try {
                    root=newton_raphson(expression, m, l, r);
                    //storing_roots(roots,root);
				//recursive_solve(expression, l, root);     if no root then no recursion here..that's y previously only
				//recursive_solve(expression, root, r);     3 recursion were seen
				//1 recursion..normal..(1-1 recursion..no root stopped)..(1-2 recursion..no root stopped)
                    roots.push_back(root);
                    recursive_solve(expression, l, root);
                    recursive_solve(expression, root, r);
			}
			catch(const char* msg) {

			}
		}
		else {
			recursive_solve(expression, l, m);
			recursive_solve(expression, m, r);
		}
	}
	else {
        roots.push_back(m);
		//storing_roots(roots,root);
		/*bool not_already_recursed=true;
        for(int n=0;n<(roots.size()-1);n++){
            if(abs1(roots[n]-root)<1e-3){
                not_already_recursed=false;
                cout<<"already recursed"<<endl;
                break;
            }
        }
        if(not_already_recursed){
            recursive_solve(expression, l, m);
            cout<<l<<" to "<<m<<" done!!"<<endl;
            recursive_solve(expression, m, r);
            cout<<m<<" to "<<r<<" done!!"<<endl;
        }*/
		recursive_solve(expression, l, m);
		recursive_solve(expression, m, r);
	}
	return;
}

#endif // newton_raphson
//newton raphson
