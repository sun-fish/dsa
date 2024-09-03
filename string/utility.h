#ifndef STRING_UTILITY
#define STRING_UTILITY

#include <assert.h>
#include <string.h>

template <typename T>
class StringUtility {
   public:
    /******************************************************************************************
     * Text     :  0   1   2   .   .   .   i-j .   .   .   .   i   .   .   n-1
     *             ------------------------|-------------------|------------
     * Pattern  :                          0   .   .   .   .   j   .   .
     *                                     |-------------------|
     ******************************************************************************************/
    // if success, return the fisrt success matched index
    // otherwise, return not less than text_string_length - pattern_string_length
    static int matchBruteForce1(T* pattern, T* text) {
        size_t text_string_size = strlen(text);
        size_t text_string_index = 0;
        size_t pattern_string_size = strlen(pattern);
        size_t pattern_string_index = 0;
        while (pattern_string_index < pattern_string_size && text_string_index < text_string_size) {
            if (text[text_string_index] == pattern[pattern_string_index]) {
                ++text_string_index;
                ++pattern_string_index;
                // compare next char
            } else {
                text_string_index -= pattern_string_index - 1;
                pattern_string_index = 0;
            }  // text string fall back j - 1, pattern string fall back to zero
        }
        return text_string_index - pattern_string_index;
    }

    /******************************************************************************************
     * Text     :  0   1   2   .   .   .   i   i+1 .   .   .   i+j .   .   n-1
     *             ------------------------|-------------------|------------
     * Pattern  :                          0   1   .   .   .   j   .   .
     *                                     |-------------------|
     ******************************************************************************************/
    // if success, return the fisrt success matched index
    // otherwise, return text_string_length - pattern_string_length + 1
    static int matchBruteForce2(T* pattern, T* text) {
        size_t text_string_length = strlen(text);
        size_t text_string_index = 0;
        size_t pattern_string_length = strlen(pattern);
        size_t pattern_string_index = 0;

        for (text_string_index = 0; text_string_index < text_string_length - pattern_string_length + 1;
             ++text_string_index) {
            for (pattern_string_index = 0; pattern_string_index < pattern_string_length; ++pattern_string_index) {
                if (text[text_string_index + pattern_string_index] != pattern[pattern_string_index]) {
                    break;
                }
            }
            if (pattern_string_index >= pattern_string_length) {
                break;
            }
        }
        return text_string_index;
    }

    static int* buildNext(char* pattern) {
        size_t pattern_string_length = strlen(pattern);
        size_t pattern_string_index = 0;
        int* next = new int[pattern_string_length];
        int temp = next[0] = -1;
        while (pattern_string_index < pattern_string_length - 1)
            if (0 <= temp && pattern[temp] != pattern[pattern_string_index])
                temp = next[temp];
            else if (pattern[++temp] != pattern[++pattern_string_index])
                next[pattern_string_index] = temp;
            else
                next[pattern_string_index] = next[temp];
        return next;
    }

    static size_t matchKMP(T* pattern, T* text) {
        int* next = buildNext(pattern);
        size_t text_string_length = (size_t)strlen(text);
        size_t text_string_index = 0;
        size_t pattern_string_length = (size_t)strlen(pattern);
        size_t pattern_string_index = 0;
        while (pattern_string_index < pattern_string_length && text_string_index < text_string_length) {
            if (0 > pattern_string_index || text[text_string_index] == pattern[pattern_string_index]) {
                text_string_index++;
                pattern_string_index++;
            } else {
                pattern_string_index = next[pattern_string_index];
            }
        }
        delete[] next;
        return text_string_index - pattern_string_index;
    }
};

#endif  // !STRING_UTILITY