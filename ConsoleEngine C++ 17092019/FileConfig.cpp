#include "FileConfig.h"
#include <fstream>
#define DATANULL 0
#define DATABOOL 'b'
#define DATACHAR 'c'
#define DATAUCHAR 'C'
#define DATASHORT 's'
#define DATAUSHORT 'S'
#define DATAINT 'i'
#define DATAUINT 'I'
#define DATAFLOAT 'f'
#define DATADOUBLE 'd'
#define DATASTRING 't'

using namespace std;

// Contruct & Deconstuct section*******************************************************************************************************
FileConfig::FileConfig(string path, string filename)
	: path(path), filename(filename)
{
	filepath = path + filename;
	ifstream inFile(path + filename);

	// Checks if file don't exist, then generate new file
	if (inFile.fail())
		fstream file(filename, ios::in | ios::out | ios::app);
	else
		FileLoad();
}
FileConfig::~FileConfig() 
{
	ClearMemory();
};

// General section ********************************************************************************************************************
template<typename T>
void FileConfig::PushVectorsBack(byte data, string name, T content, std::vector<T>& vectorArray)
{
	// If name already exist, then override the content and datatype
	for (int i = 0; i < length; i++) {
		if (nameArray[i] == name) {
			dataArray[i] = data;
			vectorArray[i] = content;
			return;
		}
	}

	// For indentifier
	dataArray.push_back(data);
	nameArray.push_back(name);

	// For datatypes
	boolArray.push_back(0);
	charArray.push_back(0);
	uCharArray.push_back(0);
	shortArray.push_back(0);
	uShortArray.push_back(0);
	intArray.push_back(0);
	uIntArray.push_back(0);
	floatArray.push_back(0);
	doubleArray.push_back(0);
	stringArray.push_back("");

	// Sets content
	vectorArray[length] = content;

	length = stringArray.size();
}
template<typename T>
T FileConfig::GetContent(string name, std::vector<T>& vectorArray)
{
	for (int i = 0; i < length; i++)
		if (nameArray[i] == name)
			return vectorArray[i];
	return 0;
}
void FileConfig::ClearMemory()
{
	length = 0;
	dataArray.clear();
	nameArray.clear();

	boolArray.clear();
	charArray.clear();
	uCharArray.clear();
	shortArray.clear();
	uShortArray.clear();
	intArray.clear();
	uIntArray.clear();
	floatArray.clear();
	doubleArray.clear();
	stringArray.clear();
}

// Write section **********************************************************************************************************************
void FileConfig::WriteBool(bool value, string name)				{ PushVectorsBack(DATABOOL, name, value, boolArray);         }
void FileConfig::WriteChar(char value, string name)				{ PushVectorsBack(DATACHAR, name, value, charArray);         }
void FileConfig::WriteUChar(unsigned char value, string name)   { PushVectorsBack(DATAUCHAR, name, value, uCharArray);       }
void FileConfig::WriteShort(short value, string name)           { PushVectorsBack(DATASHORT, name, value, shortArray);       }
void FileConfig::WriteUShort(unsigned short value, string name) { PushVectorsBack(DATAUSHORT, name, value, uShortArray);     }
void FileConfig::WriteInt(int value, string name)				{ PushVectorsBack(DATAINT, name, value, intArray);		      }
void FileConfig::WriteUInt(unsigned int value, string name)     { PushVectorsBack(DATAUINT, name, value, uIntArray);         }
void FileConfig::WriteFloat(float value, string name)           { PushVectorsBack(DATAFLOAT, name, value, floatArray);       }
void FileConfig::WriteDouble(double value, string name)			{ PushVectorsBack(DATADOUBLE, name, value, doubleArray);     }
void FileConfig::WriteString(string content, string name)		{ PushVectorsBack(DATASTRING, name, content, stringArray);   }

