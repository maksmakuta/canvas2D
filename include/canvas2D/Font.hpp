#ifndef FONT_HPP
#define FONT_HPP

namespace canvas2D {


    enum class TextAlign {
        Start,
        End,
        Left,
        Right,
        Center
    };

    enum class TextBaseline {
        Top,
        Hanging,
        Middle,
        Alphabetic,
        Ideographic,
        Bottom
    };

    enum class FontStretch {
        UltraCondensed,
        ExtraCondensed,
        Condensed,
        SemiCondensed,
        Normal,
        SemiExpanded,
        Expanded,
        ExtraExpanded,
        UltraExpanded
    };

    struct TextMetrics {
        // x-direction
        float width; // advance width
        float actualBoundingBoxLeft;
        float actualBoundingBoxRight;

        // y-direction
        float fontBoundingBoxAscent;
        float fontBoundingBoxDescent;
        float actualBoundingBoxAscent;
        float actualBoundingBoxDescent;
        float emHeightAscent;
        float emHeightDescent;
        float hangingBaseline;
        float alphabeticBaseline;
        float ideographicBaseline;
    };

    class Font {

    };

}

#endif //FONT_HPP
