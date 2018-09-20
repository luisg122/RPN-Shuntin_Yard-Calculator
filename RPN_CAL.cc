#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <functional>
#include <cmath>
#define PI  3.14159265
#define e   2.718281828
using namespace std;
double   RPN(vector <string> tokens);
void     Shunting_Yard(vector<string> token);
void     User_Choice();
//creating a strtok function from  "scratch"
vector<string> split(const string &str,function<bool(char)> delimiter=[](char c)->bool{return c==' '; } ,bool noempty=true){
    vector<string> result;
    auto prev = str.begin(); 
    auto next = str.begin();
    auto end  = str.end();
    do{
        next = find_if(prev, end, delimiter);
        if(!noempty || next != prev){
            result.push_back(string(prev,next)); // [prev,next)   
        }
        prev = next + 1;	// Move
    }
	while(next != end);
    return result;
}
//=====================================================================================
vector<string> Shuntingyard(vector<string> tokens){
    vector<string> output;	//instead of queue, we use vector.
    stack<string> yard;		//stack for operations.
    for(auto & t: tokens){
        if(t=="+"||t=="-"){
         	if(yard.empty()||yard.top()=="(") yard.push(t);
        	else{
        	  	while(1){
           			output.push_back(yard.top());
            		yard.pop();
            		if(yard.empty()||yard.top()=="(") break;
          		}
            	yard.push(t);
			}
        }
        
        else if(t=="*"||t=="/"){
        	if(yard.empty()||yard.top()=="(") yard.push(t);
        	else{
        	  	while(yard.top()=="*"||yard.top()=="/"||yard.top()=="^"){
           			output.push_back(yard.top());
            		yard.pop();
            		if(yard.empty()||yard.top()=="(") break;
          		}
            	yard.push(t);
			}
        }	
        else if(t=="^"||t=="("||t=="sin"||t=="cos"||t=="tan"||t=="log10"||t=="ln"){
        	yard.push(t);
		}
		else if(t==")"){
			while(1){
				if(yard.top()=="("){
					yard.pop();
					if(yard.top()=="sin"||yard.top()=="cos"||yard.top()=="tan"||yard.top()=="log10"||yard.top()=="ln"){					
						output.push_back(yard.top());
						yard.pop();	
					}
					break;
				}
				output.push_back(yard.top());
				yard.pop();

			}
		}
	
        else{
          output.push_back(t);
        }
    }
    while(!yard.empty()){
    output.push_back(yard.top());
    yard.pop();}
    return output;
}
//=====================================================================================
int main(){
	User_Choice();
	return 0;
}
//=====================================================================================
void User_Choice(){
	int choice = 0;
	string input_str;
	vector<string> tokens;
	
	cout << "Welcome to the RPN - Shunting Yard Calculator!!!\n"
   		 <<	"(please remember to space out your characters for each input)\n\n";	
	do{
		cout << "1. RPN Calculator\n";
		cout << "2. Shunting Yard Calculator\n";
		cout << "3. Exit Program\n";
		
		do{
			cout << "Enter Your Choice of Calculator: ";
			cin >> choice;
		}
		while(choice < 0 || choice > 3);
	
		switch(choice){
			case 1: {						//to avoid cross-initialiazation compiler error, use braces for scope of variables
			    cin.ignore(1000, '\n');		//clearing out the buffer
				while(true){
					cout   << "\nEnter RPN string (ENTER 'q' to quit): ";
					getline(cin, input_str);
					if(input_str == "q") break;
					auto tok = split(input_str);
					for(auto t: tok ) tokens.push_back(t);
					RPN(tokens);
				}
				cout << "\n================================================\n";
				tokens.clear();				//clears the vector to avoid token accumulation
				break;
			}
			case 2:{
				cin.ignore(1000, '\n');		//clearing out the buffer
				while(true){
					cout << "\nEnter Infix Expression (ENTER to 'q' to quit): ";
					getline(cin, input_str);
					if(input_str == "q") break;
					auto tok = split(input_str);
					for(auto t: tok) tokens.push_back(t);	
					Shunting_Yard(tokens);
					tokens.clear();			//clears the vector to avoid token accumulation
				}
				cout << "\n================================================\n";
				break;
			}
			case 3: break;
		}
	}
	while(choice != 3);	
}
//=====================================================================================
double RPN(vector<string> tokens){
   	stack <double> num_stack;
   	for(auto t: tokens){					//stack is a really simple structure
		if(t == "+"|| t == "-" || t == "*" || t == "/" || t == "^"){
			double b = num_stack.top();	num_stack.pop();
			double a = num_stack.top();	num_stack.pop();		
				
			if(t == "+")	num_stack.push(double(a + b));
			if(t == "-")	num_stack.push(double(a - b));
			if(t == "*")	num_stack.push(double(a * b));
			if(t == "/")	num_stack.push(double(a / b));
			if(t == "^")	num_stack.push(double(pow(a, b)));
		}	
		else if(t == "sin" || t == "cos" || t == "tan" || t == "log10" || t == "ln"){
			double c = num_stack.top(); num_stack.pop();
		
			if(t ==   "sin")   num_stack.push(sin(c));
   			if(t ==   "cos")   num_stack.push(cos(c));
   			if(t ==   "tan")   num_stack.push(tan(c));
   			if(t == "log10")   num_stack.push(log10(c));
       		if(t ==    "ln")   num_stack.push(log(c));
		}	
		else{ 
			if(t == "PI" || t == "e"){
				if(t == "PI")	num_stack.push(PI);
				if(t == "e" )   num_stack.push(e);	
			}
			else num_stack.push(stod(t));  	
		}
	}
   	cout << "ANSWER: " << num_stack.top();
	cout << "\n------------------------------------------------\n";
	//return num_stack.top();
}
//=======================================================================================
void Shunting_Yard(vector <string> tokens){
	auto output = Shuntingyard(tokens);
    cout << "\nPostfix Expression: ";
	for(auto c:output) cout << c << " ";
	cout << "\n------------------------------------------------\n";
}
//=======================================================================================
