proj2.x: test_list.o
        g++ -o proj2.x test_list.o

test_list.o: test_list.cpp
        g++ -c -std=c++11 test_list.cpp

clean:
        rm *.o proj2.x
