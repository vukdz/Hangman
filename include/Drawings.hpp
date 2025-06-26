// include/Drawings.hpp
#pragma once
#ifndef DRAWINGS_HPP
#define DRAWINGS_HPP

#include <string>
#include <vector>

const std::string s0 = "---------\n|       |\n|        \n|        \n|      \n_\n";
const std::string s1 = "---------\n|       |\n|       O\n|        \n|      \n_\n";
const std::string s2 = "---------\n|       |\n|       O\n|       |\n|      \n_\n";
const std::string s3 = "---------\n|       |\n|       O\n|      /|\n|      \n_\n";
const std::string s4 = "---------\n|       |\n|       O\n|      /|\\\n|      \n_\n";
const std::string s5 = "---------\n|       |\n|       O\n|      /|\\\n|      /\n_\n";
const std::string s6 = "---------\n|       |\n|       O\n|      /|\\\n|      / \\\n_\n";

const std::vector<std::string> hang = { s0, s1, s2, s3, s4, s5, s6 };

#endif // DRAWINGS_HPP