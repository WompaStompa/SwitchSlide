#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <switch.h>

#define FB_WIDTH  1280
#define FB_HEIGHT 720

int main(int argc, char* argv[]) {
    NWindow* win = nwindowGetDefault();
	
	Framebuffer fb;
	framebufferCreate(&fb, win, FB_WIDTH, FB_HEIGHT, PIXEL_FORMAT_RGBA_8888, 2);
	framebufferMakeLinear(&fb);

    padConfigureInput(1, HidNpadStyleSet_NpadStandard);

    PadState pad;
    padInitializeDefault(&pad);

    hidInitializeTouchScreen();

    s32 prev_touchcount=0;
	int cursor = 0;
	int cursorOld = 0;
	bool inhib = false;
	int touchI = 0;
	
    while(appletMainLoop()) {
        
        padUpdate(&pad);
        u64 kDown = padGetButtonsDown(&pad);

        if (kDown & HidNpadButton_Plus) { break; }

        HidTouchScreenState state={0};
        if (hidGetTouchScreenStates(&state, 1)) {
			if (state.count != prev_touchcount) { prev_touchcount = state.count; }
			if (state.count) {
				if (inhib) {
					cursor = (cursorOld + state.touches[0].x - touchI + FB_WIDTH)%FB_WIDTH;
				} else {
					cursorOld = cursor;
					touchI = state.touches[0].x;
					inhib = true;
				}
			} else {	inhib = false; }
        }
		
		u32 stride;
		u32* framebuf = (u32*)framebufferBegin(&fb, &stride);

        for (u32 y = 0; y < FB_HEIGHT; y++) {
			for (u32 x = 0; x < FB_WIDTH; x++)	{
				u32 pos = y*stride/sizeof(u32) + x;
				if (x == cursor) { framebuf[pos] = 0xFF; } else { framebuf[pos] = 0; }
			}
		}
		
		framebufferEnd(&fb);
	}
	framebufferClose(&fb);
	return 0;
}