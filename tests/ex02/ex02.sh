#!/bin/bash
# test.sh - Test suite for PmergeMe (ex02)
# Usage: place this file in your ex02/ directory (next to the Makefile) and run:
#   chmod +x test.sh
#   ./test.sh

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

PASS=0
FAIL=0

pass() {
    echo -e "${GREEN}[PASS]${NC} $1"
    PASS=$((PASS+1))
}

fail() {
    echo -e "${RED}[FAIL]${NC} $1"
    FAIL=$((FAIL+1))
}

# Extracts the "After: ..." line's numbers and checks they are non-decreasing.
# Returns 0 (sorted) or 1 (not sorted). Also checks the count matches expected.
check_sorted() {
    local output="$1"
    local expected_count="$2"

    local after
    after=$(echo "$output" | grep "^After:" | sed 's/^After: //' | tr -s ' ' '\n' | grep -v '^$')

    local count
    count=$(echo "$after" | grep -c '.')

    if [ -z "$after" ] && [ "$expected_count" -gt 0 ]; then
        echo "no After: line found"
        return 1
    fi

    if [ "$expected_count" -gt 0 ] && [ "$count" -ne "$expected_count" ]; then
        echo "count mismatch: expected $expected_count, got $count"
        return 1
    fi

    local sort_check
    sort_check=$(echo "$after" | sort -n -c 2>&1)
    if [ -n "$sort_check" ]; then
        echo "not sorted: $sort_check"
        return 1
    fi

    return 0
}

echo "=========================================="
echo " PmergeMe test suite"
echo "=========================================="

# ---- 1. Build ----
echo ""
echo "--- Build ---"
make re > /tmp/pmergeme_build.log 2>&1
if [ $? -eq 0 ] && [ -f ./PmergeMe ]; then
    pass "compiles cleanly with -Wall -Wextra -Werror -std=c++98"
else
    fail "build failed, see /tmp/pmergeme_build.log"
    echo "Cannot continue without a successful build."
    exit 1
fi

# ---- 2. Rebuild-idempotency (Makefile must not relink) ----
make > /tmp/pmergeme_relink.log 2>&1
if grep -q "Nothing to be done" /tmp/pmergeme_relink.log; then
    pass "make does not relink when nothing changed"
else
    fail "make relinked / recompiled with no source changes"
fi

# ---- 3. Subject's own example: 3 5 9 7 4 -> 3 4 5 7 9 ----
out=$(./PmergeMe 3 5 9 7 4 2>&1)
after=$(echo "$out" | grep "^After:" | sed 's/^After: //' | tr -s ' ')
if [ "$after" = "3 4 5 7 9 " ] || [ "$after" = "3 4 5 7 9" ]; then
    pass "subject example '3 5 9 7 4' sorts to '3 4 5 7 9'"
else
    fail "subject example '3 5 9 7 4' gave: '$after'"
fi

# ---- 4. Error case: negative number ----
out=$(./PmergeMe "-1" "2" 2>/tmp/pmergeme_err.log)
code=$?
if [ $code -ne 0 ] && grep -qi "error" /tmp/pmergeme_err.log; then
    pass "'-1 2' correctly errors (exit=$code) with message on stderr"
else
    fail "'-1 2' did not error as expected (exit=$code)"
fi

# ---- 5. Error case: no arguments ----
out=$(./PmergeMe 2>/tmp/pmergeme_err2.log)
code=$?
if [ $code -ne 0 ]; then
    pass "no arguments correctly errors (exit=$code)"
else
    fail "no arguments should error but exited 0"
fi

# ---- 6. Correctness across many sizes ----
echo ""
echo "--- Correctness across sizes ---"
SIZES="1 2 3 4 5 6 7 8 9 10 11 12 13 20 33 65 100 129 257 500 1000 2999 3000"
all_ok=1
for n in $SIZES; do
    args=$(shuf -i 1-1000000 -n "$n" | tr "\n" " ")
    out=$(./PmergeMe $args 2>&1)
    err=$(check_sorted "$out" "$n")
    if [ -n "$err" ]; then
        fail "n=$n : $err"
        all_ok=0
    fi
done
if [ "$all_ok" -eq 1 ]; then
    pass "all sizes in {$SIZES} sort correctly"
fi

# ---- 7. Duplicates ----
echo ""
echo "--- Duplicate handling ---"
out=$(./PmergeMe 5 5 5 3 3 8 1 1 2>&1)
err=$(check_sorted "$out" 8)
if [ -z "$err" ]; then
    pass "duplicate values (5 5 5 3 3 8 1 1) sort correctly"
else
    fail "duplicate values : $err"
fi

out=$(./PmergeMe $(shuf -i 1-5 -n 3000 -r | tr "\n" " ") 2>&1)
err=$(check_sorted "$out" 3000)
if [ -z "$err" ]; then
    pass "3000 values from a tiny range (heavy duplicates) sort correctly"
else
    fail "heavy duplicates : $err"
fi

# ---- 8. 3000-element requirement from the subject ----
echo ""
echo "--- Large input requirement (>= 3000 integers) ---"
out=$(./PmergeMe $(shuf -i 1-100000 -n 3000 | tr "\n" " ") 2>&1)
err=$(check_sorted "$out" 3000)
if [ -z "$err" ]; then
    pass "3000 random integers (1-100000) sort correctly"
else
    fail "3000 random integers : $err"
fi

# ---- 9. Timing output format ----
echo ""
echo "--- Timing output ---"
out=$(./PmergeMe 3 5 9 7 4 2>&1)
line_count=$(echo "$out" | wc -l)
if [ "$line_count" -eq 4 ]; then
    pass "output has exactly 4 lines (Before/After/time/time)"
else
    fail "expected 4 output lines, got $line_count"
fi

t1=$(echo "$out" | sed -n '3p' | grep -oE '[0-9]+(\.[0-9]+)?' | tail -1)
t2=$(echo "$out" | sed -n '4p' | grep -oE '[0-9]+(\.[0-9]+)?' | tail -1)
if [ -n "$t1" ] && [ -n "$t2" ] && [ "$t1" != "0" ] && [ "$t2" != "0" ]; then
    pass "timing values are non-zero and readable (vector=$t1 us, deque=$t2 us)"
else
    fail "timing values look suspicious (vector=$t1 us, deque=$t2 us) - check clock precision"
fi

# ---- 10. Boundary values ----
echo ""
echo "--- Boundary values ---"
./PmergeMe 2147483647 1 > /tmp/pmergeme_intmax.log 2>&1
if [ $? -eq 0 ]; then
    pass "INT_MAX (2147483647) accepted"
else
    fail "INT_MAX (2147483647) was rejected"
fi

./PmergeMe 2147483648 1 > /tmp/pmergeme_overflow.log 2>&1
if [ $? -ne 0 ]; then
    pass "INT_MAX+1 (2147483648) correctly rejected"
else
    fail "INT_MAX+1 (2147483648) was NOT rejected"
fi

# ---- Summary ----
echo ""
echo "=========================================="
echo -e " Results: ${GREEN}$PASS passed${NC}, ${RED}$FAIL failed${NC}"
echo "=========================================="

if [ "$FAIL" -ne 0 ]; then
    exit 1
fi
exit 0
