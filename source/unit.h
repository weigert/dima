/*
===============================
          SI Base Unit
===============================
*/

#define MAXDIM 7

void fatal(string err){
  cout<<err<<endl;
  exit(0);
}

struct unit{              //Generic SI Derived-Unit
  vector<double> dim;
  unit(){}; //Dimensionless
  unit(dlist d){
    for(auto&e: d)
      dim.push_back(e);
  }
};

const unit D =   unit({0, 0, 0, 0, 0, 0, 0});
const unit s =   unit({1, 0, 0, 0, 0, 0, 0});
const unit m =   unit({0, 1, 0, 0, 0, 0, 0});
const unit kg =  unit({0, 0, 1, 0, 0, 0, 0});
const unit A =   unit({0, 0, 0, 1, 0, 0, 0});
const unit K =   unit({0, 0, 0, 0, 1, 0, 0});
const unit mol = unit({0, 0, 0, 0, 0, 1, 0});
const unit cd =  unit({0, 0, 0, 0, 0, 0, 1});

bool operator==(const unit& l, const unit& r){
  if(l.dim.size() != r.dim.size())
    fatal("Dimension mismatch");
  for(int i = 0; i < l.dim.size(); i++)
    if(l.dim[i] != r.dim[i]) return false;
  return true;
}

bool operator!=(const unit& l, const unit& r){
  return !(l == r);
}

unit operator+(unit l, unit r){
  if(l == r) return l;
  fatal("Unit mismatch in operator +");
}

unit operator-(unit l, unit r){
  if(l == r) return l;
  fatal("Unit mismatch in operator -");
}

unit operator/(unit l, unit r){
  if(l.dim.size() != r.dim.size())
    fatal("Dimension mismatch");
  for(int i = 0; i < l.dim.size(); i++)
    l.dim[i] -= r.dim[i];
  return l;
}

unit operator*(unit l, unit r){
  if(l.dim.size() != r.dim.size())
    fatal("Dimension mismatch");
  for(int i = 0; i < l.dim.size(); i++)
    l.dim[i] += r.dim[i];
  return l;
}

template<typename T>
unit operator^(unit l, const T f){   //Note: this operator has bad precedence, so requires bracketing
  for(int i = 0; i < l.dim.size(); i++)
    l.dim[i] *= f;
  return l;
}

/* Unit STDIO */

void uprint(ostream& o, string x, double f){
  if(f == 0) return;
  if(f == 1) o<<x<<" ";
  else o<<x<<"^"<<f<<" ";
}

ostream& operator<<(ostream& o, const unit& u){
  uprint(o, "kg", u.dim[0]);
  uprint(o, "m", u.dim[1]);
  uprint(o, "A", u.dim[2]);
  uprint(o, "K", u.dim[3]);
  uprint(o, "mol", u.dim[4]);
  uprint(o, "cd", u.dim[5]);
  uprint(o, "s", u.dim[6]);
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
