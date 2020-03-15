#pragma once
/// <summary>
/// Defines a Location that also has width and height
/// </summary>
class area :
	public location
{
public:
	/// <summary>
	/// Ctor default
	/// </summary>
	area();
	/// <summary>
	/// copy ctor
	/// </summary>
	/// <param name="copy"></param>
	area(const area& copy);
	/// <summary>
	/// moce ctor
	/// </summary>
	/// <param name="move"></param>
	/// <returns></returns>
	area(const area&& move) noexcept;
	/// <summary>
	/// Ctor
	/// </summary>
	/// <param name="loc"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	explicit area(const location& loc, const int width = 0, const int height = 0);
	/// <summary>
	/// Creates an area using the four coordinates 
	/// </summary>
	/// <param name="left"></param>
	/// <param name="top"></param>
	/// <param name="right"></param>
	/// <param name="bottom"></param>
	area(const int left, const int top, const int right, const int bottom);
	/// <summary>
	/// Destructor
	/// </summary>
	virtual ~area();
	/// <summary>
	/// Human readable
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] virtual std::wstring to_string() const override;
	/// <summary>
	/// transforms the class into a json::Object
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] virtual json::Object to_json_object() const override;
	/// <summary>
	/// imports a json::Object as a class instance
	/// </summary>
	/// <param name="object"></param>
	virtual void from_json_object(const json::Object& object) override;
	/// <summary>
	/// Reads the Left coordinate of the Area, Location's X
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] int get_left() const;
	/// <summary>
	/// Reads the Top coordinate of the Area, Location's Y
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] int get_top() const;
	/// <summary>
	/// Reads the Right coordinate of the Area, Location X + Width
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] int get_right() const;
	/// <summary>
	/// Reads the Bottom coordinate of the Area, Location Y + Height
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] int get_bottom() const;
	/// <summary>
	/// Reads the Width of the Area
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] int get_width() const;
	/// <summary>
	/// Reads the Height of the Area
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] int get_height() const;
	/// <summary>
	/// Gets the Location of the Area, Location(X,Y)
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] location get_location() const;
	/// <summary>
	/// Gets the square area of the Area, Width * Height
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] int get_square_area() const;
	/// <summary>
	/// Writes the Left coordinate of the Area, Location X
	/// </summary>
	/// <param name="left"></param>
	void set_left(const int left);
	/// <summary>
	/// Writes the Top  coordinate of the Area, Location Y 
	/// </summary>
	/// <param name="top"></param>
	void set_top(const int top);
	/// <summary>
	/// Writes the Width of the Area 
	/// </summary>
	/// <param name="width"></param>
	void set_width(const int width);
	/// <summary>
	/// Writes the Height of the Area
	/// </summary>
	/// <param name="height"></param>
	void set_height(const int height);
	/// <summary>
	/// Writes a new Location for the Area, Location(X,Y) Width and Height are not affected
	/// </summary>
	/// <param name="location"></param>
	void set_location(const location& location);
	/// <summary>
	/// Determines if the area is exactly the same as another
	/// </summary>
	/// <param name="ref"></param>
	/// <returns></returns>
	bool operator ==(const area& ref) const;
	/// <summary>
	/// Determines if the area is different from another
	/// </summary>
	/// <param name="ref"></param>
	/// <returns></returns>
	bool operator !=(const area& ref) const;
	/// <summary>
	/// Decreases the size by factor, Affects both Width and Height 
	/// </summary>
	/// <param name="factor"></param>
	/// <returns></returns>
	area& operator-=(const int factor);
	/// <summary>
	/// Shrinks the Area by Area, Area(Location(X,Y), Width, Height)
	/// </summary>
	/// <param name="ref"></param>
	/// <returns></returns>
	area& operator -=(const area& ref);
	/// <summary>
	/// Increases the size by factor times, Affects both Width and Height 
	/// </summary>
	/// <param name="factor"></param>
	/// <returns></returns>
	area& operator*=(const int factor);
	/// <summary>
	/// Decreases the size by factor times, Affects both Width and Height 
	/// </summary>
	/// <param name="factor"></param>
	/// <returns></returns>
	area& operator/=(const int factor);
	/// <summary>
	/// increases the size by factor, Affects both Width and Height 
	/// </summary>
	/// <param name="factor"></param>
	/// <returns></returns>
	area& operator+=(const int factor);
	/// <summary>
	/// Grows the Area by Area, Area(Location(X,Y), Width, Height)
	/// </summary>
	/// <param name="ref"></param>
	/// <returns></returns>
	area& operator +=(const area& ref);
	/// <summary>
	/// Sets the Area exactly equal to another Area
	/// </summary>
	/// <param name="ref"></param>
	/// <returns></returns>
	area& operator =(const area& ref);
	/// <summary>
	/// move assignment operator
	/// </summary>
	/// <param name="ref"></param>
	/// <returns></returns>
	area& operator =(area&& ref) noexcept;
protected:
	/// <summary>
	/// Ensures the Right and Bottom coordinates are based on the Location(X,Y) + (Width,Height)
	/// <param name="adjust_location"</param>
	/// </summary>
	void adjust_dimensions(bool adjust_location = false);
private:
	/// <summary>
	/// Width of the Area
	/// </summary>
	int width_ = 0;
	/// <summary>
	/// Height of the Area
	/// </summary>
	int height_ = 0;
	/// <summary>
	/// The right top
	/// </summary>
	int right_ = 0;
	/// <summary>
	/// the right bottom
	/// </summary>
	int bottom_ = 0;
};

