CPPFLAGS=-O2 -std=c++0x $(shell pkg-config --cflags pninx)
LDFLAGS=$(shell pkg-config --libs pninx)

all: nxfile_ex1 nxgroup_ex1 nxgroup_ex2 nxnumfield_ex1 nxnumfield_ex2 nxstrfield_ex1 nxstrfield_ex2 nxbinfield_ex1 d4 simple_io

nxfile_ex1: nxfile_ex1.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)

nxgroup_ex1: nxgroup_ex1.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)

nxgroup_ex2: nxgroup_ex2.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)

nxnumfield_ex1: nxnumfield_ex1.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)

nxnumfield_ex2: nxnumfield_ex2.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)

nxstrfield_ex1: nxstrfield_ex1.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)

nxstrfield_ex2: nxstrfield_ex2.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)

nxbinfield_ex1: nxbinfield_ex1.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)

simple_ex1: simple_ex1.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)

simple_io: simple_io.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)

d4: d4.cpp NXHelper.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)

.PHONY: clean run

clean:
	rm -f nxfile_ex1
	rm -f nxgroup_ex1
	rm -f nxgroup_ex2
	rm -f nxnumfield_ex1
	rm -f nxnumfield_ex2
	rm -f nxstrfield_ex1
	rm -f nxstrfield_ex2
	rm -f nxbinfield_ex1
	rm -f simple_io

run:
	./nxfile_ex1
	./nxgroup_ex1
	./nxgroup_ex2
	./nxnumfield_ex1
	./nxnumfield_ex2
	./nxstrfield_ex1
	./nxstrfield_ex2
	./nxbinfield_ex1
	./d4
