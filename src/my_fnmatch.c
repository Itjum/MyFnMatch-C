#include "fnmatch.h"

struct brackets
{
    int verif;
    int index;
};

//For the ranges
int ranges(const char *pattern, const char *string)
{
    char c = *(pattern + 1);
    char stop = *(pattern + 3);
    if (c == '[' || stop == ']')
        return my_fnmatch(++pattern, string);
    while (c != *string && c != stop)
    {
        c++;
    }
    if (c == *string)
    {
        return 0;
    }
    return 1;
}

//To deal with brackets and a negation within them
struct brackets dealn(const char *pattern, const char *string, int index)
{
    struct brackets new;
    new.index = index;
    new.verif = 0;
    while (pattern[index] != '\0' && pattern[index] != ']')
        index++;
    if (pattern[index] == '\0')
    {
        if (*pattern != *string)
        {
            new.verif = 1;
        }
        else
        {
            string++;
            pattern++;
        }
    }
    if (new.verif == 0)
    {
        int j = 1;
        for (; j < index && new.verif == 0; j++)
        {
            if (pattern[j] == *string)
            {
                new.verif = 1;
            }
            if (pattern[j] == '-')
            {
                new.verif = ranges(pattern, string);
                if (new.verif == 1)
                    new.verif = 0;
                else
                    new.verif = 1;
            }
        }
        new.index = index + 1;
    }
    return new;
}

//To deal with brackets with no negation within them
struct brackets deal(const char *pattern, const char *string, int index)
{
    struct brackets new;
    new.verif = 0;
    new.index = 1;
    if (pattern[1] == '!')
    {
        return dealn(pattern, string, index);
    }
    while (pattern[index] != '\0' && pattern[index] != ']')
        index++;
    if (pattern[index] == '\0')
    {
        if (*pattern != *string)
        {
            new.verif = 1;
        }
        else
        {
            string++;
            pattern++;
        }
    }
    if (new.verif == 0)
    {
        new.verif = 1;
        int j = 1;
        for (; j < index && new.verif == 1; j++)
        {
            if (pattern[j] == *string)
            {
                new.verif = 0;
            }
            if (pattern[j] == '-')
            {
                new.verif = ranges(pattern, string);
            }
        }
        new.index = index + 1;
    }
    return new;
}

//To deal with the star cases
int star_case(const char *pattern, const char *string)
{
    int res = my_fnmatch(pattern + 1, string);
    if (res == 1)
    {
        res = my_fnmatch(pattern + 1, string + 1);
    }
    if (res == 1)
    {
        res = my_fnmatch(pattern, string + 1);
    }
    return res;
}

int string_match(const char *pattern, const char *string)
{
    if ((*pattern != *string))
    {
        return 1;
    }
    else
    {
        pattern++;
        string++;
        return my_fnmatch(pattern, string);
    }
}

int my_fnmatch(const char *pattern, const char *string)
{
    if (*string == '\0')
    {
        while (*pattern == '*')
            pattern++;
    }
    for (;*pattern != '\0' || *string != '\0'; pattern++, string++)
    {
        int i = 1;
        if (*pattern == '?' )
        {
            if (*string == '\0')
                return 1;
        }
        else if (*pattern == '*')
        {
            return star_case(pattern, string);
        }
        else if (*pattern == '[')
        {
            struct brackets new = deal(pattern, string, i);
            if (new.verif == 1)
                    return 1;
                pattern += new.index - 1;
        }
        else if (*pattern == '\\')
        {
            pattern++;
            return string_match(pattern, string);
        }
        else
        {
            if (!(*pattern == *string))
                return 1;
        }
    }
    return (*pattern == '\0' && *string == '\0') ? 0 : 1;
}
