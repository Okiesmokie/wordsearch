#include <fstream>
#include <cstdio>
#include <algorithm>

#include "word_search.h"

namespace word_search {

    WordSearch::WordSearch() {
    }

    WordSearch::~WordSearch() {
    }

    bool WordSearch::LoadFile(std::string file_name) {
        std::ifstream file;

        file.open(file_name);

        if(!file.is_open()) {
            return false;
        }

        // Clear the word vector
        word_grid_.clear();
        highlight_word_coordinates_.clear();

        word_grid_.push_back(std::vector<char>());

        int row = 0;

        while(!file.eof()) {
            char c;
            file.get(c);

            if(c != '\n') {
                word_grid_[row].push_back(static_cast<char>(::toupper(c)));
            } else {
                ++row;
                word_grid_.push_back(std::vector<char>());
            }
        }

        if(file.is_open()) {
            file.close();
        }

        return true;
    }

    void WordSearch::PrintGrid() {
        for(size_t row = 0, row_size = word_grid_.size(); row < row_size; ++row) {
            for(size_t col = 0, col_size = word_grid_[row].size(); col < col_size; ++col) {
                bool highlighted_letter = false;
                for(size_t highlight_index = 0, highlight_index_size = highlight_word_coordinates_.size(); highlight_index < highlight_index_size; highlight_index += 2) {
                    /* highlight_index increases by two each time because coordinates
                        are stored in pairs of two */

                    auto highlight_x = highlight_word_coordinates_[highlight_index];
                    auto highlight_y = highlight_word_coordinates_[highlight_index + 1];

                    if(col == highlight_x && row == highlight_y) {
                        highlighted_letter = true;
                        ::printf("[%c]", word_grid_[row][col]);
                        break;
                    }
                }

                if(!highlighted_letter) {
                    ::printf(" %c ", word_grid_[row][col]);
                }
            }

            ::printf("\n");
        }
    }

    bool WordSearch::FindWord(std::string word) {
        //highlight_word_coordinates_.clear();

        std::transform(word.begin(), word.end(), word.begin(), ::toupper);

        if(word.length() <= 1) return false;

        int direction_vector_x[] = {
            -1, 0, 1,
            -1,    1,
            -1, 0, 1
        };

        int direction_vector_y[] = {
            -1, -1, -1,
             0,      0,
             1,  1,  1
        };

        std::vector<size_t> highlight_coordinates;

        for(size_t row = 0, row_size = word_grid_.size(); row < row_size; ++row) {
            for(size_t col = 0, col_size = word_grid_[row].size(); col < col_size; ++col) {
                highlight_coordinates.clear();

                auto letter = word_grid_[row][col];

                if(letter == word[0]) {
                    if(WordSearch::PRINT_DEBUG) {
                        ::printf("First Letter: %c\n", letter);
                    }

                    if(word.length() > 1) {
                        for(size_t direction = 0, direction_size = 8; direction < direction_size; ++direction) {
                            int check_col = direction_vector_x[direction] + static_cast<int>(col);
                            int check_row = direction_vector_y[direction] + static_cast<int>(row);

                            if(check_row < word_grid_.size() && check_row >= 0) {
                                if(check_col < word_grid_[check_row].size() && check_col >= 0) {
                                    if(WordSearch::PRINT_DEBUG) {
                                        ::printf("[1] Direction %d, Checking: (%d, %d), Letter: %c\n", direction, check_col, check_row, word_grid_[check_row][check_col]);
                                    }

                                    if(word_grid_[check_row][check_col] == word[1]) {
                                        highlight_coordinates.push_back(col);
                                        highlight_coordinates.push_back(row);
                                        highlight_coordinates.push_back(check_col);
                                        highlight_coordinates.push_back(check_row);

                                        // Keep searching in the same direction
                                        bool found_word = true; // True because the loop below will not run if the word is <= 2 characters
                                        int last_check_col = check_col;
                                        int last_check_row = check_row;

                                        for(size_t i = 2, word_length = word.length(); i < word_length; ++i) {
                                            found_word = false; // If the word is > 2 characters, we haven't found it

                                            int check_col2 = direction_vector_x[direction] + static_cast<int>(last_check_col);
                                            int check_row2 = direction_vector_y[direction] + static_cast<int>(last_check_row);

                                            last_check_col = check_col2;
                                            last_check_row = check_row2;

                                            if(check_row2 < word_grid_.size() && check_row2 >= 0) {
                                                if(check_col2 < word_grid_[check_row2].size() && check_col2 >= 0) {
                                                    if(WordSearch::PRINT_DEBUG) {
                                                        ::printf("[%d] Direction %d, Checking: (%d, %d), Letter: %c\n", i, direction, check_col2, check_row2, word_grid_[check_row2][check_col2]);
                                                    }

                                                    if(word_grid_[check_row2][check_col2] != word[i]) {
                                                        highlight_coordinates.clear();
                                                        break; // Break out of i < word_length
                                                    } else {
                                                        found_word = true;
                                                        highlight_coordinates.push_back(check_col2);
                                                        highlight_coordinates.push_back(check_row2);
                                                    }
                                                }
                                            }
                                        }

                                        if(found_word) {
                                            if(WordSearch::PRINT_DEBUG) {
                                                ::printf("Found the word! Starting: (%d,%d), Direction: %d\n", col, row, direction);
                                            }
                                            highlight_word_coordinates_.insert(std::end(highlight_word_coordinates_), std::begin(highlight_coordinates), std::end(highlight_coordinates));
                                            return true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

            }
        }

        return false;
    }

} // namespace word_search