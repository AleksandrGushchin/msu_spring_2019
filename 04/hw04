#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum class Error
{
    NoError,
    CorruptedArchive
};


class Serializer
{
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream& out)
        : out_(out)
    {
    }

    template <typename T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <typename... ArgsT>
    Error operator()(ArgsT... args)
    {
        return process(forward<ArgsT>(args)...);
    }

private:
    // process использует variadic templates
    ostream &out_;

    Error process(uint64_t x)
    {
        string st = to_string(x);
        st += " ";
        out_ << st;
        return Error::NoError;
    }

    Error process(bool x)
    {
        if (x)
            out_ << "true";
        else
            out_ << "false";
        out_ << " ";
        return Error::NoError;
    }

    template <typename T>
    Error process(int x)
    {
        return Error::CorruptedArchive;
    }

    template <typename T, typename... ArgsT>
    Error process(T &&x, ArgsT&&... args)
    {
        if (process(x) == Error::CorruptedArchive)
            return Error::CorruptedArchive;
        else
            return process(forward<ArgsT>(args)...);
    }
};


class Deserializer
{
public:
    explicit Deserializer(istream &in)
        : in_(in)
    {}

    template <typename T>
    Error load(T& obj)
    {
        return obj.serialize(*this);
    }

    template <typename T, typename... ArgsT>
    Error operator()(T& x, ArgsT&&... args)
    {
        return process(x, forward<ArgsT>(args)...);
    }
private:
    istream &in_;

    Error process(bool& value)
    {
        string text;
        in_ >> text;

        if (text == "true")
            value = true;
        else if (text == "false")
            value = false;
        else
            return Error::CorruptedArchive;

        return Error::NoError;
    }

    Error process(uint64_t& x)
    {
        string text;
        in_ >> text;
        try
        {
            long long tmp = stoll(text);
            if (tmp < 0)
                return Error::CorruptedArchive;
            x = tmp;
            return Error::NoError;
        }
        catch (...)
        {
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }

    template <typename T>
    Error process(T &&x)
    {
        return Error::CorruptedArchive;
    }

    template <typename T, typename... ArgsT>
    Error process(T &&x, ArgsT&&... args)
    {
        if (process(x) == Error::CorruptedArchive)
            return Error::CorruptedArchive;
        else
            return process(forward<ArgsT>(args)...);
    }
};
