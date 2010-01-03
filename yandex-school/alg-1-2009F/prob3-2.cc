#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

typedef std::pair<int, int> Coin;  // (position, deadline)

std::istream &operator >>(std::istream &input_stream, std::vector<Coin> &vector_of_coins)
{
    int number;
    input_stream >> number;
    vector_of_coins.resize(number);
    for (int index = 0; index < number; index++)
        input_stream >> vector_of_coins[index].first >> vector_of_coins[index].second;
    return input_stream;
}

template<typename T>
std::string convert_to_string(const T &x)
{
    std::ostringstream temporary_output_string_stream;
    temporary_output_string_stream << x;
    return temporary_output_string_stream.str();
}

std::string compute_the_minimum_time_needed_to_collect_all_the_coins(std::vector<Coin> coins)
{
    int number_of_coins = coins.size();
    std::sort(coins.begin(), coins.end());  // sort by position
    
    std::vector<int> pos(number_of_coins), deadline(number_of_coins);
    for (int i = 0; i < number_of_coins; i++) {
        pos[i] = coins[i].first;
        deadline[i] = coins[i].second;
    }

    const int INFINITY = 1000000000;

    std::vector< std::vector< std::vector<int> > > minimum_time_to_collect_coins(
            number_of_coins + 1,
            std::vector< std::vector<int> >(
                number_of_coins + 1,
                std::vector<int>(2, INFINITY)));
    
    for (int index = 0; index < number_of_coins; index++) {
        minimum_time_to_collect_coins[index][index][0] = 0;
        minimum_time_to_collect_coins[index][index][1] = 0;
    }

    for (int length_of_subinterval = 2; length_of_subinterval <= number_of_coins; ++length_of_subinterval) {
        for (int subinterval_first = 0; subinterval_first + length_of_subinterval <= number_of_coins; ++subinterval_first) {
            int subinterval_last = subinterval_first + length_of_subinterval - 1;

            minimum_time_to_collect_coins[subinterval_first][subinterval_last][0] = std::min(
                minimum_time_to_collect_coins[subinterval_first + 1][subinterval_last][0] +
                    abs(pos[subinterval_first] - pos[subinterval_first + 1]),
                minimum_time_to_collect_coins[subinterval_first + 1][subinterval_last][1] +
                    abs(pos[subinterval_first] - pos[subinterval_last])
            );
            if (minimum_time_to_collect_coins[subinterval_first][subinterval_last][0] > deadline[subinterval_first])
                minimum_time_to_collect_coins[subinterval_first][subinterval_last][0] = INFINITY;
                
            minimum_time_to_collect_coins[subinterval_first][subinterval_last][1] = std::min(
                minimum_time_to_collect_coins[subinterval_first][subinterval_last - 1][0] +
                    abs(pos[subinterval_last] - pos[subinterval_first]),
                minimum_time_to_collect_coins[subinterval_first][subinterval_last - 1][1] +
                    abs(pos[subinterval_last] - pos[subinterval_last - 1])
            );
            if (minimum_time_to_collect_coins[subinterval_first][subinterval_last][1] > deadline[subinterval_last])
                minimum_time_to_collect_coins[subinterval_first][subinterval_last][1] = INFINITY;
        }
    }

    int the_answer = std::min(
        minimum_time_to_collect_coins[0][number_of_coins - 1][0],
        minimum_time_to_collect_coins[0][number_of_coins - 1][1]
    );
    if (the_answer < INFINITY)
        return convert_to_string(the_answer);
    else
        return std::string("No solution");
}

int main()
{
    std::vector<Coin> input;
    std::cin >> input;
    std::cout << compute_the_minimum_time_needed_to_collect_all_the_coins(input) << std::endl;
    return 0;
}
