#pragma once

#include "../cheat.h"

class CrosshairCheat : public Cheat {
public:
	void EndScene(IDirect3DDevice9* pDevice) override;
};