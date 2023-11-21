server:
	g++ Server.cpp -std=c++2a -lsfml-network -lsfml-system -lpthread -o Server
client:
	g++ Client.cpp -std=c++2a -lsfml-network -lsfml-system -lpthread -o Client
all:
	make server
	make client
	./Server