#include "pch.h"
#include "globals.h"
#include "Location.h"
#include "Area.h"
#include "OffsetGeometry.h"

using namespace Json;
using namespace std;

offset_geometry::offset_geometry() : area(0,0,0,0)
{
	opacity_ = 0.0F;
	use_as_switch_ = false;
	center_ = false;
	offset_left_ = 0;
	offset_right_ = 0;
	offset_top_ = 0;
	offset_bottom_ = 0;
}

offset_geometry::offset_geometry(const location& top_left, const  int width, const int height, const area& crop_offset) : area(top_left, width, height)
{
	opacity_ = 0.0F;
	use_as_switch_ = false;
	set_location(top_left);
	set_width(width);
	set_height(height);
	offset_left_ = crop_offset.get_left();
	offset_top_ = crop_offset.get_top();
	offset_right_ = crop_offset.get_right();
	offset_bottom_ = crop_offset.get_bottom();
}

std::wstring offset_geometry::toString() const
{
	std::wostringstream oss;
	oss << std::fixed << std::showpoint;
	oss << get_area().toString();
	std::wstring buffer = oss.str();
	return buffer;
}

offset_geometry::~offset_geometry()
= default;

bool offset_geometry::get_use_as_switch() const
{
	return use_as_switch_;
}

float offset_geometry::get_opacity() const
{
	return opacity_;
}

area offset_geometry::get_area() const
{
	return area(get_location(), get_width(), get_height());
}

bool offset_geometry::get_center() const
{
	return center_;
}

void offset_geometry::set_area(const area& area)
{
	set_x(area.get_x());
	set_y(area.get_y());
	set_width(area.get_width());
	set_height(area.get_height());
	adjust_dimensions();
}

void offset_geometry::set_use_as_switch(bool use_as_switch)
{
	use_as_switch_ = use_as_switch;
}

void offset_geometry::set_center(const bool center)
{
	center_ = center;
}

void offset_geometry::set_opacity(const float opacity)
{
	opacity_ = opacity;
}

area offset_geometry::get_cropping_area() const
{
	return area(offset_left_, offset_top_, offset_right_, offset_bottom_);
}

void offset_geometry::set_cropping_area(const area& area)
{
	offset_left_ = area.get_left();
	offset_right_ = area.get_right();
	offset_top_ = area.get_top();
	offset_bottom_ = area.get_bottom();
}

bool offset_geometry::operator==(const offset_geometry& ref) const
{
	return	use_as_switch_ == ref.use_as_switch_ &&
			opacity_ == ref.opacity_ &&
			get_location() == ref.get_location() &&
			get_width() == ref.get_width() &&
			get_height() == ref.get_height();
}

bool offset_geometry::operator !=(const offset_geometry& ref) const
{
	return	use_as_switch_ != ref.use_as_switch_ ||
			opacity_ != ref.opacity_ ||
			get_location() != ref.get_location() ||
			get_width() != ref.get_width() ||
			get_height() != ref.get_height();
}

offset_geometry& offset_geometry::operator -= (const offset_geometry& ref)
{
	set_location(get_location() -= ref.get_location());
	set_width(get_width() - ref.get_width());
	set_height(get_height() - ref.get_height());
	return *this;
}

offset_geometry& offset_geometry::operator += (const offset_geometry& ref)
{
	set_location(get_location() += ref.get_location());
	set_width(get_width() + ref.get_width());
	set_height(get_height() + ref.get_height());
	return *this;
}

offset_geometry& offset_geometry::operator=(const offset_geometry& ref)
{
	opacity_ = ref.opacity_;
	use_as_switch_ = ref.use_as_switch_;
	set_location(ref.get_location());
	set_width(ref.get_width());
	set_height(ref.get_height());
	center_ = ref.center_;
	return *this;
}
