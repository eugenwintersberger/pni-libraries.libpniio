CPPFLAGS=-g -O0 -std=c++11 -fno-deduce-init-list -Wall -Wextra -pedantic \
		 $(shell pkg-config --cflags pninexus) 
LDFLAGS=$(shell pkg-config --libs pninexus)

PRGS=array_arithmetic1 array_arithmetic2 array_arithmetic3 array_create \
	 array_inquery array_linear_access array_multiindex array_stl \
	 array_view_container array_view copy_file example_array2 example_array3 \
	 example_array4 type_erasure1 type_erasure2 type_erasure3  \
	 type_erasure_record

all: $(PRGS)

array_arithmetic1: array_arithmetic1.cpp 
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)

array_arithmetic2: array_arithmetic2.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)
	
array_arithmetic3:array_arithmetic3.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)
	
array_create:array_create.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)

array_inquery:array_inquery.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)
	
array_linear_access:array_linear_access.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)
	
array_multiindex:array_multiindex.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)
	
array_stl:array_stl.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)
	
array_view_container:array_view_container.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)
	
array_view:array_view.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)
	
copy_file:copy_file.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)
	
example_array2:example_array2.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)
	
example_array3:example_array3.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)

example_array4:example_array4.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)
	
type_erasure1:type_erasure1.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)
	
type_erasure2:type_erasure2.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)
	
type_erasure3: type_erasure3.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)

type_erasure_record:type_erasure_record.cpp
	$(CXX) -o $@ $< $(CPPFLAGS) $(LDFLAGS)


.PHONY: clean
	
clean:
	rm -f $(PRGS)
