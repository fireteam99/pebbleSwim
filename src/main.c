#include <pebble.h>

Window *window;
static Window *s_main_window;
TextLayer *text_layer;

static void main_window_load(Window *window) {
  
}

static void main_window_unload(Window *window) {
  
}

//initialize window
static void init() { 
  //create the main window
  s_main_window = window_create();
  
  //set handlers so you can do stuff within the window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  
  //display the main window by pushing it onto the stack
  window_stack_push(s_main_window, true);

}

//uninitialize window
static void deinit() {
  window_destroy(s_main_window);
}

int main() {
  //initializes app
  init();
  
  //Waits for app events
  app_event_loop();
  
  //denitialize app
  deinit();
  
  return 0;
}  