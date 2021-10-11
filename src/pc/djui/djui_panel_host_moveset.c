#include <stdio.h>
#include "djui.h"
#include "game/save_file.h"
#include "pc/configfile.h"

#define checkbox(parent, title, var) \
    { \
        struct DjuiCheckbox *chkbx = djui_checkbox_create(parent, title, var); \
        djui_base_set_size_type(&chkbx->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE); \
        djui_base_set_size(&chkbx->base, 1.0f, 32); \
    }

void djui_panel_host_moveset_create(struct DjuiBase* caller) {
    f32 bodyHeight = 32 * 11 + 64 * 1 + 16 * 12;

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\M\\#1be700\\O\\#00b3ff\\V\\#ffef00\\E\\#ff0800\\S\\#1be700\\E\\#00b3ff\\T");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);
    {
        checkbox(&body->base, "Enable Wallslide", &configMoveset.wallslide)
        checkbox(&body->base, "Enable Groundpound Jump", &configMoveset.ground_pound_jump)
        checkbox(&body->base, "Enable Sunshine Dive", &configMoveset.sunshine_dive)
        checkbox(&body->base, "Enable Odyssey Dive", &configMoveset.odyssey_dive)
        checkbox(&body->base, "Enable Flashback Pound", &configMoveset.flashback_pound)
        checkbox(&body->base, "Improved Movement", &configMoveset.improvedMovement)
        checkbox(&body->base, "Improved Swimming", &configMoveset.improvedSwimming)
        checkbox(&body->base, "Improved Hanging", &configMoveset.improvedHanging)
        checkbox(&body->base, "Enemy Bouncing", &configMoveset.enemyBouncing)
        checkbox(&body->base, "Full Air Control", &configMoveset.fullAirControl)
        checkbox(&body->base, "Disable Backwards Long-Jump", &configMoveset.disableBLJ)

        struct DjuiButton* button1 = djui_button_create(&body->base, "Back");
        djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button1->base, 1.0f, 64);
        djui_button_set_style(button1, 1);
        djui_interactable_hook_click(&button1->base, djui_panel_menu_back);
    }

    djui_panel_add(caller, &panel->base, defaultBase);
}
