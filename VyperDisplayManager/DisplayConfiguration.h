#pragma once
class display_configuration :
	public offset_geometry
{
public:
	std::wstring get_name() const;
	Json::Value to_json() const override;
	void json_save(const std::wstring json);
	void json_load(const std::wstring json);
protected:
private:
	std::wstring name_;
};

