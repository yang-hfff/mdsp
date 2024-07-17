all:test.exe main.exe win_test.exe osc_test.exe correct_test.exe

correct_test.exe:correct_test.o mdsp.o
	g++ $^ -o $@

osc_test.exe:osc_test.o mdsp.o
	g++ $^ -o $@

win_test.exe:win_test.o mdsp.o
	g++ $^ -o $@

test.exe:test.o mdsp.o
	g++ $^ -o $@

main.exe:main.o mdsp.o
	g++ $^ -o $@
	
mdsp.o:mdsp.c
	gcc -c $<
	
main.o:main.cpp
	g++ -c $< 
	
test.o:test.cpp
	g++ -c $<
	
win_test.o:win_test.cpp
	g++ -c $<

osc_test.o:osc_test.cpp
	g++ -c $<
	
correct_test.o:correct_test.cpp
	g++ -c $<

.PHONY:clean
clean:
	del *.exe && del *.o