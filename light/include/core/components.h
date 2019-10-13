//
// Created by k on 11/10/19.
//

#ifndef LIGHT_COMPONENTS_H
#define LIGHT_COMPONENTS_H

#include <vector>

namespace light {

    typedef struct Vector2f {
        float x;
        float y;

        Vector2f() {
            x = y = 0;
        }

        Vector2f (float x, float y){
            this->x = x;
            this->y = y;
        }
    } Vector2f;


    typedef struct ComWindow {

    } ComWindow;

    typedef struct ComWindowEvent {
        int type;
    } ComWindowEvent;

    typedef struct ComDrawable {

    } ComDrawAble;


    typedef struct ImWidget {
        int type;
        const char *text;
    } ImWidget;

    typedef struct ComImWindow {
        Vector2f size;
        Vector2f position;
        const char *name{};
        std::vector<ImWidget*> child;
    } ComImWindow;

    typedef struct ComTransform {
        Vector2f scale;
        float rotation;
        Vector2f position;
    } ComTransform;

    typedef struct ComSprite {
        const char* file;
    } ComSprite;
}

#endif //LIGHT_COMPONENTS_H
