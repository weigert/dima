# dima
zero-dependency commandline dimensional analysis tool for unit conversion and consistency validation, written in c++

Also functions as a minimalist commandline calculator (i.e. unit = dimensionless) and physical constant / unit expression dictionary in your commandline.

## Usage

dima will evaluate a mathematical expression with SI units:

    dima [expression]

The expression can consist of any of the following mathematical operators (spaces are ignored):

    +   addition
    -   subtraction
    *   multiplication
    /   division
    ^   exponentiation
    []  bracketing

Values between operators can are given by a value, unit or value unit pair:

    > dima 1
    1

    > dima m^2
    1 m^2

    > dima 1J
    1 kg m^2 s^-2

    > dima 1m^2/s^2
    1 m^2 s^-2
    
    > dima J/N
    1 m

Empty brackets will evaluate to unity:

    > dima []
    1
    
Dima has a built in set of physical constants:

    > dima R
    8.31446 kg m^2 K^-1 mol^-1 s^-2
    
You can change your cout precision (see main file) to stop early value truncation.

Note that dima uses square brackets because the default bash shell doesn't like `()` round brackets, and I don't want to always have to type `\(` and `\)`. This program is about convenience. Feel free to fork and change though if you are using a different shell.

Dima also checks for syntax errors and reports the location of the error.

### Unit Dictionary
Units are defined in a unit dictionary (see `define.h`) that you are free to tune for your specific application.

Units are expressed in terms of SI base units and stored in a map. The map stores a value-unit pair, such that e.g. ms is a {1E-3, s} tuple, referenced by the unit string "ms".

Dima will also throw errors when trying to add non-consistent units, but will evaluate correctly with units that can be combined according to their base units:

    > dima 1m + 1km
    1001 m

### Compilation

    make dima

This program has no dependencies (besides a c++ compiler and the standard template library).

Running this with privilege will place the executable in your `/usr/bin` so you can access it anywhere.

## Other Stuff

### Unit Dictionaries
A standard set of units is defined in `define.h`. Units are parsed out of the expression and identified in the map.

Note that you should express things in terms of base units to avoid potential ambiguities / conflicts.

### To Do
- Add a dictionary conflict check
- Add a unit re-expression option (compound units)
- Non-dimensional units (e.g. quantity / object) option, useful for many applications (e.g. how many moles per particle, etc.)

### Issue Reporting
Please report any inconsistencies that you notice in the program with unit expressions or full commandline expression evaluation.

### Motivation
When I do engineering tasks, I often have to do calculations that involve SI units. In literature you often find parameters, constants and experimental values given in uncommon units with strange scales, or (especially in chemical engineering publications) compound expressions of many parameters, taken to seemingly arbitrary powers, with no simple way of figuring out what the resulting dimension is (other than doing the math by hand). When doing calculations, I also want to check unit consistency and the relative magnitude of the individual terms in an expression. This requires converting units back and forth and can be tedious. Searching wikipedia for arbitrary units and their expression in base SI units, or the exact SI units of physical constants, is not necessary, since this stuff doesn't change!

For all these reasons it is useful to have a simple tool that does the dimensional analysis for you. This task is intrinsically automatable and would benefit from the reduction of potential human error in dimension conversion. Most "dimension analysis" tools I found on Github are for machine learning (dimensionality reduction of data), C / C++ libraries for adding type-safe unit literals, or something else entirely.

I just want to be able to hotkey up a console and type in "J / N" to get "m". This just improves my engineering workflow. No unnecessary bells and whistles - plain and simple. That's what this repo is intended for.

### License
MIT License
