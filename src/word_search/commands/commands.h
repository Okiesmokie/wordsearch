#include "../word_search.h"
#include "../command_interpreter.h"

namespace word_search {
    namespace commands {
        void Search(WordSearch &ws, CommandParams params);
        void Print(WordSearch &ws, CommandParams params);
        void Clear(WordSearch &ws, CommandParams params);
        void Find(WordSearch &ws, CommandParams params);
        void Load(WordSearch &ws, CommandParams params);
    } // namespace commands
} // namespace word_search