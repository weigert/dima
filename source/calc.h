/*
===================================
    Commandline Math Evaluator
===================================
*/

/*
======== Input Parsing ==========
*/

enum pc {                         //Parse Class
  NUM, UNT, OPR, BRC
};
using pt = std::pair<pc,char>;    //Parse Tuple
using pv = std::vector<pt>;       //Parse Vector

string compress(int ac, char* as[]){
  string t;
  for(int i = 1; i < ac; i++)
    t += as[i]; //append to string
  return t;
}   //Note that spaces are automatically sliced out

void invalid(int i){
  std::cout<<"Invalid expression at position "<<i<<std::endl;
  exit(0);
}

void unrecognized(int i, char c){
  std::cout<<"Unrecognized character \""<<c<<"\" at position "<<i<<std::endl;
  exit(0);
}

pv parse(string e){
  pv parsevec;

  for(string::size_type i = 0; i < e.size(); i++){
    const char c = e[i];

    string brackets = "[]";
    string operators = "+-*/^";
    string numbers = "0123456789.";

    if(numbers.find(c) != string::npos)
      parsevec.push_back(pt(NUM, c));

    else if(isalpha(c))
      parsevec.push_back(pt(UNT, c));

    else if(operators.find(c) != string::npos)
      parsevec.push_back(pt(OPR, c));

    else if(brackets.find(c) != string::npos)
      parsevec.push_back(pt(BRC, c));

    else unrecognized(i, c);
  }
  return parsevec;
}

ostream& operator<<(ostream& o, const pv& parsevec){
  for(const pt& p: parsevec)
    o<<p.first<<" "<<p.second<<std::endl;
  return o;
}

/*
============= Evaluate Parse Vector ==============
*/

val construct(pv pvec, int n){
  unit u  = D;
  double f = 1.0;

  size_t i = 0;
  string s;

  while(i < pvec.size() && pvec[i].first == NUM){ //Get Number
    s.push_back(pvec[i].second);
    i++;
  }
  if(!s.empty()) f = stof(s);
  s.clear();

  while(i < pvec.size() && pvec[i].first == UNT){ //Get Unit
    s.push_back(pvec[i].second);
    i++;
  }
  if(!s.empty()){
    val m = getval(s);
    f *= m.n; //Scale f by m.n
    u = m.u;  //Set the unit
  }

  if(i != pvec.size())  //Trailing characters
    invalid(n+i);

  return val(f, u);
}

//Operate between two values
val eval(val a, val b, char op){
  if(op == '+') a = a + b;
  else if(op == '-') a = a - b;
  else if(op == '*') a = a * b;
  else if(op == '/') a = a / b;
  else if(op == '^') a = a ^ b;
  else{
    std::cout<<"Operator "<<op<<" not recognized"<<std::endl;
    exit(0);
  }
  return a;
}

//Parse Vector Evaluator
val eval(pv pvec, int n){

  if(pvec.empty())          //Empty Vector = 1
    return val(1.0, D);

  if(pvec[0].first == OPR)  //Invalid to start with an operator
    invalid(n);

  vector<val> vvec;   //Value Vector
  vector<char> ovec;  //Operator Vector

  size_t i = 0, j = 0;  //Parse section start and current
  while(j < pvec.size()){

    if(pvec[j].second == '['){

      i = ++j;  //Start after bracket
      for(int nbrackets = 0; j < pvec.size(); j++){
        if(pvec[j].second == '[') //Open Bracket
          nbrackets++;
        else if(pvec[j].second == ']'){
          if(nbrackets == 0) //Successful close
            break;
          nbrackets--; //Decrement open brackets
        }
      }

      //Open Bracket at End
      if(j == pvec.size())
        invalid(n+i-1);

      //Recursive sub-vector evaluate
      pv newvec(pvec.begin()+i, pvec.begin()+j);
      vvec.push_back(eval(newvec, n+j));
    }

    //Add Operator
    if(pvec[j].first == OPR)
      ovec.push_back(pvec[j].second);

    //Add Value
    if(pvec[j].first == NUM ||
       pvec[j].first == UNT){


      i = j; //Start at position j
      while(pvec[j].first != OPR &&
            pvec[j].first != BRC &&
            j < pvec.size()) j++; //increment

      //Construct the value and decrease j one time
      pv newvec(pvec.begin()+i, pvec.begin()+j);
      vvec.push_back(construct(newvec, n+j));
      j--;
    }

    j++; //Increment j

    //Out-of-Place closing bracket
    if(pvec[j].second == ']')
      invalid(n+j);

  }

  if(ovec.size() + 1 != vvec.size()){
    std::cout<<"Operator count mismatch"<<std::endl;
    exit(0);
  }

  //Exponentiation
  for(size_t i = 0; i < ovec.size();){
    if(ovec[i] == '^'){
      vvec[i] = eval(vvec[i], vvec[i+1], ovec[i]);
      ovec.erase(ovec.begin()+i);
      vvec.erase(vvec.begin()+i+1, vvec.begin()+i+2);
    }
    else i++;
  }

  //Multiplication / Division
  for(size_t i = 0; i < ovec.size();){
    if(ovec[i] == '*' || ovec[i] == '/' ){
      vvec[i] = eval(vvec[i], vvec[i+1], ovec[i]);
      ovec.erase(ovec.begin()+i);
      vvec.erase(vvec.begin()+i+1, vvec.begin()+i+2);
    }
    else i++;
  }

  //Addition / Subtraction
  for(size_t i = 0; i < ovec.size();){
    if(ovec[i] == '+' || ovec[i] == '-' ){
      vvec[i] = eval(vvec[i], vvec[i+1], ovec[i]);
      ovec.erase(ovec.begin()+i);
      vvec.erase(vvec.begin()+i+1, vvec.begin()+i+2);
    }
    else i++;
  }

  return vvec[0];
}
