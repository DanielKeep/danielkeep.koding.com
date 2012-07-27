
CXX=g++
CXXFLAGS=-g -std=c++0x

CGI_EXT=.cgi

all: index.cgi

index$(CGI_EXT): index.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	@- rm *.o

clean-dist:
	@- rm index$(CGI_EXT)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

