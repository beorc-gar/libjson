test:
	gcc test.c -Wall -pedantic  -std=c11 -g -o libjsontest

clean:
	rm -rf libjsontest libjsontest.dSYM testout/got/tests/*