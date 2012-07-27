
CXX=g++
CXXFLAGS=-g -std=c++0x
TC=./tc.py

CGI_EXT=.cgi

all: index.cgi

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

