#pragma once

class Material {
public:
    float ra; 
    float rd; 
    float rs; 

    Material(float ambient, float diffuse, float specular);

    void SetAmbientCoefficient(float ambient);
    void SetDiffuseCoefficient(float diffuse);
    void SetSpecularCoefficient(float specular);

    float GetAmbientCoefficient();
    float GetDiffuseCoefficient();
    float GetSpecularCoefficient();
};