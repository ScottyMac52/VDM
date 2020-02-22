#include "pch.h"
#include "json.h"
#include "JsonObject.h"

using namespace std;
using  namespace Json;

JsonObject::JsonObject()
{
	_value = Json::Value();
	_readerBuilder = Json::CharReaderBuilder::CharReaderBuilder();
}

int JsonObject::getHashCode() const
{
	return _value.asInt();
}

std::wstring JsonObject::toString() const
{
	std::wostringstream oss;
	oss << std::fixed << std::showpoint;
	oss << _value.asCString();
	std::wstring buffer = oss.str();
	return buffer;
}
