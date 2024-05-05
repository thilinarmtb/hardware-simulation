.PHONY: all cpp verilog clean format

CXX = g++
CXXFLAGS = -Wall -Wpedantic -std=c++14
VC ?= verilator
VFLAGS ?= -Wall
INCFLAGS ?= -I/opt/homebrew/Cellar/verilator/5.024/share/verilator/include
LDFLAGS ?=
MODULE ?= bitselect

ROOT_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
UNAME_S := $(shell uname -s)
OBJ_DIR := $(ROOT_DIR)/obj_dir

INCFLAGS += -I$(OBJ_DIR)
LDFLAGS += -Wl,-rpath,$(OBJ_DIR) -L$(OBJ_DIR) -lV$(MODULE) -L$(OBJ_DIR) -lverilated
ifeq ($(UNAME_S), Darwin)
  LDFLAGS += -undefined dynamic_lookup
endif

all: cpp

cpp: verilog
	$(CXX) $(INCFLAGS) $(CXXFLAGS) $(MODULE).cpp -o $(MODULE) $(LDFLAGS)

verilog:
	$(VC) $(VFLAGS) -cc $(MODULE).v
	make -C $(OBJ_DIR) -f V$(MODULE).mk

clean:
	@rm -rf $(ROOT_DIR)/obj_dir $(MODULE) || true

format:
	clang-format -i *.[ch]pp
