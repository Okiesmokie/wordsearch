#include "command_interpreter.h"

namespace word_search {

    CommandInterpreter::CommandInterpreter(WordSearch &ws) : word_search_(ws) {
    }

    CommandInterpreter::~CommandInterpreter() {
    }

    bool CommandInterpreter::ProcessCommand(std::string command_string) {
        CommandParams params;
        //params.push_back("Test Param");

        // Split the string
        size_t position = 0;
        std::string tokenize = command_string;
        std::string command;

        while((position = tokenize.find(" ")) != std::string::npos) {
            params.push_back(tokenize.substr(0, position));
            tokenize.erase(0, position + 1); // + 1 to remove the space as well
        }

        params.push_back(tokenize);

        command = params[0];
        params.erase(std::begin(params));


        return ProcessCommand(command, params);
    }

    bool CommandInterpreter::ProcessCommand(std::string command, CommandParams params) {
        auto iterator = command_map_.find(command);

        if(iterator == command_map_.end()) {
            return false;
        }

        (*iterator->second)(word_search_, params);

        return true;
    }

    bool CommandInterpreter::AddCommand(std::string command, CommandFunction func) {
        // Check if the command already exists.
        auto iterator = command_map_.find(command);

        if(iterator != command_map_.end()) {
            return false;
        }

        // If not, add it
        command_map_.insert(std::make_pair(command, func));

        return true;
    }

} // namespace word_search