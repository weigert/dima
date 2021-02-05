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
#include <functional>

using namespace std;
using dlist = initializer_list<double>;

string fatal(string err){
  // This function is simple, but it might return custom exceptions in the future.
  return err;
}

#include "source/unit.h"
#include "source/define.h"
#include "source/func.h"
#include "source/calc.h"

int main( int argc, char* args[] ) {

  string expression = compress(argc, args);   //Compress Commandline
  pv parsevec = parse(expression);            //Parse into a vector

  try { 
    // Bug: Results end with a space
    cout<<eval(parsevec, 0)<<endl;            //Evaluate expression
  } catch (const std::exception& e) { 
    cout<<"Exc: "<<endl;
    std::cout << e.what() << endl;
  } catch (string err) {
    cout<<err<<endl;
  }

  return 0;

}
