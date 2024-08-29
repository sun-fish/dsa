#include <iostream>

#include "utility.h"
#include "string.h"

int main(int argc, char** argv) {
    String<char> char_string;
    assert(char_string.empty());

    String<wchar_t> string1(L"Chen", 4);
    string1.print();

    String<wchar_t> string2(L"Lu", 2);
    string2.print();

    string2 + string1;
    string2.print();

    string2 = String<wchar_t>(L"Lu", 2);
    string2.print();
    
    String<wchar_t> string3 = string1 + string2;
    string3.print();

    string3.prefix(string1, 4);
    string3.suffix(string2, 2);
    string1.print();
    string2.print();

    string3.subString(string1, 1, 4);
    string1.print();

    wchar_t ch = string3[4];
    assert(ch == L'L');

    wchar_t s[7] = L"ChenLu";
    String<wchar_t> string4(s, sizeof(s) / sizeof(wchar_t) - 1);
    string4.print();

    assert(string3 == string4);
    std::cout << "Press Enter to continue...";
    std::cin.get();
    return 0;
}