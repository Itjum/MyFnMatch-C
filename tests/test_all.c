#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "fnmatch.h"

Test(check, no_wildcards)
{
    //case 1 false
    const char *pattern = "abcde";
    const char *string = "abde";
    int res = my_fnmatch(pattern, string);
    //case 2 true
    const char *pattern2 = "abcdef";
    const char *string2 = "abcdef";
    int res2 = my_fnmatch(pattern2, string2);
    cr_assert(res == 1 && res2 == 0, "no wild cards");
}

Test(check, wild_one_char)
{
    //case 1 false
    const char *pattern = "abcccd";
    const char *string = "ab?c.cd";
    int res = my_fnmatch(pattern, string);
    //case 2 true
    const char *pattern2 = "ab?ccd";
    const char *string2 = "abcccd";
    int res2 = my_fnmatch(pattern2, string2);
    cr_assert(res == 1 && res2 == 0, "with wild card");
}

Test(check, wild_one_char2)
{
    //case 1 true
    const char *pattern = "ab?d?";
    const char *string = "abcde";
    int res = my_fnmatch(pattern, string);
    //case 2 true
    const char *pattern2 = "??al???";
    const char *string2 = "akaloki";
    int res2 = my_fnmatch(pattern2, string2);
    cr_assert(res == 0 && res2 == 0, "with wild card case 2");
}

Test(check, wild_star)
{
    //case 1 true
    const char *pattern = "abc**jkl*";
    const char *string = "abcgh*lkejkl";
    int res = my_fnmatch(pattern, string);
    //case 2 true
    const char *pattern2 = "*lalala";
    const char *string2 = "lalala";
    int res2 = my_fnmatch(pattern2, string2);
    cr_assert(res == 0 && res2 == 0, "with wild card case 3");
}

Test(check, wild_star2)
{
    //case 1 true
    const char *pattern = "a*.cb";
    const char *string = "a.cb.cb";
    int res = my_fnmatch(pattern, string);
    //case 2 true
    const char *pattern2 = "**";
    const char *string2 = "";
    int res2 = my_fnmatch(pattern2, string2);
    cr_assert(res == 0 && res2 == 0, "with wild card case 3");
}

Test(check, wild_star3)
{
    //case 1 true
    const char *pattern = "*a*";
    const char *string = "a";
    int res = my_fnmatch(pattern, string);
    //case 2 false
    const char *pattern2 = "a*cb";
    const char *string2 = "acbb";
    int res2 = my_fnmatch(pattern2, string2);
    cr_assert(res == 0 && res2 == 1, "with wild card case 3");
}

Test(check, bracket)
{
    //case 1 true
    const char *pattern = "[acd]cd";
    const char *string = "acd";
    int res = my_fnmatch(pattern, string);
    //case 2 false
    const char *pattern2 = "a[db";
    const char *string2 = "a[]db";
    int res2 = my_fnmatch(pattern2, string2);
    cr_assert(res == 0 && res2 == 1, "with bracket");
}

Test(check, bracket_2)
{
    //case 1 false
    const char *pattern = "[abd][tl]";
    const char *string = "bg";
    int res = my_fnmatch(pattern, string);
    //case 2 false
    const char *pattern2 = "dqfefwe[p]";
    const char *string2 = "dqfefwe";
    int res2 = my_fnmatch(pattern2, string2);
    cr_assert(res == 1 && res2 == 1, "with bracket");
}

Test(check, bracket_3)
{
    //case 1 false
    const char *pattern = "abgg*[*?]";
    const char *string = "abgglololoh";
    int res = my_fnmatch(pattern, string);
    //case 2 true
    const char *pattern2 = "abgg*[*?h]";
    const char *string2 = "abgglololoh";
    int res2 = my_fnmatch(pattern2, string2);
    cr_assert(res2 == 0 && res == 1, "with bracket and wild symbols");
}

Test(check, bracket_with_negation)
{
    //case 1 true
    const char *pattern = "ag[!pot]hl";
    const char *string = "aglhl";
    int res = my_fnmatch(pattern, string);
    //case 2 false
    const char *pattern2 = "ag[!pot]hl";
    const char *string2 = "agohl";
    int res2 = my_fnmatch(pattern2, string2);
    cr_assert(res2 == 1 && res == 0);
}

Test(check, escaping)
{
    //case 1 false
    const char *pattern = "ag\\*lhl";
    const char *string = "aglhl";
    int res = my_fnmatch(pattern, string);
    //case 2 false
    const char *pattern2 = "ag\\[!pot]hl";
    const char *string2 = "aglhl";
    int res2 = my_fnmatch(pattern2, string2);
    cr_assert(res2 == 1 && res == 1);
}

Test(check, escaping2)
{
    //case 1 true
    const char *pattern = "\?yolo";
    const char *string = "?yolo";
    int res = my_fnmatch(pattern, string);
    //case 2 true
    const char *pattern2 = "ag\\*hl";
    const char *string2 = "ag*hl";
    int res2 = my_fnmatch(pattern2, string2);
    cr_assert(res2 == 0 && res == 0);
}


Test(check, ranges)
{
    //case 1 true
    const char *pattern = "ag[A-Z]lhl";
    const char *string = "agFlhl";
    int res = my_fnmatch(pattern, string);
    //case 2 false
    const char *pattern2 = "ag[0-9]hl";
    const char *string2 = "ag99lhl";
    int res2 = my_fnmatch(pattern2, string2);
    cr_assert(res == 0 && res2 == 1);
}

Test(check, ranges2)
{
    //case 1 false
    const char *pattern = "ag[A-Z0-6]lhl";
    const char *string = "agF7lhl";
    int res = my_fnmatch(pattern, string);
    //case 2 false
    const char *pattern2 = "ag[!0-9]hl";
    const char *string2 = "ag9lhl";
    int res2 = my_fnmatch(pattern2, string2);
    cr_assert(res == 1 && res2 == 1);
}
