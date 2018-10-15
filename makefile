BUILD_PTH_UNIX := ./build/unix/
BUILD_PTH_WIN := ./build/win/
HEAD_PTH := ./include/
SRC_PTH := ./src/
BIN := ./bin/
OUTPUT_NM_UNIX := airport
OUTPUT_NM_WIN := airport.exe
GPP := g++ -g -std=c++11 -I./include
MINGW_GPP := i686-w64-mingw32-g++ -g -std=c++11 -I./include -static -fexec-charset=GBK
MKDIR := @mkdir -p


build : main.o airport.o runway.o plane.o exqueue.o
	$(MKDIR) $(BIN)
	$(GPP) -o $(BIN)$(OUTPUT_NM_UNIX) $(BUILD_PTH_UNIX)main.o $(BUILD_PTH_UNIX)airport.o $(BUILD_PTH_UNIX)runway.o $(BUILD_PTH_UNIX)plane.o $(BUILD_PTH_UNIX)exqueue.o
	$(MINGW_GPP) -o $(BIN)$(OUTPUT_NM_WIN) $(BUILD_PTH_WIN)main.o $(BUILD_PTH_WIN)airport.o $(BUILD_PTH_WIN)runway.o $(BUILD_PTH_WIN)plane.o $(BUILD_PTH_WIN)exqueue.o

main.o : $(SRC_PTH)main.cpp airport.o
	$(MKDIR) $(BUILD_PTH_UNIX)
	$(MKDIR) $(BUILD_PTH_WIN)
	$(GPP) -c -o $(BUILD_PTH_UNIX)$@ $<
	$(MINGW_GPP) -c -o $(BUILD_PTH_WIN)$@ $<

airport.o : $(SRC_PTH)airport.cpp $(HEAD_PTH)airport.hpp runway.o plane.o $(HEAD_PTH)delegate.hpp
	$(MKDIR) $(BUILD_PTH_UNIX)
	$(MKDIR) $(BUILD_PTH_WIN)
	$(GPP) -c -o $(BUILD_PTH_UNIX)$@ $<
	$(MINGW_GPP) -c -o $(BUILD_PTH_WIN)$@ $<

runway.o : $(SRC_PTH)runway.cpp $(HEAD_PTH)runway.hpp exqueue.o plane.o
	$(MKDIR) $(BUILD_PTH_UNIX)
	$(MKDIR) $(BUILD_PTH_WIN)
	$(GPP) -c -o $(BUILD_PTH_UNIX)$@ $<
	$(MINGW_GPP) -c -o $(BUILD_PTH_WIN)$@ $<

plane.o : $(SRC_PTH)plane.cpp $(HEAD_PTH)plane.hpp $(HEAD_PTH)delegate.hpp
	$(MKDIR) $(BUILD_PTH_UNIX)
	$(MKDIR) $(BUILD_PTH_WIN)
	$(GPP) -c -o $(BUILD_PTH_UNIX)$@ $<
	$(MINGW_GPP) -c -o $(BUILD_PTH_WIN)$@ $<

exqueue.o : $(HEAD_PTH)exqueue.cpp
	$(MKDIR) $(BUILD_PTH_UNIX)
	$(MKDIR) $(BUILD_PTH_WIN)
	$(GPP) -c -o $(BUILD_PTH_UNIX)$@ $<
	$(MINGW_GPP) -c -o $(BUILD_PTH_WIN)$@ $<

flush :
	@rm -f -v $(BUILD_PTH_UNIX)main.o $(BUILD_PTH_UNIX)airport.o $(BUILD_PTH_UNIX)plane.o $(BUILD_PTH_UNIX)runway.o
	@rm -f -v $(BUILD_PTH_WIN)main.o $(BUILD_PTH_WIN)airport.o $(BUILD_PTH_WIN)plane.o $(BUILD_PTH_WIN)runway.o

clean :
	@rm -f -v $(BUILD_PTH_UNIX)main.o $(BUILD_PTH_UNIX)airport.o $(BUILD_PTH_UNIX)plane.o $(BUILD_PTH_UNIX)runway.o $(BIN)airport
	@rm -f -v $(BUILD_PTH_WIN)main.o $(BUILD_PTH_WIN)airport.o $(BUILD_PTH_WIN)plane.o $(BUILD_PTH_WIN)runway.o $(BIN)airport.exe

cleanbuild : | clean build flush

run : 
	$(BIN)$(OUTPUT_NM)

buildrun : | build run
