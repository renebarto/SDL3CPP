//---------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : GenericError.cpp
//
// Namespace   : utility
//
// Class       : -
//
// Description :
//  Generic error object
//
//---------------------------------------------------------------

#include "utility/GenericError.h"

namespace utility {
    
GenericError::GenericError(const std::string& text)
    : m_text(text)
{
}
    
GenericError&
GenericError::operator <<(
    const std::string& freeText)
{
    m_text += freeText;
    return *this;
}

std::ostream &
operator <<(std::ostream& stream, const GenericError& value)
{
    return stream << value.Message();
}

} // namespace utility
