#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

	#define SPACE 100
#define DIT 100
#define DAH 300
#define MY_UUID { 0xC3, 0xAF, 0x14, 0xFA, 0x68, 0x94, 0x46, 0x34, 0x96, 0x86, 0xC0, 0xA0, 0xCD, 0x6A, 0x4D, 0x4D }
PBL_APP_INFO(MY_UUID,
             "KG6KWW", "Yoda Dev",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

Window window;
TextLayer textLayer;	
bool flag = false;
AppTimerHandle timerHandle;

void handle_init(AppContextRef ctx) 
{
  (void)ctx;
  window_init(&window, "Window Name");
  window_stack_push(&window, true /* Animated */);
  text_layer_init(&textLayer, window.layer.frame);
  text_layer_set_text(&textLayer, "Kg6kww is on the air!");
  text_layer_set_font(&textLayer, fonts_get_system_font(FONT_KEY_GOTHAM_30_BLACK));
  layer_add_child(&window.layer, &textLayer.layer);
	static const uint32_t segments[] = { 
		DAH, SPACE, DIT, SPACE, DAH, SPACE * 4, 
		DAH, SPACE, DAH, SPACE, DIT, SPACE * 4, 
		DAH, SPACE, DIT, SPACE, DIT, SPACE, DIT, SPACE, DIT, SPACE * 4,
		DAH, SPACE, DIT, SPACE, DAH, SPACE * 4, 
		DIT, SPACE, DAH, SPACE, DAH, SPACE * 4, 
		DIT, SPACE, DAH, SPACE, DAH 
	};
	VibePattern pattern = { .durations = segments, .num_segments = ARRAY_LENGTH(segments) };
	vibes_enqueue_custom_pattern(pattern);
	timerHandle = app_timer_send_event(ctx, 10000, 1);
}

void timer_handler(AppContextRef ctx, AppTimerHandle handle, uint32_t cookie)
{
	if (cookie == 1)
	{
		if (flag)
		{
			text_layer_set_text(&textLayer, "yes");
		}
		else
		{
			text_layer_set_text(&textLayer, "no");
		}
		flag = !flag;
		timerHandle = app_timer_send_event(ctx, 2000, 1);
	}		
}


void pbl_main(void *params) 
{
  PebbleAppHandlers handlers = 
  {
	.init_handler = &handle_init,
	.timer_handler = &timer_handler
  };
  app_event_loop(params, &handlers);
}
