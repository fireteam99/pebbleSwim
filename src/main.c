#include <pebble.h>

Window *window; //ppd
TextLayer *text_layer;

//initialize window
void init() { 
  window = window_create();
  window_stack_push(window, true);
  text_layer = text_layer_create(GRect(0, 0, 144, 40));
  //Sets up the text
  text_layer_set_text(text_layer, "Welcome to Pebble Swim");
  //adds the text layer as a child to the rendering
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
}

//uninitialize window
void denit() {
  window_destroy(window);
  text_layer_destroy(text_layer);
}

int main() {
  //initializes app
  init();
  
  //Waits for app events
  app_event_loop();
  
  //denitialize app
  denit();
  
  return 0;
}  