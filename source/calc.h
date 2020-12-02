enum pc {                    //Parse Class
  NUM, UNT, OPR, BRC, SPC
};
using pt = pair<pc,char>;    //Parse Tuple
using pv = vector<pt>;       //Parse Vector

string compress(int ac, char* as[]){
  string t;
  for(int i = 1; i < ac; i++)
    t += as[i]; //append to string
  return t;
}   //Note that spaces are automatically sliced out

void invalid(int i){
  cout<<"Invalid expression at position "<<i<<endl;
  exit(0);
}

void unrecognized(int i, char c){
  cout<<"Unrecognized character \""<<c<<"\" at position "<<i<<endl;
  exit(0);
}

pv parse(string e){
  pv parsevec;

  for(string::size_type i = 0; i < e.size(); i++){
    const char c = e[i];

    string brackets = "[]";
    string operators = "+-*/^%";    //Binary Operators
    string special = "!~E";         //Single Operators
    string numbers = "0123456789.";

    if(numbers.find(c) != string::npos)
      parsevec.push_back(pt(NUM, c));

    else if(isalpha(c))
      parsevec.push_back(pt(UNT, c));

    else if(operators.find(c) != string::npos)
      parsevec.push_back(pt(OPR, c));

    else if(brackets.find(c) != string::npos)
      parsevec.push_back(pt(BRC, c));

    else if(special.find(c) != string::npos)
      parsevec.push_back(pt(SPC, c));

    else unrecognized(i, c);
  }
  return parsevec;
}

ostream& operator<<(ostream& o, const pv& parsevec){
  for(const pt& p: parsevec)
    o<<p.first<<" "<<p.second<<endl;
  return o;
}

val construct(pv pvec, int n){
  unit u  = D;
  double f = 1.0;
  double p = 1.0;
  double fsgn = 1.0;
  double psgn = 0.0;

  size_t i = 0;
  string s;
  bool fp = false;

  if(pvec[i].second == '~'){
    fsgn = -1.0;
    i++;
  }

  while(i < pvec.size() && pvec[i].first == NUM){ //Get Number
    s.push_back(pvec[i].second);
    i++;
  }
  if(!s.empty()) f = stof(s);
  s.clear();

  if(pvec[i].second == 'E'){ //Test for Floating Point
    i++;
    psgn = 1.0;

    if(pvec[i].second == '~'){
      psgn = -1.0;
      i++;
    }

    while(i < pvec.size() && pvec[i].first == NUM){ //Get Number
      s.push_back(pvec[i].second);
      i++;
    }
    if(!s.empty()) p = stof(s);
    else fatal("Missing exponent in floating point representation.");
    s.clear();
  }

  if(pvec[i].second == 'E')   //Invalid Double Floating Point
    invalid(n+i);

  while(i < pvec.size() && pvec[i].first == UNT){ //Get Unit
    s.push_back(pvec[i].second);
    i++;
  }
  if(!s.empty()){
    val m = getval(s);
    f *= m.n; //Scale f by m.n
    u = m.u;  //Set the unit
  }

  if(pvec[i].second == '!'){
    f = fac(f);
    i++;
  }

  if(i != pvec.size())  //Trailing characters
    invalid(n+i);

  return val(fsgn*f*pow(10,psgn*p), u);
}

val eval(val a, val b, char op){
  if(op == '+') a = a + b;
  else if(op == '-') a = a - b;
  else if(op == '*') a = a * b;
  else if(op == '/') a = a / b;
  else if(op == '^') a = a ^ b;
  else if(op == '%') a = a % b;
  else fatal("Operator not recognized");
  return a;
}

val eval(pv pvec, int n){                         //Parse Vector Evaluator

  if(pvec.empty())                                //Empty Vector => 1 [-]
    return val(1.0, D);

  if(pvec[0].first == OPR)                        //Invalid start
    invalid(n);

  vector<val> vvec;                               //Value Vector
  vector<char> ovec;                              //Operator Vector

  size_t i = 0, j = 0;                            //Start and End
  while(j < pvec.size()){

    if(pvec[j].second == '['){                    //Opening Bracket
      i = ++j;                                    //Opening Position
      for(int nbrackets = 0; j < pvec.size(); j++){
        if(pvec[j].second == '[')                 //Open one bracket
          nbrackets++;
        else if(pvec[j].second == ']'){           //Close bracket
          if(nbrackets == 0) break;               //All brackets closed
          nbrackets--;                            //Close one bracket
        }
      }

      if(j == pvec.size())                        //Missing Closing Bracket
        invalid(n+i-1);

      pv newvec(pvec.begin()+i, pvec.begin()+j);  //Recursive Evaluate
      vvec.push_back(eval(newvec, n+j));
    }

    if(pvec[j].first == OPR)                      //Add Operator
      ovec.push_back(pvec[j].second);

    if(pvec[j].first == NUM ||                    //Add Value
       pvec[j].first == UNT ||
       pvec[j].first == SPC ){

      i = j;                                      //Start at position j
      while(pvec[j].first != OPR &&               //Increment
            pvec[j].first != BRC &&
            j < pvec.size()) j++;

      pv newvec(pvec.begin()+i, pvec.begin()+j);  //Construct Value, Move Back
      vvec.push_back(construct(newvec, n+j));
      j--;
    }

    j++;

    if(pvec[j].second == ']')                     //Out of Place Bracket
      invalid(n+j);

  }

  if(ovec.size() + 1 != vvec.size()) fatal("Operator Count Mismatch");

  function<void(string)> operate = [&](string op){
    for(size_t i = 0; i < ovec.size();){
      if(op.find(ovec[i]) != string::npos){
        vvec[i] = eval(vvec[i], vvec[i+1], ovec[i]);
        ovec.erase(ovec.begin()+i);
        vvec.erase(vvec.begin()+i+1, vvec.begin()+i+2);
      }
      else i++;
    }
  };

  operate("%");
  operate("^");
  operate("*/");
  operate("+-");

  return vvec[0];
}
