#include "TeleportEntityCheat.h"
#include <Windows.h>
#include "../offsets.h"
#include "../sdk/Entity.h"
#include "../sdk/Vector.h"

void TeleportEntityCheat::EndScene(IDirect3DDevice9* pDevice) {
	if (GetAsyncKeyState(VK_HOME) & 0x8000) {
		// TODO: 64 is an arbitrary number, use entity list size if possible.
		for (size_t i = 0; i < 64; i++) {
			Entity* entity = *(Entity**)(base_address + ENTITY_LIST + ENTITY_LIST_OFFSET * i);

			if (entity == nullptr)
				continue;

			entity->position = Vector(0, 0, 0);
		}
	}
}