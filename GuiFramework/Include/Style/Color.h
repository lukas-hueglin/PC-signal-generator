#pragma once
#include "Gui.h"

class GUI_API RGBColor {

public:
	float r;
	float g;
	float b;
	float a;

public:
	RGBColor();
	RGBColor(int hex);
	RGBColor(float r, float g, float b, float a = 1.0f);

	RGBColor lighten(float value) const;
	RGBColor darken(float value) const;

	RGBColor makeTransparent(float value) const;

public:
	static const RGBColor AliceBlue;
	static const RGBColor AntiqueWhite;
	static const RGBColor Aqua;
	static const RGBColor Aquamarine;
	static const RGBColor Azure;
	static const RGBColor Beige;
	static const RGBColor Bisque;
	static const RGBColor Black;
	static const RGBColor BlanchedAlmond;
	static const RGBColor Blue;
	static const RGBColor BlueViolet;
	static const RGBColor Brown;
	static const RGBColor BurlyWood;
	static const RGBColor CadetBlue;
	static const RGBColor Chartreuse;
	static const RGBColor Chocolate;
	static const RGBColor Coral;
	static const RGBColor CornflowerBlue;
	static const RGBColor Cornsilk;
	static const RGBColor Crimson;
	static const RGBColor Cyan;
	static const RGBColor DarkBlue;
	static const RGBColor DarkCyan;
	static const RGBColor DarkGoldenrod;
	static const RGBColor DarkGray;
	static const RGBColor DarkGreen;
	static const RGBColor DarkGrey;
	static const RGBColor DarkKhaki;
	static const RGBColor DarkMagenta;
	static const RGBColor DarkOliveGreen;
	static const RGBColor DarkOrange;
	static const RGBColor DarkOrchid;
	static const RGBColor DarkRed;
	static const RGBColor DarkSalmon;
	static const RGBColor DarkSeaGreen;
	static const RGBColor DarkSlateBlue;
	static const RGBColor DarkSlateGray;
	static const RGBColor DarkSlateGrey;
	static const RGBColor DarkTurquoise;
	static const RGBColor DarkViolet;
	static const RGBColor DeepPink;
	static const RGBColor DeepSkyBlue;
	static const RGBColor DimGray;
	static const RGBColor DimGrey;
	static const RGBColor DodgerBlue;
	static const RGBColor Firebrick;
	static const RGBColor FloralWhite;
	static const RGBColor ForestGreen;
	static const RGBColor Fuchsia;
	static const RGBColor Gainsboro;
	static const RGBColor GhostWhite;
	static const RGBColor Gold;
	static const RGBColor Goldenrod;
	static const RGBColor Gray;
	static const RGBColor Green;
	static const RGBColor GreenYellow;
	static const RGBColor Grey;
	static const RGBColor Honeydew;
	static const RGBColor HotPink;
	static const RGBColor IndianRed;
	static const RGBColor Indigo;
	static const RGBColor Ivory;
	static const RGBColor Khaki;
	static const RGBColor Lavender;
	static const RGBColor LavenderBlush;
	static const RGBColor LawnGreen;
	static const RGBColor LemonChiffon;
	static const RGBColor LightBlue;
	static const RGBColor LightCoral;
	static const RGBColor LightCyan;
	static const RGBColor LightGoldenrodYellow;
	static const RGBColor LightGray;
	static const RGBColor LightGreen;
	static const RGBColor LightGrey;
	static const RGBColor LightPink;
	static const RGBColor LightSalmon;
	static const RGBColor LightSeaGreen;
	static const RGBColor LightSkyBlue;
	static const RGBColor LightSlateGray;
	static const RGBColor LightSlateGrey;
	static const RGBColor LightSteelBlue;
	static const RGBColor LightYellow;
	static const RGBColor Lime;
	static const RGBColor LimeGreen;
	static const RGBColor Linen;
	static const RGBColor Magenta;
	static const RGBColor Maroon;
	static const RGBColor MediumAquamarine;
	static const RGBColor MediumBlue;
	static const RGBColor MediumOrchid;
	static const RGBColor MediumPurple;
	static const RGBColor MediumSeaGreen;
	static const RGBColor MediumSlateBlue;
	static const RGBColor MediumSpringGreen;
	static const RGBColor MediumTurquoise;
	static const RGBColor MediumVioletRed;
	static const RGBColor MidnightBlue;
	static const RGBColor MintCream;
	static const RGBColor MistyRose;
	static const RGBColor Moccasin;
	static const RGBColor NavajoWhite;
	static const RGBColor Navy;
	static const RGBColor OldLace;
	static const RGBColor Olive;
	static const RGBColor OliveDrab;
	static const RGBColor Orange;
	static const RGBColor OrangeRed;
	static const RGBColor Orchid;
	static const RGBColor PaleGoldenrod;
	static const RGBColor PaleGreen;
	static const RGBColor PaleTurquoise;
	static const RGBColor PaleVioletRed;
	static const RGBColor PapayaWhip;
	static const RGBColor PeachPuff;
	static const RGBColor Peru;
	static const RGBColor Pink;
	static const RGBColor Plum;
	static const RGBColor PowderBlue;
	static const RGBColor Purple;
	static const RGBColor RebeccaPurple;
	static const RGBColor Red;
	static const RGBColor RosyBrown;
	static const RGBColor RoyalBlue;
	static const RGBColor SaddleBrown;
	static const RGBColor Salmon;
	static const RGBColor SandyBrown;
	static const RGBColor SeaGreen;
	static const RGBColor Seashell;
	static const RGBColor Sienna;
	static const RGBColor Silver;
	static const RGBColor SkyBlue;
	static const RGBColor SlateBlue;
	static const RGBColor SlateGray;
	static const RGBColor SlateGrey;
	static const RGBColor Snow;
	static const RGBColor SpringGreen;
	static const RGBColor SteelBlue;
	static const RGBColor Tan;
	static const RGBColor Teal;
	static const RGBColor Thistle;
	static const RGBColor Tomato;
	static const RGBColor Turquoise;
	static const RGBColor Violet;
	static const RGBColor Wheat;
	static const RGBColor White;
	static const RGBColor WhiteSmoke;
	static const RGBColor Yellow;
	static const RGBColor YellowGreen;
	static const RGBColor Transparent;
};

class GUI_API HSVColor {

public:
	float h;
	float s;
	float v;
	float a;

public:
	HSVColor(int hex);
	HSVColor(float h, float s, float v, float a = 1.0f);

};

// create alias for RGBColor
using Color = RGBColor;