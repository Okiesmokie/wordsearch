#ifndef WORD_SEARCH_COMMAND_INTERPRETER_H_
#define WORD_SEARCH_COMMAND_INTERPRETER_H_

#include <string>
#include <vector>
#include <map>

#include "word_search.h"

namespace word_search {
    typedef std::vector<std::string> CommandParams;
    typedef void(*CommandFunction)(WordSearch &, CommandParams);
    typedef std::map<std::string, CommandFunction> CommandMap;

    class CommandInterpreter {
    public:
        CommandInterpreter(WordSearch &ws);
        ~CommandInterpreter();

        bool ProcessCommand(std::string command_string);
        bool ProcessCommand(std::string command, CommandParams params);

        bool AddCommand(std::string command, CommandFunction func);

    protected:
        WordSearch &word_search_;
        CommandMap command_map_;
    };

} // namespace word_search

#endif // WORD_SEARCH_COMMAND_INTERPRETER_H_