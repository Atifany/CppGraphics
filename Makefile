NAME := cppgraphics

_SRC := main.cpp glad.c
SRC_DIR := sources
SRC := $(_SRC:%=$(SRC_DIR)/%)
OBJ := $(SRC:%.cpp=%.o)
OBJ := $(OBJ:%.c=%.o)
DPS := $(SRC:%.cpp=%.d)
DPS := $(DPS:%.c=%.d)

GL_FLAGS :=	-lglfw3 -lGL -lX11 -lpthread			\
			-lXrandr -lXi -Wl,--no-as-needed -ldl

start: $(NAME)

$(NAME): $(OBJ)
	g++ $(GL_FLAGS) $(OBJ) -o $@

%.o: %.cpp
	g++ -MMD -MP -c $< -o $@

-include $(DPS)
