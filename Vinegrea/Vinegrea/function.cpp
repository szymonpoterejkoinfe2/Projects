#include <iostream>
#include<string>
#include <fstream>
#include <vector>
#include <map>
//#include <cctype>
//#include <cstdlib>
#include <deque>
#include <iomanip> 
#include <cmath>

#include "function.h"
#include "structure.h"


void action(int &number, int &can_decrypt_files, char* params[],const std::vector<std::string>& inputSw, const std::vector<std::string>& inputFi, bool& switch_case_one, bool& can_decrypt_switches)
{
	// Printiong short manual of program
	if (number == 1)
	{
		print_Instruction();
	}

	// when all inputs entered
	else if (number == 9)
	{
		std::cout << "Number of parameters is OK" << std::endl;

		can_decrypt_switches = switches_check(inputSw, switch_case_one);

		for (int i = 0; i < inputFi.size(); i++)
		{
			can_decrypt_files += Valid_file(inputFi[i]);
		}

	}

	// Wrong number of inputs
	else
	{
		std::cout << "Wrong number of input parameters!";
	}


}

void print_Instruction()
{
	std::cout << "Program breaks a cyphertext encrypted with an unknown key with the Vigenere method." << std::endl;
	std::cout << "The program elaborates the unknown key and decrypts the encrypted file.\n The program is run in command line with switches:" << std::endl;
	std::cout << " -i input text file (cyphertext)\n -w sample text in the same language as the cyphertext \n -k output text file with the elaborated key \n -o output text file (plainext)" << std::endl;

}

bool switches_check(const std::vector<std::string> &input_value, bool& Option_One)
{
	std::string Possibility_One[4] = {"-i","-o","-w","-k"};
	std::string Possibility_Two[4] = {"-o","-w","-k","-i"};
	int Return_true = 0;

	if (input_value[0] == "-i")
	{
		Return_true += 1;
		Option_One = true;
		for (int i = 1; i < input_value.size(); i++)
		{
			if (input_value[i] != Possibility_One[i])
			{
				std::cout << "Wrong switch: " << input_value[i] << std::endl;
			}
			else
			{
				Return_true += 1;
			}
		}
		if (Return_true == 4)
		{
			return true;
		}
		else
			return false;
	}
	else if (input_value[0] == "-o")
	{
		Return_true += 1;
		for (int i = 1; i < input_value.size(); i++)
		{
			if (input_value[i] != Possibility_Two[i])
			{
				std::cout << "Wrong switch: " << input_value[i] << std::endl;
			}
			else
			{
				Return_true += 1;
			}
		}
		if (Return_true == 4)
		{
			return true;
		}
		else
			return false;
	}
	else
	{
		std::cout << "Switch Error! you typed: " << input_value[0] << std::endl;
		for (int i = 1; i < input_value.size(); i++)
		{
			if (input_value[i] != Possibility_One[i] || input_value[i] != Possibility_One[i])
			{
				std::cout << "Switch Error! you typed: " << input_value[i] << std::endl;
			}
		}
		return false;
	}
		
}

int Valid_file(const std::string& File_Name) {

	int cycle_counter = 0;

	std::fstream file(File_Name);
	if (!file)
		std::cout << "File " << File_Name << " can't be found! Check if name is proper and/or if file exists." << std::endl;
	else
	{
		cycle_counter += 1;
		file.close();
	}
	return cycle_counter;
}

bool is_Alphabetic_Character(char& letter)
{
	char allowed_Letters[] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
	char letterevaluated = ' ';

	bool exists = std::find(std::begin(allowed_Letters), std::end(allowed_Letters), letter) != std::end(allowed_Letters);

	return exists;
}

std::deque<double> count_Letters(const std::string& file_name)
{
	const int SIZE = 'z' - 'a' + 1;
	std::deque<double> Letters_Counted;
	std::ifstream file(file_name);
	int file_size = 0;
	Letters_Counted.assign(26,0);
	bool exists = false;

	if (file)
	{
	
		char letterread = ' ', letter = ' ';
		while (file >> letterread)
		{
			letter = tolower(letterread);
			exists = is_Alphabetic_Character(letter);
			
			if (exists)
			{
				file_size++;
				Letters_Counted[letter - 'a']++;
			}
		}
		for (int i = 0; i < Letters_Counted.size(); i++)
		{
			Letters_Counted[i] = Letters_Counted[i] / file_size;
		}

	}
	return Letters_Counted;
}

std::deque<std::deque<char> > create_deque_Sepparated_letters(const std::string& file_name, const int &spacing)
{
	std::ifstream file(file_name);
	bool exists = false;
	std::deque<char> letters_separated;
	std::deque<std::deque<char> > letters_separated_deques;

	if (file)
	{
		char letterread = ' ', letter = ' ';
		
		while (file >> letterread)
		{
			letter = tolower(letterread);
			exists = is_Alphabetic_Character(letter);

			if (exists)
			{
				letters_separated.push_back(letter);
			}
		}

	}

	for (int j = 0; j < spacing; j++)
	{
		std::deque<char> separated_chars;
		
	

		
			
		
		for (int i = 0; i < letters_separated.size(); i += spacing)
		{
			separated_chars.push_back(letters_separated[i]);
		}
	

		letters_separated_deques.push_back(separated_chars);


		letters_separated.pop_front();

	}

	
	return letters_separated_deques;
}

std::deque<double> count_Letters(std::deque<char>& letters)
{

	std::deque<double> Letters_Counted;
	Letters_Counted.assign(26, 0);

	for (int i = 0; i < letters.size(); i++)
	{
		Letters_Counted[letters[i] - 'a']++;
	}
	for (int i = 0; i < Letters_Counted.size(); i++)
	{
		Letters_Counted[i] = Letters_Counted[i] / letters.size();
	}

	return Letters_Counted;
}

