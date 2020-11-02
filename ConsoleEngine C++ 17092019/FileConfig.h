#pragma once
#include "EngineCore.h"

class FileConfig
{
private:
	typedef std::string string;
	typedef unsigned char byte;
	string path, filename, filepath;

private:
	int length = 0;
	std::vector<byte> dataArray;
	std::vector<string> nameArray;

private:
	std::vector<bool> boolArray;
	std::vector<char> charArray;
	std::vector<unsigned char> uCharArray;
	std::vector<short> shortArray;
	std::vector<unsigned short> uShortArray;
	std::vector<int> intArray;
	std::vector<unsigned int> uIntArray;
	std::vector<float> floatArray;
	std::vector<double> doubleArray;
	std::vector<string> stringArray;

public:
	FileConfig(string path, string filename);
	~FileConfig();

private:
	template<typename T>
	void PushVectorsBack(byte data, string name, T content, std::vector<T>& vectorArray);
	template<typename T>
	T GetContent(string name, std::vector<T>& vectorArray);

public:
	void ClearMemory();

public:
	void WriteBool(bool value, string name);
	void WriteChar(char value, string name);
	void WriteUChar(unsigned char value, string name);
	void WriteShort(short value, string name);
	void WriteUShort(unsigned short value, string name);
	void WriteInt(int value, string name);
	void WriteUInt(unsigned int value, string name);
	void WriteFloat(float value, string name);
	void WriteDouble(double value, string name);
	void WriteString(string text, string name);

public:
	bool ReadBool(string name);
	char ReadChar(string name);
	unsigned char ReadUChar(string name);
	short ReadShort(string name);
	unsigned short ReadUShort(string name);
	int ReadInt(string name);
	unsigned int ReadUInt(string name);
	float ReadFloat(string name);
	double ReadDouble(string name);
	string ReadString(string name);

public:
	void FileSave();
	void FileLoad();
	void FileDelete();
};