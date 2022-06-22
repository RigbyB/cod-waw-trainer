#include "CrosshairCheat.h"
#include <d3d9.h>

void CrosshairCheat::EndScene(IDirect3DDevice9* pDevice) {
    D3DCOLOR crosshair_color = D3DCOLOR_XRGB(255, 0, 0);

    D3DVIEWPORT9 viewport;
    pDevice->GetViewport(&viewport);

    int length = 20;
    int thickness = 2;
    int x = viewport.Width / 2 - thickness / 2;
    int y = viewport.Height / 2 - thickness / 2;

    // Horizontal Line
    D3DRECT rect = {
        x - length / 2,
        y - thickness / 2,
        x + length / 2,
        y + thickness / 2
    };

    pDevice->Clear(
        1,
        &rect,
        D3DCLEAR_TARGET,
        crosshair_color,
        0,
        0
    );

    // Vertical Line   
    rect = {
        x - thickness / 2,
        y - length / 2,
        x + thickness / 2,
        y + length / 2
    };

    pDevice->Clear(
        1,
        &rect,
        D3DCLEAR_TARGET,
        crosshair_color,
        0,
        0
    );
}