/*
 * CustomView --
 * Copyright (C) 2013 HAYASHI Kentaro
 *
 */

#include "config.h"
#include <glib.h>
#include <glib/gi18n-lib.h>
#include <glib/gprintf.h>
#include <gtk/gtk.h>
#include <libintl.h>

#define PLUGIN_NAME N_("CustomView")
#define PLUGIN_DESC N_("Customize view plugin for Sylpheed")

#include "sylmain.h"
#include "plugin.h"
#include "alertpanel.h"
#include "foldersel.h"
#include "headerview.h"
#include "messageview.h"
#include "procheader.h"

#include "copying.h"
#include "sylplugin_factory.h"
#include "customview.h"

static SylPluginInfo info = {
  N_(PLUGIN_NAME),
  VERSION,
  "HAYASHI Kentaro",
  N_(PLUGIN_DESC)
};

static CustomViewOption option;


void plugin_load(void)
{
  gpointer user_data;

  SYLPF_START_FUNC;

  syl_init_gettext(CUSTOMVIEW, "lib/locale");

  syl_plugin_add_menuitem("/Tools", NULL, NULL, NULL);
  syl_plugin_add_menuitem("/Tools",
                          _("CustomView [customview]"),
                          exec_customview_menu_cb, NULL);
  g_signal_connect_after(syl_app_get(),
                         "init-done",
                         G_CALLBACK(init_done_cb),
                         NULL);

  user_data = &option;
  sylpf_load_option_rcfile((SylPluginFactoryOption*)user_data,
                           CUSTOMVIEW_RC);
  option.hide_folderview_flag = g_key_file_get_boolean(option.rcfile,
                                                       SYLPF_ID,
                                                       OPTION_HIDE_FOLDERVIEW,
                                                       NULL);
  SYLPF_END_FUNC;
}

void plugin_unload(void)
{
  SYLPF_START_FUNC;
  SYLPF_END_FUNC;
}

SylPluginInfo *plugin_info(void)
{
  return &info;
}

gint plugin_interface_version(void)
{
    return 0x0108;
    /* return SYL_PLUGIN_INTERFACE_VERSION; */
}

static void init_done_cb(GObject *obj, gpointer data)
{
  SYLPF_START_FUNC;

  sylpf_update_folderview_visibility(!option.hide_folderview_flag);

  SYLPF_END_FUNC;
}

static void exec_customview_menu_cb(void)
{
  GtkWidget *dialog;
  gint response;

  SYLPF_START_FUNC;

  dialog = create_preference_dialog(&option);

  gtk_widget_show_all(dialog);
  response = gtk_dialog_run(GTK_DIALOG(dialog));

  switch (response) {
  case GTK_RESPONSE_OK:
    save_preference_dialog(&option);
    break;
  case GTK_RESPONSE_CANCEL:
  default:
    break;
  }

  gtk_widget_destroy(dialog);

  SYLPF_END_FUNC;
}

static GtkWidget *create_preference_dialog(CustomViewOption *option)
{
  GtkWidget *vbox, *hbox;
  GtkWidget *dialog;
  gpointer mainwin;
  GtkWidget *window;
  GtkWidget *notebook;

  SYLPF_START_FUNC;

  mainwin = syl_plugin_main_window_get();
  window = ((MainWindow*)mainwin)->window;

  dialog = gtk_dialog_new_with_buttons(_("CustomView"),
                                       GTK_WINDOW(window),
                                       GTK_DIALOG_MODAL,
                                       GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                       GTK_STOCK_OK, GTK_RESPONSE_OK,
                                       NULL);

  sylpf_init_preference_dialog_size(dialog);

  vbox = gtk_vbox_new(FALSE, SYLPF_BOX_SPACE);
  hbox = gtk_hbox_new(TRUE, SYLPF_BOX_SPACE);

  gtk_container_add(GTK_CONTAINER(hbox), vbox);
  gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), hbox);

  notebook = gtk_notebook_new();
  create_config_main_page(notebook, option);
  sylpf_append_config_about_page(notebook,
                                 option->rcfile,
                                 _("About"),
                                 _(PLUGIN_NAME),
                                 _(PLUGIN_DESC),
                                 _(copyright));

  gtk_widget_show(notebook);
  gtk_box_pack_start(GTK_BOX(vbox), notebook, TRUE, TRUE, 0);
  gtk_box_set_spacing(GTK_BOX(GTK_DIALOG(dialog)->vbox), SYLPF_BOX_SPACE);

  SYLPF_RETURN_VALUE(dialog);
}

static void create_config_main_page(GtkWidget *notebook,
                                    CustomViewOption *option)
{
  GtkWidget *vbox;
  GtkWidget *folderview;
  GtkWidget *label;

  SYLPF_START_FUNC;

  vbox = gtk_vbox_new(FALSE, SYLPF_BOX_SPACE);

  option->hide_folderview = gtk_check_button_new_with_label(_("Hide folder view"));
  folderview = sylpf_pack_widget_with_aligned_frame(option->hide_folderview, _("View option"));

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(option->hide_folderview),
                               option->hide_folderview_flag);

  gtk_box_pack_start(GTK_BOX(vbox), folderview, FALSE, FALSE, 0);

  label = gtk_label_new(_("General"));
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vbox, label);
  gtk_widget_show_all(notebook);

  SYLPF_END_FUNC;
}


static void save_preference_dialog(CustomViewOption *option)
{
  gboolean flag;

  SYLPF_START_FUNC;

  flag = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(option->hide_folderview));
  option->hide_folderview_flag = flag;

  g_key_file_set_boolean(option->rcfile,
                         SYLPF_ID,
                         OPTION_HIDE_FOLDERVIEW,
                         option->hide_folderview_flag);

  sylpf_save_option_rcfile((SylPluginFactoryOption*)option);

  sylpf_update_folderview_visibility(!flag);

  SYLPF_END_FUNC;
}
