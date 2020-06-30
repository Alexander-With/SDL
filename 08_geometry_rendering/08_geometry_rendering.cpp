#include <SDL.h>
#include <stdio.h>

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
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

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
		while (!quit){
			// Handle events on queue
			while(SDL_PollEvent(&e) != 0){
				// User request quit
				if(e.type == SDL_QUIT){
					quit = true;
				}
			}

			// Clear screen
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);

			// Render red filled quad
			SDL_Rect fillRect = { 
				SCREEN_WIDTH / 4,
				SCREEN_HEIGHT / 4,
				SCREEN_WIDTH / 2,
				SCREEN_HEIGHT / 2 
			};
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect(gRenderer, &fillRect);

			// Render green outlined quad
			SDL_Rect outlineRect = {
				SCREEN_WIDTH / 6,
				SCREEN_HEIGHT / 6,
				SCREEN_WIDTH * 2/3,
				SCREEN_HEIGHT * 2/3
			};
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
			SDL_RenderDrawRect(gRenderer, &outlineRect);

			// Draw blue horizontal line
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
			SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

			// Draw vertical line of yellow dots
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
			for(int i = 0; i < SCREEN_HEIGHT; i += 4){
				SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, i);
			}

			// Update screen
			SDL_RenderPresent(gRenderer);
		}
	}
	
	// Free resources and close SDL
	closeSDL();

	return 0;
}