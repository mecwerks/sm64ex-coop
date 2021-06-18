#include <ultra64.h>
#include "sm64.h"
#include "djui.h"
#include "game/ingame_menu.h"
#include "game/segment2.h"
#include "src/pc/pc_main.h"
#include "src/pc/gfx/gfx_window_manager_api.h"
#include "gfx_dimensions.h"

static const Vtx vertex_djui_simple_rect[] = {
    {{{ 0, -1, 0}, 0, { 0, 0 }, { 0xff, 0xff, 0xff, 0xff }}},
    {{{ 1, -1, 0}, 0, { 0, 0 }, { 0xff, 0xff, 0xff, 0xff }}},
    {{{ 1,  0, 0}, 0, { 0, 0 }, { 0xff, 0xff, 0xff, 0xff }}},
    {{{ 0,  0, 0}, 0, { 0, 0 }, { 0xff, 0xff, 0xff, 0xff }}},
};

const Gfx dl_djui_simple_rect[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_FADE, G_CC_FADE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPVertex(vertex_djui_simple_rect, 4, 0),
    gsSP2Triangles(0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

/////////////////////////////////////////////

static Vtx vertex_djui_ia_char[] = {
    {{{ 0, -16, 0}, 0, {   0, 256}, { 0xff, 0xff, 0xff, 0xff }}},
    {{{ 8, -16, 0}, 0, {   0,   0}, { 0xff, 0xff, 0xff, 0xff }}},
    {{{ 8,   0, 0}, 0, { 512,   0}, { 0xff, 0xff, 0xff, 0xff }}},
    {{{ 0,   0, 0}, 0, { 512, 256}, { 0xff, 0xff, 0xff, 0xff }}},
};

const Gfx dl_djui_ia_text_begin[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_FADEA, G_CC_FADEA),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

const Gfx dl_djui_ia_text_settings[] = {
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 3, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, ((16 * 8 + G_IM_SIZ_4b_INCR) >> G_IM_SIZ_4b_SHIFT) - 1, CALC_DXT(16, G_IM_SIZ_4b_BYTES)),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_4b, 1, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 3, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (8 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPVertex(vertex_djui_ia_char, 4, 0),
    gsSPExecuteDjui(G_TEXCLIP_DJUI),
    gsSP2Triangles(0,  1,  2, 0x0, 0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

void djui_gfx_render_char(u8 c) {
    void** fontLUT;
    void* packedTexture;

    fontLUT = segmented_to_virtual(main_font_lut);
    packedTexture = segmented_to_virtual(fontLUT[c]);

    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_IA, G_IM_SIZ_16b, 1, VIRTUAL_TO_PHYSICAL(packedTexture));
    gSPDisplayList(gDisplayListHead++, dl_djui_ia_text_settings);

}
/////////////////////////////////////////////

static const Vtx vertex_djui_image[] = {
    {{{ 0, -1, 0 }, 0, {   0, 512 }, { 0xff, 0xff, 0xff, 0xff }}},
    {{{ 1, -1, 0 }, 0, { 512,   512 }, { 0xff, 0xff, 0xff, 0xff }}},
    {{{ 1,  0, 0 }, 0, { 512,   0 }, { 0xff, 0xff, 0xff, 0xff }}},
    {{{ 0,  0, 0 }, 0, { 0, 0 }, { 0xff, 0xff, 0xff, 0xff }}},
};

const Gfx dl_djui_image[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_FADEA, G_CC_FADEA),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(NULL, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16, 0, G_TX_CLAMP, G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPExecuteDjui(G_TEXOVERRIDE_DJUI),
    gsSPVertex(vertex_djui_image, 4, 0),
    gsSPExecuteDjui(G_TEXCLIP_DJUI),
    gsSP2Triangles(0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

void djui_gfx_render_texture(const u8* texture, u16 w, u16 h) {
    gDPSetTextureOverrideDjui(gDisplayListHead++, texture, w, h);
    gSPDisplayList(gDisplayListHead++, dl_djui_image);
}

/////////////////////////////////////////////

void djui_gfx_position_translate(f32* x, f32* y) {
    u32 windowWidth, windowHeight;
    wm_api->get_dimensions(&windowWidth, &windowHeight);
    *x = GFX_DIMENSIONS_FROM_LEFT_EDGE(0) + *x * ((f32)SCREEN_HEIGHT / (f32)windowHeight);
    *y = SCREEN_HEIGHT - *y * ((f32)SCREEN_HEIGHT / (f32)windowHeight);
}

void djui_gfx_scale_translate(f32* width, f32* height) {
    u32 windowWidth, windowHeight;
    wm_api->get_dimensions(&windowWidth, &windowHeight);
    
    *width  = *width * ((f32)SCREEN_HEIGHT / (f32)windowHeight);
    *height = *height * ((f32)SCREEN_HEIGHT / (f32)windowHeight);
}

void djui_gfx_size_translate(f32* size) {
    u32 windowWidth, windowHeight;
    wm_api->get_dimensions(&windowWidth, &windowHeight);

    *size = *size * ((f32)SCREEN_HEIGHT / (f32)windowHeight);
}

bool djui_gfx_add_clipping_specific(struct DjuiBase* base, bool rotatedUV, f32 dX, f32 dY, f32 dW, f32 dH) {
    struct DjuiBaseRect* clip = &base->clip;

    f32 clipX2 = clip->x + clip->width;
    f32 clipY2 = clip->y + clip->height;

    f32 dX2 = dX + dW;
    f32 dY2 = dY + dH;

    // completely clipped
    if (dX2 < clip->x) { return true; }
    if (dX  > clipX2)  { return true; }
    if (dY2 < clip->y) { return true; }
    if (dY  > clipY2)  { return true; }

    f32 dClipX1 = fmax((clip->x - dX) / dW, 0);
    f32 dClipY1 = fmax((clip->y - dY) / dH, 0);
    f32 dClipX2 = fmax((dX - (clipX2 - dW)) / dW, 0);
    f32 dClipY2 = fmax((dY - (clipY2 - dH)) / dH, 0);

    if ((dClipX1 != 0) || (dClipY1 != 0) || (dClipX2 != 0) || (dClipY2 != 0)) {
        gDPSetTextureClippingDjui(gDisplayListHead++, rotatedUV, (u8)(dClipX1 * 255), (u8)(dClipY1 * 255), (u8)(dClipX2 * 255), (u8)(dClipY2 * 255));
    }

    return false;
}

bool djui_gfx_add_clipping(struct DjuiBase* base) {
    struct DjuiBaseRect* comp = &base->comp;
    return djui_gfx_add_clipping_specific(base, false, comp->x, comp->y, comp->width, comp->height);
}