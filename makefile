testlist: testlist.c GList.c
	gcc -o $@ $^

testdebugger: testlist.c GList.c
	gcc -g $^ -o $@
