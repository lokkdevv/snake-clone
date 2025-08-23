default:
	g++ src/main.cpp -o build/main.exe -O2 -std=gnu++23 -Ilibs/raylib -Llibs/raylib -lraylib -lwinmm -lgdi32 -lopengl32 -mwindows

web:
	em++ src/main.cpp -o build/web/index.html --shell-file html_template/template.html -s USE_GLFW=3 -s ASYNCIFY -s FORCE_FILESYSTEM=1 -Ilibs/raylib -Llibs/raylib/web -lraylib

clean:
	del main.exe

cleanw:
	del index.html index.js index.wasm