# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++23 -Wall
DEBUGFLAGS = -g
RELEASEFLAGS = -O2

# Directories
PUBLISHER_DIR = publisher
SUBSCRIBER_DIR = subscriber
UTILS_DIR = utils
BIN_DEBUG = debug
BIN_RELEASE = release

# Output files
PUB_OUT = $(PUBLISHER_DIR)/bin/$(BIN_RELEASE)/pub.out
SUB_OUT = $(SUBSCRIBER_DIR)/bin/$(BIN_RELEASE)/sub.out

# Libraries
UTILS_LIB = $(UTILS_DIR)/libutils.a

# Header and Source Files
UTILS_HEADERS = $(UTILS_DIR)/include
PUBLISHER_HEADERS = $(PUBLISHER_DIR)/include
SUBSCRIBER_HEADERS = $(SUBSCRIBER_DIR)/include

UTILS_SOURCES = $(UTILS_DIR)/src/client.cpp $(UTILS_DIR)/src/server.cpp $(UTILS_DIR)/src/cryptoFactory.cpp $(UTILS_DIR)/src/crypto.cpp
PUBLISHER_SOURCES = $(PUBLISHER_DIR)/src/publisher.cpp $(PUBLISHER_DIR)/src/crypto_generator.cpp
SUBSCRIBER_SOURCES = $(SUBSCRIBER_DIR)/src/subscriber.cpp

# Test files containing main functions
PUBLISHER_TEST = $(PUBLISHER_DIR)/test/main.cpp
SUBSCRIBER_TEST = $(SUBSCRIBER_DIR)/test/main.cpp

# Compile Type
BUILD = release
CXXFLAGS += $(RELEASEFLAGS)

ifeq ($(BUILD), debug)
    CXXFLAGS += $(DEBUGFLAGS)
    BIN_DIR = $(BIN_DEBUG)
else
    BIN_DIR = $(BIN_RELEASE)
endif

# Object files
UTILS_OBJS = $(UTILS_SOURCES:.cpp=.o)
PUBLISHER_OBJS = $(PUBLISHER_SOURCES:.cpp=.o)
SUBSCRIBER_OBJS = $(SUBSCRIBER_SOURCES:.cpp=.o)

# Target rules
all: $(UTILS_LIB) publisher subscriber

# Build Utils Library
$(UTILS_LIB): $(UTILS_OBJS)
	@echo "Building library..."
	ar rcs $(UTILS_LIB) $(UTILS_OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(PUBLISHER_HEADERS) -I$(SUBSCRIBER_HEADERS) -I$(UTILS_HEADERS) -c $< -o $@

# Build Publisher
publisher: $(PUBLISHER_OBJS) $(PUBLISHER_TEST)
	@echo "Building publisher..."
	@mkdir -p $(PUBLISHER_DIR)/bin/$(BIN_DIR)
	$(CXX) $(CXXFLAGS) -I$(PUBLISHER_HEADERS) -I$(UTILS_HEADERS) $(PUBLISHER_OBJS) $(PUBLISHER_TEST) -o $(PUB_OUT) $(UTILS_LIB)

# Build Subscriber
subscriber: $(SUBSCRIBER_OBJS) $(SUBSCRIBER_TEST)
	@echo "Building subscriber..."
	@mkdir -p $(SUBSCRIBER_DIR)/bin/$(BIN_DIR)
	$(CXX) $(CXXFLAGS) -I$(SUBSCRIBER_HEADERS) -I$(UTILS_HEADERS) $(SUBSCRIBER_OBJS) $(SUBSCRIBER_TEST) -o $(SUB_OUT) $(UTILS_LIB)

# Run Publisher
run-publisher:
	./$(PUB_OUT)

# Run Subscriber
run-subscriber:
	./$(SUB_OUT) $(ARGS) 

# Clean
clean:
	@echo "Cleaning up..."
	rm -f $(UTILS_OBJS) $(UTILS_LIB)
	rm -f $(PUBLISHER_OBJS) $(PUB_OUT)
	rm -f $(SUBSCRIBER_OBJS) $(SUB_OUT)
	rm -rf $(PUBLISHER_DIR)/bin/$(BIN_DEBUG) $(PUBLISHER_DIR)/bin/$(BIN_RELEASE)
	rm -rf $(SUBSCRIBER_DIR)/bin/$(BIN_DEBUG) $(SUBSCRIBER_DIR)/bin/$(BIN_RELEASE)
