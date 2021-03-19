exp5 : DiskOperate.o FileOperate.o main.o
	g++ -o exp5 DiskOperate.o FileOperate.o main.o
DiskOperate.o : DiskOperate.cpp DiskOperate.h
	g++ -g -c DiskOperate.cpp
FileOperate.o : FileOperate.cpp FileOperate.h
	g++ -g -c FileOperate.cpp
main.o : main.cpp DiskOperate.h FileOperate.h
	g++ -g -c main.cpp
clean :
	rm exp5 DiskOperate.o FileOperate.o
