# compile with c++17
text-client:
	g++ -std=c++17 main-client.cc src/*.cc -o text-client

text-server:
	g++ -std=c++17 main-server.cc src/*.cc -o text-server

clean:
	@echo 'You should implement me for points'
