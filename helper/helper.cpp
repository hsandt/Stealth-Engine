//
//  helper.cpp
//  SDL2_Tutorial_Lesson4
//
//  Created by L Nguyen Huu on 03/04/2014.
//  Copyright (c) 2014 L Nguyen Huu. All rights reserved.
//

#include "helper.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/**
 * Log an SDL error with some error message to the output stream of our choice
 * @param os The output stream to write the message too
 * @param msg The error message to write, format will be msg error: SDL_GetError()
 */
void logSDLError(std::ostream &os, const std::string &msg) {
    os << msg << ": error" << SDL_GetError() << std::endl;
}

/**
 * Loads an image into a texture on the rendering device
 * @param file The image file to load
 * @param ren The renderer to load the texture onto
 * @return the loaded texture, or nullptr if something went wrong.
 */
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer* ren) {
    
    SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
    if (texture == nullptr) {
        logSDLError(std::cerr, "LoadTexture");
    }
    return texture;
    
}

/**
 * Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
 * the texture's width and height
 * @param tex The source texture we want to draw
 * @param ren The renderer we want to draw too
 * @param x The x coordinate to draw too
 * @param y The y coordinate to draw too
 * @param clip The sub-section of the texture to draw (clipping rect)
                default of nullptr draws the entire texture
 */
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, const SDL_Rect *clip) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    if (clip != nullptr) {
        dst.w = clip->w;
        dst.h = clip->h;
    }
    else {
        SDL_QueryTexture(tex, nullptr, nullptr, &dst.w, &dst.h);
    }
    // query the texture to infer the original size (w/h) (otherwise the texture will be stretched)
    renderTexture(tex, ren, dst, clip);
}

/**
 * Draw an SDL_Texture to an SDL_Renderer at position x, y, with some width and height
 * @param tex The source texture we want to draw
 * @param ren The renderer we want to draw too
 * @param dst The destination rectangle, or NULL for the
 *                   entire rendering target.
 * @param clip A pointer to the source rectangle, or NULL for the entire
 *                   texture.
 */
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, const SDL_Rect& dst, const SDL_Rect *clip) {
    // Setup the dest rect at the wanted pos (will scale the texture to fit)
    SDL_RenderCopy(ren, tex, clip, &dst);
}

SDL_Texture* renderText(const std::string &message, const std::string &fontFile,
                        SDL_Color color, int fontSize, SDL_Renderer *renderer)
{
    // Open the font
    TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
    if (font == nullptr) {
        logSDLError(std::cerr, "TTF_OpenFont");
        return nullptr;
    }
    // render text to a surface
    SDL_Surface *textSurf = TTF_RenderText_Blended(font, message.c_str(), color);
    if (textSurf == nullptr) {
        TTF_CloseFont(font);
        logSDLError(std::cout, "TTF_RenderText");
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurf);
    if (texture == nullptr) {
        logSDLError(std::cerr, "CreateTexture");
    }
    
    // Clean up the surface and font
    SDL_FreeSurface(textSurf);
    TTF_CloseFont(font);
    return texture;
}
