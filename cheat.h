#pragma once

struct IDirect3DDevice9;

class Cheat {
public:
	virtual void EndScene(IDirect3DDevice9* pDevice) { }
};