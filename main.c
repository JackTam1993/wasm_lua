#include "lua.h"
#include <lauxlib.h>
#include <lualib.h>
#include <stdlib.h>
#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE
const char* jsonToData(const char* json) {

	lua_State *lua = luaL_newstate();
	luaL_openlibs(lua);
	int retLoad = luaL_dofile(lua, "./script/fa.lua");

	if (retLoad == 0) {
        printf("load file success retLoad:%d\n", retLoad);
    } else {
		return 0;
	}

	lua_getglobal(lua, "jsonToData");
    lua_pushstring(lua, json);

	int pcallRet = lua_pcall(lua,1,1,0);
    if (pcallRet != 0) {
        printf("error %s\n", lua_tostring(lua, -1));
        char* failed = "failed";
        return 0;
    }

    // 获取 Lua 函数的返回值
    if (lua_isstring(lua, -1)) { // 如果返回值是一个字符串
        const char *data_str = lua_tostring(lua, -1);
		printf("data from lua: %s \n", data_str);
        return data_str;
    }

    lua_close(lua);

	return 0;
}

const char* dataToJson(const char* data) {

	lua_State *lua = luaL_newstate();
	luaL_openlibs(lua);
	int retLoad = luaL_dofile(lua, "./script/fa.lua");

	if (retLoad == 0) {
        printf("load file success retLoad:%d\n", retLoad);
    } else {
		return 0;
	}

	lua_getglobal(lua, "dataToJson");
    lua_pushstring(lua, data);

	int pcallRet = lua_pcall(lua,1,1,0);
    if (pcallRet != 0) {
        printf("error %s\n", lua_tostring(lua, -1));
        char* failed = "failed";
        return 0;
    }

	// 获取 Lua 函数的返回值
    if (lua_isstring(lua, -1)) { // 如果返回值是一个字符串
        const char *json_str = lua_tostring(lua, -1);
		printf("data from lua: %s \n", json_str);
        return json_str;
    }

    lua_close(lua);

	return 0;
}