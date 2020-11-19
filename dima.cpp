/*
==============================
DIMA dimensional analysis tool
& commandline calculator.

This is not a library.
This is actually for using.

By Nicholas McDonald 2020
==============================
*/

#include <iostream>
#include <string>
#include "math.h"
#include <map>
#include <vector>
#include <array>
#include <initializer_list>

using namespace std;
using dlist = initializer_list<double>;

#include "source/unit.h"
#include "source/define.h"
#include "source/func.h"
#include "source/calc.h"

int main( int argc, char* args[] ) {

  //cout.precision(17);

  string expression = compress(argc, args);   //Compress Commandline
  pv parsevec = parse(expression);            //Parse into a vector

  val n = eval(parsevec, 0);
  cout<<n<<endl;

  return 0;

}
