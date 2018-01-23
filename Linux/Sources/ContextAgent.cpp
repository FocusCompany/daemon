//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <libwnck/libwnck.h>
#include <FocusSerializer.hpp>
#include "ContextAgent.hpp"
#include "FocusContextEventPayload.pb.h"

static ContextAgent *ca_instance;

static void window_switch_handler(
  WnckScreen *screen,
  WnckWindow *previously_active_window,
  gpointer user_data
) {
  (void)previously_active_window, (void)user_data;
  WnckWindow *active_window;
  GList *window_l;
  WnckWindow *window;
  char const *winname;

  wnck_screen_force_update(screen);
  active_window = wnck_screen_get_active_window(screen);
  for (
    window_l = wnck_screen_get_windows (screen);
    window_l != NULL;
    window_l = window_l->next
  ) {
    window = WNCK_WINDOW(window_l->data);
    winname = wnck_window_get_name(window);
    if (window == active_window)
    {
      g_print("%s%s\n", winname, " (active)");
      ca_instance->OnContextChanged("", winname);
    }
    else
      g_print("%s\n", winname);
  }
}

ContextAgent::ContextAgent() {
  ca_instance = this;
}

ContextAgent::~ContextAgent() {}

void ContextAgent::Run() {
  WnckScreen *screen;

  gtk_init_check(NULL, NULL);
  screen = wnck_screen_get_default();
  while (gtk_events_pending())
    gtk_main_iteration();
  g_signal_connect(
    screen,
    "active-window-changed",
    G_CALLBACK(window_switch_handler),
    NULL
  );
  gtk_main();
}

void ContextAgent::OnContextChanged(const std::string &processName, const std::string &windowTitle) const {
    Focus::ContextEventPayload context;
    context.set_processname(processName);
    context.set_windowname(windowTitle);

    Focus::Event event = FocusSerializer::CreateEventFromContext("OnWindowsContextChanged", context);

    _eventEmitter->Emit("OnWindowsContextChanged", event);
}