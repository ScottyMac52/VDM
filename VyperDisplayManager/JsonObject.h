#pragma once
class JsonObject
{
public:
	JsonObject();
	virtual int getHashCode() const;
	virtual std::wstring toString() const;
protected:
	Json::Value _value;
	Json::CharReaderBuilder _readerBuilder;
private:
};

