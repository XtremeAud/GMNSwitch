CC=g++
BIN=gmn_switch
FLAGS=-Wall -g -fpermissive -std=c++0x
RM=-rm -f
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)

#SRC LIB & INC
SRC_INC=-I/data/GMNSwitch/tags/tag_2015_4_4/inc
SRC_LIB=-L/data/GMNSwitch/tags/tag_2015_4_4/lib

#boost lib
BOOST_INC=-I/usr/local/include
BOOST_LIB=-L/usr/local/lib
BOOST_LINK=-lboost_system -lboost_filesystem

#thrift
THRIFT_LINK=-lthrift
THRIFT_INC=-I/usr/local/include/thrift
THRIFT_LIB=-L/usr/local/lib

#combine the inc & lib
INC=$(SRC_INC) $(BOOST_INC) $(THRIFT_INC)
LIB=$(SRC_LIB) $(BOOST_LIB) $(THRIFT_LIB) $(THRIFT_LINK)

all: $(BIN)

%.d: %.cpp
	$(CC) -MM $(FLAGS) $(INC) $< -o $@

%.o: %.cpp %.d
	$(CC) -c $(FLAGS) $(INC) $< -o $@

gmn_switch:main.o main.o GmnSwitch_constants.o GmnSwitch_types.o TGmnSwitchService.o GmnClient_constants.o GmnClient_types.o TGmnClientService.o
	$(CC) $(FLAGS) -o $@ main.o GmnSwitch_constants.o GmnSwitch_types.o TGmnSwitchService.o GmnClient_constants.o GmnClient_types.o TGmnClientService.o $(USER_LINK) $(OPENCV_LIB) $(BOOST_LINK) $(LIB)

clean:
	$(RM) *.o
	$(RM) *.d
	$(RM) $(BIN)

-include $(SRC:.cpp=.d)
