#pragma once

class IGrabbable
{
public:
    virtual ~IGrabbable() = default;

    virtual void onGrab() = 0;
};