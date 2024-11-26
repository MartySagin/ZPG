#pragma once

class Material {
    private:
        float ra; 
        float rd; 
        float rs; 

    public:
        Material(float ambient, float diffuse, float specular);

        void SetAmbientCoefficient(float ambient);
        void SetDiffuseCoefficient(float diffuse);
        void SetSpecularCoefficient(float specular);

        float GetAmbientCoefficient();
        float GetDiffuseCoefficient();
        float GetSpecularCoefficient();
};