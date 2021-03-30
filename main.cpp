#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <string>
#include <vector>
#include <tuple>
#include <future>
#include <functional>
#include <chrono>
#include <cctype>
#include <locale>
#include <iomanip>


// TODO: Implement exception handling for file IO


// TODO: Finish defining this function
bool csv_to_vector (std::vector<std::pair<std::string,std::string>>& vec, const std::string& file_path, const bool shuffle) {
  std::ifstream file;
  file.open(file_path);
  for (std::string line; std::getline(file, line);) {
    vec.push_back(std::make_pair(line.substr(0, line.find(',')), line.substr(line.find(',')+1)));
  }
  file.close();
  
  if (shuffle) {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(vec.begin(), vec.end(), std::default_random_engine(seed));
  }

  return true;
}


// TODO: Finish defining main
int main(int argc, char** argv) {
  

  std::string file_path(argv[1]);
  std::vector<std::pair<std::string,std::string>> question_vec;
  std::vector<std::tuple<std::string,std::string,std::string>> wrong_answers;
  std::string answer;
  bool shuffle;

  std::cout << "\n\n\t===== Welcome to BashFlash ======";
  std::cout << "\n\n\t> File Provided: " << file_path;
  std::cout << "\n\n\t> Do you want to shuffle the deck?\n" << "\n\n\t(yes/no): ";
  while (true) {
    std::cin >> answer;
    if (answer == "yes") {
      shuffle = true;
      break;
    }
    else if (answer == "no") {
      shuffle = false;
      break;
    }
    else
      std::cout << "\n\t> Please answer yes or no: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');



  std::future<bool> file_read_success = std::async(std::launch::async, &csv_to_vector, std::ref(question_vec), std::ref(file_path), shuffle);

  std::cout << "\n\t> Are you ready to begin?" << "\n\n\t(yes/no): ";
  
  while (true) {
    std::cin >> answer;
    if (answer == "yes") 
      break;
    else if (answer == "no")
      return 0;
    else
      std::cout << "\n\t> Please answer yes or no: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');


  if(!file_read_success.get()) {
    std::cerr << "\n\t> ERROR: Could not read file\n\n> EXITING\n" << std::endl;
    return -1;
  }

  std::cout << "\t> Let's begin...\n\n\t========================================\n";

  unsigned short total = 0;
  unsigned short correct = 0;

  for (std::pair<std::string,std::string> prompt_answer : question_vec) {
    std::string input;
    std::cout << "\n\t" << total+1 << ". "  << prompt_answer.first <<
      "\n\tanswer: ";
    std::getline(std::cin,input);

    
    std::string lowercase_correct_answer = prompt_answer.second;
    std::string lowercase_user_answer = input;
    std::transform(lowercase_correct_answer.begin(), lowercase_correct_answer.end(), lowercase_correct_answer.begin(), [](char c){return static_cast<char>(std::tolower(c));});
    std::transform(lowercase_user_answer.begin(), lowercase_user_answer.end(), lowercase_user_answer.begin(), [](char c){return static_cast<char>(std::tolower(c));});

    
    
    if (lowercase_user_answer == "quit")
      break;
    if (lowercase_user_answer == lowercase_correct_answer)
      correct++;
    else
      wrong_answers.push_back(std::make_tuple(prompt_answer.first, prompt_answer.second, input));

#ifdef DEBUG
    std::cout << "(DEBUG Input: " << input << ')' << std::endl;
#endif

    total++;
  }

  std::cout << "\n\t===== Results =====\n";
  std::cout << "\tCorrect: " << correct << "\n\tTotal: " << total << '\n' 
    << "\tPercentage: " << std::setprecision(4) << (correct/(total * 1.0f)) 
    << '\n' << std::endl;
  
  std::cout << "\n\tQuestions you missed:\n";

  if (argc == 3) {
    std::ofstream output_file;
    output_file.open(argv[2]);
    for (std::tuple<std::string,std::string,std::string> prompt_answer_user : wrong_answers) {
      output_file << std::get<0>(prompt_answer_user) << ',' << std::get<1>(prompt_answer_user) << '\n';
      std::cout << "\tQ: " << std::get<0>(prompt_answer_user) << '\n';
      std::cout << "\tA: " << std::get<1>(prompt_answer_user) << '\n';
      std::cout << "\tU: " << std::get<2>(prompt_answer_user) << "\n\n"; 
    }
    output_file.close();
  }
  else {
    for (std::tuple<std::string,std::string,std::string> prompt_answer_user : wrong_answers) {
      std::cout << "\tQ: " << std::get<0>(prompt_answer_user) << '\n';
      std::cout << "\tA: " << std::get<1>(prompt_answer_user) << '\n';
      std::cout << "\tU: " << std::get<2>(prompt_answer_user) << "\n\n";
    }
  }

  std::cout << std::endl;
  
  return 0;
}
