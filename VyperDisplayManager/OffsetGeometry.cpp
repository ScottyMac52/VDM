#include "pch.h"
#include "globals.h"
#include "json_check.h"
#include "Location.h"
#include "Area.h"
#include "OffsetGeometry.h"

using namespace json;
using namespace std;

#pragma region ctor and dtor

offset_geometry::offset_geometry() : area(0, 0, 0, 0)
{
	opacity_ = 0.0F;
	use_as_switch_ = false;
	center_ = false;
	offset_left_ = 0;
	offset_right_ = 0;
	offset_top_ = 0;
	offset_bottom_ = 0;
}

offset_geometry::offset_geometry(const offset_geometry& source)
	: area(source)
{
	opacity_ = source.opacity_;
	use_as_switch_ = source.use_as_switch_;
	center_ = source.center_;
	offset_left_ = source.offset_left_;
	offset_right_ = source.offset_right_;
	offset_top_ = source.offset_top_;
	offset_bottom_ = source.offset_bottom_;
}

offset_geometry::offset_geometry(const offset_geometry&& move) noexcept
{
	*this = move;
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

offset_geometry::~offset_geometry()
= default;

#pragma endregion ctor and dtor

#pragma region to_string()

std::wstring offset_geometry::to_string() const
{
	std::wostringstream oss;
	oss << std::fixed << std::showpoint;
	oss << get_area().to_string();
	std::wstring buffer = oss.str();
	return buffer;
}

#pragma endregion to_string()

#pragma region get methods

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

area offset_geometry::get_cropping_area() const
{
	return area(offset_left_, offset_top_, offset_right_, offset_bottom_);
}

#pragma endregion get methods

#pragma region set methods

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


void offset_geometry::set_cropping_area(const area& area)
{
	offset_left_ = area.get_left();
	offset_right_ = area.get_right();
	offset_top_ = area.get_top();
	offset_bottom_ = area.get_bottom();
}

#pragma endregion set methods

#pragma region json

json::Object offset_geometry::to_json_object() const
{
	auto object = area::to_json_object();
	set_object_property(object, L"useAsSwitch", get_use_as_switch());
	set_object_property(object, L"opacity", opacity_);
	set_object_property(object, L"center", center_);
	set_object_property(object, L"xOffsetStart", offset_left_);
	set_object_property(object, L"xOffsetFinish", offset_right_);
	set_object_property(object, L"yOffsetStart", offset_top_);
	set_object_property(object, L"yOffsetFinish", offset_bottom_);
	return object;
}

void offset_geometry::from_json_object(const json::Object& object)
{
	auto left = 0, top = 0, right = 0, bottom = 0;
	area::from_json_object(object);
	if (property_exists(object, L"xOffsetStart"))
	{
		left = Integer(object[L"xOffsetStart"]).Value();
	}

	if (property_exists(object, L"xOffsetFinish"))
	{
		right = Integer(object[L"xOffsetFinish"]).Value();
	}

	if (property_exists(object, L"yOffsetStart"))
	{
		top = Integer(object[L"yOffsetStart"]).Value();
	}

	if (property_exists(object, L"yOffsetFinish"))
	{
		bottom = Integer(object[L"yOffsetFinish"]).Value();
	}
	set_cropping_area(area(left, top, right, bottom));

	if (property_exists(object, L"useAsSwitch"))
	{
		set_use_as_switch(Boolean(object[L"useAsSwitch"]).Value());
	}

	if (property_exists(object, L"opacity"))
	{
		set_opacity(Number(object[L"opacity"]).Value());
	}

	if (property_exists(object, L"center"))
	{
		set_use_as_switch(Boolean(object[L"center"]).Value());
	}
}

#pragma endregion json

#pragma region operators

offset_geometry& offset_geometry::operator=(const offset_geometry& ref)
{
	if (this == &ref)
		return *this;

	set_area(ref.get_area());
	set_cropping_area(ref.get_cropping_area());
	opacity_ = ref.opacity_;
	use_as_switch_ = ref.use_as_switch_;
	center_ = ref.center_;
	return *this;
}

offset_geometry& offset_geometry::operator=(offset_geometry&& ref) noexcept
{
	*this = ref;
	return *this;
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

#pragma endregion operators

