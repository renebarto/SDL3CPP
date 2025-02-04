//---------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : Error.cpph
//
// Namespace   : utility
//
// Class       : -
//
// Description :
//  System error object
//
//---------------------------------------------------------------

#include "utility/Error.h"

#include <iomanip>

namespace utility {
    
Error::Error(int errorCode, const std::string& errorString, const std::string& text)
    : m_errorCode{ errorCode }
    , m_errorString{ errorString }
    , m_text{ text }
{
}

Error &
Error::operator <<(
    const std::string& freeText)
{
    m_text += freeText;
    return *this;
}

std::ostream &
operator <<(std::ostream& stream, const Error& value)
{
    auto fillChar = stream.fill();
    return stream 
        << std::dec << value.ErrorCode() 
        << " (" << std::hex << std::setw(2) << std::setfill('0') << value.ErrorCode() << "): "
        << value.ErrorString() << " " << value.Message() << std::setfill(fillChar);
}

} // namespace utility
