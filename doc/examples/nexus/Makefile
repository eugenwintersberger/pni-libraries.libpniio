CPPFLAGS=-O0 -g -std=c++0x $(shell pkg-config --cflags pniio)
LDFLAGS=$(shell pkg-config --libs pniio)

all: nxfile_ex1 nxgroup_ex1 nxgroup_ex2 nxnumfield_ex1 nxnumfield_ex2 \
	nxstrfield_ex1 nxstrfield_ex2 nxbinfield_ex1 simple_io thread_ex1 \
	nxnumfield_ex4 nxpath_match count_entries count_detectors

nxfile_ex1: nxfile_ex1.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)

count_entries: count_entries.cpp
	$(CXX) $(CPPFLAGS) -o $@ $< $(LDFLAGS)

count_detectors: count_detectors.cpp
	$(CXX) $(CPPFLAGS) -o $@ $< $(LDFLAGS)

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

thread_ex1: thread_ex1.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS) -lpthread

nxnumfield_ex4: nxnumfield_ex4.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)
	
nxpath_match: nxpath_match.cpp
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
	rm -r thread_ex1
	rm -rf nxnumfield_ex4
	rm -rf nxpath_match
	rm -rf count_entries
	rm -rf count_detectors

run:
	./nxfile_ex1
	./nxgroup_ex1
	./nxgroup_ex2
	./nxnumfield_ex1
	./nxnumfield_ex2
	./nxnumfield_ex4
	./nxstrfield_ex1
	./nxstrfield_ex2
	./nxbinfield_ex1
	./simple_io
	./nxpath_match
