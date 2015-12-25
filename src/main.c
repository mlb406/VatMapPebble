#include <pebble.h>
#include "main.h"

#define KEY_GW 0
#define KEY_SS 1
#define KEY_KK 2
#define KEY_LL 3
#define KEY_GD 4
#define KEY_CC 5
#define KEY_PH 6
#define KEY_LON 7

#define GND 1
#define TWR 2
#define APP 3

static Window *window;
static BitmapLayer *background_layer;
static GBitmap *background_bitmap;
static Layer *airports_layer;
static TextLayer *lon_layer, *time_layer;

static void update_time() {
  time_t temp = time(NULL);
  struct tm *t = localtime(&temp);
  
  static char time_buffer[] = "00:00";
  if (clock_is_24h_style() == true) {
    strftime(time_buffer, sizeof(time_buffer), "%H:%M", t);
  } else {
    strftime(time_buffer, sizeof(time_buffer), "%H:%M", t);
  }
  text_layer_set_text(time_layer, time_buffer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
  if(tick_time->tm_min % 15 == 0) {
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    dict_write_uint8(iter, 0, 0);
    app_message_outbox_send();
  }
}

static void update_airports() {
  layer_mark_dirty(window_get_root_layer(window));
}

static void airports_create_proc(Layer *layer, GContext *ctx) {
  GPoint SS = GPoint(115, 118);
  GPoint GW = GPoint(106, 118);
  GPoint LL = GPoint(102, 126);
  GPoint CC = GPoint(80, 86);
  GPoint KK = GPoint(110, 132);
  GPoint GD = GPoint(78, 128);
  GPoint PH = GPoint(66, 22);
  
  graphics_context_set_fill_color(ctx, GColorBlack);
  
  graphics_fill_circle(ctx, GW, 1);
  graphics_fill_circle(ctx, SS, 1);
  graphics_fill_circle(ctx, LL, 1);
  graphics_fill_circle(ctx, KK, 1);
  graphics_fill_circle(ctx, GD, 1);
  graphics_fill_circle(ctx, PH, 1);
  graphics_fill_circle(ctx, CC, 1);
  
  if (persist_read_int(KEY_GW) > 0) {
    #ifdef PBL_PLATFORM_BASALT 
      switch(persist_read_int(KEY_GW)) {
        case 1:
          graphics_context_set_fill_color(ctx, GColorFromRGB(0, 255, 0));
          break;
        case 2:
          graphics_context_set_fill_color(ctx, GColorFromRGB(255, 0, 0));
          break;
        case 3:
          graphics_context_set_fill_color(ctx, GColorFromRGB(255, 170, 0));
          break;
      }
    #endif
    graphics_fill_circle(ctx, GW, 1);
  }
  
  if (persist_read_int(KEY_SS) > 0) {
    #ifdef PBL_PLATFORM_BASALT 
      switch(persist_read_int(KEY_SS)) {
        case 1:
          graphics_context_set_fill_color(ctx, GColorFromRGB(0, 255, 0));
          break;
        case 2:
          graphics_context_set_fill_color(ctx, GColorFromRGB(255, 0, 0));
          break;
        case 3:
          graphics_context_set_fill_color(ctx, GColorFromRGB(255, 170, 0));
          break;
      }
    #endif
    graphics_fill_circle(ctx, SS, 1);
  }
  
  if (persist_read_int(KEY_KK) > 0) {
    #ifdef PBL_PLATFORM_BASALT 
      switch(persist_read_int(KEY_KK)) {
        case 1:
          graphics_context_set_fill_color(ctx, GColorFromRGB(0, 255, 0));
          break;
        case 2:
          graphics_context_set_fill_color(ctx, GColorFromRGB(255, 0, 0));
          break;
        case 3:
          graphics_context_set_fill_color(ctx, GColorFromRGB(255, 170, 0));
          break;
      }
    #endif
    graphics_fill_circle(ctx, KK, 1);
  }
  
  if (persist_read_int(KEY_LL) > 0) {
    #ifdef PBL_PLATFORM_BASALT 
      switch(persist_read_int(KEY_LL)) {
        case 1:
          graphics_context_set_fill_color(ctx, GColorFromRGB(0, 255, 0));
          break;
        case 2:
          graphics_context_set_fill_color(ctx, GColorFromRGB(255, 0, 0));
          break;
        case 3:
          graphics_context_set_fill_color(ctx, GColorFromRGB(255, 170, 0));
          break;
      }
    #endif
    graphics_fill_circle(ctx, LL, 1);
  }
  
  if (persist_read_int(KEY_GD) > 0) {
    #ifdef PBL_PLATFORM_BASALT 
      switch(persist_read_int(KEY_GD)) {
        case 1:
          graphics_context_set_fill_color(ctx, GColorFromRGB(0, 255, 0));
          break;
        case 2:
          graphics_context_set_fill_color(ctx, GColorFromRGB(255, 0, 0));
          break;
        case 3:
          graphics_context_set_fill_color(ctx, GColorFromRGB(255, 170, 0));
          break;
      }
    #endif
    graphics_fill_circle(ctx, GD, 1);
  }
  
  if (persist_read_int(KEY_CC) > 0) {
    #ifdef PBL_PLATFORM_BASALT 
      switch(persist_read_int(KEY_CC)) {
        case 1:
          graphics_context_set_fill_color(ctx, GColorFromRGB(0, 255, 0));
          break;
        case 2:
          graphics_context_set_fill_color(ctx, GColorFromRGB(255, 0, 0));
          break;
        case 3:
          graphics_context_set_fill_color(ctx, GColorFromRGB(255, 170, 0));
          break;
      }
    #endif
    graphics_fill_circle(ctx, CC, 1);
  }
  
  if (persist_read_int(KEY_PH) > 0) {
    #ifdef PBL_PLATFORM_BASALT 
      switch(persist_read_int(KEY_PH)) {
        case 1:
          graphics_context_set_fill_color(ctx, GColorFromRGB(0, 255, 0));
          break;
        case 2:
          graphics_context_set_fill_color(ctx, GColorFromRGB(255, 0, 0));
          break;
        case 3:
          graphics_context_set_fill_color(ctx, GColorFromRGB(255, 170, 0));
          break;
      }
    #endif
    graphics_fill_circle(ctx, PH, 1);
  }
  
  static char lon_buffer[256];
  static char buffer[256];
  persist_read_string(KEY_LON, lon_buffer, sizeof(lon_buffer));
  if (strcmp(lon_buffer, "") != 0) {
    persist_read_string(KEY_LON, lon_buffer, sizeof(lon_buffer));
    strcpy(buffer, "LON: ");
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%s", buffer);
    APP_LOG(APP_LOG_LEVEL_DEBUG_VERBOSE, "%s", buffer);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%s", lon_buffer);
    strcat(buffer, lon_buffer);
    text_layer_set_text(lon_layer, buffer);
  }
   
}

static void main_window_load() {
  background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MAP_BG);
  background_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
  bitmap_layer_set_bitmap(background_layer, background_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(background_layer));
  
  airports_layer = layer_create(GRect(0, 0, 144, 168));
  layer_set_update_proc(airports_layer, airports_create_proc);
  layer_add_child(window_get_root_layer(window), airports_layer);
  
  lon_layer = text_layer_create(GRect(0, 130, 144, 20));
  text_layer_set_text_color(lon_layer, GColorBlack);
  text_layer_set_background_color(lon_layer, GColorClear);
  text_layer_set_text_alignment(lon_layer, GTextAlignmentLeft);
  text_layer_set_font(lon_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(lon_layer));
  
  time_layer = text_layer_create(GRect(0, -5, 140, 30));
  text_layer_set_text_alignment(time_layer, GTextAlignmentRight);
  text_layer_set_text_color(time_layer, GColorFromRGB(255, 0, 0));
  text_layer_set_background_color(time_layer, GColorClear);
  text_layer_set_font(time_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text(time_layer, "00:00");
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(time_layer));
}

