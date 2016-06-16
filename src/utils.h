#ifndef UTILS_H
#define UTILS_H

class Color
{
    public:
        float r, g, b;
        Color(float rr = 1.0f, float gg = 1.0f, float bb = 1.0f);
};

// Couleur par défaut
const Color RED(1.0f, 0.0f, 0.0f);
const Color BLUE(0.0f, 0.0f, 1.0f);
const Color GREEN(0.0f, 1.0f, 0.0f);
const Color YELLOW(1.0f, 1.0f, 0.0f);
const Color WHITE(1.0f, 1.0f, 1.0f);

#endif // UTILS_H
