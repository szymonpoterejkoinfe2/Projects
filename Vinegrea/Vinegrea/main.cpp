#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iomanip> 
#include <deque>
#include "function.h"
#include "structure.h"


int main(int number, char * params[])
{
	
	std::vector<std::string> Input_Switches, Input_Files;
	int Can_Decrypt_Files = 0, keylength = 0;
	std::vector<shift_value> Shift_and_Value;
	const int NUMBER_OF_FILES { 4 };
	bool Can_Decrypt_Switches = false, Switch_case_One = false;
	std::string encrypted_text_file = "";
	std::string pattern_text_file = "";
	std::string key_file = "";
	std::string output_file = "";


	for (int i = 1; i < number; i++)
	{
		if (i % 2 == 1)
		{
			Input_Switches.push_back(params[i]);
		}
		else
			Input_Files.push_back(params[i]);
	}

	action(number,Can_Decrypt_Files,params,Input_Switches,Input_Files,Switch_case_One,Can_Decrypt_Switches);

	if (Switch_case_One && Input_Switches.size() >= NUMBER_OF_FILES)
	{
		encrypted_text_file = Input_Files[0];
		pattern_text_file = Input_Files[2];
		key_file = Input_Files[3];
		output_file = Input_Files[1];
	}
	else if (Input_Switches.size() >= NUMBER_OF_FILES)
	{
		encrypted_text_file = Input_Files[3];
		pattern_text_file = Input_Files[1];
		key_file = Input_Files[2];
		output_file = Input_Files[0];
	}

	if(Can_Decrypt_Files == NUMBER_OF_FILES && Can_Decrypt_Switches)
	{
			 
				std::cout << "All files were found!" << std::endl;
				std::cout << "Decryption in progress..." << std::endl;
				std::ifstream file(encrypted_text_file);
				keylength = findkeyLength(encrypted_text_file);

				std::deque<double> letters_Counted = count_Letters(pattern_text_file);
				
				std::deque<std::deque<char> > letters_separated_deques = create_deque_Sepparated_letters(encrypted_text_file, keylength);
				for (int i = 0; i < letters_separated_deques.size(); i++)
				{
					std::deque<double> averages_spacing = count_Letters(letters_separated_deques[i]);

					Shift_and_Value.push_back(find_shift(letters_Counted, averages_spacing));

				}
				decrypt(output_file, Shift_and_Value, encrypted_text_file, key_file);

	}
	else
	{
		return 0;
	}

	return 0;
}
