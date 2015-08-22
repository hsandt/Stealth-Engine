//
//  helper.h
//  SDL2_Tutorial_Lesson4
//
//  Created by L Nguyen Huu on 03/04/2014.
//  Copyright (c) 2014 L Nguyen Huu. All rights reserved.
//

#pragma once

#include <iostream>

#include <SDL2/SDL.h>

void logSDLError(std::ostream &os, const std::string &msg);

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer* ren);

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, const SDL_Rect *clip = nullptr);

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, const SDL_Rect& dst, const SDL_Rect *clip = nullptr);

/**
 * Render the message we want to display to a texture for drawing
 * @param message The message we want to display
 * @param fontFile The font we want to use to render the text
 * @param color The color we want the text to be
 * @param fontSize The size we want the font to be
 * @param renderer The renderer to load the texture in
 * @return An SDL_Texture containing the rendered message, or nullptr if something went wrong
 */
SDL_Texture* renderText(const std::string &message, const std::string &fontFile,
                        SDL_Color color, int fontSize, SDL_Renderer *renderer);

