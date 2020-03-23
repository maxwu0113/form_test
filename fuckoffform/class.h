#pragma once
using namespace System;
public ref class MyItem
{
public: MyItem(System::String^ displayName, System::Int32 readValue)
{
	this->DisplayName = displayName;
	this->ReadValue = readValue;
}
private: System::String^ DisplayName;
private: System::Int32 ReadValue;
public: System::Int32 readvalue()
{
	return ReadValue;
}
public: System::String^ ToString() override
{
	return this->DisplayName;
}
};
