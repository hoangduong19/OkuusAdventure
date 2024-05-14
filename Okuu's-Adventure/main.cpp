#include "Gameloop.h"
Gameloop* g = new Gameloop();
int main(int argc, char* args[])
{
	double first;
	double last = 0;
	g->initialize();
	while (g->getgameState())
	{
		g->Event();
		g->update();
		g->render();
		first = SDL_GetTicks();
		if (first - last < 16.7)
		{
			SDL_Delay(16.7 - (first - last));

		}
		last = first;
	}
	g->clear();
	return 0;
}