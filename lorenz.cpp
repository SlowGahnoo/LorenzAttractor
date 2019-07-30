#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

const int WIDTH = 800;
const int HEIGHT = 800;

void drawscr(SDL_Renderer* &renderer, double x, double y, double dx, double dy, int* color)
{
	static int i = 0;
	SDL_RenderDrawLine(renderer, 10*x+WIDTH/2, -10*y+HEIGHT/2, 10*(x+dx)+WIDTH/2, -10*(y+dy)+HEIGHT/2);
	SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 255);
	//Rendering less lines for huge speedup while still being accurate
	if (i == 100) {
		SDL_RenderPresent(renderer);
		SDL_Delay(10); //Delay to stop flickering
		i = 0;
	} i++;

}

void colorit(int *color, double dx, double dy, double dz)
{
	if (dy >= 0.01 || dy <=-0.01) {color[0]++; color[1]--; color[2]--;}
	if (dx >= 0.01 || dx <=-0.01) {color[0]--; color[1]++; color[2]--;}
	if (dz >= 0.01 || dz <=-0.01) {color[0]--; color[1]--; color[2]++;}
	if (color[0] > 254) color[0]--; else if (color[0] < 2) color[0]++;
	if (color[1] > 254) color[1]--; else if (color[1] < 2) color[1]++;
	if (color[2] > 254) color[2]--; else if (color[2] < 2) color[2]++;
}

int main(void)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event event;
	Uint32 rflags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, rflags, &window, &renderer);
	SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);
	SDL_RenderPresent(renderer);

	double x = 1.0;
	double y = 1.0;
	double z = 1.0;
	double a = 10;
	double b = 28;
	double c = static_cast<double>(8)/3;
	double dt = 0.001;
	int color[3] = {64, 64, 64}; //{r, g, b}

	
	for (double t = 0 ;; t += dt) {
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT) break;
		double dx = (a * (y - x))*dt;
		double dy = (x * (b - z) - y)*dt;
		double dz = (x * y - c * z)*dt;
		printf("%f %f %f %f\n", x, y, z, t);
		colorit(color, dx, dy, dz);
		drawscr(renderer, x, y, dx, dy, color);
		x = x + dx;
		y = y + dy;
		z = z + dz;
	}

	SDL_DestroyRenderer(renderer); renderer = nullptr;
	SDL_DestroyWindow(window); window = nullptr;
	SDL_Quit();
}
