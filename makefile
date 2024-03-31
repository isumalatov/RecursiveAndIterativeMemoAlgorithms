#Ilyas Umalatov

all: mcp

maze: mcp.cc
	g++ -o mcp mcp.cc

tar:
	tar -cvzf X727815E.tar.gz mcp.cc makefile

clean:
	rm -f mcp X727815E.tar.gz mcp

