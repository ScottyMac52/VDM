#include "pch.h"
#include "globals.h"
#include "json_check.h"
#include "Location.h"

using namespace std;
using namespace json;

#pragma region ctr and dtor

location::location()
{
	x_ = 0;
	y_ = 0;
}

location::location(const location& copy)
{
	x_ = copy.x_;
	y_ = copy.y_;
}

location::location(const location&& move) noexcept
{
	*this = move;
}

location::~location()
= default;

#pragma endregion ctr and dtor

#pragma region to_string

std::wstring location::to_string() const
{
	std::wostringstream oss;
	oss << std::fixed << std::showpoint;
	oss << "(" << setprecision(0) << x_ << ", " << setprecision(0) << y_ << ")";
	std::wstring buffer = oss.str();
	return buffer;

}

#pragma endregion to_string

#pragma region get methods

int location::get_x() const
{
	return x_;
}

int location::get_y() const
{
	return y_;
}

float location::get_distance(const location& ref) const
{
	return get_distance(*this, ref);
}

float location::get_distance(const location& ref, const location& ref2) const
{
	const auto a = static_cast<float>(abs(ref2.x_ - ref.x_));
	const auto b = static_cast<float>(abs(ref2.y_ - ref.y_));
	return hypotf(a, b);
}

#pragma endregion get methods

#pragma region json

json::Object location::to_json_object() const
{
	json::Object object;
	set_object_property(object, L"left", x_);
	set_object_property(object, L"top", y_);
	return object;
}

void location::from_json_object(const json::Object& object)
{
	if (property_exists(object, L"left"))
	{
		x_ = Integer(object[L"left"]).Value();
	}

	if (property_exists(object, L"top"))
	{
		y_ = Integer(object[L"top"]).Value();
	}
}

#pragma endregion json

#pragma region set methods

void location::set_x(const int& x)
{
	x_ = x;
}

void location::set_y(const int& y)
{
	y_ = y;
}

#pragma endregion set methods

#pragma region operators

bool location::operator==(const location& ref) const
{
	return x_ == ref.x_ && y_ == ref.y_;
}

bool location::operator!=(const location& ref) const
{
	return x_ != ref.x_ || y_ != ref.y_;
}

location& location::operator-=(const location& ref)
{
	x_ -= ref.x_;
	y_ -= ref.y_;
	return *this;
}

location& location::operator+=(const location& ref)
{
	x_ += ref.x_;
	y_ += ref.y_;
	return *this;
}

location& location::operator=(const location& ref)
{
	if (this == &ref)
		return *this;

	set_x(ref.get_x());
	set_y(ref.get_y());
	return *this;
}

location& location::operator=(location&& ref) noexcept
{
	*this = ref;
	return *this;
}

#pragma endregion operators

