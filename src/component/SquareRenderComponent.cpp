//
// Created by wing on 15/10/13.
//

#include "RenderComponent.h"

#include "SquareRenderComponent.h"

#include "GameObject.h"

using namespace std;

void SquareRenderComponent::render(SDL_Renderer *renderer) {
    shared_ptr<GameObject> sp_GameObject = gameObject.lock();
    
    //cout << "rendering at " << go -> GetPosition().x() << endl;
    //BOOST_LOG_TRIVIAL(warning) << "test";
    SDL_Rect r;
    //int w = 640, h = 480;

    sp_GameObject->GetComponent<RenderComponent>();

    r.w = 20;
    r.h = 20;
    // iterate on actors only or check for rendering component?
//    r.x = sp_GameObject.transform.position.x();
//    r.y = sp_GameObject.transform.position.y();

    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0, 0xff);
    SDL_RenderDrawRect(renderer, &r);
}
