#pragma once

#include "../cheat.h"

class TeleportEntityCheat : public Cheat {
public:
	void EndScene(IDirect3DDevice9* pDevice) override;
};