#ifndef __SYLPF_CUSTOMVIEW_H_INCLUDED__
#define __SYLPF_CUSTOMVIEW_H_INCLUDED__

#define CUSTOMVIEW "customview"
#define CUSTOMVIEW_RC "customviewrc"

#define OPTION_HIDE_FOLDERVIEW "hide-folderview"

typedef struct _CustomViewOption CustomViewOption;

struct _CustomViewOption {
  /* General section */
  /* full path to ghostbiffrc*/
  gchar *rcpath;
  /* rcfile */
  GKeyFile *rcfile;

  GtkWidget *hide_folderview;
  gboolean hide_folderview_flag;
};

static void init_done_cb(GObject *obj, gpointer data);
static void exec_customview_menu_cb(void);
static GtkWidget *create_preference_dialog(CustomViewOption *option);
static void create_config_main_page(GtkWidget *notebook,
                                      CustomViewOption *option);
static void save_preference_dialog(CustomViewOption *option);

#endif
