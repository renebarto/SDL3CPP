//------------------------------------------------------------------------
// Copyright   : Copyright(c) 2021 René Barto
//
// File        : Exception.h
//
// Namespace   : core
//
// Class       : -
//
// Description :
//
//---------------------------------------------------------------

#pragma once

#include <string>
#include <exception>
#include <sstream>
#include <iomanip>
#include <cstring>
//#include "core/Util.h"
#include "osal/utilities//TypeInfo.h"

namespace core
{

class BaseException : public std::exception
{
protected:
    std::string m_message;
    const std::exception* m_innerException;
    mutable std::string m_whatMessage;
public:
    BaseException()
        : m_message()
        , m_innerException(nullptr)
        , m_whatMessage()
    {
    }
    BaseException(const BaseException& innerException)
        : m_message()
        , m_innerException(&innerException)
        , m_whatMessage()
    {
    }
    // Not a copy constructor!!
    BaseException(const std::exception& innerException)
        : m_message()
        , m_innerException(&innerException)
        , m_whatMessage()
    {
    }
    BaseException(const std::string& message)
        : m_message(message)
        , m_innerException(nullptr)
        , m_whatMessage()
    {
    }
    BaseException(const std::string& message, const std::exception& innerException)
        : m_message(message)
        , m_innerException(&innerException)
        , m_whatMessage()
    {
    }
    ~BaseException() throw ()
    {
    }
    BaseException& operator = (const BaseException& other)
    {
        m_message = other.m_message;
        m_innerException = other.m_innerException;
        return *this;
    }
    const char* what() const throw()
    {
        m_whatMessage = FormatMessage();
        return m_whatMessage.c_str();
    }
    virtual std::string BuildMessage() const
    {
        return "";
    }
    const std::string& GetMessage() const
    {
        return m_message;
    }
    void SetMessage(const std::string& value)
    {
        m_message = value;
    }
private:
    std::string FormatMessage() const
    {
        std::ostringstream stream;
        stream << osal::type(*this);
        std::string buildMessage = BuildMessage();
        if (!buildMessage.empty())
            stream << " - " << BuildMessage();
        if (!m_message.empty())
            stream << ": " << m_message;
        if (m_innerException)
        {
            stream << std::endl << "-->" << m_innerException->what();
        }
        return stream.str();
    }
};

class Exception : public BaseException
{
protected:
    const char* m_functionName;
    const char* m_fileName;
    int m_line;
public:
    Exception() = delete;
    Exception(const char* functionName, const char* fileName, int line)
        : BaseException()
        , m_functionName(functionName)
        , m_fileName(fileName)
        , m_line(line)
    {
    }
    Exception(const char* functionName, const char* fileName, int line,
              const std::string& message)
        : BaseException(message)
        , m_functionName(functionName)
        , m_fileName(fileName)
        , m_line(line)
    {
    }
    Exception(const char* functionName, const char* fileName, int line,
              const std::string& message, const std::exception& innerException)
        : BaseException(message, innerException)
        , m_functionName(functionName)
        , m_fileName(fileName)
        , m_line(line)
    {
    }
    ~Exception() throw ()
    {
    }
    virtual std::string BuildMessage() const
    {
        std::ostringstream stream;
        if (m_functionName != nullptr)
            stream << "in " << m_functionName;
        if (m_fileName != nullptr)
        {
            stream << " [" << m_fileName;
            if (m_line > 0)
                stream << ":" << m_line;
            stream << "]";
        }
        return stream.str();
    }
};

class SystemError : public Exception
{
protected:
    int errorCode_;
public:
    SystemError(const char* functionName, const char* fileName, int line, int errorCode)
        : Exception(functionName, fileName, line)
        , errorCode_(errorCode)
    {
    }
    SystemError(const char* functionName, const char* fileName, int line, int errorCode, std::string message)
        : Exception(functionName, fileName, line, message)
        , errorCode_(errorCode)
    {
    }
    ~SystemError() throw ()
    {
    }
    int GetErrorCode() const
    {
        return errorCode_;
    }
    virtual std::string BuildMessage() const
    {
        std::ostringstream stream;
        stream << Exception::BuildMessage() << " errno=" << errorCode_
               << " (0x" << std::hex << std::setw(8) << std::setfill('0') << errorCode_ << "): "
               << '"' << strerror(errorCode_) << '"';
        return stream.str();
    }
};

class RuntimeError : public Exception
{
public:
    RuntimeError(const char* functionName, const char* fileName, int line, std::string message)
        : Exception(functionName, fileName, line, message)
    {
    }
    ~RuntimeError() throw ()
    {
    }
};

class ArgumentException : public Exception
{
protected:
    std::string argument_;
public:
    ArgumentException(const char* functionName, const char* fileName, int line,
                      std::string argument)
        : Exception(functionName, fileName, line)
        , argument_(argument)
    {
    }
    ArgumentException(const char* functionName, const char* fileName, int line,
                      std::string argument, std::string message)
        : Exception(functionName, fileName, line, message)
        , argument_(argument)
    {
    }
    ~ArgumentException() throw ()
    {
    }
    virtual std::string BuildMessage() const
    {
        std::ostringstream stream;
        stream << Exception::BuildMessage();
        if (!argument_.empty())
            stream << ": argument: " << argument_;
        return stream.str();
    }
};

class ArgumentOutOfRangeException : public ArgumentException
{
public:
    ArgumentOutOfRangeException(const char* functionName, const char* fileName, int line,
                                std::string argument)
        : ArgumentException(functionName, fileName, line, argument)
    {
    }
    ArgumentOutOfRangeException(const char* functionName, const char* fileName, int line,
                                std::string argument, std::string message)
        : ArgumentException(functionName, fileName, line, argument, message)
    {
    }
    ~ArgumentOutOfRangeException() throw ()
    {
    }
    virtual std::string BuildMessage() const
    {
        std::ostringstream stream;
        stream << Exception::BuildMessage();
        if (!argument_.empty())
            stream << ": argument out of range: " << argument_;
        return stream.str();
    }
};

class ArgumentNullException : public ArgumentException
{
public:
    ArgumentNullException(const char* functionName, const char* fileName, int line,
                          std::string argument) :
        ArgumentException(functionName, fileName, line, argument)
    {
    }
    ~ArgumentNullException() throw ()
    {
    }
    virtual std::string BuildMessage() const
    {
        std::ostringstream stream;
        stream << Exception::BuildMessage();
        if (!argument_.empty())
            stream << ": argument null: " << argument_;
        return stream.str();
    }
};

class OperationException : public Exception
{
public:
    OperationException(const char* functionName, const char* fileName, int line,
                       std::string message)
        : Exception(functionName, fileName, line, message)
    {
    }
    ~OperationException() throw ()
    {
    }
};

class OperationNotSupportedException : public OperationException
{
public:
    OperationNotSupportedException(const char* functionName, const char* fileName, int line,
                                   std::string message)
        : OperationException(functionName, fileName, line, message)
    {
    }
    ~OperationNotSupportedException() throw ()
    {
    }
    virtual std::string BuildMessage() const
    {
        std::ostringstream stream;
        stream << Exception::BuildMessage();
        stream << ": operation not supported";
        return stream.str();
    }
};

} // namespace core
