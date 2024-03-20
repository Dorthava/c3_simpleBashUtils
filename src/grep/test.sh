#!/bin/bash

echo Test 1-------------------------------------------------
./s21_grep -e utility test/test1.txt > s21_grep_test
grep -e utility test/test1.txt > grep
diff -s s21_grep_test grep
echo Test 2-------------------------------------------------
./s21_grep -i utility test/test1.txt > s21_grep_test
grep -i utility test/test1.txt > grep
diff -s s21_grep_test grep
echo Test 3-------------------------------------------------
./s21_grep -v utility test/test1.txt > s21_grep_test
grep -v utility test/test1.txt > grep
diff -s s21_grep_test grep
echo Test 4-------------------------------------------------
./s21_grep -c utility test/test1.txt > s21_grep_test
grep -c utility test/test1.txt > grep
diff -s s21_grep_test grep
echo Test 5-------------------------------------------------
./s21_grep -l utility test/test1.txt > s21_grep_test
grep -l utility test/test1.txt > grep
diff -s s21_grep_test grep
echo Test 6-------------------------------------------------
./s21_grep -n utility test/test1.txt > s21_grep_test
grep -n utility test/test1.txt > grep
diff -s s21_grep_test grep
echo Test 7-------------------------------------------------
./s21_grep -h utility test/test1.txt > s21_grep_test
grep -h utility test/test1.txt > grep
diff -s s21_grep_test grep
echo Test 8-------------------------------------------------
./s21_grep -s utility test/test1.txt test/test.txt > s21_grep_test
grep -s utility test/test1.txt test/test.txt > grep
diff -s s21_grep_test grep
echo Test 9-------------------------------------------------
./s21_grep -in utility test/test1.txt test/test2.txt > s21_grep_test
grep -in utility test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 10-------------------------------------------------
./s21_grep -cv utility test/test1.txt test/test2.txt > s21_grep_test
grep -cv utility test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 11-------------------------------------------------
./s21_grep -iv utility test/test1.txt test/test2.txt > s21_grep_test
grep -iv utility test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 12-------------------------------------------------
./s21_grep -lv utility test/test1.txt test/test2.txt > s21_grep_test
grep -lv utility test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 13-------------------------------------------------
./s21_grep -o utility test/test1.txt test/test2.txt > s21_grep_test
grep -o utility test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 14-------------------------------------------------
./s21_grep -o utility test/test2.txt > s21_grep_test
grep -o utility test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 15-------------------------------------------------
./s21_grep -ho utility test/test2.txt > s21_grep_test
grep -ho utility test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 16-------------------------------------------------
./s21_grep -nf test/test1.txt test/test2.txt > s21_grep_test
grep -nf test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 17-------------------------------------------------
./s21_grep -f test/test1.txt test/test2.txt > s21_grep_test
grep -f test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep