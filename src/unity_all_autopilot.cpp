/*
 * unity_all_autopilot.cpp
 *
 * Instantiate all the autopilot tests
 *
 * Do not add this file to vera++ checks.
 *
 * See LICENSE.md for Copyright information.
 */

#include <gtest/gtest.h>
#include "listtests.h"
#include "unity_autopilot_test.h"

using namespace unity::autopilot_wrapper;

INSTANTIATE_TEST_CASE_P (LauncherCapture, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.launcher.test_capture"));
INSTANTIATE_TEST_CASE_P (LauncherIconBehavior, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.launcher.test_icon_behavior"));
INSTANTIATE_TEST_CASE_P (LauncherKeynav, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.launcher.test_keynav"));
INSTANTIATE_TEST_CASE_P (LauncherReveal, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.launcher.test_reveal"));
INSTANTIATE_TEST_CASE_P (LauncherShortcut, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.launcher.test_shortcut"));
INSTANTIATE_TEST_CASE_P (LauncherSwitcher, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.launcher.test_swither"));
INSTANTIATE_TEST_CASE_P (LauncherVisual, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.launcher.test_visual"));
INSTANTIATE_TEST_CASE_P (CommandLens, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_command_lens"));
INSTANTIATE_TEST_CASE_P (DashCategoryHeader, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_dash.CategoryHeaderTests"));
INSTANTIATE_TEST_CASE_P (DashBorder, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_dash.DashBorderTests"));
INSTANTIATE_TEST_CASE_P (DashClipboard, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_dash.DashClipboardTests"));
INSTANTIATE_TEST_CASE_P (DashCrossMonitors, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_dash.DashCrossMonitorsTests"));
INSTANTIATE_TEST_CASE_P (DashDBusIface, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_dash.DashDBusIfaceTests"));
INSTANTIATE_TEST_CASE_P (DashKeyNav, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_dash.DashKeyNavTests"));
INSTANTIATE_TEST_CASE_P (DashKeyboardFocus, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_dash.DashKeyboardFocusTests"));
INSTANTIATE_TEST_CASE_P (DashLensResults, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_dash.DashLensResultsTests"));
INSTANTIATE_TEST_CASE_P (DashMultiKey, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_dash.DashMultiKeyTests"));
INSTANTIATE_TEST_CASE_P (DashReveal, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_dash.DashRevealTests"));
INSTANTIATE_TEST_CASE_P (DashRevealWithSpread, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_dash.DashRevealWithSpreadTests"));
INSTANTIATE_TEST_CASE_P (DashSearchInput, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_dash.DashSearchInputTests"));
INSTANTIATE_TEST_CASE_P (DashVisual, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_dash.DashVisualTests"));
INSTANTIATE_TEST_CASE_P (DashPreviewClickCancel, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_dash.PreviewClickCancelTests"));
INSTANTIATE_TEST_CASE_P (DashPreviewInvocation, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_dash.PreviewInvocationTests"));
INSTANTIATE_TEST_CASE_P (GObjectIntrospection, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_gobject_introspection"));
INSTANTIATE_TEST_CASE_P (HomeLens, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_home_lens"));
INSTANTIATE_TEST_CASE_P (HudAlternativeKeybindings, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_hud.HudAlternativeKeybindingsTests"));
INSTANTIATE_TEST_CASE_P (HudBehavior, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_hud.HudBehaviorTests"));
INSTANTIATE_TEST_CASE_P (HudCrossMonitors, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_hud.HudCrossMonitorsTests"));
INSTANTIATE_TEST_CASE_P (HudLauncherInteractions, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_hud.HudLauncherInteractionsTests"));
INSTANTIATE_TEST_CASE_P (HudLockedLauncherInteractions, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_hud.HudLockedLauncherInteractionsTests"));
INSTANTIATE_TEST_CASE_P (HudVisual, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_hud.HudVisualTests"));
INSTANTIATE_TEST_CASE_P (IBusAnthyIgnore, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_ibus.IBusTestsAnthyIgnore"));
INSTANTIATE_TEST_CASE_P (IBusHangulIgnore, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_ibus.IBusTestsHangulIgnore"));
INSTANTIATE_TEST_CASE_P (IBusPinyinIgnore, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_ibus.IBusTestsPinyinIgnore"));
INSTANTIATE_TEST_CASE_P (PanelCrossMonitors, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_panel.PanelCrossMonitorsTests"));
INSTANTIATE_TEST_CASE_P (PanelGrabArea, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_panel.PanelGrabAreaTests"));
INSTANTIATE_TEST_CASE_P (PanelHover, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_panel.PanelHoverTests"));
INSTANTIATE_TEST_CASE_P (PanelIndicatorEntry, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_panel.PanelIndicatorEntryTests"));
INSTANTIATE_TEST_CASE_P (PanelKeyNavigation, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_panel.PanelKeyNavigationTests"));
INSTANTIATE_TEST_CASE_P (PanelMenu, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_panel.PanelMenuTests"));
INSTANTIATE_TEST_CASE_P (PanelTitle, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_panel.PanelTitleTests"));
INSTANTIATE_TEST_CASE_P (PanelWindowButtons, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_panel.PanelWindowButtonsTests"));
INSTANTIATE_TEST_CASE_P (QuicklistAction, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_quicklist.QuicklistActionTests"));
INSTANTIATE_TEST_CASE_P (QuicklistKeyNavigation, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_quicklist.QuicklistKeyNavigationTests"));
INSTANTIATE_TEST_CASE_P (ApplicationLensSearch, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_search.ApplicationLensSearchTests"));
INSTANTIATE_TEST_CASE_P (ShoppingLens, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_shopping_lens.ShoppingLensTests"));
INSTANTIATE_TEST_CASE_P (ShortcutHintInteractions, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_shortcut_hint.ShortcutHintInteractionsTests"));
INSTANTIATE_TEST_CASE_P (ShortcutHint, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_shortcut_hint.ShortcutHintTests"));
INSTANTIATE_TEST_CASE_P (ShowDesktop, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_showdesktop.ShowDesktopTests"));
INSTANTIATE_TEST_CASE_P (Spread, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_spread.SpreadTests"));
INSTANTIATE_TEST_CASE_P (SwitcherDetailsMode, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_switcher.SwitcherDetailsModeTests"));
INSTANTIATE_TEST_CASE_P (Switcher, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_switcher.SwitcherTests"));
INSTANTIATE_TEST_CASE_P (SwitcherWindowsManagement, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_switcher.SwitcherWindowsManagementTests"));
INSTANTIATE_TEST_CASE_P (SwitcherWorkspace, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_switcher.SwitcherWorkspaceTests"));
INSTANTIATE_TEST_CASE_P (UnityLogging, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.test_unity_logging.UnityLoggingTests"));
INSTANTIATE_TEST_CASE_P (XIM, Autopilot,
                         AllAutopilotTestsIn ("unity.tests.xim.test_gcin"));
