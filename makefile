#Ilyas Umalatov X7278165E
all: mcp

maze: mcp.cc
	g++ -o mcp mcp.cc

tar:
	tar -cvzf X7278165E.tar.gz mcp.cc makefile

clean:
	rm -f mcp X7278165E.tar.gz mcp

