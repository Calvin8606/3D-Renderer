build:
	clang -Wall -Wextra ./src/*.c -o renderer \
	-I/opt/homebrew/include/SDL2 \
	-L/opt/homebrew/lib -lSDL2 \


run: build
	./renderer

clean:
	rm -f renderer
