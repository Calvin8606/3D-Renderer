#pragma once
#include <SDL.h>
#include <stdbool.h>
#include <stdint.h>

extern int window_width;
extern int window_height;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern uint32_t *color_buffer;
extern SDL_Texture *color_buffer_texture;

bool init_window(void);
void render_color_buffer(void);
void clear_color_buffer(uint32_t color);
void draw_pixel(int x, int y, uint32_t color);
void draw_grid(void);
void draw_rect(int x, int y, int width, int height, uint32_t color);
void destroy_window(void);
