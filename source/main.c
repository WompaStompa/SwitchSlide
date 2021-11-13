#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <switch.h>
#include "image_bin.h"

#define FB_WIDTH  1280
#define FB_HEIGHT 720

int main(int argc, char* argv[]) {
	
	NWindow* win = nwindowGetDefault();
	
	Framebuffer fb;
	framebufferCreate(&fb, win, FB_WIDTH, FB_HEIGHT, PIXEL_FORMAT_RGBA_8888, 2);
	framebufferMakeLinear(&fb);
	
	u8* imageptr = (u8*)image_bin;
	
	padConfigureInput(1, HidNpadStyleSet_NpadStandard);
	PadState pad;
	padInitializeDefault(&pad);
	hidInitializeTouchScreen();
	
	s32 prev_touchcount=0;
	int touchI = 0;
	int hLine = 0, hLineOld = 0, hairBool = 0;
	int slide = 0, slideOld = 0, slideBool = 0;
	bool inhib = false;
	
	while(appletMainLoop()) {
		padUpdate(&pad);
		u64 kDown = padGetButtonsDown(&pad);
		if (kDown & HidNpadButton_Plus) { break; }
		if (kDown & HidNpadButton_A) { slideBool = !slideBool; }
		if (kDown & HidNpadButton_B) { slide = 0; }
		if (kDown & HidNpadButton_X) { hLine = 0; }
		HidTouchScreenState state={0};
		
		if (hidGetTouchScreenStates(&state, 1)) {
			if (state.count != prev_touchcount) { prev_touchcount = state.count; }
			if (state.count) {
				if (inhib) {
					slide = (slideOld + slideBool*(state.touches[0].x - touchI) + FB_WIDTH)%FB_WIDTH;
					hLine = (hLineOld + (!slideBool)*(state.touches[0].x - touchI) + FB_WIDTH)%FB_WIDTH;
				} else {
					slideOld = slide;
					hLineOld = hLine;
					touchI = state.touches[0].x;
					inhib = true;
				}
			} else { inhib = false; }
		}
		
		u32 stride;
		u32* framebuf = (u32*)framebufferBegin(&fb, &stride);
		
		for (u32 x = 0; x < FB_WIDTH; x++) {
			for (u32 y = 0; y < FB_HEIGHT/3; y++) {
				u32 pos = y*stride/sizeof(u32) + x;
				hairBool = !(x - hLine);
				
				u32 imagepos = y * FB_WIDTH + x;
				framebuf[pos] = RGBA8_MAXALPHA((!hairBool)*imageptr[imagepos*3+2], hairBool*0xFF + (!hairBool)*imageptr[imagepos*3+1], (!hairBool)*imageptr[imagepos*3+0]);
			}
			for (u32 y = FB_HEIGHT/3; y < 2*FB_HEIGHT/3; y++) {
				u32 pos = y*stride/sizeof(u32) + x;
				hairBool = !(x - hLine);
				
				u32 imagepos = y * FB_WIDTH + (x - slide + FB_WIDTH)%FB_WIDTH;
				framebuf[pos] = RGBA8_MAXALPHA((!hairBool)*imageptr[imagepos*3+2], hairBool*0xFF + (!hairBool)*imageptr[imagepos*3+1], (!hairBool)*imageptr[imagepos*3+0]);
			}
			for (u32 y = 2*FB_HEIGHT/3; y < FB_HEIGHT; y++) {
				u32 pos = y*stride/sizeof(u32) + x;
				hairBool = !(x - hLine);
				
				u32 imagepos = y * FB_WIDTH + x;
				framebuf[pos] = RGBA8_MAXALPHA((!hairBool)*imageptr[imagepos*3+2], hairBool*0xFF + (!hairBool)*imageptr[imagepos*3+1], (!hairBool)*imageptr[imagepos*3+0]);
			}
		}
		framebufferEnd(&fb);
	}
	framebufferClose(&fb);
	return 0;
}
