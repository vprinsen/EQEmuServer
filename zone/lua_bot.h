#ifdef BOTS
#ifndef EQEMU_LUA_BOT_H
#define EQEMU_LUA_BOT_H
#ifdef LUA_EQEMU

#include "lua_mob.h"

class Bot;
class Lua_Bot;
class Lua_Mob;

namespace luabind {
	struct scope;
}

luabind::scope lua_register_bot();

class Lua_Bot : public Lua_Mob
{
	typedef Bot NativeType;
public:
	Lua_Bot() { SetLuaPtrData(nullptr); }
	Lua_Bot(Bot *d) { SetLuaPtrData(reinterpret_cast<Entity*>(d)); }
	virtual ~Lua_Bot() { }

	operator Bot*() {
		return reinterpret_cast<Bot*>(GetLuaPtrData());
	}

	void AddBotItem(uint16 slot_id, uint32 item_id);
	void AddBotItem(uint16 slot_id, uint32 item_id, int16 charges);
	void AddBotItem(uint16 slot_id, uint32 item_id, int16 charges, bool attuned);
	void AddBotItem(uint16 slot_id, uint32 item_id, int16 charges, bool attuned, uint32 augment_one);
	void AddBotItem(uint16 slot_id, uint32 item_id, int16 charges, bool attuned, uint32 augment_one, uint32 augment_two);
	void AddBotItem(uint16 slot_id, uint32 item_id, int16 charges, bool attuned, uint32 augment_one, uint32 augment_two, uint32 augment_three);
	void AddBotItem(uint16 slot_id, uint32 item_id, int16 charges, bool attuned, uint32 augment_one, uint32 augment_two, uint32 augment_three, uint32 augment_four);
	void AddBotItem(uint16 slot_id, uint32 item_id, int16 charges, bool attuned, uint32 augment_one, uint32 augment_two, uint32 augment_three, uint32 augment_four, uint32 augment_five);
	void AddBotItem(uint16 slot_id, uint32 item_id, int16 charges, bool attuned, uint32 augment_one, uint32 augment_two, uint32 augment_three, uint32 augment_four, uint32 augment_five, uint32 augment_six);
	uint32 CountBotItem(uint32 item_id);
	Lua_Mob GetOwner();
	bool HasBotItem(uint32 item_id);
	void RemoveBotItem(uint32 item_id);
};

#endif
#endif
#endif