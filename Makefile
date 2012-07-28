
CXX=g++
CXXFLAGS=-g -std=c++0x
INSTALL=cp -a
TC=./tc.py

CGI_EXT=.cgi

SITE_NAME=danielkeep.koding.com
INSTALL_FILES=index.cgi .htaccess
INSTALL_DIR=../../../Sites/$(SITE_NAME)/website

all: $(INSTALL_FILES)

install: $(INSTALL_FILES)
	$(INSTALL) $^ $(INSTALL_DIR)

index$(CGI_EXT): index.o
	$(CXX) $(CXXFLAGS) -o $@ $(filter %.o,$^)

index.o: index.t.h

clean:
	@- rm *.o
	@- rm *.t.h

clean-dist:
	@- rm index$(CGI_EXT)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

%.t.h: %.t.html
	$(TC) $(patsubst %.t.html,%,$<) $< $@

