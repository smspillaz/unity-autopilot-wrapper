/*
 * compiz_autopilot_tests.h
 *
 * An array of autopilot tests relevant to compiz.
 *
 * See LICENSE.md for Copyright information
 */

#ifndef UAW_COMPIZ_AUTOPILOT_TESTS_H
#define UAW_COMPIZ_AUTOPILOT_TESTS_H

namespace
{
    char const * AutopilotTests[] =
    {
        "unity.tests.launcher.test_icon_behavior.LauncherIconsTests.test_clicking_icon_twice_initiates_spread",
        "unity.tests.launcher.test_icon_behavior.LauncherIconsTests.test_expo_launcher_icon_initiates_expo",
        "unity.tests.launcher.test_icon_behavior.LauncherIconsTests.test_expo_launcher_icon_terminates_expo",
        "unity.tests.launcher.test_icon_behavior.LauncherIconsTests.test_launcher_activate_last_focused_window",
        "unity.tests.launcher.test_icon_behavior.LauncherIconsTests.test_unminimize_initially_minimized_windows",
        "unity.tests.launcher.test_icon_behavior.LauncherIconsTests.test_unminimize_minimized_immediately_after_show_windows",
        "unity.tests.launcher.test_icon_behavior.LauncherIconsTests.test_while_in_scale_mode_the_dash_will_still_open",
        "unity.tests.test_dash.DashRevealWithSpreadTests.test_command_lens_opens_when_in_spread",
        "unity.tests.test_dash.DashRevealWithSpreadTests.test_dash_closes_on_spread",
        "unity.tests.test_dash.DashRevealWithSpreadTests.test_dash_opens_when_in_spread",
        "unity.tests.test_dash.DashRevealWithSpreadTests.test_lens_opens_when_in_spread",
        "unity.tests.test_hud.HudBehaviorTests.test_alt_arrow_keys_not_eaten",
        "unity.tests.test_panel.PanelCrossMonitorsTests.test_panel_title_updates_moving_window",
        "unity.tests.test_panel.PanelCrossMonitorsTests.test_window_buttons_close_inactive_when_clicked_in_another_monitor",
        "unity.tests.test_panel.PanelCrossMonitorsTests.test_window_buttons_dont_show_for_maximized_window_on_mouse_in",
        "unity.tests.test_panel.PanelCrossMonitorsTests.test_window_buttons_dont_show_in_other_monitors_when_dash_is_open",
        "unity.tests.test_panel.PanelCrossMonitorsTests.test_window_buttons_dont_show_in_other_monitors_when_hud_is_open",
        "unity.tests.test_panel.PanelCrossMonitorsTests.test_window_buttons_minimize_inactive_when_clicked_in_another_monitor",
        "unity.tests.test_panel.PanelCrossMonitorsTests.test_window_buttons_unmaximize_inactive_when_clicked_in_another_monitor",
        "unity.tests.test_panel.PanelGrabAreaTests.test_focus_the_maximized_window_works",
        "unity.tests.test_panel.PanelGrabAreaTests.test_lower_the_maximized_window_works",
        "unity.tests.test_panel.PanelGrabAreaTests.test_panels_dont_steal_keynav_foucs_from_hud",
        "unity.tests.test_panel.PanelGrabAreaTests.test_unmaximize_from_grab_area_works",
        "unity.tests.test_panel.PanelHoverTests.test_menus_show_for_maximized_window_on_mouse_in_btn_area",
        "unity.tests.test_panel.PanelHoverTests.test_menus_show_for_maximized_window_on_mouse_in_grab_area",
        "unity.tests.test_panel.PanelHoverTests.test_menus_show_for_maximized_window_on_mouse_in_menu_area",
        "unity.tests.test_panel.PanelHoverTests.test_only_menus_show_for_restored_window_on_mouse_in_grab_area",
        "unity.tests.test_panel.PanelHoverTests.test_only_menus_show_for_restored_window_on_mouse_in_menu_area",
        "unity.tests.test_panel.PanelHoverTests.test_only_menus_show_for_restored_window_on_mouse_in_window_btn_area",
        "unity.tests.test_panel.PanelMenuTests.test_menus_dont_show_for_maximized_window_on_mouse_out",
        "unity.tests.test_panel.PanelMenuTests.test_menus_dont_show_for_restored_window_on_mouse_out",
        "unity.tests.test_panel.PanelMenuTests.test_menus_dont_show_if_a_new_application_window_is_opened",
        "unity.tests.test_panel.PanelMenuTests.test_menus_show_for_maximized_window_on_mouse_in",
        "unity.tests.test_panel.PanelMenuTests.test_menus_show_for_restored_window_on_mouse_in",
        "unity.tests.test_panel.PanelMenuTests.test_menus_shows_when_new_application_is_opened",
        "unity.tests.test_panel.PanelTitleTests.test_panel_shows_app_title_with_maximised_app",
        "unity.tests.test_panel.PanelTitleTests.test_panel_title_doesnt_change_with_switcher",
        "unity.tests.test_panel.PanelTitleTests.test_panel_title_on_empty_desktop",
        "unity.tests.test_panel.PanelTitleTests.test_panel_title_updates_on_maximized_window_title_changes",
        "unity.tests.test_panel.PanelTitleTests.test_panel_title_updates_when_switching_to_maximized_app",
        "unity.tests.test_panel.PanelTitleTests.test_panel_title_with_maximized_application",
        "unity.tests.test_panel.PanelTitleTests.test_panel_title_with_maximized_window_restored_child",
        "unity.tests.test_panel.PanelTitleTests.test_panel_title_with_restored_application",
        "unity.tests.test_panel.PanelWindowButtonsTests.test_double_click_unmaximize_window",
        "unity.tests.test_panel.PanelWindowButtonsTests.test_minimize_button_disabled_for_non_minimizable_windows",
        "unity.tests.test_panel.PanelWindowButtonsTests.test_window_buttons_dont_show_for_maximized_window_on_mouse_out",
        "unity.tests.test_panel.PanelWindowButtonsTests.test_window_buttons_dont_show_for_restored_window",
        "unity.tests.test_panel.PanelWindowButtonsTests.test_window_buttons_dont_show_for_restored_window_with_mouse_in_panel",
        "unity.tests.test_panel.PanelWindowButtonsTests.test_window_buttons_dont_show_on_empty_desktop",
        "unity.tests.test_panel.PanelWindowButtonsTests.test_window_buttons_minimize_button_works_for_window",
        "unity.tests.test_panel.PanelWindowButtonsTests.test_window_buttons_show_for_maximized_window_on_mouse_in",
        "unity.tests.test_panel.PanelWindowButtonsTests.test_window_buttons_unmaximize_button_works_for_window",
        "unity.tests.test_panel.PanelWindowButtonsTests.test_window_buttons_unmaximize_follows_fitts_law",
        "unity.tests.test_showdesktop.ShowDesktopTests.test_showdesktop_hides_apps",
        "unity.tests.test_showdesktop.ShowDesktopTests.test_showdesktop_switcher",
        "unity.tests.test_showdesktop.ShowDesktopTests.test_showdesktop_unhides_apps",
        "unity.tests.test_showdesktop.ShowDesktopTests.test_unhide_single_app",
        "unity.tests.test_spread.SpreadTests.test_scale_application_windows",
        "unity.tests.test_spread.SpreadTests.test_scaled_window_closes_on_close_button_click",
        "unity.tests.test_spread.SpreadTests.test_scaled_window_closes_on_middle_click",
        "unity.tests.test_spread.SpreadTests.test_scaled_window_is_focused_on_click",
        "unity.tests.test_switcher.SwitcherDetailsModeTests.test_detail_mode_selects_last_active_window",
        "unity.tests.test_switcher.SwitcherDetailsModeTests.test_detail_mode_selects_third_window",
        "unity.tests.test_switcher.SwitcherDetailsTests.test_no_details_for_apps_on_different_workspace",
        "unity.tests.test_switcher.SwitcherTests.test_application_window_is_fake_decorated",
        "unity.tests.test_switcher.SwitcherTests.test_application_window_is_fake_decorated_in_detail_mode",
        "unity.tests.test_switcher.SwitcherWindowsManagementTests.test_switcher_raises_only_last_focused_window",
        "unity.tests.test_switcher.SwitcherWindowsManagementTests.test_switcher_rises_next_window_of_same_application",
        "unity.tests.test_switcher.SwitcherWindowsManagementTests.test_switcher_rises_other_application",
        "unity.tests.test_switcher.SwitcherWorkspaceTests.test_switcher_all_mode_shows_all_apps",
        "unity.tests.test_switcher.SwitcherWorkspaceTests.test_switcher_can_switch_to_minimised_window",
        "unity.tests.test_switcher.SwitcherWorkspaceTests.test_switcher_is_disabled_when_wall_plugin_active",
        "unity.tests.test_switcher.SwitcherWorkspaceTests.test_switcher_shows_current_workspace_only"
    };
}
#endif
