//
// Created by k on 11/10/19.
//

#ifndef LIGHT_COMPONENTS_H
#define LIGHT_COMPONENTS_H

namespace light {
    typedef struct ComWindow {

    } ComWindow;

    typedef struct ComWindowEvent {
        int type;
    } ComWindowEvent;

    typedef struct ComDrawable {

    } ComDrawAble;

    typedef struct Vector2 {
        int x;
        int y;
    } Vector2;

    typedef struct ComTransform {
        Vector2 scale;
        float rotation;
        Vector2 position;
        uint64_t parent;
    } ComTransform;
}

#endif //LIGHT_COMPONENTS_H
