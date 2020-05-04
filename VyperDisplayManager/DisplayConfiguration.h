#pragma once

class display_configuration :
	 public offset_geometry
{
public:
	[[nodiscard]] std::wstring get_key() const;
	[[nodiscard]] virtual json::Object to_json_object() const override;
	virtual void from_json_object(const json::Object& object) override;
	list<display_configuration> from_json(std::wstringstream& stream) const;
	display_configuration& operator=(const json::Object& object);
protected:
private:
	std::wstring key_;
};