shift_value find_shift(std::deque<double>& sample_average, std::deque<double>& decrypted_average)
{
	size_t cycles = sample_average.size();
	int  step = 0;
	
	double suma_z_roznic_pomiedzy_2_dequami = 0;
	std::vector<double>	sumy;
	shift_value shift_min;

	
	while (step < cycles)
	{
		
		std::vector<double> WektorRoznic;


		for (int i = 0; i < sample_average.size(); i++)
		{
			double absolute_value = fabs(decrypted_average[i] - sample_average[i]);
	
			WektorRoznic.push_back(absolute_value);
		}

			double holder = 0;
			holder = sample_average.back();
			sample_average.pop_back();
			sample_average.push_front(holder);

		suma_z_roznic_pomiedzy_2_dequami = Sum_of_shift(WektorRoznic);
		
		sumy.push_back(suma_z_roznic_pomiedzy_2_dequami);
		
		step++;
	}
	
	shift_min = min_difference(sumy);

	return shift_min;
}

double Sum_of_shift(std::vector<double>& vector_Of_averages)
{
	double added_avg = 0, final_average = 0;

	for (int i = 0; i < vector_Of_averages.size(); i++)
	{
		added_avg += vector_Of_averages[i];
	}
	final_average = (added_avg/vector_Of_averages.size());
	return final_average;
}

shift_value min_difference(const std::vector<double>& vector_Of_averages)
{
	double comparing_min_value = 100;
	int shift = 0;
	shift_value p;

	for (int i = 0; i < vector_Of_averages.size(); i++)
	{
		if (vector_Of_averages[i] < comparing_min_value)
		{
			shift = i;
			comparing_min_value = vector_Of_averages[i];
		}
	}
	p.Structshift = shift;
	
	return p;
	
}

int findkeyLength(const std::string& file_name)
{
	std::ifstream file(file_name);
	int file_size = 0;
	char letterread = ' ', letter = ' ';
	std::deque<std::deque<double>> coincedence_indexes;
	std::deque<double> coincedence_indexes_of_spacing_i;
	const double proportion = 0.40;

	while (file >> letterread)
	{
		letter = tolower(letterread);
		bool exists = is_Alphabetic_Character(letter);

		if (exists)
		{
			file_size++;
		}
	}

	


	for (int i = 1; i < (file_size / 2) + 1; i++)
	{
		std::deque<std::deque<char>> letters_separated = create_deque_Sepparated_letters(file_name, i);

		std::deque<std::deque<double>> averages_counted;

		for (int j = 0; j < letters_separated.size(); j++)
		{
				averages_counted.push_back(count_Letters(letters_separated[j]));
		}

		double average_of_index = 0;

	

		for (int k = 0; k < averages_counted.size(); k++)
		{
			average_of_index += calculate_index_of_coincedence(averages_counted[k]);
		}

		average_of_index = (average_of_index / averages_counted.size());
		coincedence_indexes_of_spacing_i.push_back(average_of_index);

		if (coincedence_indexes_of_spacing_i.size() > 2)
		{
			for (int k = 1; k < coincedence_indexes_of_spacing_i.size(); k++)
			{
				double compare = (coincedence_indexes_of_spacing_i[k - 1] += (coincedence_indexes_of_spacing_i[k - 1] * proportion));

				if (compare < coincedence_indexes_of_spacing_i[k])
				{
					int key = k + 1;

					//std::cout <<"Key: "<< key << std::endl;

					return key;
				}

			}
		}

	}
	/*for (int k = 0; k < coincedence_indexes_of_spacing_i.size(); k++)
	{
		std::cout << coincedence_indexes_of_spacing_i[k] << " ";
	}
	std::cout << std::endl;*/
	//std::cout << "Key: 1" << std::endl;
	return 1;
}

double calculate_index_of_coincedence(std::deque<double> input_averages)
{
	double index = 0;

	for (int i = 0; i < input_averages.size(); i++)
	{
		index += ((input_averages[i] * input_averages[i]));

	}
	return index;

}

void decrypt(std::string& Return_File_Name, std::vector<shift_value>& key, std::string& Input_File_name, std::string& Key_file)
{
	std::ifstream input_file(Input_File_name);
	std::ofstream output_file(Return_File_Name);
	std::ofstream key_file(Key_file);
	const int sta = 1;

	int shift = 0,incrementer = 0;

	if (input_file && output_file)
	{
		std::string line = "";
		char letter = ' ', helper =' ';
		while (std::getline(input_file, line, '\0')) {
			bool exists = false;
			incrementer = 0;

			for (int i = 0; i < line.size(); i++) {

				letter = tolower(line[i]);
				exists = is_Alphabetic_Character(letter);

				if (exists)
				{
					shift = key[incrementer % key.size()].Structshift;

					if (int(letter - shift) < int('a'))
					{
						helper = char(int('z' - (shift - (letter - 'a') - sta)));
					}
					else
					{
						helper = char(int(letter - shift));

					}
					output_file << helper;
					incrementer++;
				}
				else
				{
					output_file << letter;
				}
			}
		}

		std::cout << "Decryption successful! Check file: " << Return_File_Name << " to see decrypted text and file: " <<Key_file << " to see shift." << std::endl;

	}
	key_file << "Shift is equal: ";
	for (int i = 0; i < key.size(); i++)
	{

		key_file << key[i].Structshift << " ";

	}
	key_file << " Key size is equal: " << key.size();

	input_file.close();
	output_file.close();
	key_file.close();


}


	


