#include "pch.h"
#include "globals.h"
#include "json_check.h"
#include "Location.h"
#include "Area.h"

using namespace json;
using namespace std;

#pragma region ctor and dtor

area::area() : location(0, 0)
{
	width_ = 0;
	height_ = 0;
	right_ = 0;
	bottom_ = 0;
}

area::area(const area& copy)
	: location(copy)
{
	width_ = copy.width_;
	height_ = copy.height_;
	right_ = copy.right_;
	bottom_ = copy.bottom_;
}

area::area(const area&& move) noexcept
{
	*this = move;
}

area::area(const location& loc, const int width, const int height) : location(loc.get_x(), loc.get_y())
{
	width_ = width;
	height_ = height;
	right_ = loc.get_x() + width;
	bottom_ = loc.get_y() + height;
}

area::area(const int left, const int  top, const int right, const int bottom) : location(left, top)
{
	right_ = right;
	bottom_ = bottom;
	width_ = abs(right_ - get_x());
	height_ = abs(bottom_ - get_y());
}

area::~area()
= default;

#pragma endregion ctor and dtor

#pragma region to_string()

std::wstring area::to_string() const
{
	std::wostringstream oss;
	oss << std::fixed << std::showpoint;
	oss << get_location().to_string() << " -> Size: (" << setprecision(0) << width_ << ", " << setprecision(0) << height_  << ")";
	std::wstring buffer = oss.str();
	return buffer;
}

#pragma endregion to_string()

#pragma region json

json::Object area::to_json_object() const
{
	auto object = location::to_json_object();
	set_object_property(object, L"width", get_width());
	set_object_property(object, L"height", get_height());
	return object;
}

void area::from_json_object(const json::Object& object)
{
	auto width_specified = false;
	auto height_specified = false;

	location::from_json_object(object);
	if (property_exists(object, L"width"))
	{
		set_width(Integer(object[L"width"]).Value());
		width_specified = true;
	}

	if (property_exists(object, L"height"))
	{
		set_height(Integer(object[L"height"]).Value());
		height_specified = true;
	}

	if (width_specified)
	{
		right_ = get_left() + width_;
	}
	else
	{
		width_ = abs(get_right() - get_left());
	}

	if (height_specified)
	{
		bottom_ = get_top() + height_;
	}
	else
	{
		height_ = abs(get_bottom() - get_top());
	}

}

#pragma endregion json

#pragma region get methods

int area::get_left() const
{
	return get_x();
}

int area::get_top() const
{
	return get_y();
}

int area::get_right() const
{
	return right_;
}

int area::get_bottom() const
{
	return bottom_;
}

int area::get_width() const
{
	return width_;
}

int area::get_height() const
{
	return height_;
}

location area::get_location() const
{
	return location(get_x(), get_y());
}

int area::get_square_area() const
{
	return width_ * height_;
}

#pragma endregion get methods

#pragma region set methods

void area::set_left(const int left)
{
	set_x(left);
	adjust_dimensions();
}

void area::set_top(const int top)
{
	set_y(top);
	adjust_dimensions();
}

void area::set_width(const int width)
{
	width_ = width;
	adjust_dimensions();
}

void area::set_height(const int height)
{
	height_ = height;
	adjust_dimensions();
}

void area::set_location(const location& location)
{
	set_x(location.get_x());
	set_y(location.get_y());
	adjust_dimensions();
}

#pragma endregion set methods

#pragma region operators

area& area::operator=(const area& ref)
{
	if (this == &ref)
		return *this;

	set_location(ref.get_location());
	width_ = ref.width_;
	height_ = ref.height_;
	adjust_dimensions();
	return *this;
}

area& area::operator=(area&& ref) noexcept
{
	*this = ref;
	return *this;
}

bool area::operator==(const area& ref) const
{
	return	get_x() == ref.get_x() &&
			get_y() == ref.get_y() &&
			width_ == ref.width_ &&
			height_ == ref.height_ &&
			right_ == ref.right_ &&
			bottom_ == ref.bottom_;
}

bool area::operator!=(const area& ref) const
{
	return	get_x() != ref.get_x() ||
			get_y() != ref.get_y() ||
			width_ != ref.width_ ||
			height_ != ref.height_ ||
			right_ != ref.right_ ||
			bottom_ != ref.bottom_;
}

area& area::operator-=(const int factor)
{
	width_ -= factor;
	height_ -= factor;
	adjust_dimensions();
	return *this;
}

area& area::operator-=(const area& ref)
{
	set_x(get_x() - ref.get_x());
	set_y(get_y() - ref.get_y());
	width_ -= ref.width_;
	height_ -= ref.height_;
	adjust_dimensions();
	return *this;
}

area& area::operator*=(const int factor)
{
	width_ *= factor;
	height_ *= factor;
	adjust_dimensions();
	return *this;
}

area& area::operator/=(const int factor)
{
	width_ /= factor;
	height_ /= factor;
	adjust_dimensions();
	return *this;
}

area& area::operator+=(const int factor)
{
	width_ += factor;
	height_ += factor;
	adjust_dimensions();
	return *this;
}

area& area::operator+=(const area& ref)
{
	set_x(get_x() + ref.get_x());
	set_y(get_y() + ref.get_y());
	width_ += ref.width_;
	height_ += ref.height_;
	adjust_dimensions();
	return *this;
}

#pragma endregion operators

#pragma region area adjustment

void area::adjust_dimensions(const bool adjust_location)
{
	if (adjust_location)
	{
		set_left(right_ - width_);
		set_top(bottom_ - height_);
	}
	else
	{
		right_ = get_x() + width_;
		bottom_ = get_y() + height_;
	}
}

#pragma endregion area adjustment
