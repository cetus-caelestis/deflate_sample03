//-------------------------------------------------------------
//! @brief	�Ȉ�ZLib
//! @author	��ĩ�=��ڽè�
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

//! �f�R�[�h����
std::vector<unsigned char> Decode(const unsigned char* binary, size_t numByte);


}// end namespace Deflate
}// end namespace MyUtility