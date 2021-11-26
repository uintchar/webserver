src = $(wildcard ./src/*.cpp)
obj = $(patsubst %.cpp, %.o, $(src))
target = webserver.out
cc = g++

$(target) : $(obj)
	$(cc) $(obj) -o $(target) -lrt -pthread

%.o : %.cpp
	$(cc) -c $< -o $@

.PHONY : clean
clean :
	rm $(obj)