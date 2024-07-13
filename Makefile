all:test.exe main.exe

test.exe:test.o mdsp.o
	g++ $^ -o $@

main.exe:main.o mdsp.o
	g++ $^ -o $@
	
main.o:main.cpp
	g++ -c $< 
	
mdsp.o:mdsp.c
	gcc -c $<
	
test.o:test.cpp
	g++ -c $<


.PHONY:clean
clean:
	del *.exe && del *.o