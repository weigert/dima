/*
===============================
          Functions
===============================
*/

double fac(double f){
  if((f - (int)f)>0.0) throw fatal("This is not the gamma function.");
  if(f > 100) throw fatal("Please don't break computer.");
  if(f == 0.0) return 1.0;
  return f*fac(f-1.0);
}
