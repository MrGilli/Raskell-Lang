//raskell parser.
//mov(i) 10 -> age; this raskell code will assign the value 10 to the int variable age.
//mov(s) "hello world" -> hello_string; this raskell code will assign the string 'hello world' to the string variable hello_string.
//mov(b) TRUE -> bool_example; boolean example in raskell.
//define f(hello):
//  take -> age, hello_string; Parses the variables age and hello_string into the function like def main(age, hello_string): in python.
//  out -> hello_string -> " and universe"; prints "hello world and universe" to the console
//  close /f(hello); END OF HELLO FUNCTION.

#include <fstream> 
#include <iostream> 
#include <string> 
#include <sstream>
#include <unordered_map>
using namespace std; 

void check_colon(string line, int line_count){
    size_t colon = line.find(';');
    if(colon == std::string::npos){
        // no endl colon
        cerr << "FATAL ERROR: no colon on line with code: " << line << endl;
    }
    else {
        return;
    }
}
int main() {
    std::unordered_map<std::string, int> intVariables; // Stores integer variables and their values
    std::string input_file;
    std::string raskell_file_extension = ".rk";
    std::string raskell_vars[5] = {"out", "mov(i)", "mov(s)", "mov(b)", "add"};

    std::cout << "FILE TO COMPILE(file_name.rk): ";
    std::cin >> input_file;
    bool isFound = input_file.find(raskell_file_extension) != std::string::npos;
    if (!isFound) {
        std::cout << "File '" << input_file << "' is not a raskell code file (file_name.rk)" << std::endl;
        std::cerr << "FATAL ERROR NO RASKELL SOURCE CODE FILE FOUND.";
        return 1;
    }

    std::ifstream inputFile(input_file);
    if (!inputFile.is_open()) {
        std::cerr << "No raskell compilable file named: " << input_file << std::endl;
        return 1;
    }

    std::string line;
    std::cout << input_file << " program output: " << "\n\n";
    int line_count = 1;
    while (std::getline(inputFile, line)) {
        bool print_operator = line.find(raskell_vars[0]) != std::string::npos;
        bool mov_i_operator = line.find(raskell_vars[1]) != std::string::npos;
        bool add_operator = line.find(raskell_vars[4]) != std::string::npos;

        if (print_operator) {
            check_colon(line, line_count);
            size_t arrow_pos = line.find("->");
            if (arrow_pos != std::string::npos) {
                std::string var_name = line.substr(arrow_pos + 3, line.size() - arrow_pos - 4);
                auto it = intVariables.find(var_name);
                if (it != intVariables.end()) {
                    std::cout << it->second << std::endl;
                } else {
                    std::cerr << "FATAL ERROR: Variable '" << var_name << "' not found." << std::endl;
                }
            }
        } else if (mov_i_operator) {
            check_colon(line, line_count);
            size_t space_pos = line.find(" ");
            if (space_pos != std::string::npos) {
                size_t arrow_pos = line.find("->", space_pos);
                if (arrow_pos != std::string::npos) {
                    std::string var_name = line.substr(arrow_pos + 3, line.size() - arrow_pos - 4);
                    int value = std::stoi(line.substr(space_pos + 1, arrow_pos - space_pos - 1));
                    intVariables[var_name] = value;
                }
            }
        } else if (add_operator) {
            check_colon(line, line_count);
            size_t space_pos = line.find(' ');
            if (space_pos != std::string::npos) {
                // Find the position of "->" after the space
                size_t arrow_pos = line.find("->", space_pos);
                size_t equal_pos = line.find("=>");
                if (arrow_pos != std::string::npos) {
                    // Extract the two integer values before and after "->"
                    std::string num1_str = line.substr(space_pos + 1, arrow_pos - space_pos - 1);
                    std::string num2_str = line.substr(arrow_pos + 3);
                    std::string var_name = line.substr(equal_pos + 3, line.size() - equal_pos - 4);
                    // Convert the substrings to integers
                    int num1 = stoi(num1_str);
                    int num2 = stoi(num2_str);
                    // Perform the addition and print the result
                    int value = num1 + num2;
                    intVariables[var_name] = value;
                    //std::cout << var_name << std::endl;
                }
            }
        }
        ++line_count;
    }

    inputFile.close();
    return 0;
}