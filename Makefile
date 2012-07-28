
CXX=g++
CXXFLAGS=-g $(CXX11_FLAGS)
CXX11_FLAGS=-std=c++11
INSTALL=cp -a
TC=./tc.py

CGI_EXT=.cgi

SITE_NAME=danielkeep.koding.com
INSTALL_FILES=index.cgi .htaccess
INSTALL_DIR=../../../Sites/$(SITE_NAME)/website

include $(wildcard Makefile.local)

all: $(INSTALL_FILES)

install: $(INSTALL_FILES)
	$(INSTALL) $^ $(INSTALL_DIR)

index$(CGI_EXT): index.o utils.o
	$(CXX) $(CXXFLAGS) -o $@ $(filter %.o,$^)

index.o: index.t.h c++11.h utils.h

clean:
	@- rm *.o
	@- rm *.t.h

clean-dist:
	@- rm index$(CGI_EXT)

sandwich:
	@- [[ $$UID -ne 0 ]] && echo Make it yourself. || echo Ok.

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

%.t.h: %.t.html $(TC)
	$(TC) $(patsubst %.t.html,%,$<) $< $@

