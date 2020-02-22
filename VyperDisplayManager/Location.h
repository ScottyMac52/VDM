#pragma once
/// <summary>
/// Defines an X,Y coordinate
/// </summary>
class location 
	: public JsonObject
{
public:

	/// <summary>
	/// Constructor with coordinates
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	explicit location(const int x = 0, const int y = 0)
	{
		x_ = x;
		y_ = y;
	}
	/// <summary>
	/// Destructor
	/// </summary>
	virtual ~location();
	/// <summary>
	/// Human readable
	/// </summary>
	/// <returns></returns>
	std::wstring toString() const override;
	/// <summary>
	/// Offsets the current location by the specified x,y offset/>
	/// </summary>
	/// <param name="ref"></param>
	void off_set(const location& ref);
	/// <summary>
	/// Gets a default location of (0,0)
	/// </summary>
	/// <returns></returns>
	static location get_start();
	/// <summary>
	/// Gets the X value of the location
	/// </summary>
	/// <returns></returns>
	int get_x() const;
	/// <summary>
	/// Gets the Y value of the location
	/// </summary>
	/// <returns></returns>
	int get_y() const;
	/// <summary>
	/// Gets the distance between this location and another one
	/// </summary>
	/// <param name="ref"></param>
	/// <returns></returns>
	float get_distance(const location& ref) const;
	/// <summary>
	/// Gets the distance between two locations
	/// </summary>
	/// <param name="ref"></param>
	/// <param name="ref2"></param>
	/// <returns></returns>
	float get_distance(const location& ref, const location& ref2) const;
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
	/// <summary>
	/// Sets the location equal to another
	/// </summary>
	/// <param name="ref"></param>
	/// <returns></returns>
	//location& operator =(const location& ref);
	location& operator=(const location& ref)
	{
		x_ = ref.x_;
		y_ = ref.y_;
		return *this;
	}
protected:
	/// <summary>
	/// Sets the X value of the location
	/// </summary>
	/// <param name="x"></param>
	void set_x(const int x);
	/// <summary>
	/// Sets the Y value of the location
	/// </summary>
	/// <param name="y"></param>
	void set_y(const int y);
	// Operators
private:
	/// <summary>
	/// The X coordinate
	/// </summary>
	int x_;
	/// <summary>
	/// The Y coordinate
	/// </summary>
	int y_;
};

