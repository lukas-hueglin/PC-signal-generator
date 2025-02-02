#include "Gui.h"
#include "Style/Style.h"
#include "Style/WidgetStyleBuilder.h"
#include "Style/Palette.h"


WidgetStyle Style::Default() {

	return WidgetStyle::create()
		.edgeColor(Palette::PrimaryWidget().lighten(1.2f))
		.edgeThickness(1.0f)
		.fillColor(Palette::PrimaryWidget(), WidgetState::Normal)
		.fillColor(Palette::PrimaryWidget().lighten(1.5f), WidgetState::Hover)
		.fillColor(Palette::PrimaryWidget().lighten(1.3f), WidgetState::Click)
		.fontName(L"SegoeUI")
		.fontSize(12)
		.lineStyle(LineStyle::Solid)
		.radius(7.0f)
		.textAlignment(Alignment::CenterLeft)
		.textColor(Palette::Text());
}

WidgetStyle Style::Layout()
{
	return WidgetStyle::create()
		.edgeColor(Palette::PrimaryWidget().lighten(1.2f))
		.edgeThickness(1.0f)
		.fillColor(Palette::Background(), WidgetState::Normal)
		.fontName(L"SegoeUI")
		.fontSize(12)
		.lineStyle(LineStyle::Solid)
		.radius(7.0f)
		.textAlignment(Alignment::CenterLeft)
		.textColor(Palette::Text());
}

WidgetStyle Style::Slider() {

	return WidgetStyle::create()
		.edgeColor(Palette::PrimaryWidget().lighten(1.2f))
		.edgeThickness(1.0f)
		.fillColor(Palette::PrimaryWidget(), WidgetState::Normal)
		.fillColor(Palette::PrimaryWidget().lighten(1.5f), WidgetState::Hover)
		.fillColor(Palette::PrimaryWidget().lighten(1.3f), WidgetState::Click)
		.fontName(L"SegoeUI")
		.fontSize(12)
		.highlightColor(Palette::Highlight(), WidgetState::Normal)
		.highlightColor(Palette::Highlight().lighten(1.5f), WidgetState::Hover)
		.highlightColor(Palette::Highlight().lighten(1.3f), WidgetState::Click)
		.lineStyle(LineStyle::Solid)
		.radius(7.0f)
		.textAlignment(Alignment::CenterRight)
		.textColor(Palette::Text());
}

WidgetStyle Style::CheckBox() {

	return WidgetStyle::create()
		.edgeColor(Palette::PrimaryWidget().lighten(1.2f))
		.edgeThickness(1.0f)
		.fillColor(Palette::PrimaryWidget(), WidgetState::Normal)
		.fillColor(Palette::Highlight().makeTransparent(0.75f), WidgetState::Hover)
		.fillColor(Palette::Highlight(), WidgetState::Click)
		.fontName(L"SegoeUI")
		.fontSize(12)
		.lineStyle(LineStyle::Solid)
		.radius(4.0f)
		.textAlignment(Alignment::CenterLeft)
		.textColor(Palette::Text());
}

WidgetStyle Style::Title() {

	return WidgetStyle::create()
		.edgeColor(Palette::PrimaryWidget().lighten(1.2f))
		.edgeThickness(1.0f)
		.fillColor(Palette::PrimaryWidget(), WidgetState::Normal)
		.fillColor(Palette::PrimaryWidget().lighten(1.5f), WidgetState::Hover)
		.fillColor(Palette::PrimaryWidget().lighten(1.3f), WidgetState::Click)
		.fontName(L"SegoeUI")
		.fontSize(14)
		.fontWeight(FontWeight::SemiBold)
		.lineStyle(LineStyle::Solid)
		.radius(7.0f)
		.textAlignment(Alignment::CenterLeft)
		.textColor(Palette::Text());
}

WidgetStyle Style::DropDown(Justification justification)
{
	WidgetStyleBuilder builder = WidgetStyle::create()
		.edgeColor(Palette::SecondaryWidget().lighten(1.2f))
		.edgeThickness(1.0f)
		.fillColor(Palette::SecondaryWidget(), WidgetState::Normal)
		.fillColor(Palette::SecondaryWidget().lighten(1.5f), WidgetState::Hover)
		.fillColor(Palette::SecondaryWidget().lighten(1.3f), WidgetState::Click)
		.fontName(L"SegoeUI")
		.fontSize(12)
		.lineStyle(LineStyle::Solid)
		.textAlignment(Alignment::CenterLeft)
		.textColor(Palette::Text());

	switch (justification) {

	case Justification::Leading:
		return builder.radius(7.0f, 7.0f, 0.0f, 0.0f);
	case Justification::Middle:
		return builder.radius(0.0f);
	case Justification::Trailing:
		return builder.radius(0.0f, 0.0f, 7.0f, 7.0f);

	}
}
