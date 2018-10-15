BUILD_PTH := ./build/
HEAD_PTH := ./include/
SRC_PTH := ./src/
BIN := ./bin/
OUTPUT_NM := airport
GPP := g++ -g -std=c++11 -I./include
MKDIR := @mkdir -p


build : main.o airport.o runway.o plane.o exqueue.o
	$(MKDIR) $(BIN)
	$(GPP) -o $(BIN)$(OUTPUT_NM) $(BUILD_PTH)main.o $(BUILD_PTH)airport.o $(BUILD_PTH)runway.o $(BUILD_PTH)plane.o $(BUILD_PTH)exqueue.o

main.o : $(SRC_PTH)main.cpp airport.o
	$(MKDIR) $(BUILD_PTH)
	$(GPP) -c -o $(BUILD_PTH)$@ $<

airport.o : $(SRC_PTH)airport.cpp $(HEAD_PTH)airport.hpp runway.o plane.o $(HEAD_PTH)delegate.hpp
	$(MKDIR) $(BUILD_PTH)
	$(GPP) -c -o $(BUILD_PTH)$@ $<

runway.o : $(SRC_PTH)runway.cpp $(HEAD_PTH)runway.hpp exqueue.o plane.o
	$(MKDIR) $(BUILD_PTH)
	$(GPP) -c -o $(BUILD_PTH)$@ $<

plane.o : $(SRC_PTH)plane.cpp $(HEAD_PTH)plane.hpp $(HEAD_PTH)delegate.hpp
	$(MKDIR) $(BUILD_PTH)
	$(GPP) -c -o $(BUILD_PTH)$@ $<

exqueue.o : $(HEAD_PTH)exqueue.cpp
	$(MKDIR) $(BUILD_PTH)
	$(GPP) -c -o $(BUILD_PTH)$@ $<

flush :
	@rm -f -v $(BUILD_PTH)main.o $(BUILD_PTH)airport.o $(BUILD_PTH)plane.o $(BUILD_PTH)runway.o

clean :
	@rm -f -v $(BUILD_PTH)main.o $(BUILD_PTH)airport.o $(BUILD_PTH)plane.o $(BUILD_PTH)runway.o $(BIN)airport

cleanbuild : | clean build flush

run : 
	$(BIN)$(OUTPUT_NM)

buildrun : | build run
