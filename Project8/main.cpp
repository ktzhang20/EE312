#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <map>
#include "Parse.h"
using namespace std;

const uint32_t sizeArray = 4096;
string text;
vector<char> arr;
vector<string> line;
vector<int32_t> arr2;
stack<int> calc;
map<string, int> varStorage;
bool checkToken(string s){
  if(s == "set" || s == "var" || s == "output" || s == "text")
    return false;
  return true;
}


int operandoperator(int x, string i, int y){
  if(i == "+"){
    return x + y;
  }
  else if(i == "-"){
    return x - y;
  }
  else if(i == "/"){
    return x / y;
  }
  else if(i == "*"){
    return x * y;
  }
  else if(i == "=="){
    return x == y;
  }
  else if(i == "<"){
    return x < y;
  }
  else if(i == ">"){
    return x > y;
  }
  else if(i == ">="){
    return x >= y;
  }
  else if(i == "<="){
    return x <= y;
  }
  else if(i == "=="){
    return x == y;
  }
  else if(i == "!="){
    return x != y;
  }
  else if(i == "&&"){
    return x && y;
  }
  else if(i == "||"){
    return x || y;
  }
  else if (i == "%"){
    return x % y;
  }


  return 0;
}


void printText(){
  read_next_token();
  cout << next_token();
}



void readLine() {
  line.clear();
  while (checkToken(text)) {
    auto item = varStorage.find(text);
    if(item != varStorage.end()){
      line.push_back(to_string(item->second));
    }
    else{
    line.push_back(text);
    }
    text = peek_next_token();
    if(!checkToken(text)){
      break;
    }
    if(text == "//"){
      skip_line();
      read_next_token();
      text = peek_next_token();
    }
    else{
    read_next_token();
    text = next_token();
    }
    
  }
  /*for(string s: line){
    cout << s;
  }
  cout << endl;*/
}


bool checkExpo(string s){
  if(s == "+" || s == "-" || s == "/" || s == "*" || s == "==" || s == "<" || s == ">" || s == ">=" || s == "<=" || s == "!=" || s == "%"|| s == "&&" || s == "||"){
    return true;
  }
  return false;
}

int doMath(){
  int l = 0; int r = 0; string sign;
  for(int i = line.size()-1; i >= 0; i--){
    if(line[i] == "!"){
      int x = calc.top();
      calc.pop();
      if(x == 0)
        calc.push(1);
      else
        calc.push(0);
      continue;
    }
    if(line[i] == "~"){
      int x = calc.top();
      calc.pop();
      x = -x;
      calc.push(x);
      continue;
    }
    if(checkExpo(line[i])){
      l = calc.top();
      calc.pop();
      r = calc.top();
      calc.pop();
      sign = line[i];
      calc.push(operandoperator(l,sign,r));
      continue;
    }
    int x = stoi(line[i]);
    calc.push(x);
    
  }
  l = calc.top();
  calc.pop();
  return l;
}

void setVar(){
  read_next_token();
  text = next_token();
  int i = 0;
  auto item = varStorage.find(text);
  if(item != varStorage.end()){
    text = peek_next_token();
    if(next_token_type == SYMBOL){
      read_next_token();
      readLine();
      i = doMath();
    }
    else{
      i = token_number_value;
    }
    item -> second = i;
  }
  else{
    cout << "This key does not exist.";
  }
}

void createVar(){
  read_next_token();
  text = next_token();
  string name = text;
  auto item = varStorage.find(text);
  if(item != varStorage.end()){
    cout << "variable " << text << " incorrectly re-initialized" << endl;
    peek_next_token();
    int i = 0;
    if(next_token_type == SYMBOL){
      text = peek_next_token();
      read_next_token();
      readLine();
      i = doMath();
    }
    else{
      i = token_number_value;
    }
    item->second = i;
    
  }
  else{
    peek_next_token();
    int i = 0;
    if(next_token_type == SYMBOL){
      text = peek_next_token();
      read_next_token();
      readLine();
      i = doMath();
    }
    else{
      i = token_number_value;
    }
    varStorage.insert({name, i});
  }
}




void output(){
  read_next_token();
  text = next_token();
  auto item = varStorage.find(text);
  if(item != varStorage.end()){
    cout << item -> second;
  }
  else{ 
  readLine();
  cout << doMath();
  }
}





void SelectFunction(){
  if(text == "set"){
    setVar();
  }
  else if(text == "var"){
    createVar();
  }
  else if(text == "output"){
    output();
  }
  else if(text == "text"){
    printText();
  }
  else
    cout << "not a valid function. " << endl;
}





void run(){
  while(next_token_type != END){
    text = next_token();
    if(text == "//"){
      skip_line();
      read_next_token();
      continue;
    }
    if(next_token_type == NAME){
      SelectFunction();
    }
    
    read_next_token();
  }
}

int main(void) {
  set_input("test_grader.blip");
  run();
} 