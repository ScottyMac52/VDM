#include "pch.h"
#include "globals.h"
#include "Location.h"

using namespace std;
using namespace Json;

location::~location()
{
}

std::wstring location::toString() const
{
	std::wostringstream oss;
	oss << std::fixed << std::showpoint;
	oss << "(" << x_ << ", " << y_ << ")";
	std::wstring buffer = oss.str();
	return buffer;

}

void location::off_set(const location& ref)
{
	*this += ref;
}

location location::get_start()
{
	return location(0, 0);
}

int location::get_x() const
{
	return x_;
}

int location::get_y() const
{
	return y_;
}


void location::set_x(const int x)
{
	x_ = x;
}

void location::set_y(const int y)
{
	y_ = y;
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
/*
location& location::operator=(const location& ref)
{
	x_= ref.x_;
	y_ = ref.y_;
	return *this;
}
*/

