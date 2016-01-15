#include "commands.h"

#include <iostream>
#include <cstdio>

namespace word_search {
    namespace commands {

        void Search(WordSearch &ws, CommandParams params) {
            std::string input = "";

            for(;;) {
                ::system("cls");

                ws.PrintGrid();

                ::printf("Input '@@@' to return to command mode\n");
                ::printf("Search: ");

                std::getline(std::cin, input);

                if(input == "@@@") {
                    ::system("cls");
                    break;
                } else {
                    ws.FindWord(input);
                }
            }
        }

        void Print(WordSearch &ws, CommandParams params) {
            ws.PrintGrid();
        }

        void Clear(WordSearch &ws, CommandParams params) {
            ws.ClearHighlights();
            printf("Highlighted words have been cleared.\n");
        }

        void Find(WordSearch &ws, CommandParams params) {
            if(params.size() <= 0) {
                printf("[!] Usage: find [word1] [word2] [word3] ...\n");
                return;
            }

            for(auto param : params) {
                printf("Searching for: %s... ", param.c_str());

                if(ws.FindWord(param)) {
                    printf("Found!\n");
                } else {
                    printf("Not found.\n");
                }
            }
        }

        void Load(WordSearch &ws, CommandParams params) {
            if(params.size() <= 0) {
                printf("[!] Usage: load [filename] ...\n");
                return;
            }

            // Join all the parameters with spaces between
            std::string file_name = "";

            for(auto param : params) {
                file_name += param + " ";
            }

            // Remove the last space
            file_name.erase(file_name.length() - 1);

            printf("Loading: %s... ", file_name.c_str());

            if(ws.LoadFile(file_name)) {
                printf("Success!\n");
            } else {
                printf("File not found.\n");
            }
        }

    } // namespace commands
} // namespace word_search