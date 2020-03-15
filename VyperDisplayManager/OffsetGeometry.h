#pragma once

// Forward declaration
class area;

class offset_geometry :
	public area
{
public:
	offset_geometry();
	offset_geometry(const location& top_left, const int width, const int height, const area& crop_offset = area(0,0,0,0));
	[[nodiscard]] virtual std::wstring to_string() const override;
	virtual ~offset_geometry();
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
	bool operator ==(const offset_geometry& ref) const;
	bool operator !=(const offset_geometry& ref) const;
	offset_geometry& operator -= (const offset_geometry& ref);
	offset_geometry& operator += (const offset_geometry& ref);
	offset_geometry& operator = (const offset_geometry& ref);
	[[nodiscard]] virtual json::Object to_json_object() const override;
	virtual void from_json_object(const json::Object& object) override;
protected:
	int offset_left_;
	int offset_top_;
	int offset_right_;
	int offset_bottom_;
private:
	bool use_as_switch_;
	float opacity_;
	bool center_;
};

