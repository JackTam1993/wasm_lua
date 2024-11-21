all: main.o

# main.o: main.c lua
# 	emcc -Ilua-5.3.4/src main.c lua-5.3.4/src/liblua.a -s WASM=1 -O2 -o main.js -s EXPORTED_FUNCTIONS="['_jsonToData', '_dataToJson']" -sEXPORTED_RUNTIME_METHODS=ccall,cwrap --preload-file=script/fa.lua

main.o: main.c lua
	emcc -Ilua-5.3.4/src main.c lua-5.3.4/src/liblua.a -s WASM=1 -Oz --profiling-funcs -sSTANDALONE_WASM -o main-standalone.wasm -s EXPORTED_FUNCTIONS="['_jsonToData', '_dataToJson']" -sEXPORTED_RUNTIME_METHODS=ccall,cwrap --preload-file=script/fa.lua --no-entry

lua:
	cd lua-5.3.4/src && make generic CC='emcc -s WASM=1'