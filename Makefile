main.exe:main.o mdsp.o
	g++ $^ -o $@
	
main.o:main.cpp
	g++ -c $< 
	
mdsp.o:mdsp.c
	gcc -c $<


.PHONY:clean
clean:
	del *.exe && del *.o