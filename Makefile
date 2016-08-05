comp=g++ -std=c++11
dir=bin
obj=	$(dir)/main.o \
		$(dir)/TestMaker.o

default : checkBin $(dir)/TestMaker

checkBin :
	@ if [ ! -d $(dir) ]; then mkdir $(dir); fi

$(dir)/TestMaker : $(obj)
	$(comp) $(obj) -o $(dir)/TestMaker

$(dir)/%.o : %.cpp
	$(comp) -c $< -o $@

clean :
	rm -rf $(dir)
