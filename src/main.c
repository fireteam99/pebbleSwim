#include <pebble.h>

//make sure the js file is ready to be loaded
typedef enum {
  AppKeyReady = 0
} AppKey;

static void inbox_received_handler(DictionaryIterator *iter, void *context) {
  Tuple *ready_tuple = dict_find(iter, AppKeyReady);
  if(ready_tuple) {
    // PebbleKit JS is ready! Safe to send messages
    // run initialization functions
  }
}

//Stuff for first window
static TextLayer *s_welcome_layer;
static TextLayer *s_welcome_layer_begin;
static Window *s_welcome_window;
static GFont s_welcome_font;
static GFont s_welcome_begin_font;

//Stuff for second window
static Window *s_timer_window;
static TextLayer *s_timer_layer;
static TextLayer *s_completion_layer;
static TextLayer *s_info_layer;
static GFont s_timer_font;
static GFont s_completion_font;
static GFont s_info_font;


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
  fonts_unload_custom_font(s_welcome_font);
  fonts_unload_custom_font(s_welcome_begin_font);
}

//switches the screen to the timer
static void display_timer_screen(void) {
  window_stack_push(s_timer_window, false);
}

//calls the switching function when a single click detected
static void select_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  display_timer_screen();
}

//define the types of clicks for welcome
static void config_provider_welcome(Window *window) {  
  //single click configs
  window_single_click_subscribe(BUTTON_ID_SELECT, (ClickHandler) select_single_click_handler);
}


//Functions relating to second window

//initializes timer layers 
static void timer_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  
  //gets the boundaries based on type of watch
  GRect bounds = layer_get_bounds(window_layer);
  
  //creates and sets the textlayers to the constraints
  s_timer_layer = text_layer_create(
      GRect(0, PBL_IF_ROUND_ELSE(58, 52), bounds.size.w, 50));
  s_completion_layer = text_layer_create(
      GRect(0, PBL_IF_ROUND_ELSE(58, 120), bounds.size.w, 50));
  s_info_layer = text_layer_create(
      GRect(0, PBL_IF_ROUND_ELSE(58, 25), bounds.size.w, 50));
  
  
  //initialize custom fonts
  s_timer_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_MECHANICAL_OUT_OBL_40));
  s_completion_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_MECHANICAL_OUT_OBL_18));
  s_info_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_MECHANICAL_OUT_OBL_16));
  
  
  //format text layouts
  text_layer_set_background_color(s_timer_layer, GColorClear);
  text_layer_set_text(s_timer_layer, "00:00");
  text_layer_set_text_color(s_timer_layer, GColorWhite);
  text_layer_set_font(s_timer_layer, s_timer_font);
  text_layer_set_text_alignment(s_timer_layer, GTextAlignmentCenter);
  
  text_layer_set_background_color(s_info_layer, GColorClear);
  text_layer_set_text(s_info_layer, "100 Free");
  text_layer_set_text_color(s_info_layer, GColorWhite);
  text_layer_set_font(s_info_layer, s_info_font);
  text_layer_set_text_alignment(s_info_layer, GTextAlignmentCenter);
  
  text_layer_set_background_color(s_completion_layer, GColorClear);
  text_layer_set_text(s_completion_layer, "4/5");
  text_layer_set_text_color(s_completion_layer, GColorWhite);
  text_layer_set_font(s_completion_layer, s_completion_font);
  text_layer_set_text_alignment(s_completion_layer, GTextAlignmentCenter);
  
  //Add the text layer to the root layer
  layer_add_child(window_layer, text_layer_get_layer(s_timer_layer));
  layer_add_child(window_layer, text_layer_get_layer(s_info_layer));
  layer_add_child(window_layer, text_layer_get_layer(s_completion_layer));
}

//streams data from the phone to the watch
static void update_timer() {
  //variables streamed from the phone
  //write them into textlayers
}

//destroys timer layers/fonts
static void timer_window_unload(Window *window) {
  text_layer_destroy(s_timer_layer);
  text_layer_destroy(s_info_layer);
  text_layer_destroy(s_completion_layer);
  
  fonts_unload_custom_font(s_timer_font);
  fonts_unload_custom_font(s_completion_font);
  fonts_unload_custom_font(s_info_font);

}

//creates the tick handler
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_timer();
}

//defines the up click
static void up_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  //calls function to pass boolean
}

//defines the down click
static void down_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  //calls function to pass boolean
}

//define the types of clicks for timer
static void config_provider_welcome(Window *window) {  
  //single click configs
  window_single_click_subscribe(BUTTON_ID_SELECT, (ClickHandler) up_single_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, (ClickHandler) down_single_click_handler);
}


//initialize all windows
static void init() { 
  //initializes ticker time services
  tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
  
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
  window_set_click_config_provider(s_welcome_window, (ClickConfigProvider) config_provider_welcome);
  
  //set up button functionality for timer window
  window_set_click_config_provider(s_timer_window, (ClickConfigProvider) config_provider_timer);
  
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