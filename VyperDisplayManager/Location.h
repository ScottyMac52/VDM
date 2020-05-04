#pragma once
/// <summary>
/// Defines an X,Y coordinate
/// </summary>
class location :
	protected json_check
{
public:

	/// <summary>
	/// Default ctor
	/// </summary>
	location();
	/// <summary>
	/// Constructor with coordinates
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	explicit location(const int x, const int y)
	{
		x_ = x;
		y_ = y;
	}
	/// <summary>
	/// copy ctor
	/// </summary>
	/// <param name="copy"></param>
	location(const location& copy);
	/// <summary>
	/// move ctor
	/// </summary>
	/// <param name="move"></param>
	location(const location&& move) noexcept;
	/// <summary>
	/// Destructor
	/// </summary>
	virtual ~location();
	/// <summary>
	/// Human readable
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] virtual std::wstring to_string() const;
	/// <summary>
	/// Gets the X value of the location
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] int get_x() const;
	/// <summary>
	/// Gets the Y value of the location
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] int get_y() const;
	/// <summary>
	/// Gets the distance between this location and another one
	/// </summary>
	/// <param name="ref"></param>
	/// <returns></returns>
	[[nodiscard]] float get_distance(const location& ref) const;
	/// <summary>
	/// Gets the distance between two locations
	/// </summary>
	/// <param name="ref"></param>
	/// <param name="ref2"></param>
	/// <returns></returns>
	[[nodiscard]] float get_distance(const location& ref, const location& ref2) const;
	/// <summary>
	/// overridden to_json_object() 
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] json::Object to_json_object() const override;
	/// <summary>
	/// overridden from_json_object()
	/// </summary>
	/// <param name="object"></param>
	void from_json_object(const json::Object& object) override;
	/// <summary>
	/// operator = for assignment
	/// </summary>
	/// <param name="ref"></param>
	/// <returns></returns>
	location& operator=(const location& ref);
	/// <summary>
	/// move assignment operator
	/// </summary>
	/// <param name="ref"></param>
	/// <returns></returns>
	location& operator=(location&& ref) noexcept;
	/// <summary>
	/// Determines if this location is the same as another
	/// </summary>
	/// <param name="ref"></param>
	/// <returns></returns>
	bool operator ==(const location& ref) const;
	/// <summary>
	/// Determines of this location is NOT the same as another
	/// </summary>
	/// <param name="ref"></param>
	/// <returns></returns>
	bool operator !=(const location& ref) const;
	/// <summary>
	/// Changes the current location by (-x,-y)
	/// </summary>
	/// <param name="ref"></param>
	/// <returns></returns>
	location& operator -=(const location& ref);
	/// <summary>
	/// Changes the current location by (+x,+y)
	/// </summary>
	/// <param name="ref"></param>
	/// <returns></returns>
	location& operator +=(const location& ref);
protected:
	/// <summary>
	/// Sets the X value of the location
	/// </summary>
	/// <param name="x"></param>
	void set_x(const int& x);
	/// <summary>
	/// Sets the Y value of the location
	/// </summary>
	/// <param name="y"></param>
	void set_y(const int& y);
	// Operators
private:
	/// <summary>
	/// The X coordinate
	/// </summary>
	int x_{};
	/// <summary>
	/// The Y coordinate
	/// </summary>
	int y_{};
};

