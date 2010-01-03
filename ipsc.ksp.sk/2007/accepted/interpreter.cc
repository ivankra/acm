#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include <map>

#define VERBOSE 1 // verboseness level: 0 silent, 1 normal (report result only), 2 verbose
#define IFVERB(x) if (VERBOSE>=1) { x ; }
#define IFVERB2(x) if (VERBOSE>=2) { x ; }
#define ERROR(x) { IFVERB(cerr << x << endl;); exit(1); }
#define MAXSTEPS 1000000

using namespace std;

typedef unsigned int number; // note that we assume that int has 32 bits

deque<number> Q; // queue
vector<string> Prog; // program
map<string,int> Labels; // maps labels to lines
map<string,int>::iterator label; // we are gonna look for labels 
vector<number> Vars; // variables a-z
int IP; // instruction pointer
int SC; // step count

int QGET() { if (Q.empty()) ERROR("Queue empty."); int t=Q.front(); Q.pop_front(); return t; }

int main(void) {
  string stmp;
  number x,y;

  while (cin >> stmp) { 
    Prog.push_back(stmp);
    if (stmp[0]==':') Labels[stmp.substr(1,1000)]=Prog.size()-1;
  }
  Prog.push_back(string("Q"));

  IFVERB2(cerr << "Program:" << endl;);
  IFVERB2(for (vector<string>::iterator it=Prog.begin();it!=Prog.end();++it) cerr << "  " << *it << endl;);
  IFVERB2(cerr << "-----" << endl;);

  Vars.resize(300,0);
  IP=SC=0;
  while (1) {
    IFVERB2(cerr << "  ip=" << IP << " command=" << Prog[IP] << " steps=" << SC << endl;);
    switch (Prog[IP][0]) {
      case 'C': // print as char
        if (Prog[IP].length()==1) cout << char(QGET()%256); else {
          if ((Prog[IP][1]<'a') || (Prog[IP][1]>'z')) ERROR("Incorrect variable name.");
          cout << char(Vars[int(Prog[IP][1])]%256);
        }
        break;
//      case 'D': x=QGET(); Q.push_back(x); Q.push_back(x); break; // duplication 
      case 'E': // jump if equal 
        if (Prog[IP].length()<3) ERROR("Command missing a variable.");
        if ((Prog[IP][1]<'a') || (Prog[IP][1]>'z')) ERROR("Incorrect variable name.");
        if ((Prog[IP][2]<'a') || (Prog[IP][2]>'z')) ERROR("Incorrect variable name.");
        if (Vars[int(Prog[IP][1])] == Vars[int(Prog[IP][2])]) {
          label=Labels.find(Prog[IP].substr(3,1000)); 
          if (label!=Labels.end()) IP=(label->second)-1;
        }
        break;
      case 'G': // jump if greater 
        if (Prog[IP].length()<3) ERROR("Command missing a variable.");
        if ((Prog[IP][1]<'a') || (Prog[IP][1]>'z')) ERROR("Incorrect variable name.");
        if ((Prog[IP][2]<'a') || (Prog[IP][2]>'z')) ERROR("Incorrect variable name.");
        if (Vars[int(Prog[IP][1])] > Vars[int(Prog[IP][2])]) {
          label=Labels.find(Prog[IP].substr(3,1000)); 
          if (label!=Labels.end()) IP=(label->second)-1;
        }
        break;
      case 'J': // unconditional jump
        label=Labels.find(Prog[IP].substr(1,1000)); 
        if (label!=Labels.end()) IP=(label->second)-1;
        break;
      case 'P': // print
        if (Prog[IP].length()==1) cout << QGET() << endl; else {
          if ((Prog[IP][1]<'a') || (Prog[IP][1]>'z')) ERROR("Incorrect variable name.");
          cout << Vars[int(Prog[IP][1])] << endl;
        }
        break;
      case 'Q': cerr << "Terminated correctly after " << SC << " steps." << endl; return 0; break; // quit
      case 'Z': // jump if zero
        if (Prog[IP].length()==1) ERROR("Command missing a variable.");
        if ((Prog[IP][1]<'a') || (Prog[IP][1]>'z')) ERROR("Incorrect variable name.");
        if (!Vars[int(Prog[IP][1])]) {
          label=Labels.find(Prog[IP].substr(2,1000)); 
          if (label!=Labels.end()) IP=(label->second)-1;
        }
        break;
      case ':': break; // declaration of a label
      case '+': x=QGET(); y=QGET(); Q.push_back((x+y)%65536); break; // addition
      case '-': x=QGET(); y=QGET(); Q.push_back((65536+x-y)%65536); break; // subtraction 
      case '*': x=QGET(); y=QGET(); Q.push_back((x*y)%65536); break; // multiplication 
      case '/': x=QGET(); y=QGET(); if (!y) ERROR("Division by zero."); Q.push_back(x/y); break; // division 
      case '%': x=QGET(); y=QGET(); if (!y) ERROR("Division by zero."); Q.push_back(x%y); break; // modulo
      case '>': // get into a variable
        if (Prog[IP].length()==1) ERROR("Command missing a variable.");
        if ((Prog[IP][1]<'a') || (Prog[IP][1]>'z')) ERROR("Incorrect variable name.");
        Vars[int(Prog[IP][1])]=QGET();
        break;
      case '<': // put from a variable
        if (Prog[IP].length()==1) ERROR("Command missing a variable.");
        if ((Prog[IP][1]<'a') || (Prog[IP][1]>'z')) ERROR("Incorrect variable name.");
        Q.push_back(Vars[int(Prog[IP][1])]);
        break;
      default: Q.push_back(atoi(Prog[IP].c_str())%65536); break; // convert to a number && push it
    }
    IP++; SC++; 
    if (SC>MAXSTEPS) ERROR("Too many steps.");
  }
  return 0;
}
