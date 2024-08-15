#include <discord_rpc.h>
#include <lua.hpp>
#include <cstring>

extern "C" __declspec(dllexport) int Initialize(lua_State* L) {
    const char* clientId = luaL_checkstring(L, 1);
    DiscordEventHandlers handlers = {};
    Discord_Initialize(clientId, &handlers, 1, nullptr);
    return 0;
}

extern "C" __declspec(dllexport) int SetPresence(lua_State* L) {
    DiscordRichPresence presence = {};

    presence.state = luaL_optstring(L, 1, nullptr);
    presence.details = luaL_optstring(L, 2, nullptr);
    presence.startTimestamp = luaL_optinteger(L, 3, 0);
    presence.endTimestamp = luaL_optinteger(L, 4, 0);
    presence.largeImageKey = luaL_optstring(L, 5, nullptr);
    presence.largeImageText = luaL_optstring(L, 6, nullptr);
    presence.smallImageKey = luaL_optstring(L, 7, nullptr);
    presence.smallImageText = luaL_optstring(L, 8, nullptr);
    presence.partyId = luaL_optstring(L, 9, nullptr);
    presence.partySize = luaL_optinteger(L, 10, 0);
    presence.partyMax = luaL_optinteger(L, 11, 0);
    presence.matchSecret = luaL_optstring(L, 12, nullptr);
    presence.joinSecret = luaL_optstring(L, 13, nullptr);
    presence.spectateSecret = luaL_optstring(L, 14, nullptr);
    presence.instance = lua_toboolean(L, 15);

    Discord_UpdatePresence(&presence);
    return 0;
}

extern "C" __declspec(dllexport) int ClearPresence(lua_State* L) {
    Discord_ClearPresence();
    return 0;
}

extern "C" __declspec(dllexport) int Shutdown(lua_State* L) {
    Discord_Shutdown();
    return 0;
}

extern "C" __declspec(dllexport) int luaopen_DiscordRPC(lua_State* L) {
    static const luaL_Reg funcs[] = {
        {"Initialize", Initialize},
        {"SetPresence", SetPresence},
        {"ClearPresence", ClearPresence},
        {"Shutdown", Shutdown},
        {nullptr, nullptr}
    };

    luaL_newlib(L, funcs);
    return 1;
}