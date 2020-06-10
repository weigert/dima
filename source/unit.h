/*
===============================
          SI Base Unit
===============================
*/

struct unit{            //Generic SI Derived-Unit
  double s   = 0;        //Time
  double m   = 0;        //Length
  double kg  = 0;        //Mass
  double A   = 0;        //Current
  double K   = 0;        //Thermodynamic Temperature
  double mol = 0;        //Amount
  double cd  = 0;        //Luminosity

  unit(){}; //Dimensionless
  unit(int _s, int _m, int _kg, int _A, int _K, int _mol,  int _cd){
    s = _s; m = _m; kg = _kg; A = _A, K = _K, mol = _mol, cd = _cd;
  }
};

const unit D =   unit(0, 0, 0, 0, 0, 0, 0);
const unit s =   unit(1, 0, 0, 0, 0, 0, 0);
const unit m =   unit(0, 1, 0, 0, 0, 0, 0);
const unit kg =  unit(0, 0, 1, 0, 0, 0, 0);
const unit A =   unit(0, 0, 0, 1, 0, 0, 0);
const unit K =   unit(0, 0, 0, 0, 1, 0, 0);
const unit mol = unit(0, 0, 0, 0, 0, 1, 0);
const unit cd =  unit(0, 0, 0, 0, 0, 0, 1);

bool operator==(const unit& l, const unit& r){
  if(l.s   != r.s)   return false;
  if(l.m   != r.m)   return false;
  if(l.kg  != r.kg)  return false;
  if(l.A   != r.A)   return false;
  if(l.K   != r.K)   return false;
  if(l.mol != r.mol) return false;
  if(l.cd  != r.cd)  return false;
  return true;
}

bool operator!=(const unit& l, const unit& r){
  return !(l == r);
}

unit operator+(unit l, unit r){
  if(l == r) return l;

  //Decide on a more comprehensive exit message

  //somehow output the position of the error!
  std::cout<<"Unit mismatch in operator +: "<<std::endl;
  exit(0);
}

unit operator-(unit l, unit r){
  if(l == r) return l;
  std::cout<<"Unit mismatch in operator -: "<<std::endl;
  exit(0);
}

unit operator/(unit l, unit r){
  l.s   -= r.s;
  l.m   -= r.m;
  l.kg  -= r.kg;
  l.A   -= r.A;
  l.K   -= r.K;
  l.mol -= r.mol;
  l.cd  -= r.cd;
  return l;
}

unit operator*(unit l, unit r){
  l.s   += r.s;
  l.m   += r.m;
  l.kg  += r.kg;
  l.A   += r.A;
  l.K   += r.K;
  l.mol += r.mol;
  l.cd  += r.cd;
  return l;
}

template<typename T>
unit operator^(unit l, const T f){   //Note: this operator has bad precedence, so requires bracketing
  l.s   *= f;
  l.m   *= f;
  l.kg  *= f;
  l.A   *= f;
  l.K   *= f;
  l.mol *= f;
  l.cd  *= f;
  return l;
}

/* Unit STDIO */

void uprint(ostream& o, string x, double f){
  if(f == 0) return;
  if(f == 1) o<<x<<" ";
  else o<<x<<"^"<<f<<" ";
}

ostream& operator<<(ostream& o, const unit& u){
  uprint(o, "kg", u.kg);
  uprint(o, "m", u.m);
  uprint(o, "A", u.A);
  uprint(o, "K", u.K);
  uprint(o, "mol", u.mol);
  uprint(o, "cd", u.cd);
  uprint(o, "s", u.s);
  return o;
}

/*
===============================
     Compound Unit + Value
===============================
*/

struct val{ //Scale + Unit
  double n = 1.0;
  unit u;

  val(){};  //Dimensionless Single Value
  val(double _n, unit _u):n{_n},u(_u){};
};

bool operator==(const val& l, const val& r){
  if(l.u != r.u) return false;
  if(l.n != r.n) return false;
  return true;
}

val operator+(val l, const val& r){
  l.u = l.u + r.u;
  l.n = l.n + r.n;
  return l;
}

val operator-(val l, const val& r){
  l.u = l.u - r.u;
  l.n = l.n - r.n;
  return l;
}

val operator*(val l, const val& r){
  l.n = l.n * r.n;
  l.u = l.u * r.u;
  return l;
}

val operator/(val l, const val& r){
  l.n = l.n / r.n;
  l.u = l.u / r.u;
  return l;
}

val operator^(val l, const val& r){
  if(r.u != D){
    std::cout<<"Non-dimensionless exponent"<<std::endl;
    exit(0);
  }
  l.n = pow(l.n, r.n);
  l.u = l.u ^ r.n;
  return l;
}

ostream& operator<<(ostream& o, const val& v){
  return (o << v.n <<" "<< v.u);
}
