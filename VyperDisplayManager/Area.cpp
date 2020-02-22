#include "pch.h"
#include "globals.h"
#include "Location.h"
#include "Area.h"

using namespace Json;
using namespace std;

area::area(): location(0,0)
{
	width_ = 0;
	height_ = 0;
	right_ = 0;
	bottom_ = 0;
}

area::area(const location& loc, const int width, const int height): location(loc.get_x(), loc.get_y())
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

std::wstring area::toString() const
{
	std::wostringstream oss;
	oss << std::fixed << std::showpoint;
	oss << get_location().toString() << " -> Size: (" << width_ << ", " << height_  << ")";
	std::wstring buffer = oss.str();
	return buffer;
}

RECT area::to_rect() const
{
	RECT rect;
	rect.left = get_x();
	rect.top = get_y();
	rect.right = right_;
	rect.bottom = bottom_;

	return rect;
}

Json::Value area::to_json() const
{
	Json::Value value(Json::objectValue);
	value["left"] = get_left();
	value["top"] = get_top();
	value["width"] = get_width();
	value["height"] = get_height();
	return value;
}


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

location area::get_location() const
{
	return location(get_x(),  get_y());
}

void area::set_location(const location& location)
{
	set_x(location.get_x());
	set_y(location.get_y());
	adjust_dimensions();
}

int area::get_square_area() const
{
	return width_ * height_;
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

area& area::operator=(const area& ref)
{
	set_x(ref.get_x());
	set_y(ref.get_y());
	width_ = ref.width_;
	height_ = ref.height_;
	adjust_dimensions();
	return *this;
}

void area::adjust_dimensions()
{
	right_ = get_x() + width_;
	bottom_ = get_y() + height_;
}

