//-------------------------------------------------------------
//! @brief	簡易ZLib
//! @author	ｹｰﾄｩｽ=ｶｴﾚｽﾃｨｽ
//-------------------------------------------------------------
#pragma once

//-------------------------------------------------------------
// include
//-------------------------------------------------------------
#include <vector>

namespace MyUtility
{
namespace ZLib
{

//! デコードする
std::vector<unsigned char> Decode(const unsigned char* binary, size_t numByte);


}// end namespace Deflate
}// end namespace MyUtility