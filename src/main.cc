#include "word_search/word_search.h"
#include "word_search/command_interpreter.h"
#include "word_search/commands/commands.h"

#include <string>
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {
    word_search::WordSearch ws;
    word_search::CommandInterpreter command_interpreter(ws);

    printf("***********************\n");
    printf("*** WordSearch v1.0 ***\n");
    printf("***********************\n");

    if(!ws.LoadFile(R"(data\words.txt)")) {
        printf("\n[!] Could not find 'data\\words.txt'\n");
        printf("[!] Please load the word search manually using the `load` command.\n");
    }

    std::string input = "";

    command_interpreter.AddCommand("search", word_search::commands::Search);
    command_interpreter.AddCommand("print", word_search::commands::Print);
    command_interpreter.AddCommand("clear", word_search::commands::Clear);
    command_interpreter.AddCommand("find", word_search::commands::Find);
    command_interpreter.AddCommand("load", word_search::commands::Load);

    for(;;) {
        printf("\n> ");
        std::getline(std::cin, input);

        if(input == "exit") {
            break;
        } else {
            if(!command_interpreter.ProcessCommand(input)) {
                printf("[!] Command not found: %s\n", input.c_str());
            }
        }
    }

    return 0;
}