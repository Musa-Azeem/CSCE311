text-client: src/* inc/*
	g++ -std=c++17 src/main-client.cc src/text-client.cc src/Unix-Domain-Socket.cc -o text-client

text-server: src/* inc/*
	g++ -std=c++17 src/main-server.cc src/text-server.cc src/Unix-Domain-Socket.cc src/search.cc -o text-server

clean:
	rm text-client text-server
