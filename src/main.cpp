#include <iostream>
#include <fstream>
#include <string>

#include "MyUtility/Deflate.h"
#include "MyUtility/ZLib.h"

void DecodeDeflateTest()
{
	using namespace MyUtility;

	// ñ≥à≥èk "aaaaa"
	const unsigned char codedData[] = "\x01\x05\x00\xFA\xFF\x61\x61\x61\x61\x61";

	auto data = Deflate::Decode(codedData, std::size(codedData)-1);

	std::basic_string<unsigned char> resultStr(data.data(), data.size());
	std::cout << resultStr.c_str() << std::endl;
}
void DecodeZLibTest()
{
	using namespace MyUtility;

	// ZLib ÉfÅ[É^ "0, 255 255 255"
	const unsigned char codedData[] = "\x18\x57\x63\xF8\xFF\xFF\x3F\x00\x05\xFE\x02\xFE";

	auto data = ZLib::Decode(codedData, std::size(codedData) - 1);

	std::basic_string<unsigned char> resultStr(data.data(), data.size());
	for (auto byte : resultStr)
	{
		std::cout << static_cast<int>(byte) << " ";
	}
}


int main()
{
	try
	{
		std::cout << "-- deflate --" << std::endl;
		DecodeDeflateTest();

		std::cout << "-- zlib --" << std::endl;
		DecodeZLibTest();
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what();
	}
	catch (...)
	{

	}
	getchar();
	return 0;
}

