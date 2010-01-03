#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

std::string int_to_str(int x)
{
    int max_digits_in_int = ceil(log(static_cast<double>(INT_MAX)) / log(10.0));
    char buf[max_digits_in_int + 1];
    ::sprintf(buf, "%d", x);
    return buf;
}

std::string solve(const std::string &input)
{
    std::vector<int> stack;

    int closing_of[CHAR_MAX];
    closing_of['('] = ')';
    closing_of['['] = ']';
    closing_of['{'] = '}';

    for (size_t i = 0; i < input.size(); i++) {
        int c = input[i];
        if (c == '(' || c == '[' || c == '{')
            stack.push_back(c);
        else if (stack.size() > 0 && c == closing_of[stack.back()])
            stack.pop_back();
        else
            return int_to_str(i);
    }

    if (stack.size() > 0) 
        return int_to_str(input.size());
    else
        return "CORRECT";
}

std::string read_input()
{
    std::string input;
    std::cin >> input;
    return input;
}

void write_output(const std::string &output)
{
    std::cout << output << std::endl;
}

int main()
{
    write_output(solve(read_input()));
}
