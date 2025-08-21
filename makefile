win: main.cpp
	g++ main.cpp -o main.exe -O2 -std=gnu++23 -IC:/raylib/raylib/src -LC:/raylib/raylib/src -lraylib -lwinmm -lgdi32 -lopengl32 -mwindows
	./main.exe

web: main.cpp
	em++ main.cpp -o index.html --shell-file html_template/template.html -s USE_GLFW=3 -s ASYNCIFY -s FORCE_FILESYSTEM=1 -IC:/raylib/raylib/src -LC:/raylib/raylib/src/web -lraylib

clean:
	del main.exe

cleanw:
	del index.html index.js index.wasm