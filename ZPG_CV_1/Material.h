#pragma once

class Material {
    private:
        float ra; 
        float rd; 
        float rs; 
		int shininess;

    public:
        Material(float ambient, float diffuse, float specular, int shininess);

        void SetAmbientCoefficient(float ambient);
        void SetDiffuseCoefficient(float diffuse);
        void SetSpecularCoefficient(float specular);
		void SetShininess(int shininess);

        float GetAmbientCoefficient();
        float GetDiffuseCoefficient();
        float GetSpecularCoefficient();
		int GetShininess();
};