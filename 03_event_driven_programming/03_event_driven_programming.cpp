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
// The surface contained by the window
SDL_Surface* gScreenSurface = NULL;
// The image we will load and show on the screen
SDL_Surface* gImage = NULL;

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
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL){
			printf("Window cloud not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else{
			// Get windows surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
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
		// Load media
		if(!loadMedia()){
			printf("Failed to load media!\n");
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
				// Apply the image
				SDL_BlitSurface(gImage, NULL, gScreenSurface, NULL);

				// Update the image
				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}
	
	// Free resources and close SDL
	closeSDL();

	return 0;
}