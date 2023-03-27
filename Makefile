NAME := cppgraphics

_SRC := main.cpp glad.c
SRC_DIR := sources
SRC := $(_SRC:%=$(SRC_DIR)/%)
OBJ := $(SRC:%.cpp=%.o)
OBJ := $(OBJ:%.c=%.o)
DPS := $(SRC:%.cpp=%.d)
DPS := $(DPS:%.c=%.d)

#GL_FLAGS := -L/usr/local/lib -lglfw3 -lrt -lm -ldl -lX11 -lpthread -lxcb -lXau -lXdmcp
GL_FLAGS := -std=c++11 -Wall -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor
#GL_FLAGS :=	-lrt -lXrandr		\
			-lXinerama -lXi -lXcursor -lGL -lm				\
			-lXrender -ldrm -L/usr/local/lib -lglfw		\
			-lXxf86vm -lXfixes -lXext -lX11					\
			-lpthread -lxcb -lXau -lXdmcp					\
			-Wl,--no-as-needed -ldl

start: $(NAME)

$(NAME): $(OBJ)
	g++ $(GL_FLAGS) $(OBJ) -o $@

%.o: %.cpp
	g++ -MMD -MP -c $< -o $@

-include $(DPS)
