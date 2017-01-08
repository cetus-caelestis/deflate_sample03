//-------------------------------------------------------------
//! @brief	簡易ZLib
//! @author	ｹｰﾄｩｽ=ｶｴﾚｽﾃｨｽ
//-------------------------------------------------------------

//-------------------------------------------------------------
// include
//-------------------------------------------------------------
#include <cstdint> // uint32_t
#include <vector>
#include <type_traits>

#include "Deflate.h"
#include "ZLib.h"

// すべてunsigned charへ
// すべてunsignedへ

//-------------------------------------------------------------
// using
//-------------------------------------------------------------
using namespace MyUtility;

namespace
{
//-------------------------------------------------------------
// inner function
//-------------------------------------------------------------

// @brief Adler-32チェックサムを読み出す
//-------------------------------------------------------------
uint32_t ReadAdler32(const unsigned char* datatop)
{
	uint32_t result = (datatop[0] << 24)
					+ (datatop[1] << 16)
					+ (datatop[2] << 8)
					+ (datatop[3]);
	return result;
}

// @brief Adler-32チェックサムを返す
//-------------------------------------------------------------
uint32_t CalcAdler32(const std::vector<unsigned char>& dataArray)
{
	uint32_t a = 1; 
	uint32_t b = 0;

	for (unsigned char byte : dataArray)
	{
		a = (a + byte) % 65521;
		b = (b + a)    % 65521;
	}
	return (b << 16) + a;
}
}// endnamespace

//-------------------------------------------------------------
// function
//-------------------------------------------------------------


// @brief デコードする
//-------------------------------------------------------------	
std::vector<unsigned char> MyUtility::ZLib::Decode(const unsigned char* binary, size_t numByte)
{
	// 圧縮メソッドタイプ
	{
		const unsigned compressMethodType = binary[0] & 0x0F;
		if (compressMethodType != 0x08)
		{
			throw std::runtime_error("deflate圧縮以外のタイプが指定されました、非対応につきDecodeできません");
		}
	}
	// スライド窓サイズ 256(2^8) ～ 32768(2^15)
	const unsigned compressInfo = (binary[0] & 0xF0)>>4;
	const unsigned slideWindowSize = (0x01 << (compressInfo + 8));

	if (slideWindowSize > 32768)
	{
		throw std::runtime_error("要求されたスライド窓のサイズが大きすぎるみたいです");
	}
	// Zlibヘッダチェック
	// 結果が31の倍数にならなければならない
	{
		const unsigned zlibHeader = binary[0] * 256 + binary[1];
		if (zlibHeader % 31 != 0)
		{
			throw std::runtime_error("Zlibのヘッダの整合性チェックに失敗しました");
		}
	}
	// プリセット辞書には非対応
	if ( binary[1] & 0x20)
	{
		throw std::runtime_error("プリセット辞書非対応です、Decodeできません、");
	}

	// 解凍とデータに壊れがないかのチェック
	const unsigned ZLIB_EX_DATA_SIZE = 6;	// ヘッダ2byte + フッタ4byte
	auto result = MyUtility::Deflate::Decode(&binary[2], numByte-ZLIB_EX_DATA_SIZE, slideWindowSize);

	auto adler32CheckSum = ReadAdler32(&binary[numByte -4]);
	if (adler32CheckSum != CalcAdler32(result))
	{
		throw std::runtime_error("圧縮データが壊れているみたいです。Decodeに失敗しました");
	}	
	return result;
}