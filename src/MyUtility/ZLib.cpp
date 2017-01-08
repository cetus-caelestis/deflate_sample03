//-------------------------------------------------------------
//! @brief	�Ȉ�ZLib
//! @author	��ĩ�=��ڽè�
//-------------------------------------------------------------

//-------------------------------------------------------------
// include
//-------------------------------------------------------------
#include <cstdint> // uint32_t
#include <vector>
#include <type_traits>

#include "Deflate.h"
#include "ZLib.h"

// ���ׂ�unsigned char��
// ���ׂ�unsigned��

//-------------------------------------------------------------
// using
//-------------------------------------------------------------
using namespace MyUtility;

namespace
{
//-------------------------------------------------------------
// inner function
//-------------------------------------------------------------

// @brief Adler-32�`�F�b�N�T����ǂݏo��
//-------------------------------------------------------------
uint32_t ReadAdler32(const unsigned char* datatop)
{
	uint32_t result = (datatop[0] << 24)
					+ (datatop[1] << 16)
					+ (datatop[2] << 8)
					+ (datatop[3]);
	return result;
}

// @brief Adler-32�`�F�b�N�T����Ԃ�
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


// @brief �f�R�[�h����
//-------------------------------------------------------------	
std::vector<unsigned char> MyUtility::ZLib::Decode(const unsigned char* binary, size_t numByte)
{
	// ���k���\�b�h�^�C�v
	{
		const unsigned compressMethodType = binary[0] & 0x0F;
		if (compressMethodType != 0x08)
		{
			throw std::runtime_error("deflate���k�ȊO�̃^�C�v���w�肳��܂����A��Ή��ɂ�Decode�ł��܂���");
		}
	}
	// �X���C�h���T�C�Y 256(2^8) �` 32768(2^15)
	const unsigned compressInfo = (binary[0] & 0xF0)>>4;
	const unsigned slideWindowSize = (0x01 << (compressInfo + 8));

	if (slideWindowSize > 32768)
	{
		throw std::runtime_error("�v�����ꂽ�X���C�h���̃T�C�Y���傫������݂����ł�");
	}
	// Zlib�w�b�_�`�F�b�N
	// ���ʂ�31�̔{���ɂȂ�Ȃ���΂Ȃ�Ȃ�
	{
		const unsigned zlibHeader = binary[0] * 256 + binary[1];
		if (zlibHeader % 31 != 0)
		{
			throw std::runtime_error("Zlib�̃w�b�_�̐������`�F�b�N�Ɏ��s���܂���");
		}
	}
	// �v���Z�b�g�����ɂ͔�Ή�
	if ( binary[1] & 0x20)
	{
		throw std::runtime_error("�v���Z�b�g������Ή��ł��ADecode�ł��܂���A");
	}

	// �𓀂ƃf�[�^�ɉ�ꂪ�Ȃ����̃`�F�b�N
	const unsigned ZLIB_EX_DATA_SIZE = 6;	// �w�b�_2byte + �t�b�^4byte
	auto result = MyUtility::Deflate::Decode(&binary[2], numByte-ZLIB_EX_DATA_SIZE, slideWindowSize);

	auto adler32CheckSum = ReadAdler32(&binary[numByte -4]);
	if (adler32CheckSum != CalcAdler32(result))
	{
		throw std::runtime_error("���k�f�[�^�����Ă���݂����ł��BDecode�Ɏ��s���܂���");
	}	
	return result;
}