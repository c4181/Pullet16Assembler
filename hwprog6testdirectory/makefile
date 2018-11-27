GPP = g++ -O3 -Wall -std=c++11

UTILS = ../../Utilities

A = main.o
D = dabnamespace.o
E = pullet16assembler.o
C = codeline.o
H = hex.o
M = onememoryword.o
Y = symbol.o
S = scanner.o
SL = scanline.o
U = utils.o

Aprog: $A $D $E $C $H $M $Y $S $(SL) $U
	$(GPP) -o Aprog $A $D $E $C $H $M $Y $S $(SL) $U

main.o: main.h main.cc
#	$(GPP) -DBINARY -c main.cc
	$(GPP) -c main.cc

dabnamespace.o: dabnamespace.h dabnamespace.cc
	$(GPP) -c dabnamespace.cc

pullet16assembler.o: pullet16assembler.h pullet16assembler.cc
#	$(GPP) -c -DEBUG pullet16assembler.cc
	$(GPP) -c pullet16assembler.cc

codeline.o: codeline.h codeline.cc
	$(GPP) -c codeline.cc

hex.o: hex.h hex.cc
	$(GPP) -c hex.cc

onememoryword.o: onememoryword.h onememoryword.cc
	$(GPP) -c onememoryword.cc

symbol.o: symbol.h symbol.cc
	$(GPP) -c symbol.cc

scanner.o: $(UTILS)/scanner.h $(UTILS)/scanner.cc
	$(GPP) -c $(UTILS)/scanner.cc

scanline.o: $(UTILS)/scanline.h $(UTILS)/scanline.cc
	$(GPP) -c $(UTILS)/scanline.cc

utils.o: $(UTILS)/utils.h $(UTILS)/utils.cc
	$(GPP) -c $(UTILS)/utils.cc
