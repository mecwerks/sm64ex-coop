#pragma once
#include "djui.h"

#pragma pack(1)
struct DjuiImage {
    struct DjuiBase base;
    const u8* texture;
    u16 textureWidth;
    u16 textureHeight;
};

void djui_image_set_image(struct DjuiImage* image, const u8* texture, u16 textureWidth, u16 textureHeight);

struct DjuiImage* djui_image_create(struct DjuiBase* parent, const u8* texture, u16 textureWidth, u16 textureHeight);