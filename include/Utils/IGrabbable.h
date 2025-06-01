#pragma once

class IGrabbable
{
public:
    virtual ~IGrabbable() = default;

    // Función que se ejecuta cuando el jugador lo recoge
    virtual void onGrab() = 0;
};