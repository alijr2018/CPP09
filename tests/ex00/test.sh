#!/bin/bash

# **************************************************************************** #
#                               BitcoinExchange Tester                         #
# **************************************************************************** #

EXEC="./btc"
DATA="data.csv"

GREEN="\033[0;32m"
RED="\033[0;31m"
YELLOW="\033[1;33m"
NC="\033[0m"

if [ ! -f "$EXEC" ]; then
    echo -e "${RED}Error:${NC} $EXEC not found."
    exit 1
fi

if [ ! -f "$DATA" ]; then
    echo -e "${RED}Error:${NC} data.csv not found."
    exit 1
fi

TMP_DIR=$(mktemp -d)

cleanup() {
    rm -rf "$TMP_DIR"
}

trap cleanup EXIT

run_test() {
    local name="$1"
    local content="$2"

    local file="$TMP_DIR/test.txt"

    echo -e "$content" > "$file"

    echo -e "${YELLOW}========== $name ==========${NC}"
    echo "Input:"
    cat "$file"
    echo
    echo "Output:"
    "$EXEC" "$file"
    echo
}

echo -e "${GREEN}Running BitcoinExchange tests...${NC}"
echo

# --------------------------------------------------------------------------
# Valid inputs
# --------------------------------------------------------------------------

run_test "Valid Input" \
"date | value
2011-01-03 | 3
2012-06-15 | 12.5
2021-10-12 | 42"

run_test "Boundary Value 0" \
"date | value
2012-01-01 | 0"

run_test "Boundary Value 1000" \
"date | value
2012-01-01 | 1000"

# --------------------------------------------------------------------------
# Invalid values
# --------------------------------------------------------------------------

run_test "Negative Number" \
"date | value
2012-01-01 | -5"

run_test "Too Large" \
"date | value
2012-01-01 | 1001"

run_test "Not a Number" \
"date | value
2012-01-01 | hello"

run_test "Empty Value" \
"date | value
2012-01-01 |"

# --------------------------------------------------------------------------
# Invalid dates
# --------------------------------------------------------------------------

run_test "Invalid Month" \
"date | value
2012-13-01 | 5"

run_test "Invalid Day" \
"date | value
2012-02-30 | 5"

run_test "Bad Format" \
"date | value
12-10-2012 | 5"

run_test "Missing Date" \
"date | value
| 5"

# --------------------------------------------------------------------------
# Earliest date
# --------------------------------------------------------------------------

run_test "Before Database" \
"date | value
1900-01-01 | 5"

# --------------------------------------------------------------------------
# Missing header
# --------------------------------------------------------------------------

run_test "No Header" \
"2012-01-01 | 5"

# --------------------------------------------------------------------------
# Bad separator
# --------------------------------------------------------------------------

run_test "Wrong Separator" \
"date | value
2012-01-01 : 5"

# --------------------------------------------------------------------------
# Multiple lines
# --------------------------------------------------------------------------

run_test "Mixed File" \
"date | value
2011-01-03 | 3
2012-15-01 | 4
2013-01-01 | -2
2014-01-01 | 999
2014-01-01 | 1001
hello
2015-06-30 | 10"

# --------------------------------------------------------------------------
# Empty file
# --------------------------------------------------------------------------

touch "$TMP_DIR/empty.txt"

echo -e "${YELLOW}========== Empty File ==========${NC}"
"$EXEC" "$TMP_DIR/empty.txt"

echo
echo -e "${GREEN}All tests completed.${NC}"