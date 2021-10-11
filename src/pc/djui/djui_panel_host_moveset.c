#include <stdio.h>
#include "djui.h"
#include "game/save_file.h"
#include "pc/configfile.h"

void djui_panel_host_moveset_create(struct DjuiBase* caller) {
    f32 bodyHeight = 32 * 5 + 64 * 1 + 16 * 6;

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\M\\#1be700\\O\\#00b3ff\\V\\#ffef00\\E\\#ff0800\\S\\#1be700\\E\\#00b3ff\\T");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);
    {
        struct DjuiCheckbox* checkbox1 = djui_checkbox_create(&body->base, "Enable Wallslide", &configMoveset.wallslide);
        djui_base_set_size_type(&checkbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox1->base, 1.0f, 32);

        struct DjuiCheckbox* checkbox2 = djui_checkbox_create(&body->base, "Enable Groundpound Jump", &configMoveset.ground_pound_jump);
        djui_base_set_size_type(&checkbox2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox2->base, 1.0f, 32);

        struct DjuiCheckbox* checkbox3 = djui_checkbox_create(&body->base, "Enable Sunshine Dive", &configMoveset.sunshine_dive);
        djui_base_set_size_type(&checkbox3->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox3->base, 1.0f, 32);

        struct DjuiCheckbox* checkbox4 = djui_checkbox_create(&body->base, "Enable Odyssey Dive", &configMoveset.odyssey_dive);
        djui_base_set_size_type(&checkbox4->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox4->base, 1.0f, 32);

        struct DjuiCheckbox* checkbox5 = djui_checkbox_create(&body->base, "Enable Flashback Pound", &configMoveset.flashback_pound);
        djui_base_set_size_type(&checkbox5->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox5->base, 1.0f, 32);
    }

    djui_panel_add(caller, &panel->base, defaultBase);
}
