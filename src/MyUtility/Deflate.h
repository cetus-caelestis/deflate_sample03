//-------------------------------------------------------------
//! @brief	�Ȉ�Deflate����
//! @author	��ĩ�=��ڽè�
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

//! �f�R�[�h����
std::vector<unsigned char> Decode(const unsigned char* binary, size_t numByte, size_t slideWindowSize = 32768);


}// end namespace Deflate
}// end namespace MyUtility