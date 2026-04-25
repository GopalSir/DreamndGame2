# Makefile for DreamndGame2

#Compiler Info 
CXX := g++
CXXINCLUDEFLAGS = 	-I$(GLEW_INCLUDE_DIR) \
					-I$(GLFW_INCLUDE_DIR) \
					-I$(DREAMENGINE_INCLUDE_DIR)

CXXLIBPATHFLAGS =   -L$(GLEW_LIB_DIR) \
					-L$(GLFW_LIB_DIR) \


CXXLIBNAMEFLAGS =   -l:libGLEW.a \
					-l$(GLFW_LIB)\

			



# Third Party Install Directory
THIRD_PARTY_INSTALL := ThirdParty/install

# Lua Directories
LUA_DIR := ThirdParty/lua-5.5.0
LUA_INSTALL_DIR := $(THIRD_PARTY_INSTALL)/lua
LUA_LIB_DIR := $(LUA_INSTALL_DIR)/lib
LUA_INCLUDE_DIR := $(LUA_INSTALL_DIR)/include
LUA_LIB := lua # Just the lib name without the path ( that's what g++ wants)
LUA_INCLUDE := lua.hpp # Just the include file name without the path ( that's what g++ wants)

# GLEW Directories ( latest 2.3.1)
GLEW_DIR := ThirdParty/glew-2.3.1
GLEW_INSTALL_DIR := $(THIRD_PARTY_INSTALL)/glew
GLEW_LIB_DIR := $(GLEW_INSTALL_DIR)/lib64
GLEW_INCLUDE_DIR := $(GLEW_INSTALL_DIR)/include
GLEW_LIB := GLEW # Just the lib name without the path ( that's what g++ wants)
GLEW_INCLUDE := glew.hpp # Just the include file name without the path ( that's what g++ wants)

# GLFW Directories
GLFW_DIR := ThirdParty/glfw-3.4/glfw-3.4
GLFW_BUILD_DIR := $(GLFW_DIR)/build
GLFW_INSTALL_DIR := $(THIRD_PARTY_INSTALL)/glfw
GLFW_LIB_DIR := $(GLFW_INSTALL_DIR)/lib
GLFW_INCLUDE_DIR := $(GLFW_INSTALL_DIR)/include
GLFW_LIB := glfw3 # Just the lib name without the path ( that's what g++ wants)
GLFW_INCLUDE := glfw3.hpp # Just the include file name without the path ( that's what g++ wants)

#DreamEngine Directories
DREAMENGINE_DIR := DreamEngine
DREAMENGINE_SRC_DIR := $(DREAMENGINE_DIR)/src
DREAMENGINE_INCLUDE_DIR := $(DREAMENGINE_DIR)/include
DREAMENGINE_LIB_DIR := $(DREAMENGINE_DIR)/lib
DREAMENGINE_LIB := dreamengine
DREAMENGINE_LIB_FILE := $(DREAMENGINE_LIB_DIR)/lib$(DREAMENGINE_LIB).a
DREAMENGINE_SRC_FILES := $(shell find ${DREAMENGINE_SRC_DIR} -type f -name '*.cpp' )
DREAMENGINE_OBJ_FILES := $(patsubst ${DREAMENGINE_SRC_DIR}/%.cpp,${DREAMENGINE_LIB_DIR}/%.o,${DREAMENGINE_SRC_FILES}  )

#ClientGame Directories
CLIENTGAME_DIR = ClientGame
CLIENTGAME_SRC_DIR := $(CLIENTGAME_DIR)/src
CLIENTGAME_CPP_FILES := $(shell find $(CLIENTGAME_SRC_DIR) -type f -name '*.cpp')
CLIENTGAME_INCLUDE_DIR := $(CLIENTGAME_DIR)/include
CLIENTGAME_OUTPUT_DIR := Install/ClientGame



#Targets
empty: 
	@echo "Building Nothing"
	@echo $(DREAMENGINE_SRC_FILES)


all: build_client

build_client: build_engine
	$(CXX) \
	-I$(CLIENTGAME_INCLUDE_DIR) \
	-I$(LUA_INCLUDE_DIR) \
	$(CXXINCLUDEFLAGS) \
	$(CLIENTGAME_CPP_FILES) \
	-L$(DREAMENGINE_LIB_DIR) -l$(DREAMENGINE_LIB) \
	-L$(LUA_LIB_DIR) -l$(LUA_LIB) \
	$(CXXLIBPATHFLAGS) $(CXXLIBNAMEFLAGS) \
	-lGL -ldl -lm -lpthread -lX11 \
	-o $(CLIENTGAME_OUTPUT_DIR)/ClientGame 
	


build_engine: build_lua build_glew build_glfw $(DREAMENGINE_LIB_FILE)


#g++ -c -o DreamEngine.o DreamEngine.cpp -I$(GLEW_INCLUDE_DIR) -I$(GLFW_INCLUDE_DIR) 

$(DREAMENGINE_LIB_FILE) : $(DREAMENGINE_OBJ_FILES)
	@mkdir -p $(dir $@)
	ar rcs $@ $^

#Pattern rule for DREAMENGINE_OBJ_FILES
${DREAMENGINE_LIB_DIR}/%.o : ${DREAMENGINE_SRC_DIR}/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXINCLUDEFLAGS) -c $< -o $@

#Clean all
clean:
	@echo "Cleaning"
	$(MAKE) -C $(LUA_DIR) clean
	$(MAKE) -C $(GLEW_DIR) clean
	$(MAKE) -C $(GLFW_BUILD_DIR) clean


#Build Lua at new install directory 
build_lua:
	@echo "Building Lua"
	$(MAKE) -C $(LUA_DIR) linux 
	$(MAKE) -C $(LUA_DIR) install INSTALL_TOP=$(abspath $(LUA_INSTALL_DIR))


#Build GLEW at new install directory
build_glew:
	@echo "Building GLEW"
	$(MAKE) -C $(GLEW_DIR) 
	$(MAKE) -C $(GLEW_DIR) install GLEW_DEST=$(abspath $(GLEW_INSTALL_DIR)) GLEW_PREFIX=$(abspath $(GLEW_INSTALL_DIR))

#Build GLFW at new install directory
build_glfw:
	@echo "Building GLFW"
	cmake -B $(GLFW_BUILD_DIR) -S $(GLFW_DIR) -G "Unix Makefiles" -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF -DCMAKE_INSTALL_PREFIX=$(abspath $(GLFW_INSTALL_DIR))
	cmake --build $(GLFW_BUILD_DIR)
	cmake --install $(GLFW_BUILD_DIR)

