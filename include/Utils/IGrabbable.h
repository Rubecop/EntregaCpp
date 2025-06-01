#pragma once

class IGrabbable
{
public:
    virtual ~IGrabbable() = default;

    // Funci�n que se ejecuta cuando el jugador lo recoge
    virtual void onGrab() = 0;
};