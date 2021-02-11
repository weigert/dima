map <string, val> ud = {

  //Time
  {"hour",val(3600, s)},
  {"min", val(60, s)},
  {"ks",  val(1E+3, s)},
  {"s",   val(1, s)},
  {"ms",  val(1E-3, s)},
  {"us",  val(1E-6, s)},
  {"ns",  val(1E-9, s)},

  //Distance
  {"km",  val(1E+3, m)},
  {"m",   val(1, m)},
  {"dm",  val(1E-1, m)},
  {"cm",  val(1E-2, m)},
  {"mm",  val(1E-3, m)},
  {"um",  val(1E-6, m)},
  {"nm",  val(1E-9, m)},

  //Mass
  {"t",   val(1E+3, kg)},
  {"kg",  val(1, kg)},
  {"g",   val(1E-3, kg)},
  {"mg",  val(1E-6, kg)},
  {"ug",  val(1E-9, kg)},

  //Current
  {"kA",  val(1E+3, A)},
  {"A",   val(1, A)},
  {"mA",  val(1E-3, A)},
  {"uA",  val(1E-6, A)},

  //Amount
  {"kmol",  val(1E+3, mol)},
  {"mol",   val(1, mol)},
  {"mmol",  val(1E-3, mol)},
  {"umol",  val(1E-6, mol)},

  //Temperature
  {"RT",  val(300, K)},
  {"K",   val(1, K)},
  {"mK",  val(1E-3, K)},
  {"uK",  val(1E-6, K)},

  /* candela? really? */
  {"cd",  val(1, cd)},

  //Derived Units
  {"J", val(1, kg*(m^2)/(s^2))},    //Joule   (Energy / Work)
  {"erg", val(1E-7, kg*(m^2)/(s^2))},    //erg   (Energy / Work)
  {"eV", val(1.602176634E-19, kg*(m^2)/(s^2))},  //Electron Volt
  {"kcal", val(4184, kg*(m^2)/(s^2))},    //Joule   (Energy / Work)

  {"W",   val(1, kg*(m^2)/(s^3))},    //Watt    (Power)

  {"mN",   val(1E-3, kg*m/(s^2))},        //Newton  (Force)
  {"N",   val(1, kg*m/(s^2))},        //Newton  (Force)
  {"dyn", val(1E-5, kg*m/(s^2))},     //dynes  (Force)

  {"kV",  val(1E+3, kg*(m^2)/(s^3)/A)},  //Voltage (Energy per Charge)
  {"V",   val(1, kg*(m^2)/(s^3)/A)},  //Voltage (Energy per Charge)
  {"mV",  val(1E-3, kg*(m^2)/(s^3)/A)},  //Voltage (Energy per Charge)

  {"GHz",   val(1E+9, D/s)},           //Hertz   (Frequency)
  {"MHz",   val(1E+6, D/s)},           //Hertz   (Frequency)
  {"kHz",   val(1E+3, D/s)},           //Hertz   (Frequency)
  {"Hz",    val(1E+0, D/s)},           //Hertz   (Frequency)
  {"mHz",   val(1E-3, D/s)},           //Hertz   (Frequency)
  {"uHz",   val(1E-6, D/s)},           //Hertz   (Frequency)
  {"Bq",    val(1E+0, D/s)},           //Becquerel   (Frequency)

  {"Torr",  val(133.322, kg/m/(s^2))},
  {"atm",   val(101325, kg/m/(s^2))},    //Pascal  (Pressure)
  {"Pa",    val(1, kg/m/(s^2))},    //Pascal  (Pressure)
  {"kbar",  val(1E+8, kg/m/(s^2))},
  {"bar",   val(1E+5, kg/m/(s^2))}, //Bar
  {"mbar",  val(1E+2, kg/m/(s^2))},

  {"C",     val(1, A*s)},           //Coulomb (Charge)

  //Physical Constants
  {"R",   val(8.31446261815324, kg*(m^2)/(s^2)/K/mol)},
  {"kB",  val(1.380649E-23, kg*(m^2)/(s^2)/K)},
  {"F",  val(96485.3329, A*s/mol)},
  {"NA",  val(6.02214076E+23, D/mol)},
  {"h",   val(6.62607015E-34, kg*(m^2)/(s^3))},

  //Mathematical Constants
  {"pi", val(3.14159265359, D)},
  {"e", val(2.718281828459, D)}
};

val getval(string s){
  if(ud.find(s) != ud.end()) return ud[s];
  throw fatal("Could not identify unit \""+s+"\"");
  return val(0, D);
}
