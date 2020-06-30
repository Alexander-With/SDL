#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

// Starts up SDL and creates window
bool initSDL();
// Loads media
bool loadMedia();
// Frees media and shuts down SDL
void closeSDL();

// The window we'll be rending to
SDL_Window* gWindow = NULL;
// The window renderer
SDL_Renderer* gRenderer = NULL;
// The image we will load and show on the screen
SDL_Surface *gImage = NULL;

// Window Size
const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 640;

bool initSDL(){
	// Initialization flag
	bool success = true;

	// Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else{
		// Create Window
		gWindow = SDL_CreateWindow(
			"SDL Tutorial", 
			SDL_WINDOWPOS_UNDEFINED, 
			SDL_WINDOWPOS_UNDEFINED, 
			SCREEN_WIDTH, 
			SCREEN_HEIGHT, 
			SDL_WINDOW_SHOWN
		);
		if(gWindow == NULL){
			printf("Window cloud not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else{
			// Get windows surface
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if(gRenderer == NULL){
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else{
				//Initialize remderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}
	}

	return success;
}

bool loadMedia(){
	// Loading success flag
	bool success = true;

	// load splash image
	gImage = SDL_LoadBMP("image.bmp");
	if(gImage == NULL){
		printf("Unable to load image %s! SDL Error: %s\n", "image.bmp", SDL_GetError());
		success = false;
	}

	return success;
}

void closeSDL(){
	// Deallocate surface
	SDL_FreeSurface(gImage);
	gImage = NULL;

	// Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystem
	SDL_Quit();
}

int main(int argc, char* args[]){
	// Main loop flag
	bool quit = false;

	// Event handler
	SDL_Event e;

	// Start up SDL and create window
	if(!initSDL()){
		printf("Failed to Initialize!\n");
	}
	else{
		// Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		// Generate board
		int squaresSize = 8*8;
		SDL_Rect squares[squaresSize];
		int squaresColor[squaresSize*4]; 

		int i = 0;
		for (int yRect = 0; yRect < SCREEN_HEIGHT; yRect += SCREEN_HEIGHT / 8){
			for (int xRect = 0; xRect < SCREEN_WIDTH; xRect += SCREEN_WIDTH / 8){
				squares[i++] = {
					xRect,
					yRect,
					SCREEN_WIDTH / 8,
					SCREEN_HEIGHT / 8
				};
			}
		}

		for(int i = 0; i < squaresSize * 4; i += 4){
			squaresColor[i + 0] = rand() % 255;
			squaresColor[i + 1] = rand() % 255;
			squaresColor[i + 2] = rand() % 255;
			squaresColor[i + 3] = 0xFF;
		}

		// Render board
		for(int i = 0; i < squaresSize; i++){
			SDL_SetRenderDrawColor(gRenderer, squaresColor[i * 4 + 0], squaresColor[i * 4 + 1], squaresColor[i * 4 + 2], squaresColor[i * 4 + 3]);
			SDL_RenderFillRect(gRenderer, &squares[i]);
		}

		// Update screen
		SDL_RenderPresent(gRenderer);

		while (!quit){
			// Handle events on queue
			while(SDL_PollEvent(&e) != 0){
				// User request quit
				if(e.type == SDL_QUIT){
					quit = true;
				}
			}

			// // Render board
			// for (int i = 0; i < squaresSize; i++){
			// 	squares[i].x = squares[i].x + 1;
			// 	if (squares[i].x > SCREEN_WIDTH){
			// 		squares[i].x = 0;
			// 	}
			// 	SDL_SetRenderDrawColor(gRenderer, squaresColor[i * 4 + 0], squaresColor[i * 4 + 1], squaresColor[i * 4 + 2], squaresColor[i * 4 + 3]);
			// 	SDL_RenderFillRect(gRenderer, &squares[i]);
			// }

			// // Update screen
			// SDL_RenderPresent(gRenderer);

			SDL_Delay(16);	// Frame Cap
		}
	}
	
	// Free resources and close SDL
	closeSDL();

	return 0;
}