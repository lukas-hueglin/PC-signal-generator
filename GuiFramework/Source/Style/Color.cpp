#include "Gui.h"
#include "Style/Color.h"

RGBColor::RGBColor() : r(0.0f), g(0.0f), b(0.0f), a(0.0f) { }

RGBColor::RGBColor(int hex) {

	// extract alpha
	if (hex > 0xffffff) {
		a = (0xff & hex) / 255.0f;
		hex = hex >> 8;
	}
	else { a = 1.0f; }

	// extract blue
	b = (0xff & hex) / 255.0f;
	hex = hex >> 8;

	// extract green
	g = (0xff & hex) / 255.0f;
	hex = hex >> 8;

	// extract red
	r = (0xff & hex) / 255.0f;
	hex = hex >> 8;
}

RGBColor::RGBColor(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) { }

RGBColor RGBColor::lighten(float value) const {

	float new_r = min(max(r * value, 0.0f), 1.0f);
	float new_g = min(max(g * value, 0.0f), 1.0f);
	float new_b = min(max(b * value, 0.0f), 1.0f);

	return RGBColor(new_r, new_g, new_b, a);
}

RGBColor RGBColor::darken(float value) const {

	float new_r = min(max(r / value, 0.0f), 1.0f);
	float new_g = min(max(g / value, 0.0f), 1.0f);
	float new_b = min(max(b / value, 0.0f), 1.0f);

	return RGBColor(new_r, new_g, new_b, a);
}

RGBColor RGBColor::makeTransparent(float value) const {
	RGBColor newColor = *this;
	newColor.a *= value;

	return newColor;
}

HSVColor::HSVColor(int hex) {

	// extract alpha
	if (hex > 0xffffff) {
		a = (0xff & hex) / 255.0f;
		hex = hex >> 8;
	}
	else { a = 1.0f; }

	// extract value
	v = (0xff & hex) / 255.0f;
	hex = hex >> 8;

	// extract saturation
	s = (0xff & hex) / 255.0f;
	hex = hex >> 8;

	// extract hue
	h = (0xff & hex) / 255.0f;
	hex = hex >> 8;
}

HSVColor::HSVColor(float h, float s, float v, float a) : h(h), s(s), v(v), a(a) { }


