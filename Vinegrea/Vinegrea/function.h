#pragma once
#ifndef FUNCTION_H
#define FUNCTION_H

#include "structure.h"

/** A function that is responsible for checking the correctness of program input data
@param number holds number of input parameters
@param can_decrypt_files holds number of correct files on which the program operates.
@param params holds input parameters
@param inputSw vector of input switches
@param inputFi vector of input and output files
@param switch_case_one bool confirming that the first combination of input switches is met
@param can_decrypt_switches bool which confirms that all input switches are valid.
@return Function does not return any value
*/
void action(int& number, int& can_decrypt_files, char* params[], const std::vector<std::string>& inputSw, const std::vector<std::string>& inputFi, bool& switch_case_one, bool& can_decrypt_switches);


/** A function that prints short program instructions.
@param Function does not require any parameters
@return Function does not return any value
*/
void print_Instruction();

/** A function that checks the correctness of program input switches.
@param input_value vector of input switches, the correctness of which we check
@param Option_One bool evaluates whether we have encountered the first possibility of switches
@return Function return true if all input switches are correct
*/
bool switches_check(const std::vector<std::string>& input_value, bool& Option_One);

/** A function that checks the correctness of input file.
@param File_Name the name of the file we are checking for correctness
@return Function return 1 if input file exists if not then 0
*/
int Valid_file(const std::string& File_Name);

/** A function that calculates the average of the number of each letter in the input file.
@param file_Name name of the file containing the text whose average number of letters will be counted
@return The function returns a deque containing the average of the occurrences.
*/
std::deque<double> count_Letters(const std::string &file_name);

/** A function that generates deques containing letters from the input file. these letters are divided by spaces of length n
@param file_Name name of the file containing the text from which characters will be taken
@param spacing is the value which represents te leng of spaces between letters.
@return The function returns a deque containing deques with separated characters.
*/
std::deque<std::deque<char> > create_deque_Sepparated_letters(const std::string& file_name, const int& spacing);

/** A function that calculates the average of the number of each letter in the input deque.
@param letters name of the deque containing the encrypted message which letter average we want to calculate.
@return The function returns a deque containing the average of the occurrences.
*/
std::deque<double> count_Letters(std::deque<char>& letters);

/** A function that looks for an shift between a single letter in the encoded file and a letter in the plaintext file using their averages.
@param sample_average deque cantaining average of the occurrences of sample file.
@param decrypted_average deque cantaining average of the occurrences of decrypted file.
@return The function returns an int that corresponds to the shift of the encrypted message
*/
shift_value find_shift(std::deque<double>& sample_average, std::deque<double>& decrypted_average);

/** A functionthat sums all values from the input vector.
@param vector_Of_averages the vector in which we want to sum all the values
@return Function return sum of vector
*/
double Sum_of_shift(std::vector<double>& vector_Of_averages);

//! A function that finds the smallest value in the input vector.
//!@param vector_Of_averages the vector in which we want to find the smallest value.
//!@return Function return smallest value in vector
shift_value min_difference(const std::vector<double>& vector_Of_averages);

//! A function that dtermines if input characte is alphabetic
//!@param letter character we evaluate.
//!@return true if input character is alphabetic
bool is_Alphabetic_Character(char& letter);

/** A function hat calculate index of coincedence of the input deque.
@param input_averages deque containing average occurance of every alphabetic character.
@return Function returns index of coincede of input deque.
*/
double calculate_index_of_coincedence(std::deque<double> input_averages);

/** A function that determines the most likely length of the key used to encrypt the message
@param file_name name of the file containing the encrypted message whose key length we are looking for.
@return the function returns an int which is the most likely length of the searched key.
*/
int findkeyLength(const std::string& file_name);

/** A function that decrypts an encrypted message based on a previously found shift.
@param Return_File_Name name of the file where the decrypted message is to be saved
@param key vector with strict shift containing shift value of every key character.
@param Input_File_name the name of the file we want to decrypt.
@param Key_file file where the key to decrypt the message is to be saved
@return Function does not return any value
*/
void decrypt(std::string& Return_File_Name, std::vector<shift_value>& key, std::string& Input_File_name, std::string& Key_file);
#endif