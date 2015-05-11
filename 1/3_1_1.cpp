//3_1_1 task Pavel Pivkin

#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>

#define NIL "*"
#define a 127 // simple number


class HashTable {
    public:
                        HashTable();
                        HashTable(std::size_t buf_);
                        ~HashTable();
        bool            Add(const std::string &str);
        bool            Remove(const std::string &str); // return "false" if there is not string in the HashTable
        int             IsContains(const std::string &str); // return -1 if there is not string in the HashTable else return string position
        void            Print();
    
    private:
        std::size_t     buf;
        std::size_t     real_size;
        float           GetFullFactor();
        void            Increase();
        std::string     *array;
        std::size_t     Hash(std::string, size_t M); 
        
};  

int main() {
    HashTable hashTable;
    char operation = ' ';
    std::string input_string;
    while(  std::cin.get(operation) ) {
        std::getline(std::cin, input_string);
        switch(operation){
            case '+':
                if(hashTable.Add(input_string)) {
                    std::cout << "OK" << std::endl;
                } else {
                    std::cout << "FAIL" << std::endl;
                }               
                break;
            case '-':
                if(hashTable.Remove(input_string)) {
                    std::cout << "OK" << std::endl;
                } else {
                    std::cout << "FAIL" << std::endl;
                }
                break;
            case '?':
                if(hashTable.IsContains(input_string) != -1) {
                    std::cout << "OK" << std::endl;
                } else {
                    std::cout << "FAIL" << std::endl;
                }     
                break; 
        }
    }
    
    return 0;
}


HashTable::HashTable() : buf(8), real_size(0) {
    array = new std::string [buf];
}

HashTable::HashTable(std::size_t buf_) : buf(buf_), real_size(0) {
    array = new std::string [buf];
}

HashTable::~HashTable() {
    delete [] array;
}

bool HashTable::Add(const std::string &str) {
    if ( str != "" && str != NIL && IsContains(str) == -1 ) {
        this -> Increase();
        std::size_t i = 1;
        std::size_t prob = Hash(str, buf);
        while( array[prob] != "\0" || array[prob] == NIL ) {
            prob = (prob + i + i*i) % buf;
            i++;
        }
        array[prob] = str;
        real_size++;
        return true;
    } else {
        return false;
    }
}

std::size_t HashTable::Hash(std::string str, std::size_t M) {
    std::size_t h = 0;
    for (std::size_t i = 0; i < str.size(); i++) {
        h = (a * h + str[i]) % M;
    }
    return h;
}

void HashTable::Print() {
    for (std::size_t i = 0; i < buf; i++) {
        if(array[i] == "\0") {
            std::cout << "NOTHING YET" << std::endl;
        }
        else if(array[i] == NIL) {
            std::cout << "NIL HERE" << std::endl;
        }
        else {
            std::cout << array[i] << std::endl;
        }
    }
}
void HashTable::Increase(){
    if (GetFullFactor() >= 0.75) {
        HashTable *tmpHashTable = new HashTable(buf * 2);
        for(std::size_t i = 0; i < buf; i++) {
            tmpHashTable -> Add(array[i]);
        }
        delete[] array;
        buf = buf * 2;
        array = new std::string[buf];
        real_size = tmpHashTable -> real_size;
        for(std::size_t i = 0; i < buf; i++) {
            array[i] = tmpHashTable -> array[i];
        }
        delete tmpHashTable;
    }
}

float HashTable::GetFullFactor() {
    return float(real_size)/float(buf);
}

int HashTable::IsContains(const std::string &str) {
    std::size_t i = 1;
    int prob = Hash(str, buf);
    while( array[prob] != "\0" || array[prob] == NIL ) {
        if (array[prob] == str) {
            return prob;
        }
        prob = (prob + i + i*i) % buf;
        i++;
    }
    return -1;
}

bool HashTable::Remove(const std::string &str) {
    int remove_index = IsContains(str);
    if(remove_index > -1) {
        array[remove_index] = NIL;
        return true;
    } else {
        return false;
    }    
}


