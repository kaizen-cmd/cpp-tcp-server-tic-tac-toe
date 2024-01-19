CXX = g++
CXXFLAGS = -std=c++11 -I./src

SRCDIR = ./src
TESTDIR = ./tests

SERVER_SRC = $(wildcard $(SRCDIR)/tcp_server/*.cpp)
CLIENT_SRC = $(wildcard $(SRCDIR)/client/*.cpp)
BOARDGAMES_SRC = $(wildcard $(SRCDIR)/boardGames/*.cpp)
SRCS = $(BOARDGAMES_SRC)
HEADERS = $(wildcard $(SRCDIR)/*.h)
TEST_SOURCES = $(wildcard $(TESTDIR)/*.cpp)

all: server client test

server: $(SERVER_SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SERVER_SRC) $(SRCS) -o binaries/game_tcp_server

client: $(CLIENT_SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(CLIENT_SRC) $(SRCS) -o binaries/game_client

test: $(TEST_SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(TEST_SOURCES) $(SRCS) -o test_suite
	./test_suite

clean:
	rm -f server client test_suite
