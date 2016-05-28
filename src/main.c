#include <pebble.h>

static TextLayer *s_welcome_layer;
static TextLayer *s_welcome_layer_begin;
static Window *s_main_window;
static GFont s_welcome_font;
static GFont s_welcome_begin_font;

static void main_window_load(Window *window) {  
  s_welcome_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_HELVETICA_CHILDREN_18));
  s_welcome_begin_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_HELVETICA_CHILDREN_12));
  
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer); //gets the boundaries based on type of watch
  
  //sets the textlayer to the constraints
  s_welcome_layer = text_layer_create(
      GRect(0, PBL_IF_ROUND_ELSE(58, 52), bounds.size.w, 50));
  s_welcome_layer_begin = text_layer_create(
      GRect(0, PBL_IF_ROUND_ELSE(58, 120), bounds.size.w, 50));
  
  //Format the text layout
  text_layer_set_background_color(s_welcome_layer, GColorClear);
  text_layer_set_text(s_welcome_layer, "Welcome to Pebble Swim");
  text_layer_set_text_color(s_welcome_layer, GColorWhite);
  text_layer_set_font(s_welcome_layer, s_welcome_font);
  text_layer_set_text_alignment(s_welcome_layer, GTextAlignmentCenter);
  
  text_layer_set_background_color(s_welcome_layer_begin, GColorClear);
  text_layer_set_text(s_welcome_layer_begin, "Press Select");
  text_layer_set_text_color(s_welcome_layer_begin, GColorWhite);
  text_layer_set_font(s_welcome_layer_begin, s_welcome_begin_font);
  text_layer_set_text_alignment(s_welcome_layer_begin, GTextAlignmentCenter);
  
  //Add the text layer to the root layer
  layer_add_child(window_layer, text_layer_get_layer(s_welcome_layer));
  layer_add_child(window_layer, text_layer_get_layer(s_welcome_layer_begin));
}

static void main_window_unload(Window *window) {
  text_layer_destroy(s_welcome_layer);
  text_layer_destroy(s_welcome_layer_begin);
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