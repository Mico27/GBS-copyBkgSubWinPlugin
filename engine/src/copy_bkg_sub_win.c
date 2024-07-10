#pragma bank 255

#include <gbdk/platform.h>
#include "system.h"
#include "vm.h"
#include "gbs_types.h"

void set_xy_win_submap(const UBYTE * source, UBYTE bank, UBYTE width, UBYTE x, UBYTE y, UBYTE w, UBYTE h) OLDCALL;

void copy_background_submap_to_overlay(SCRIPT_CTX * THIS) OLDCALL BANKED {
	
	uint8_t bkg_x = *(int8_t*)VM_REF_TO_PTR(FN_ARG0);
	uint8_t bkg_y = *(int8_t*)VM_REF_TO_PTR(FN_ARG1);
	uint8_t win_x = *(int8_t*)VM_REF_TO_PTR(FN_ARG2);
	uint8_t win_y = *(int8_t*)VM_REF_TO_PTR(FN_ARG3);
	uint8_t width = *(int8_t*)VM_REF_TO_PTR(FN_ARG4);
	uint8_t height = *(int8_t*)VM_REF_TO_PTR(FN_ARG5);
	uint8_t scene_bank = *(uint8_t *) VM_REF_TO_PTR(FN_ARG6);
	const scene_t * scene_ptr = *(scene_t **) VM_REF_TO_PTR(FN_ARG7);		
	scene_t scn;
    MemcpyBanked(&scn, scene_ptr, sizeof(scn), scene_bank);
	background_t bkg;
    MemcpyBanked(&bkg, scn.background.ptr, sizeof(bkg), scn.background.bank);
    unsigned char* tilemap_ptr = bkg.tilemap.ptr;
	unsigned char* tilemap_attr_ptr = bkg.cgb_tilemap_attr.ptr;		
	UWORD offset = (bkg_y * bkg.width) + bkg_x;
#ifdef CGB
    if (_is_CGB) {
        VBK_REG = 1;
        set_xy_win_submap(tilemap_attr_ptr + offset,  bkg.cgb_tilemap_attr.bank, bkg.width, win_x, win_y, width, height);
        VBK_REG = 0;
    }
#endif
    set_xy_win_submap(tilemap_ptr + offset, bkg.tilemap.bank, bkg.width, win_x, win_y, width, height);
	
}

void copy_background_submap_to_overlay_base(SCRIPT_CTX * THIS) OLDCALL BANKED {
	int16_t bkg_pos = *(int16_t*)VM_REF_TO_PTR(FN_ARG0);
	int16_t win_pos = *(int16_t*)VM_REF_TO_PTR(FN_ARG1);
	int16_t wh = *(int16_t*)VM_REF_TO_PTR(FN_ARG2);
	uint8_t tile_idx_offset = *(int8_t*)VM_REF_TO_PTR(FN_ARG3);
	uint8_t scene_bank = *(uint8_t *) VM_REF_TO_PTR(FN_ARG4);
	const scene_t * scene_ptr = *(scene_t **) VM_REF_TO_PTR(FN_ARG5);	

	UBYTE bkg_x = bkg_pos & 0xFF;
	UBYTE bkg_y = (bkg_pos >> 8) & 0xFF;
	UBYTE win_x = win_pos & 0xFF;
	UBYTE win_y = (win_pos >> 8) & 0xFF;
	UBYTE width = wh & 0xFF;
	UBYTE height = (wh >> 8) & 0xFF;
	
	scene_t scn;
    MemcpyBanked(&scn, scene_ptr, sizeof(scn), scene_bank);
	background_t bkg;
    MemcpyBanked(&bkg, scn.background.ptr, sizeof(bkg), scn.background.bank);
    unsigned char* tilemap_ptr = bkg.tilemap.ptr;
	unsigned char* tilemap_attr_ptr = bkg.cgb_tilemap_attr.ptr;		
	
	if (width > 20){
		width = 20;
	}
	if (height > 18){
		height = 18;
	}
	UBYTE tmp_tile_buffer[20];
	UBYTE buffer_size = sizeof(UBYTE) * width;
	for (int i = 0; i < height; i++){		
		UWORD offset = ((bkg_y + i) * bkg.width) + bkg_x;
#ifdef CGB
		if (_is_CGB) {
			VBK_REG = 1;
			MemcpyBanked(tmp_tile_buffer, tilemap_attr_ptr + offset, buffer_size, bkg.cgb_tilemap_attr.bank);
			set_win_tiles(win_x & 31, (win_y + i) & 31, width, 1, tmp_tile_buffer);
			VBK_REG = 0;
		}
#endif
		MemcpyBanked(tmp_tile_buffer, tilemap_ptr + offset, buffer_size, bkg.tilemap.bank);
		set_win_based_tiles(win_x & 31, (win_y + i) & 31, width, 1, tmp_tile_buffer, tile_idx_offset);
	}	
}