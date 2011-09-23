#makefile for building debian packages

SCONS=scons

clean:
	$(SCONS) -c

all:
	$(SCONS) all

install:
	$(SCONS) PREFIX=/usr --install-sandbox=$(DESTDIR) install CXX=$(CXX)