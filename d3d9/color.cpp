#include "color.h"
#include <cstdlib>
#include <cstring>
#include <assert.h>

SRColor::SRColor(unsigned int clr_)
{
	argb = clr_;
}

SRColor::SRColor(int red_, int green_, int blue_)
{
	assert(red_ <= 255 && red_ >= 0);
	assert(green_ <= 255 && green_ >= 0);
	assert(blue_ <= 255 && blue_ >= 0);

	alpha = 0xFF;
	red = static_cast<unsigned char>(red_);
	green = static_cast<unsigned char>(green_);
	blue = static_cast<unsigned char>(blue_);
}

SRColor::SRColor(int alpha_, int red_, int green_, int blue_)
{
	assert(alpha_ <= 255 && alpha_ >= 0);
	assert(red_ <= 255 && red_ >= 0);
	assert(green_ <= 255 && green_ >= 0);
	assert(blue_ <= 255 && blue_ >= 0);

	SRColor(red_, green_, blue_);
	alpha = static_cast<unsigned char>(alpha_);
}

SRColor::SRColor(const SRColor &clr_)
{
	argb = clr_.argb;
}

SRColor::SRColor(ColorDominater dominater, unsigned char alpha_)
{
	alpha = alpha_;
	setDominater(dominater);

}

ColorDominater SRColor::dominater()
{
	if (red == green && green == blue && blue == 0)
		return ColorDominater::eCdBlack;
	if (red == green && green == blue && blue == 0xFF)
		return ColorDominater::eCdWhite;
	if (red == green && green == blue)
		return ColorDominater::eCdGray;

	if (red > green + blue)
		return ColorDominater::eCdRed;
	if (green > red + blue)
		return ColorDominater::eCdGreen;
	if (blue > green + red)
		return ColorDominater::eCdBlue;

	if (red + green > blue){
		if (red - green >= 0x20 ||
			green - red >= 0x20){
			if (red > green)
				return ColorDominater::eCdOrange;
			return ColorDominater::eCdLimeGreen;
		}
		return ColorDominater::eCdYellow;
	}

	if (blue + green > red){
		if (blue - green >= 0x20 ||
			green - blue >= 0x20){
			if (blue > green)
				return ColorDominater::eCdCyanBlue;
			return ColorDominater::eCdLiteGreen;
		}
		return ColorDominater::eCdCyan;
	}

	if (red + blue > green){
		if (red - blue >= 0x20 ||
			blue - red >= 0x20){
			if (red > blue)
				return ColorDominater::eCdManganous;
			return ColorDominater::eCdPurple;
		}
		return ColorDominater::eCdMagenta;
	}


	return ColorDominater::eCdUnknown;
}

void SRColor::setDominater(ColorDominater dominater)
{
	switch (dominater) {
		case eCdBlack:
			red = 0;
			green = 0;
			blue = 0;
			break;
		case eCdGray:
			red = 0x80;
			green = 0x80;
			blue = 0x80;
			break;
		case eCdWhite:
			red = 0xFF;
			green = 0xFF;
			blue = 0xFF;
			break;
		case eCdRed:
			red = 0xFF;
			green = 0;
			blue = 0;
			break;
		case eCdGreen:
			red = 0;
			green = 0xFF;
			blue = 0;
			break;
		case eCdBlue:
			red = 0;
			green = 0;
			blue = 0xFF;
			break;
		case eCdYellow:
			red = 0xFF;
			green = 0xFF;
			blue = 0;
			break;
		case eCdCyan:
			red = 0;
			green = 0xFF;
			blue = 0xFF;
			break;
		case eCdMagenta:
			red = 0xFF;
			green = 0;
			blue = 0xFF;
			break;
		case eCdOrange:
			red = 0xFF;
			green = 0x80;
			blue = 0;
			break;
		case eCdLimeGreen:
			red = 0x80;
			green = 0xFF;
			blue = 0;
			break;
		case eCdCyanBlue:
			red = 0;
			green = 0x80;
			blue = 0xFF;
			break;
		case eCdLiteGreen:
			red = 0;
			green = 0xFF;
			blue = 0x80;
			break;
		case eCdManganous:
			red = 0xFF;
			green = 0;
			blue = 0x80;
			break;
		case eCdPurple:
			red = 0x80;
			green = 0;
			blue = 0xFF;
			break;
		case eCdUnknown:
			red = static_cast<unsigned char>(rand() % 255);
			green = static_cast<unsigned char>(rand() % 255);
			blue = static_cast<unsigned char>(rand() % 255);
			break;
	}
}

SRColor SRColor::invert()
{
	return SRColor(static_cast<unsigned char>(0xFF - red),
				   static_cast<unsigned char>(0xFF - green),
				   static_cast<unsigned char>(0xFF - blue));
}

SRColor SRColor::toRGBA()
{
	SRColor rgba = argb;
	unsigned char a = rgba.alpha;
	rgba.alpha = rgba.blue;
	rgba.blue = a;
	return rgba;
}

const char *SRColor::dominaterToString(ColorDominater dominater)
{
	switch (dominater) {
		case eCdBlack:
			return "black";
		case eCdGray:
			return "gray";
		case eCdWhite:
			return "white";
		case eCdRed:
			return "red";
		case eCdGreen:
			return "green";
		case eCdBlue:
			return "blue";
		case eCdYellow:
			return "yellow";
		case eCdCyan:
			return "cyan";
		case eCdMagenta:
			return "magenta";
		case eCdOrange:
			return "orange";
		case eCdLimeGreen:
			return "lime-green";
		case eCdCyanBlue:
			return "cyan-blue";
		case eCdLiteGreen:
			return "lite-green";
		case eCdManganous:
			return "manganous";
		case eCdPurple:
			return "purple";
		case eCdUnknown:
			return "unknown";
	}
}

ColorDominater SRColor::stringToDominater(const char *color)
{
	if (strcmp(strlwr(const_cast<char*>(color)), "black") == 0)
		return eCdBlack;
	else if (strcmp(strlwr(const_cast<char*>(color)), "gray") == 0)
		return eCdGray;
	else if (strcmp(strlwr(const_cast<char*>(color)), "white") == 0)
		return eCdWhite;
	else if (strcmp(strlwr(const_cast<char*>(color)), "red") == 0)
		return eCdRed;
	else if (strcmp(strlwr(const_cast<char*>(color)), "green") == 0)
		return eCdGreen;
	else if (strcmp(strlwr(const_cast<char*>(color)), "blue") == 0)
		return eCdBlue;
	else if (strcmp(strlwr(const_cast<char*>(color)), "yellow") == 0)
		return eCdYellow;
	else if (strcmp(strlwr(const_cast<char*>(color)), "cyan") == 0)
		return eCdCyan;
	else if (strcmp(strlwr(const_cast<char*>(color)), "magenta") == 0)
		return eCdMagenta;
	else if (strcmp(strlwr(const_cast<char*>(color)), "orange") == 0)
		return eCdOrange;
	else if (strcmp(strlwr(const_cast<char*>(color)), "lime-green") == 0)
		return eCdLimeGreen;
	else if (strcmp(strlwr(const_cast<char*>(color)), "cyan-blue") == 0)
		return eCdCyanBlue;
	else if (strcmp(strlwr(const_cast<char*>(color)), "lite-green") == 0)
		return eCdLiteGreen;
	else if (strcmp(strlwr(const_cast<char*>(color)), "manganous") == 0)
		return eCdManganous;
	else if (strcmp(strlwr(const_cast<char*>(color)), "purple") == 0)
		return eCdPurple;
	return eCdUnknown;
}
