#pragma once

// Forward declaration
class area;

class offset_geometry :
	public area
{
public:
	/// <summary>
	/// ctor
	/// </summary>
	offset_geometry();
	/// <summary>
	/// copy ctor
	/// </summary>
	/// <param name="source"></param>
	offset_geometry(const offset_geometry& source);
	/// <summary>
	/// move ctor
	/// </summary>
	/// <param name="move"></param>
	/// <returns></returns>
	offset_geometry(const offset_geometry&& move) noexcept;
	/// <summary>
	/// alternate ctor
	/// </summary>
	/// <param name="top_left"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="crop_offset"></param>
	offset_geometry(const location& top_left, const int width, const int height, const area& crop_offset = area(0,0,0,0));
	/// <summary>
	/// dtor
	/// </summary>
	virtual ~offset_geometry();
	/// <summary>
	/// to_string()
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] virtual std::wstring to_string() const override;
	/// <summary>
	/// Get the use_as_switch setting
	/// </summary>
	/// <returns>bool</returns>
	[[nodiscard]] bool get_use_as_switch() const;
	/// <summary>
	/// Get the opacity setting
	/// </summary>
	/// <returns>float</returns>
	[[nodiscard]] float get_opacity() const;
	/// <summary>
	/// Gets the current Area
	/// </summary>
	/// <returns>Area</returns>
	[[nodiscard]] area get_area() const;
	/// <summary>
	/// Gets the center setting
	/// </summary>
	/// <returns>bool</returns>
	[[nodiscard]] bool  get_center() const;
	/// <summary>
	/// Sets the current Area
	/// </summary>
	/// <param name="area"></param>
	void set_area(const area& area);
	/// <summary>
	/// Sets the UseAsSwitch parameter
	/// </summary>
	/// <param name="use_as_switch"></param>
	void set_use_as_switch(const bool use_as_switch);
	/// <summary>
	/// set center
	/// </summary>
	/// <param name="center"></param>
	void set_center(const bool center);
	/// <summary>
	/// Sets the Opacity
	/// </summary>
	/// <param name="opacity"></param>
	void set_opacity(const float opacity);
	/// <summary>
	/// Gets the Area that will be cropped 
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] area get_cropping_area() const;
	/// <summary>
	/// Sets the area to crop
	/// </summary>
	/// <param name="area"></param>
	void set_cropping_area(const area& area);
	// Operators
	/// <summary>
	/// assignment operator
	/// </summary>
	/// <param name="ref"></param>
	/// <returns></returns>
	offset_geometry& operator=(const offset_geometry& ref);
	/// <summary>
	/// move assignment operator
	/// </summary>
	/// <param name="ref"></param>
	/// <returns></returns>
	offset_geometry& operator=(offset_geometry&& ref) noexcept;
	/// <summary>
	/// equality operator
	/// </summary>
	/// <param name="ref"></param>
	/// <returns></returns>
	bool operator ==(const offset_geometry& ref) const;
	/// <summary>
	/// non equality operator
	/// </summary>
	/// <param name="ref"></param>
	/// <returns></returns>
	bool operator !=(const offset_geometry& ref) const;
	/// <summary>
	/// decrease = operator
	/// </summary>
	/// <param name="ref"></param>
	/// <returns></returns>
	offset_geometry& operator -= (const offset_geometry& ref);
	/// <summary>
	/// increase = operator
	/// </summary>
	/// <param name="ref"></param>
	/// <returns></returns>
	offset_geometry& operator += (const offset_geometry& ref);
	/// <summary>
	/// to_json_object()
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] virtual json::Object to_json_object() const override;
	/// <summary>
	/// from_json_object()
	/// </summary>
	/// <param name="object"></param>
	virtual void from_json_object(const json::Object& object) override;
protected:
	int offset_left_ = 0;
	int offset_top_ = 0;
	int offset_right_ = 0;
	int offset_bottom_ = 0;
private:
	bool use_as_switch_ = false;
	float opacity_ = 1.0F;
	bool center_ = false;
};

