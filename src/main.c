#include "SDL_render.h"
#include "SDL_video.h"
#include <SDL.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool is_running = false;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int window_width = 800;
int window_height = 600;

uint32_t *color_buffer = NULL;
SDL_Texture *color_buffer_texture = NULL;

bool init_window(void) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Error initializing SDL.\n");
    return false;
  }

  // Get Actual Max Window and Height
  SDL_DisplayMode display_mode;
  SDL_GetCurrentDisplayMode(0, &display_mode);
  window_width = display_mode.w;
  window_height = display_mode.h;

  window = SDL_CreateWindow("3D Graphics", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, window_width, window_height,
                            SDL_WINDOW_BORDERLESS);

  if (!window) {
    fprintf(stderr, "Error Creating Window\n");
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) {
    fprintf(stderr, "Renderer not working\n");
    return false;
  }

  SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

  return true;
}

void setup(void) {
  // Create allocate space in the size of the screen so that we can fill it with
  // pixels of color
  color_buffer =
      (uint32_t *)malloc(sizeof(uint32_t) * window_width * window_height);
  // Create SDL Texture that is used to display color
  color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                           SDL_TEXTUREACCESS_STREAMING,
                                           window_width, window_height);
}

void handle_input(void) {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
  case SDL_QUIT:
    is_running = false;
    break;
  case SDL_KEYDOWN:
    if (event.key.keysym.sym == SDLK_ESCAPE) {
      is_running = false;
      break;
    }
  }
}

void update(void) {
  // TODO
}

void render_color_buffer(void) {
  SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer,
                    (int)window_width * sizeof(uint32_t));
  SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void clear_color_buffer(uint32_t color) {
  for (int y = 0; y < window_height; y++) {
    for (int x = 0; x < window_width; x++) {
      color_buffer[(window_width * y) + x] = color;
    }
  }
}

void draw_grid(void) {
  for (int y = 0; y < window_height; y++) {
    for (int x = 0; x < window_width; x++) {
      if (x % 10 == 0 || y % 10 == 0) {
        color_buffer[(window_width * y) + x] = 0xFFFFFFFF;
      }
    }
  }
}

void draw_rect(int x, int y, int width, int height, uint32_t color) {
  for (int i = y; i < window_height; i++) {
    for (int j = x; j < window_width; j++) {
      if (i < y + height && j < x + width) {
        color_buffer[(window_width * i) + j] = color;
      }
    }
  }
}

void render(void) {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderClear(renderer);

  draw_grid();
  draw_rect(100, 100, 250, 100, 0xFF31D126);

  render_color_buffer();
  clear_color_buffer(0xFF000000);

  SDL_RenderPresent(renderer);
}

void destroy_window(void) {
  free(color_buffer);
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

int main(void) {
  is_running = init_window();

  setup();

  while (is_running) {
    handle_input();
    update();
    render();
  }

  destroy_window();

  return 0;
}
