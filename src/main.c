#include <pebble.h>

//Stuff for first window
static TextLayer *s_welcome_layer;
static TextLayer *s_welcome_layer_begin;
static Window *s_welcome_window;
static GFont s_welcome_font;
static GFont s_welcome_begin_font;

//Stuff for second window
static Window *s_timer_window;

//loads welcome window layers
static void welcome_window_load(Window *window) {
  //intialize fonts
  s_welcome_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_HELVETICA_CHILDREN_18));
  s_welcome_begin_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_HELVETICA_CHILDREN_12));
  
  Layer *window_layer = window_get_root_layer(window);
  //gets the boundaries based on type of watch
  GRect bounds = layer_get_bounds(window_layer); 
  
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

//destroys layers in welcome window
static void welcome_window_unload(Window *window) {
  text_layer_destroy(s_welcome_layer);
  text_layer_destroy(s_welcome_layer_begin);
}

//switches the screen to the timer
static void display_timer_screen(void) {
  window_stack_push(s_timer_window, false);
}

//calls the switching function when a single click detected
static void select_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  display_timer_screen();
}

//define the types of clicks
static void config_provider(Window *window) {  
  //single click configs
  window_single_click_subscribe(BUTTON_ID_SELECT, (ClickHandler) select_single_click_handler);
}

//Functions relating to second window

//initializes layers 
static void timer_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  //gets the boundaries based on type of watch
  GRect bounds = layer_get_bounds(window_layer);
}

//destroys layers
static void timer_window_unload(Window *window) {
  
}


//initialize all windows
static void init() { 
  //create the welcome window
  s_welcome_window = window_create();
  s_timer_window = window_create();
  
  //set the background for the windows
  window_set_background_color(s_welcome_window, GColorVividCerulean);
  window_set_background_color(s_timer_window, GColorVividCerulean);
  
  //set handlers so you can do stuff within the welcome window
  window_set_window_handlers(s_welcome_window, (WindowHandlers) {
    .load = welcome_window_load,
    .unload = welcome_window_unload
  });
  //set handlers so you can do stuff within the timer window
  window_set_window_handlers(s_timer_window, (WindowHandlers) {
    .load = timer_window_load,
    .unload = timer_window_unload
  });
  
  //sets up button functionality for welcome window
    window_set_click_config_provider(s_welcome_window, (ClickConfigProvider) config_provider);
  
  //display the welcome window by pushing it onto the stack
  window_stack_push(s_welcome_window, true);

}

//uninitialize all windows
static void deinit() {
  window_destroy(s_welcome_window);
  window_destroy(s_timer_window);
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