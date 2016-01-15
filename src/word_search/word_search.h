#ifndef WORD_SEARCH_WORD_SEARCH_H_
#define WORD_SEARCH_WORD_SEARCH_H_

#include <vector>
#include <string>

namespace word_search {

    class WordSearch {
    public:
        WordSearch();
        ~WordSearch();

        bool LoadFile(std::string file_name);

        void PrintGrid();
        bool FindWord(std::string word);

        void ClearHighlights() {
            highlight_word_coordinates_.clear();
        }

        static const bool PRINT_DEBUG = false;

    protected:
        std::vector<std::vector<char>> word_grid_;
        std::vector<size_t> highlight_word_coordinates_;
    };

} // namespace word_search

#endif // WORD_SEARCH_WORD_SEARCH_H_