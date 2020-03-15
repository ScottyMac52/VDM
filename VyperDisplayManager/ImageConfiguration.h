#pragma once
class image_configuration :
	public offset_geometry
{
public:
	image_configuration();
	image_configuration(LPCWSTR name, LPCWSTR file_path, LPCWSTR file_name, const float opacity, const area& image_area, const area& cropping_area);
	~image_configuration();
	[[nodiscard]] virtual std::wstring to_string() const override;
	[[nodiscard]] virtual json::Object to_json_object() const override;
	virtual void from_json_object(const json::Object& object) override;
protected:
private:
	std::wstring file_name_;
	std::wstring file_path_;
	std::wstring module_n_ame_;
	std::wstring name_;
	area cropping_area_;
};

