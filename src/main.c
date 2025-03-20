#include "display.h"

bool is_running = false;

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

void render(void) {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderClear(renderer);

  draw_grid();
  draw_pixel(20, 20, 0xFFFFFF00);
  draw_rect(100, 100, 250, 100, 0xFF31D126);

  render_color_buffer();
  clear_color_buffer(0xFF000000);

  SDL_RenderPresent(renderer);
}

void update(void) {
  // TODO
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
