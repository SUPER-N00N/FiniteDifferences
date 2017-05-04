CPP     	= 	clang -g  -std=c++14 -fexceptions -fpermissive
STRIPPER 	= 	./removecomments.pl
EMCC    	=       ~/Extern/emscripten3/emscripten/emcc -Wc++11-extensions -std=c++11
OPT             = 	 -s PRECISE_I64_MATH=1
SET     	= 	-O2 -s ALLOW_MEMORY_GROWTH=1 -s ASM_JS=0
LIBPATH 	= 
SYSLIBS 	= 	-lstdc++ -lboost_regex -lboost_thread -lboost_system -lboost_date_time -lrt  -lpthread -lm
PRGS		=	findiffd


all: le_build tree_test #findiffd

tree_test: le_build/tree_test.o
	$(CPP) -fexceptions -D_BOOL  $^ -I$(INCPATH) -L$(LIBPATH) $(SYSLIBS) -o $@
le_build/tree_test.o: tree_test.cpp spaces.h algebra.h math_helpers.h simplicial_complex.h cubical_complex.h cw_complex.h
	$(CPP) -fexceptions -D_BOOL -c $< -I$(INCPATH) -L$(LIBPATH)  -DHAVE_IOMANIP -DHAVE_IOSTREAM -DHAVE_LIMITS_H -o $@

findiffd: le_build/findiffd.o
	$(CPP) -fexceptions -D_BOOL  $^ -I$(INCPATH) -L$(LIBPATH) $(SYSLIBS) -o $@

clean:
	rm -rf le_build findiffd;\

le_build/websdrd.o: findiffd.cpp findiffd.h blargh.h spaces.h algebra.h math_helpers.h cubical_complex.h simplicial_complex.h
	$(CPP) -fexceptions -D_BOOL -c $< -I$(INCPATH) -L$(LIBPATH)  -DHAVE_IOMANIP -DHAVE_IOSTREAM -DHAVE_LIMITS_H -o $@

le_build:
	mkdir ./le_build

findiffclient-opt.js: findiffclient.js
	closure-compiler --language_in=ECMASCRIPT5  --compilation_level ADVANCED_OPTIMIZATIONS --js $< --warning_level QUIET > $@ && cp ./$@ ./data/
findiffclient.js: main.js webglfoo.js tree-stripped.js
	cat LAfoo2.js PerfCount.js tree-stripped.js main.js > $@ && cp ./$@ ./data/

tree.js: tree.cpp tree.sym tree.h
	$(EMCC) $(OPT) $<  -o $@ -s EXPORTED_FUNCTIONS=$(shell cat tree.sym) $(SET)
tree-stripped.js: tree.js
	$(STRIPPER) tree.js > $@
tree.sym: tree.cpp
symbols=\"[`awk '$$1 ~/EMCEXPORT/{sub(/\(.*/,"");printf "\x27_"$$3"\x27,"}' $<`]\";echo $$symbols > tree.sym; echo "Functions to export: " $$symbols;


