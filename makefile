BUILD_PTH := ./build/
HEAD_PTH := ./include/
SRC_PTH := ./src/
BIN := ./bin/
GPP := g++ -g -std=c++11 -I./include
MKDIR := @mkdir -p


build : main.o airport.o plane.o runway.o
	$(MKDIR) $(BIN)
	$(GPP) -o $(BIN)airport $(BUILD_PTH)main.o $(BUILD_PTH)airport.o $(BUILD_PTH)runway.o $(BUILD_PTH)plane.o

main.o : $(SRC_PTH)main.cpp airport.o
	$(MKDIR) $(BUILD_PTH)
	$(GPP) -c -o $(BUILD_PTH)$@ $<

airport.o : $(SRC_PTH)airport.cpp $(HEAD_PTH)airport.hpp runway.o plane.o $(HEAD_PTH)delegate.hpp
	$(MKDIR) $(BUILD_PTH)
	$(GPP) -c -o $(BUILD_PTH)$@ $<

runway.o : $(SRC_PTH)runway.cpp $(HEAD_PTH)runway.hpp plane.o
	$(MKDIR) $(BUILD_PTH)
	$(GPP) -c -o $(BUILD_PTH)$@ $<

plane.o : $(SRC_PTH)plane.cpp $(HEAD_PTH)plane.hpp $(HEAD_PTH)delegate.hpp
	$(MKDIR) $(BUILD_PTH)
	$(GPP) -c -o $(BUILD_PTH)$@ $<

flush :
	@rm -f -v $(BUILD_PTH)main.o $(BUILD_PTH)airport.o $(BUILD_PTH)plane.o $(BUILD_PTH)runway.o

clean :
	@rm -f -v $(BUILD_PTH)main.o $(BUILD_PTH)airport.o $(BUILD_PTH)plane.o $(BUILD_PTH)runway.o $(BIN)airport

cleanbuild : | clean build flush