// Read section ***********************************************************************************************************************
bool FileConfig::ReadBool(string name)				{ return GetContent(name, boolArray);   }
char FileConfig::ReadChar(string name)				{ return GetContent(name, charArray);   }
unsigned char FileConfig::ReadUChar(string name)    { return GetContent(name, uCharArray);  }
short FileConfig::ReadShort(string name)            { return GetContent(name, shortArray);  }
unsigned short FileConfig::ReadUShort(string name)  { return GetContent(name, uShortArray); }
int FileConfig::ReadInt(string name)                { return GetContent(name, intArray);	}
unsigned int FileConfig::ReadUInt(string name)      { return GetContent(name, uIntArray);   }
float FileConfig::ReadFloat(string name)            { return GetContent(name, floatArray);  }
double FileConfig::ReadDouble(string name)          { return GetContent(name, doubleArray); }
string FileConfig::ReadString(string name)		    { return GetContent(name, stringArray);	}

// File section ***********************************************************************************************************************
void FileConfig::FileSave()
{
	ofstream outFile;
	outFile.open(filepath);
	if (outFile.fail())
		return;
	for (int i = 0; i < length; i++)
	{
		// Contiune if datatype is dataNull
		if (dataArray[i] == DATANULL)
			continue;

		// Write indentifier
		outFile << byte(dataArray[i]) << "_";
		outFile << nameArray[i] << ": ";

		// Write the data specified
		switch (dataArray[i]){
		case DATABOOL  : outFile << boolArray[i];   break;
		case DATACHAR  : outFile << charArray[i];   break;
		case DATAUCHAR : outFile << uCharArray[i];  break;
		case DATASHORT : outFile << shortArray[i];  break;
		case DATAUSHORT: outFile << uShortArray[i]; break;
		case DATAINT   : outFile << intArray[i];    break;
		case DATAUINT  : outFile << uIntArray[i];   break;
		case DATAFLOAT : outFile << floatArray[i];  break;
		case DATADOUBLE: outFile << doubleArray[i]; break;
		case DATASTRING: outFile << stringArray[i]; break;
		}outFile << " ;\n";
	}outFile.close();
}
void FileConfig::FileLoad()
{
	std::ifstream inFile;
	inFile.open(filepath);
	if (inFile.fail())
		return;

	while (1)
	{
		byte data = 0;
		byte breaker = 0;
		string name = "";
		string checker = "";

		bool boolValue = 0;
		char charValue = 0;
		unsigned char uCharValue = 0;
		short shortValue = 0;
		unsigned short uShortValue = 0;
		int intValue = 0;
		unsigned int uIntValue = 0;
		float floatValue = 0;
		double doubleValue = 0;
		string stringContent = "";

		inFile >> data >> breaker >> name;
		name = name.substr(0, name.length() - 1);

		switch (data)
		{
		case DATABOOL:
			inFile >> boolValue >> checker;
			WriteBool(boolValue, name);
			break;
		case DATACHAR:
			inFile >> charValue >> checker;
			WriteChar(charValue, name);
			break;
		case DATAUCHAR:
			inFile >> uCharValue >> checker;
			WriteUChar(uCharValue, name);
			break;
		case DATASHORT:
			inFile >> shortValue >> checker;
			WriteShort(shortValue, name);
			break;
		case DATAUSHORT:
			inFile >> uShortValue >> checker;
			WriteUShort(uShortValue, name);
			break;
		case DATAINT:
			inFile >> intValue >> checker;
			WriteInt(intValue, name);
			break;
		case DATAUINT:
			inFile >> uIntValue >> checker;
			WriteUInt(uIntValue, name);
			break;
		case DATAFLOAT:
			inFile >> floatValue >> checker;
			WriteFloat(floatValue, name);
			break;
		case DATADOUBLE:
			inFile >> doubleValue >> checker;
			WriteDouble(doubleValue, name);
			break;
		case DATASTRING:
			// Loads the content string
			while (1){
				inFile >> checker;
				if (checker == ";") break;
				stringContent += checker + " ";
			}
			// Cuts the lasts space off the content string and adds it to memory
			stringContent = stringContent.substr(0, stringContent.length() - 1);
			WriteString(stringContent, name);
			break;
		default:
			inFile.close();
			return;
		}
	}
}
void FileConfig::FileDelete()
{
	std::remove(filepath.c_str());
}