// add constant colors
const RGBColor RGBColor::AliceBlue				{ 0xf0f8ff };
const RGBColor RGBColor::AntiqueWhite			{ 0xfaebd7 };
const RGBColor RGBColor::Aqua					{ 0x00ffff };
const RGBColor RGBColor::Aquamarine				{ 0x7fffd4 };
const RGBColor RGBColor::Azure					{ 0xf0ffff };
const RGBColor RGBColor::Beige					{ 0xf5f5dc };
const RGBColor RGBColor::Bisque					{ 0xffe4c4 };
const RGBColor RGBColor::Black					{ 0x000000 };
const RGBColor RGBColor::BlanchedAlmond			{ 0xffebcd };
const RGBColor RGBColor::Blue					{ 0x0000ff };
const RGBColor RGBColor::BlueViolet				{ 0x8a2be2 };
const RGBColor RGBColor::Brown					{ 0xa52a2a };
const RGBColor RGBColor::BurlyWood				{ 0xdeb887 };
const RGBColor RGBColor::CadetBlue				{ 0x5f9ea0 };
const RGBColor RGBColor::Chartreuse				{ 0x7fff00 };
const RGBColor RGBColor::Chocolate				{ 0xd2691e };
const RGBColor RGBColor::Coral					{ 0xff7f50 };
const RGBColor RGBColor::CornflowerBlue			{ 0x6495ed };
const RGBColor RGBColor::Cornsilk				{ 0xfff8dc };
const RGBColor RGBColor::Crimson				{ 0xdc143c };
const RGBColor RGBColor::Cyan					{ 0x00ffff };
const RGBColor RGBColor::DarkBlue				{ 0x00008b };
const RGBColor RGBColor::DarkCyan				{ 0x008b8b };
const RGBColor RGBColor::DarkGoldenrod			{ 0xb8860b };
const RGBColor RGBColor::DarkGray				{ 0xa9a9a9 };
const RGBColor RGBColor::DarkGreen				{ 0x006400 };
const RGBColor RGBColor::DarkGrey				{ 0xa9a9a9 };
const RGBColor RGBColor::DarkKhaki				{ 0xbdb76b };
const RGBColor RGBColor::DarkMagenta			{ 0x8b008b };
const RGBColor RGBColor::DarkOliveGreen			{ 0x556b2f };
const RGBColor RGBColor::DarkOrange				{ 0xff8c00 };
const RGBColor RGBColor::DarkOrchid				{ 0x9932cc };
const RGBColor RGBColor::DarkRed				{ 0x8b0000 };
const RGBColor RGBColor::DarkSalmon				{ 0xe9967a };
const RGBColor RGBColor::DarkSeaGreen			{ 0x8fbc8f };
const RGBColor RGBColor::DarkSlateBlue			{ 0x483d8b };
const RGBColor RGBColor::DarkSlateGray			{ 0x2f4f4f };
const RGBColor RGBColor::DarkSlateGrey			{ 0x2f4f4f };
const RGBColor RGBColor::DarkTurquoise			{ 0x00ced1 };
const RGBColor RGBColor::DarkViolet				{ 0x9400d3 };
const RGBColor RGBColor::DeepPink				{ 0xff1493 };
const RGBColor RGBColor::DeepSkyBlue			{ 0x00bfff };
const RGBColor RGBColor::DimGray				{ 0x696969 };
const RGBColor RGBColor::DimGrey				{ 0x696969 };
const RGBColor RGBColor::DodgerBlue				{ 0x1e90ff };
const RGBColor RGBColor::Firebrick				{ 0xb22222 };
const RGBColor RGBColor::FloralWhite			{ 0xfffaf0 };
const RGBColor RGBColor::ForestGreen			{ 0x228b22 };
const RGBColor RGBColor::Fuchsia				{ 0xff00ff };
const RGBColor RGBColor::Gainsboro				{ 0xdcdcdc };
const RGBColor RGBColor::GhostWhite				{ 0xf8f8ff };
const RGBColor RGBColor::Gold					{ 0xffd700 };
const RGBColor RGBColor::Goldenrod				{ 0xdaa520 };
const RGBColor RGBColor::Gray					{ 0x808080 };
const RGBColor RGBColor::Green					{ 0x008000 };
const RGBColor RGBColor::GreenYellow			{ 0xadff2f };
const RGBColor RGBColor::Grey					{ 0x808080 };
const RGBColor RGBColor::Honeydew				{ 0xf0fff0 };
const RGBColor RGBColor::HotPink				{ 0xff69b4 };
const RGBColor RGBColor::IndianRed				{ 0xcd5c5c };
const RGBColor RGBColor::Indigo					{ 0x4b0082 };
const RGBColor RGBColor::Ivory					{ 0xfffff0 };
const RGBColor RGBColor::Khaki					{ 0xf0e68c };
const RGBColor RGBColor::Lavender				{ 0xe6e6fa };
const RGBColor RGBColor::LavenderBlush			{ 0xfff0f5 };
const RGBColor RGBColor::LawnGreen				{ 0x7cfc00 };
const RGBColor RGBColor::LemonChiffon			{ 0xfffacd };
const RGBColor RGBColor::LightBlue				{ 0xadd8e6 };
const RGBColor RGBColor::LightCoral				{ 0xf08080 };
const RGBColor RGBColor::LightCyan				{ 0xe0ffff };
const RGBColor RGBColor::LightGoldenrodYellow	{ 0xfafad2 };
const RGBColor RGBColor::LightGray				{ 0xd3d3d3 };
const RGBColor RGBColor::LightGreen				{ 0x90ee90 };
const RGBColor RGBColor::LightGrey				{ 0xd3d3d3 };
const RGBColor RGBColor::LightPink				{ 0xffb6c1 };
const RGBColor RGBColor::LightSalmon			{ 0xffa07a };
const RGBColor RGBColor::LightSeaGreen			{ 0x20b2aa };
const RGBColor RGBColor::LightSkyBlue			{ 0x87cefa };
const RGBColor RGBColor::LightSlateGray			{ 0x778899 };
const RGBColor RGBColor::LightSlateGrey			{ 0x778899 };
const RGBColor RGBColor::LightSteelBlue			{ 0xb0c4de };
const RGBColor RGBColor::LightYellow			{ 0xffffe0 };
const RGBColor RGBColor::Lime					{ 0x00ff00 };
const RGBColor RGBColor::LimeGreen				{ 0x32cd32 };
const RGBColor RGBColor::Linen					{ 0xfaf0e6 };
const RGBColor RGBColor::Magenta				{ 0xff00ff };
const RGBColor RGBColor::Maroon					{ 0x800000 };
const RGBColor RGBColor::MediumAquamarine		{ 0x66cdaa };
const RGBColor RGBColor::MediumBlue				{ 0x0000cd };
const RGBColor RGBColor::MediumOrchid			{ 0xba55d3 };
const RGBColor RGBColor::MediumPurple			{ 0x9370db };
const RGBColor RGBColor::MediumSeaGreen			{ 0x3cb371 };
const RGBColor RGBColor::MediumSlateBlue		{ 0x7b68ee };
const RGBColor RGBColor::MediumSpringGreen		{ 0x00fa9a };
const RGBColor RGBColor::MediumTurquoise		{ 0x48d1cc };
const RGBColor RGBColor::MediumVioletRed		{ 0xc71585 };
const RGBColor RGBColor::MidnightBlue			{ 0x191970 };
const RGBColor RGBColor::MintCream				{ 0xf5fffa };
const RGBColor RGBColor::MistyRose				{ 0xffe4e1 };
const RGBColor RGBColor::Moccasin				{ 0xffe4b5 };
const RGBColor RGBColor::NavajoWhite			{ 0xffdead };
const RGBColor RGBColor::Navy					{ 0x000080 };
const RGBColor RGBColor::OldLace				{ 0xfdf5e6 };
const RGBColor RGBColor::Olive					{ 0x808000 };
const RGBColor RGBColor::OliveDrab				{ 0x6b8e23 };
const RGBColor RGBColor::Orange					{ 0xffa500 };
const RGBColor RGBColor::OrangeRed				{ 0xff4500 };
const RGBColor RGBColor::Orchid					{ 0xda70d6 };
const RGBColor RGBColor::PaleGoldenrod			{ 0xeee8aa };
const RGBColor RGBColor::PaleGreen				{ 0x98fb98 };
const RGBColor RGBColor::PaleTurquoise			{ 0xafeeee };
const RGBColor RGBColor::PaleVioletRed			{ 0xdb7093 };
const RGBColor RGBColor::PapayaWhip				{ 0xffefd5 };
const RGBColor RGBColor::PeachPuff				{ 0xffdab9 };
const RGBColor RGBColor::Peru					{ 0xcd853f };
const RGBColor RGBColor::Pink					{ 0xffc0cb };
const RGBColor RGBColor::Plum					{ 0xdda0dd };
const RGBColor RGBColor::PowderBlue				{ 0xb0e0e6 };
const RGBColor RGBColor::Purple					{ 0x800080 };
const RGBColor RGBColor::RebeccaPurple			{ 0x663399 };
const RGBColor RGBColor::Red					{ 0xff0000 };
const RGBColor RGBColor::RosyBrown				{ 0xbc8f8f };
const RGBColor RGBColor::RoyalBlue				{ 0x4169e1 };
const RGBColor RGBColor::SaddleBrown			{ 0x8b4513 };
const RGBColor RGBColor::Salmon					{ 0xfa8072 };
const RGBColor RGBColor::SandyBrown				{ 0xf4a460 };
const RGBColor RGBColor::SeaGreen				{ 0x2e8b57 };
const RGBColor RGBColor::Seashell				{ 0xfff5ee };
const RGBColor RGBColor::Sienna					{ 0xa0522d };
const RGBColor RGBColor::Silver					{ 0xc0c0c0 };
const RGBColor RGBColor::SkyBlue				{ 0x87ceeb };
const RGBColor RGBColor::SlateBlue				{ 0x6a5acd };
const RGBColor RGBColor::SlateGray				{ 0x708090 };
const RGBColor RGBColor::SlateGrey				{ 0x708090 };
const RGBColor RGBColor::Snow					{ 0xfffafa };
const RGBColor RGBColor::SpringGreen			{ 0x00ff7f };
const RGBColor RGBColor::SteelBlue				{ 0x4682b4 };
const RGBColor RGBColor::Tan					{ 0xd2b48c };
const RGBColor RGBColor::Teal					{ 0x008080 };
const RGBColor RGBColor::Thistle				{ 0xd8bfd8 };
const RGBColor RGBColor::Tomato					{ 0xff6347 };
const RGBColor RGBColor::Turquoise				{ 0x40e0d0 };
const RGBColor RGBColor::Violet					{ 0xee82ee };
const RGBColor RGBColor::Wheat					{ 0xf5deb3 };
const RGBColor RGBColor::White					{ 0xffffff };
const RGBColor RGBColor::WhiteSmoke				{ 0xf5f5f5 };
const RGBColor RGBColor::Yellow					{ 0xffff00 };
const RGBColor RGBColor::YellowGreen			{ 0x9acd32 };
const RGBColor RGBColor::Transparent			{ 0, 0, 0, 0 };