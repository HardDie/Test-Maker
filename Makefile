comp=g++ -std=c++11
dir=bin
obj=	$(dir)/main.o \
		$(dir)/TestMaker.o

default : $(dir)/TestMaker

$(dir)/TestMaker : $(obj)
	$(comp) $(obj) -o $(dir)/TestMaker

$(dir)/%.o : %.cpp
	$(comp) -c $< -o $@

clean :
	rm -rf $(dir)/*.o $(dir)/TestMaker
