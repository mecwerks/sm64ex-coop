#include "djui.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"

static void djui_panel_newoptions_apply(UNUSED struct DjuiBase* caller) {
    configWindow.settings_changed = true;
}

void djui_panel_newoptions_create(struct DjuiBase* caller) {
    f32 bodyHeight = 32 * 7 + 64 * 1 + 16 * 6;

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\D\\#1be700\\I\\#00b3ff\\S\\#ffef00\\P\\#ff0800\\L\\#1be700\\A\\#00b3ff\\Y");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);

    {
        struct DjuiCheckbox* checkbox1 = djui_checkbox_create(&body->base, "Paper Mode", &configNewOptions.paper_mode);
        djui_base_set_size_type(&checkbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox1->base, 1.0f, 32);
        djui_interactable_hook_value_change(&checkbox1->base, djui_panel_newoptions_apply);
        defaultBase = &checkbox1->base;

        struct DjuiButton* button6 = djui_button_create(&body->base, "Back");
        djui_base_set_size_type(&button6->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button6->base, 1.0f, 64);
        djui_button_set_style(button6, 1);
        djui_interactable_hook_click(&button6->base, djui_panel_menu_back);
    }

    djui_panel_add(caller, &panel->base, defaultBase);
}
