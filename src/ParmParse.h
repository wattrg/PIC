#include <lua.hpp>
#include <LuaBridge.h>
#include <Vector.h>
#include <iostream>
#include <vector>

#ifndef ParmParse_H
#define ParmParse_H

using namespace luabridge;

/*
Class which reads information from the lua scripts
Uses LuaBridge to interface with lua
*/

class ParmParse {
private:
     lua_State * L;
public:
   

    ParmParse (char const * file){
        L = luaL_newstate();
        luaL_openlibs(L);
        luaL_dofile(L,file);
        lua_pcall(L,0,0,0);
    }
    
    template <typename T>
    int readVariable(T & var, char const * name){
        LuaRef lua_var (L, new T);
        lua_var = getGlobal(L, name);
        if (!lua_var.isNil()){
            var = lua_var.cast<T>();
            return 0;
        }
        else
        {
            std::cout << "Failed reading " << name << "from lua file \n";
            return 1;
        }
    }
};

#endif // ParmParse_H