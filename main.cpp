#include <iostream>
#include <fstream>
#include "deque.h"
#include <vector>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0]
                  << " <input_file> <fclass_cap>"
                  << std::endl;
        exit(1);
    }
    std::ifstream passanger_list;

    passanger_list.open(argv[1]);
    if (!passanger_list.good()) {
        std::cerr << "Error: cannot open file "<< argv[1] << std::endl;
        exit(1);
    }

    int first_class_num = atoi(argv[2]);
    if(first_class_num <= 0){
        std::cerr << "Error: invalid first class capacity"<< std::endl;
        exit(1);
    }

    Deque<int> deq;

    std::vector<int> passanger_vec;

    while(!passanger_list.eof()){
        int temp;
        passanger_list >> temp;
        passanger_vec.push_back(temp);
    }

    auto num_of_passanger = passanger_vec.size() - 1;

    for(unsigned int i = 0; i < num_of_passanger;i++){
        if(passanger_vec[i] <= first_class_num){
            deq.PushFront(passanger_vec[i]);
        } else{
            deq.PushBack(passanger_vec[i]);
        }
    }

    for(unsigned int i = 0; i < deq.Size(); i++){
        std::cout<<deq[i]<<" ";
    }
    std::cout<<'\n';
    return 0;


}