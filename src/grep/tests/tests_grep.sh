#!/bin/bash

F1="tests/test_1.txt"
F2="tests/test_2.txt"
F3="tests/test_3.txt"
PATTERNS="tests/patterns.reg"

i=0
suc=0
fail=0

echo "---------------------------------------------------"
echo "No-flag test"
i=$((i+1))
grep int "$F1" "$F2" "$F3" > 1 && ./s21_grep int "$F1" "$F2" "$F3" > 2 && if diff -q 1 2;
then echo "Test 1 SUCCESSFUL"; suc=$((suc+1));
else echo "Test 1 FAILED";  fail=$((fail+1)); fi

echo "---------------------------------------------------"

echo "Test flag -v"
i=$((i+1))
grep -v int "$F1" "$F2" "$F3" > 1 && ./s21_grep -v int "$F1" "$F2" "$F3" > 2 && if diff -q 1 2;
then echo "Test 2 SUCCESSFUL"; suc=$((suc+1));
else echo "Test 2 FAILED"; fail=$((fail+1)); fi

echo "---------------------------------------------------"

echo "Test flag -i"
i=$((i+1))
grep -i INT "$F1" "$F2" "$F3" > 1 && ./s21_grep -i INT "$F1" "$F2" "$F3" > 2 && if diff -q 1 2;
then echo "Test 3 SUCCESSFUL"; suc=$((suc+1));
else echo "Test 3 FAILED"; fail=$((fail+1)); fi

echo "---------------------------------------------------"

echo "Test flags -iv"
i=$((i+1))
grep -iv INT "$F1" "$F2" "$F3" > 1 && ./s21_grep -iv INT "$F1" "$F2" "$F3" > 2 && if diff -q 1 2;
then echo "Test 4 SUCCESSFUL"; suc=$((suc+1));
else echo "Test 4 FAILED"; fail=$((fail+1)); fi

echo "---------------------------------------------------"

echo "Test flag -n"
i=$((i+1))
grep -n return "$F1" "$F2" "$F3" > 1 && ./s21_grep -n return "$F1" "$F2" "$F3" > 2 && if diff -q 1 2;
then echo "Test 5 SUCCESSFUL"; suc=$((suc+1));
else echo "Test 5 FAILED"; fail=$((fail+1)); fi

echo "---------------------------------------------------"

echo "Test flags -in"
i=$((i+1))
grep -in return "$F1" "$F2" "$F3" > 1 && ./s21_grep -in return "$F1" "$F2" "$F3" > 2 && if diff -q 1 2;
then echo "Test 6 SUCCESSFUL"; suc=$((suc+1));
else echo "Test 6 FAILED"; fail=$((fail+1)); fi

echo "---------------------------------------------------"

echo "Test flags -ie 1 pattern"
i=$((i+1))
grep -ie ^int "$F1" "$F2" "$F3" > 1 && ./s21_grep -ie ^int "$F1" "$F2" "$F3" > 2 && if diff -q 1 2;
then echo "Test 7 SUCCESSFUL"; suc=$((suc+1));
else echo "Test 7 FAILED"; fail=$((fail+1)); fi

echo "---------------------------------------------------"

echo "Test flags -ince 1 pattern"
i=$((i+1))
grep -ince ^int "$F1" "$F2" "$F3" > 1 && ./s21_grep -ince ^int "$F1" "$F2" "$F3" > 2 && if diff -q 1 2;
then echo "Test 8 SUCCESSFUL"; suc=$((suc+1));
else echo "Test 8 FAILED"; fail=$((fail+1)); fi
echo "---------------------------------------------------"

echo "Test flags -lh"
i=$((i+1))
grep -lh 1 "$F1" "$F2" "$F3" > 1 && ./s21_grep -lh 1 "$F1" "$F2" "$F3" > 2 && if diff -q 1 2;
then echo "Test 9 SUCCESSFUL"; suc=$((suc+1));
else echo "Test 9 FAILED"; fail=$((fail+1)); fi

echo "---------------------------------------------------"

echo "Test flags -hc"
i=$((i+1))
grep -hc return "$F1" "$F2" "$F3" > 1 && ./s21_grep -hc return "$F1" "$F2" "$F3" > 2 && if diff -q 1 2;
then echo "Test 10 SUCCESSFUL"; suc=$((suc+1));
else echo "Test 10 FAILED"; fail=$((fail+1)); fi

echo "---------------------------------------------------"

echo "Test flag -e 2 patterns"
i=$((i+1))
grep -e while -e for "$F1" "$F2" "$F3" > 1 && ./s21_grep -e while -e for "$F1" "$F2" "$F3" > 2 && if diff -q 1 2;
then echo "Test 11 SUCCESSFUL"; suc=$((suc+1));
else echo "Test 11 FAILED"; fail=$((fail+1)); fi

echo "---------------------------------------------------"

echo "Test flag -s"
i=$((i+1))
if [[ $(grep for no_file) == $(./s21_grep for no_file) ]];
then echo "Test 12 SUCCESSFUL"; suc=$((suc+1));
else echo "Test 12 FAILED"; fail=$((fail+1)); fi

echo "---------------------------------------------------"

echo "Test flag -f"
i=$((i+1))
grep -f "$PATTERNS" "$F1" "$F2" "$F3" > 1 && ./s21_grep -f "$PATTERNS" "$F1" "$F2" "$F3" > 2 && if diff -q 1 2;
then echo "Test 13 SUCCESSFUL"; suc=$((suc+1));
else echo "Test 13 FAILED"; fail=$((fail+1)); fi

echo "---------------------------------------------------"

echo "Test flags -oi"
i=$((i+1))
grep -oi return "$F1" "$F2" "$F3" > 1 && ./s21_grep -oi return "$F1" "$F2" "$F3" > 2 && if diff -q 1 2;
then echo "Test 14 SUCCESSFUL"; suc=$((suc+1));
else echo "Test 14 FAILED"; fail=$((fail+1)); fi

echo "---------------------------------------------------"

echo "Test flags -ohf"
i=$((i+1))
grep -ohf "$PATTERNS" "$F1" "$F2" "$F3" > 1 && ./s21_grep -ohf "$PATTERNS" "$F1" "$F2" "$F3" > 2 && if diff -q 1 2;
then echo "Test 15 SUCCESSFUL"; suc=$((suc+1));
else echo "Test 15 FAILED"; fail=$((fail+1)); fi

echo "---------------------------------------------------"

echo "Test flags -oinc"
i=$((i+1))
grep -oinc return "$F1" "$F2" "$F3" > 1 && ./s21_grep -oinc return "$F1" "$F2" "$F3" > 2 && if diff -q 1 2;
then echo "Test 16 SUCCESSFUL"; suc=$((suc+1));
else echo "Test 16 FAILED"; fail=$((fail+1)); fi

echo "---------------------------------------------------"

echo "FAIL: $fail"
echo "SUCCESS: $suc"
echo "ALL TESTS: $i"

rm 1 2
