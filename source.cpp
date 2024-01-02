#include <chrono>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <random>
#include <fstream>
#include <string>
#include <sstream>

 std::vector<int> findDiagonalOrder(std::vector<std::vector<int>>& nums) {
        std::unordered_map<int, std::vector<int>> groups;
        for(int i = (int)nums.size() - 1; i >= 0; i--){
            for(int j = 0; j < nums[i].size(); ++j){
                groups[i + j].push_back(nums[i][j]);
            }
        }

        std::vector<int> answer;
        int curr = 0;
        while(groups.find(curr) != groups.end()){
            for(int& num : groups[curr]){
                answer.push_back(num);
            }

            ++curr;
        }

        return answer;
    }

    std::vector<int> findDiagonalOrderBFS(std::vector<std::vector<int>>& nums) {
        std::queue<std::pair<int, int>> q;
        std::vector<int> answer;
        q.push({0, 0});
        while(!q.empty()){
            int currentSize = q.size();
            bool firstElement = true;
            while(currentSize--){
                std::pair<int, int> curr = q.front();
                q.pop();

                answer.push_back(nums[curr.first][curr.second]);
                if(firstElement){
                    if(curr.first + 1 < nums.size() && curr.second < nums[curr.first + 1].size()){
                        q.push({curr.first + 1, curr.second});
                    }
                    firstElement = false;
                }

                if(curr.second + 1 < nums[curr.first].size()){
                    q.push({curr.first, curr.second + 1});
                }
            }
        }

        return answer;
    }

void generateTestCases(){
    std::cout << "Generating... please wait...\n";
    std::default_random_engine engine(time(0));
    std::uniform_int_distribution<int> random(1, 50000);
    for(int i = 0; i < 20; ++i){
        std::string fileName = "DataSet_";
        std::ofstream outputFile{fileName + std::to_string(i) + "_10^7.txt"};
        for(int k = 0; k < 10000; ++k){
            std::string row;
            for(int j = 0; j < 1000; ++j){
               row.append(std::to_string(random(engine)) + " ");
            }
            
            row.pop_back();
            row.push_back('\n');
            outputFile.write(row.c_str(), row.size());
        }
        outputFile.close();
    }

    std::cout << "Test cases generated successfully" << std::endl;
}

int main(){
    //generateTestCases();
    //Read file into vector
    std::ifstream inputFile{"DataSet_19_10^7.txt"};
    std::vector<std::vector<int>> matrix;
    std::string line;
    while(std::getline(inputFile, line)){
        std::string num;
        std::stringstream stream(line);
        std::vector<int> row;
        while(std::getline(stream, num, ' ')){
            row.push_back(std::stoi(num));
        }
        matrix.push_back(row);
    }

    //Start testing
    auto timeOne = std::chrono::high_resolution_clock::now();
    //findDiagonalOrder(matrix);
    findDiagonalOrderBFS(matrix);
    auto timeTwo = std::chrono::high_resolution_clock::now();
    std::cout << "\n\nTest duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(timeTwo - timeOne).count() << "ms\n\n";
}