comp=g++ -std=c++11
dir=bin
obj=	$(dir)/Main.o \
		$(dir)/TestMaker.o	\
		$(dir)/TestFunctions.o \
		$(dir)/TestCharTranslate.o \
		$(dir)/Global.o

default : checkBin $(dir)/TestMaker

checkBin :
	@ if [ ! -d $(dir) ]; then mkdir $(dir); fi

$(dir)/TestMaker : $(obj)
	$(comp) $(obj) -o $(dir)/TestMaker

$(dir)/%.o : %.cpp
	$(comp) -c $< -o $@

clean :
	rm -rf $(dir)
