//-------------------------------------------------------------
//! @brief	簡易Deflate実装
//! @author	ｹｰﾄｩｽ=ｶｴﾚｽﾃｨｽ
//-------------------------------------------------------------
#pragma once

//-------------------------------------------------------------
// include
//-------------------------------------------------------------
#include <vector>

namespace MyUtility
{
namespace Deflate
{

//! デコードする
std::vector<unsigned char> Decode(const unsigned char* binary, size_t numByte, size_t slideWindowSize = 32768);


}// end namespace Deflate
}// end namespace MyUtility