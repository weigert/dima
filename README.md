# dima
commandline dimensional analysis tool for unit conversion and consistency validation

## Motivation
When I do engineering tasks, I often have to do calculations that involve SI units. In literature you often find parameters, constants and experimental values given in uncommon units with strange scales, or (especially in chemical engineering publications) compound expressions of many parameters, taken to seemingly arbitrary powers, with no simple way of figuring out what the resulting dimension is (other than doing the math by hand). When doing calculations, I also want to check unit consistency and the relative magnitude of the individual terms in an expression. This requires converting units back and forth and can be tedious. Searching wikipedia for arbitrary units and their expression in base SI units, or the exact SI units of physical constants, is not necessary, since this stuff doesn't change!

For all these reasons it is useful to have a simple tool that does the dimensional analysis for you. This task is intrinsically automatable and would benefit from the reduction of potential human error in dimension conversion. Most "dimension analysis" tools I found on Github are for machine learning (dimensionality reduction of data), C / C++ libraries for adding type-safe unit literals, or something else entirely.

I just want to be able to hotkey up a console and type in "J / N" to get "m". This just improves my engineering workflow. No unnecessary bells and whistles - plain and simple. That's what this repo is intended for.

## Features 
Coming soon.
