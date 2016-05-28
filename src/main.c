#include <pebble.h>

static TextLayer *s_welcome_layer;
static Window *s_main_window;

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer); //gets the boundaries based on type of watch
  
  //sets the textlayer to the constraints
  s_welcome_layer = text_layer_create(
      GRect(0, PBL_IF_ROUND_ELSE(58, 52), bounds.size.w, 50));
  
  //Format the text layout
  text_layer_set_background_color(s_welcome_layer, GColorFromRGB(0, 170, 255));
  text_layer_set_text(s_welcome_layer, "Welcome to Pebble Swim");
  text_layer_set_text_color(s_welcome_layer, GColorWhite);
  text_layer_set_font(s_welcome_layer, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));
  text_layer_set_text_alignment(s_welcome_layer, GTextAlignmentCenter);
  
  //Add the text layer to the root layer
  layer_add_child(window_layer, text_layer_get_layer(s_welcome_layer));
}

static void main_window_unload(Window *window) {
  text_layer_destroy(s_welcome_layer);
}

//initialize window
static void init() { 
  //create the main window
  s_main_window = window_create();
  
  //set the background for the window
  window_set_background_color(s_main_window, GColorVividCerulean);
  
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