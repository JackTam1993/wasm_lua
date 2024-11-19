all: main.o

main.o: main.c lua
	emcc -Ilua-5.3.4/src main.c lua-5.3.4/src/liblua.a -s WASM=1 -O3 -o main.wasm -s STANDALONE_WASM -s EXPORTED_FUNCTIONS="['_jsonToData', '_dataToJson']" -sEXPORTED_RUNTIME_METHODS=ccall,cwrap --preload-file=script/fa.lua -s ERROR_ON_UNDEFINED_SYMBOLS=0

lua:
	cd lua-5.3.4/src && make generic CC='emcc -s WASM=1'