static void main_window_unload() {
  gbitmap_destroy(background_bitmap);
  bitmap_layer_destroy(background_layer);
  layer_destroy(airports_layer);
  text_layer_destroy(lon_layer);
  text_layer_destroy(time_layer);
}

static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  Tuple *t = NULL;
  
  t = dict_read_first(iterator);
  while (t != NULL) {
    switch (t->key) {
      case KEY_GW:
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Got KEY_GW");
        persist_write_int(KEY_GW, t->value->int16);
        break;
      case KEY_SS:
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Got KEY_SS");
        persist_write_int(KEY_SS, t->value->int16);
        break;
      case KEY_KK:
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Got KEY_KK");
        persist_write_int(KEY_KK, t->value->int16);
        break;
      case KEY_LL:
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Got KEY_LL");
        persist_write_int(KEY_LL, t->value->int16);
        break;
      case KEY_GD:
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Got KEY_GD");
        persist_write_int(KEY_GD, t->value->int16);
        break;
      case KEY_CC:
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Got KEY_CC");
        persist_write_int(KEY_CC, t->value->int16);
        break;
      case KEY_PH:
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Got KEY_PH");
        persist_write_int(KEY_PH, t->value->int16);
        break;
      case KEY_LON:
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Got KEY_LON");
        persist_write_string(KEY_LON, t->value->cstring);
        break;
      default:
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Unknown key :(");
        break;
    }
    t = dict_read_next(iterator);
  }
  update_airports();
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}

static void init() {
  window = window_create();
  
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
  
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
  window_set_window_handlers(window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  
  window_stack_push(window, true);
  
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
  
  update_time();
}

static void deinit() {
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
  return 0;
}