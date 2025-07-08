NAME = ft_scop

CFLAGS = -g -MP -MMD

GLFW_PATH = libs/glfw
GLAD_PATH = libs/glad
GLM_PATH = libs/glm

GLFW = $(GLFW_PATH)/libglfw3.a
GLAD_SRC = $(GLAD_PATH)/glad.c
GLAD = $(GLAD_SRC:.c=.o)

INCLUDES = -Iincludes/ -Ilibs/

SRC = main.cpp\
		shaders/Shaders.cpp\
		Buffers/VBO.cpp\
		Buffers/VAO.cpp\
		Buffers/EBO.cpp\
		Texture/Texture.cpp\
		Camera/Camera.cpp\
		Window/Window.cpp\
		ObjectHandler/ObjectLoader.cpp\
		ObjectHandler/Object.cpp\
		ShadowMap/ShadowMap.cpp\
		ObjectSelecter/ObjectSelecter.cpp

OBJ = $(addprefix obj/, $(SRC:.cpp=.o))
DEPS = $(addprefix obj/, $(SRC:.cpp=.d))

all: glfw glad glm $(NAME)

$(GLAD): %.o: %.c
	@gcc $(INCLUDES) $< -c -o $@
	@echo "\033[32;1mCompiled " $@ "\033[0m"

obj/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	@c++ $(CFLAGS) $(INCLUDES) $< -c -o $@
	@echo "\033[32;1mCompiled " $@ "\033[0m"


download_glfw:
	@cd libs; \
	rm -rf glfw 2>/dev/null; \
	echo "\033[31;1;4mglfw Not Found\033[0m"; \
	echo "\033[31;1mDownloading it from github\033[0m"; \
	git clone https://github.com/glfw/glfw.git GLFW; \
	echo "\033[31;1mCompiling it\033[0m"; \
	cmake -S GLFW -B GLFW/build; \
	cmake --build GLFW/build; \
	mkdir -p glfw; \
	cp GLFW/include/GLFW/glfw3.h glfw/.; \
	cp GLFW/build/src/libglfw3.a glfw/.; \
	rm -rf GLFW

glfw:
	@mkdir -p libs
	@if ls ./libs/glfw 2>/dev/null | grep -q "glfw3.h" ; then \
		echo "\033[32;1;4mglfw Header Found\033[0m"; \
	else \
		make --no-print-directory download_glfw; \
	fi
	@if ls ./libs/glfw 2>/dev/null | grep -q "libglfw3.a" ; then \
		echo "\033[32;1;4mglfw Library Found\033[0m"; \
	else \
		make --no-print-directory download_glfw; \
	fi


download_glad:
	@cd libs; \
	echo "\033[31;1;4mglad Not Found\033[0m"; \
	echo "\033[31;1mDownloading it from github\033[0m"; \
	git clone https://github.com/Dav1dde/glad.git glad; \
	echo "\033[31;1mCompiling it\033[0m"; \
	pip install glad; \
	python -m glad --out-path=glad/build --generator=c; \
	mkdir -p glad2; \
	cp glad/build/include/glad/glad.h glad2/.; \
	cp glad/build/src/glad.c glad2/.; \
	rm -rf glad; \
	mv glad2 glad

glad:
	@mkdir -p libs
	@if ls ./libs/glad 2>/dev/null | grep -q "glad.h" ; then \
		echo "\033[32;1;4mglad Header Found\033[0m"; \
	else \
		make --no-print-directory download_glad; \
	fi
	@if ls ./libs/glad 2>/dev/null | grep -q "glad.c" ; then \
		echo "\033[32;1;4mglad File Found\033[0m"; \
	else \
		make --no-print-directory download_glad; \
	fi


download_glm:
	@cd libs; \
	echo "\033[31;1;4mglad Not Found\033[0m"; \
	echo "\033[31;1mDownloading it from github\033[0m"; \
	git clone https://github.com/g-truc/glm.git GLM; \
	echo "\033[31;1mGetting the Headers\033[0m"; \
	mkdir -p glm; \
	mv GLM/glm .; \
	rm -rf GLM

glm:
	@mkdir -p libs
	@if ls ./libs/glm 2>/dev/null | grep -q "glm.hpp" ; then \
		echo "\033[32;1;4mglm Header Found\033[0m"; \
	else \
		make --no-print-directory download_glm; \
	fi



$(NAME): $(GLAD) $(OBJ)
	@c++ -o $(NAME) $(CFLAGS) $(OBJ) $(GLAD) $(GLFW) $(INCLUDES)
	@echo "\033[32;1;4mCompiled executable\033[0m"

cleanlibs:
	rm -rf $(GLFW_PATH)
	rm -rf $(GLAD_PATH)
	rm -rf $(GLM_PATH)

clean:
	@rm -rf obj/
	@rm -rf libs/glad/glad.o 2>/dev/null
	@echo "\033[0;32;1mCleaned objects\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;32;1mCleaned executable\033[0m"

re: fclean all

.PHONY: all glfw glad glm clean fclean re cleanlibs

-include $(DEPS)%