#include "pch.h"
#include "globals.h"
#include "Location.h"
#include "Area.h"
#include "OffsetGeometry.h"
#include "ImageConfiguration.h"

using namespace Json;
using namespace std;

image_configuration::image_configuration()
= default;

image_configuration::image_configuration(const LPCWSTR name, const LPCWSTR file_path, const LPCWSTR file_name, const float opacity, const area& image_area, const area& cropping_area)
{
	name_ = name;
	file_path_ = file_path;
	file_name_ = file_name;
	set_opacity(opacity);
	set_area(image_area);
	cropping_area_ = cropping_area;
}

image_configuration::~image_configuration()
= default;
