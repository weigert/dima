#!/usr/bin/env sh
CASES=()


# Escaping operators in expressions
CASES+=('./dima "5\2+10"' '12')
CASES+=('./dima 5\\2+10' '12')

CASES+=('./dima 20*[1000m^2]' '2e+07 m^2')

# The utility does not support the sqrt function, users can use the `^`operator instead
CASES+=('./dima 2^[0-2]' '0.25')
CASES+=('./dima 2^~2' '0.25')
CASES+=('./dima 2^-2' 'Operator Count Mismatch')

# This test highlights an internal issue: ['Unrecognized character "_" at position 45' vs 'expected 'Unrecognized character "_" at position 21']:
CASES+=('./dima 12+[ 3 * 3]' 'Unrecognized character "_" at position 21')

CASES+=('./dima 12+[2^[- 4]]' 'Invalid expression at position 15')

CASES+=('./dima sin[pi]' 'Could not identify unit "sin"')
CASES+=('./dima "sin*[12]"' 'Could not identify unit "sin"')

# example of working with environment variables:
CASES+=('VAR=3;./dima "$VAR+2"' '5')
# example of working with dates:
CASES+=('DATE1=$(date --date="04/02/2020 07:21:22" +"%s");DATE2=$(date --date="01/02/2020 07:21:22" +"%s");./dima "[${DATE1}s-${DATE2}s]\24hour"' '90')
# CASES+=( )



len=${#CASES[@]}
cols=2
rows=$((len / cols))


for ((i = 0; i < len; i += 2)); do
    expression=${CASES[$i]}
    expectedValue=${CASES[$i + 1]}
    res=$(sh -c "$expression")
    # Bug: Results end with a space
    res=$(echo $res | sed -e 's/^[[:space:]]*//')
    # echo "[$expression/$expectedValue/$res]"
    if [ "$res" != "$expectedValue" ]; then
        echo "[Test failed] the expression '$expression' returns '$res', expected '$expectedValue'"
    fi
done
