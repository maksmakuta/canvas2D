#ifndef PATH_HPP
#define PATH_HPP

namespace canvas2D {

    enum class LineCap {
        Butt,
        Round,
        Square
    };

    enum class LineJoin {
        Round,
        Bevel,
        Miter
    };

    class Path {
    public:
        Path();

        void beginPath();
        void closePath();

        void moveTo(float x, float y);
        void lineTo(float x, float y);
        void arcTo(float x1, float y1, float x2, float y2, float r);
        void bezierTo(float x1, float y1, float x2, float y2);
        void bezierTo(float x1, float y1, float x2, float y2, float x3, float y3);

        void rect(float x,float y,float w, float h);
        void roundRect(float x,float y,float w, float h, const std::initializer_list<float>& r);
        void arc(float x,float y,float r, float start, float end, bool ccw = false);
        void ellipse(float x, float y, float rx, float ry, float rot, float start, float end, bool ccw = false);

    };
}

#endif //PATH_HPP
