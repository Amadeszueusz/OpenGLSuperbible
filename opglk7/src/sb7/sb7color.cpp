#include <vmath.h>
#include <sb7color.h>

namespace sb7
{

static vmath::vec4 colorfromhex(const unsigned int hex)
{
    return vmath::vec4(float((hex >> 16) & 0xFF) / 255.0f, float((hex >> 8) & 0xFF) / 255.0f, float((hex >> 0) & 0xFF) / 255.0f, 1.0f);
}

const vmath::vec4 color::AliceBlue = colorfromhex(0xF0F8FF);
const vmath::vec4 color::AntiqueWhite = colorfromhex(0xFAEBD7);
const vmath::vec4 color::Aqua = colorfromhex(0x00FFFF);
const vmath::vec4 color::Aquamarine = colorfromhex(0x7FFFD4);
const vmath::vec4 color::Azure = colorfromhex(0xF0FFFF);
const vmath::vec4 color::Beige = colorfromhex(0xF5F5DC);
const vmath::vec4 color::Bisque = colorfromhex(0xFFE4C4);
const vmath::vec4 color::Black = colorfromhex(0x000000);
const vmath::vec4 color::BlanchedAlmond = colorfromhex(0xFFEBCD);
const vmath::vec4 color::Blue = colorfromhex(0x0000FF);
const vmath::vec4 color::BlueViolet = colorfromhex(0x8A2BE2);
const vmath::vec4 color::Brown = colorfromhex(0xA52A2A);
const vmath::vec4 color::BurlyWood = colorfromhex(0xDEB887);
const vmath::vec4 color::CadetBlue = colorfromhex(0x5F9EA0);
const vmath::vec4 color::Chartreuse = colorfromhex(0x7FFF00);
const vmath::vec4 color::Chocolate = colorfromhex(0xD2691E);
const vmath::vec4 color::Coral = colorfromhex(0xFF7F50);
const vmath::vec4 color::CornflowerBlue = colorfromhex(0x6495ED);
const vmath::vec4 color::Cornsilk = colorfromhex(0xFFF8DC);
const vmath::vec4 color::Crimson = colorfromhex(0xDC143C);
const vmath::vec4 color::Cyan = colorfromhex(0x00FFFF);
const vmath::vec4 color::DarkBlue = colorfromhex(0x00008B);
const vmath::vec4 color::DarkCyan = colorfromhex(0x008B8B);
const vmath::vec4 color::DarkGoldenRod = colorfromhex(0xB8860B);
const vmath::vec4 color::DarkGray = colorfromhex(0xA9A9A9);
const vmath::vec4 color::DarkGreen = colorfromhex(0x006400);
const vmath::vec4 color::DarkKhaki = colorfromhex(0xBDB76B);
const vmath::vec4 color::DarkMagenta = colorfromhex(0x8B008B);
const vmath::vec4 color::DarkOliveGreen = colorfromhex(0x556B2F);
const vmath::vec4 color::DarkOrange = colorfromhex(0xFF8C00);
const vmath::vec4 color::DarkOrchid = colorfromhex(0x9932CC);
const vmath::vec4 color::DarkRed = colorfromhex(0x8B0000);
const vmath::vec4 color::DarkSalmon = colorfromhex(0xE9967A);
const vmath::vec4 color::DarkSeaGreen = colorfromhex(0x8FBC8F);
const vmath::vec4 color::DarkSlateBlue = colorfromhex(0x483D8B);
const vmath::vec4 color::DarkSlateGray = colorfromhex(0x2F4F4F);
const vmath::vec4 color::DarkTurquoise = colorfromhex(0x00CED1);
const vmath::vec4 color::DarkViolet = colorfromhex(0x9400D3);
const vmath::vec4 color::DeepPink = colorfromhex(0xFF1493);
const vmath::vec4 color::DeepSkyBlue = colorfromhex(0x00BFFF);
const vmath::vec4 color::DimGray = colorfromhex(0x696969);
const vmath::vec4 color::DodgerBlue = colorfromhex(0x1E90FF);
const vmath::vec4 color::FireBrick = colorfromhex(0xB22222);
const vmath::vec4 color::FloralWhite = colorfromhex(0xFFFAF0);
const vmath::vec4 color::ForestGreen = colorfromhex(0x228B22);
const vmath::vec4 color::Fuchsia = colorfromhex(0xFF00FF);
const vmath::vec4 color::Gainsboro = colorfromhex(0xDCDCDC);
const vmath::vec4 color::GhostWhite = colorfromhex(0xF8F8FF);
const vmath::vec4 color::Gold = colorfromhex(0xFFD700);
const vmath::vec4 color::GoldenRod = colorfromhex(0xDAA520);
const vmath::vec4 color::Gray = colorfromhex(0x808080);
const vmath::vec4 color::Green = colorfromhex(0x008000);
const vmath::vec4 color::GreenYellow = colorfromhex(0xADFF2F);
const vmath::vec4 color::HoneyDew = colorfromhex(0xF0FFF0);
const vmath::vec4 color::HotPink = colorfromhex(0xFF69B4);
const vmath::vec4 color::IndianRed = colorfromhex(0xCD5C5C);
const vmath::vec4 color::Indigo = colorfromhex(0x4B0082);
const vmath::vec4 color::Ivory = colorfromhex(0xFFFFF0);
const vmath::vec4 color::Khaki = colorfromhex(0xF0E68C);
const vmath::vec4 color::Lavender = colorfromhex(0xE6E6FA);
const vmath::vec4 color::LavenderBlush = colorfromhex(0xFFF0F5);
const vmath::vec4 color::LawnGreen = colorfromhex(0x7CFC00);
const vmath::vec4 color::LemonChiffon = colorfromhex(0xFFFACD);
const vmath::vec4 color::LightBlue = colorfromhex(0xADD8E6);
const vmath::vec4 color::LightCoral = colorfromhex(0xF08080);
const vmath::vec4 color::LightCyan = colorfromhex(0xE0FFFF);
const vmath::vec4 color::LightGoldenRodYellow = colorfromhex(0xFAFAD2);
const vmath::vec4 color::LightGray = colorfromhex(0xD3D3D3);
const vmath::vec4 color::LightGreen = colorfromhex(0x90EE90);
const vmath::vec4 color::LightPink = colorfromhex(0xFFB6C1);
const vmath::vec4 color::LightSalmon = colorfromhex(0xFFA07A);
const vmath::vec4 color::LightSeaGreen = colorfromhex(0x20B2AA);
const vmath::vec4 color::LightSkyBlue = colorfromhex(0x87CEFA);
const vmath::vec4 color::LightSlateGray = colorfromhex(0x778899);
const vmath::vec4 color::LightSteelBlue = colorfromhex(0xB0C4DE);
const vmath::vec4 color::LightYellow = colorfromhex(0xFFFFE0);
const vmath::vec4 color::Lime = colorfromhex(0x00FF00);
const vmath::vec4 color::LimeGreen = colorfromhex(0x32CD32);
const vmath::vec4 color::Linen = colorfromhex(0xFAF0E6);
const vmath::vec4 color::Magenta = colorfromhex(0xFF00FF);
const vmath::vec4 color::Maroon = colorfromhex(0x800000);
const vmath::vec4 color::MediumAquaMarine = colorfromhex(0x66CDAA);
const vmath::vec4 color::MediumBlue = colorfromhex(0x0000CD);
const vmath::vec4 color::MediumOrchid = colorfromhex(0xBA55D3);
const vmath::vec4 color::MediumPurple = colorfromhex(0x9370DB);
const vmath::vec4 color::MediumSeaGreen = colorfromhex(0x3CB371);
const vmath::vec4 color::MediumSlateBlue = colorfromhex(0x7B68EE);
const vmath::vec4 color::MediumSpringGreen = colorfromhex(0x00FA9A);
const vmath::vec4 color::MediumTurquoise = colorfromhex(0x48D1CC);
const vmath::vec4 color::MediumVioletRed = colorfromhex(0xC71585);
const vmath::vec4 color::MidnightBlue = colorfromhex(0x191970);
const vmath::vec4 color::MintCream = colorfromhex(0xF5FFFA);
const vmath::vec4 color::MistyRose = colorfromhex(0xFFE4E1);
const vmath::vec4 color::Moccasin = colorfromhex(0xFFE4B5);
const vmath::vec4 color::NavajoWhite = colorfromhex(0xFFDEAD);
const vmath::vec4 color::Navy = colorfromhex(0x000080);
const vmath::vec4 color::OldLace = colorfromhex(0xFDF5E6);
const vmath::vec4 color::Olive = colorfromhex(0x808000);
const vmath::vec4 color::OliveDrab = colorfromhex(0x6B8E23);
const vmath::vec4 color::Orange = colorfromhex(0xFFA500);
const vmath::vec4 color::OrangeRed = colorfromhex(0xFF4500);
const vmath::vec4 color::Orchid = colorfromhex(0xDA70D6);
const vmath::vec4 color::PaleGoldenRod = colorfromhex(0xEEE8AA);
const vmath::vec4 color::PaleGreen = colorfromhex(0x98FB98);
const vmath::vec4 color::PaleTurquoise = colorfromhex(0xAFEEEE);
const vmath::vec4 color::PaleVioletRed = colorfromhex(0xDB7093);
const vmath::vec4 color::PapayaWhip = colorfromhex(0xFFEFD5);
const vmath::vec4 color::PeachPuff = colorfromhex(0xFFDAB9);
const vmath::vec4 color::Peru = colorfromhex(0xCD853F);
const vmath::vec4 color::Pink = colorfromhex(0xFFC0CB);
const vmath::vec4 color::Plum = colorfromhex(0xDDA0DD);
const vmath::vec4 color::PowderBlue = colorfromhex(0xB0E0E6);
const vmath::vec4 color::Purple = colorfromhex(0x800080);
const vmath::vec4 color::RebeccaPurple = colorfromhex(0x663399);
const vmath::vec4 color::Red = colorfromhex(0xFF0000);
const vmath::vec4 color::RosyBrown = colorfromhex(0xBC8F8F);
const vmath::vec4 color::RoyalBlue = colorfromhex(0x4169E1);
const vmath::vec4 color::SaddleBrown = colorfromhex(0x8B4513);
const vmath::vec4 color::Salmon = colorfromhex(0xFA8072);
const vmath::vec4 color::SandyBrown = colorfromhex(0xF4A460);
const vmath::vec4 color::SeaGreen = colorfromhex(0x2E8B57);
const vmath::vec4 color::SeaShell = colorfromhex(0xFFF5EE);
const vmath::vec4 color::Sienna = colorfromhex(0xA0522D);
const vmath::vec4 color::Silver = colorfromhex(0xC0C0C0);
const vmath::vec4 color::SkyBlue = colorfromhex(0x87CEEB);
const vmath::vec4 color::SlateBlue = colorfromhex(0x6A5ACD);
const vmath::vec4 color::SlateGray = colorfromhex(0x708090);
const vmath::vec4 color::Snow = colorfromhex(0xFFFAFA);
const vmath::vec4 color::SpringGreen = colorfromhex(0x00FF7F);
const vmath::vec4 color::SteelBlue = colorfromhex(0x4682B4);
const vmath::vec4 color::Tan = colorfromhex(0xD2B48C);
const vmath::vec4 color::Teal = colorfromhex(0x008080);
const vmath::vec4 color::Thistle = colorfromhex(0xD8BFD8);
const vmath::vec4 color::Tomato = colorfromhex(0xFF6347);
const vmath::vec4 color::Turquoise = colorfromhex(0x40E0D0);
const vmath::vec4 color::Violet = colorfromhex(0xEE82EE);
const vmath::vec4 color::Wheat = colorfromhex(0xF5DEB3);
const vmath::vec4 color::White = colorfromhex(0xFFFFFF);
const vmath::vec4 color::WhiteSmoke = colorfromhex(0xF5F5F5);
const vmath::vec4 color::Yellow = colorfromhex(0xFFFF00);
const vmath::vec4 color::YellowGreen = colorfromhex(0x9ACD32);

}