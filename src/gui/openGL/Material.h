#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

class Material {

public:
    virtual ~Material() {};

    virtual void bind() const = 0;
    virtual void updateUniforms() const = 0;
    virtual void unbind() const = 0;
};

#endif // MATERIAL_H
