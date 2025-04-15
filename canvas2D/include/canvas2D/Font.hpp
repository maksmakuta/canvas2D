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

    enum class Direction {
        LTR,
        RTL
    };

    enum class FontKerning {
        Auto,
        Normal,
        None
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

    enum class TextRendering {
        Auto,
        OptimizeSpeed,
        OptimizeLegibility,
        GeometricPrecision
    };

    class Font {
    public:
        Font();
    };

}

#endif //FONT_HPP
