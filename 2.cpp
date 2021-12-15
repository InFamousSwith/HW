#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
    int c0 = 0;
    int c1 = 0;
    int a;
    int sum1 = 0;
    int sum2 = 0;
    int symb;
    std::ifstream filein;
    filein.open(argv[1]);
    std::vector<int> sym;
    if (argc == 3 ) {
        std::ifstream file;
        file.open(argv[1]);
        if (!file.is_open()) {
            std::cout << "ERROR: не удалось открыть файл!" << std::endl;
        }
        else {
            file >> a;
            while (file >> symb)
            {
                sym.push_back(symb);
            }
        }
        filein.close();
		sort(sym.begin(),sym.end());
		for(int i = 0;i < a/2; i++){
            sum1 += sym[i];
		}
		for(int i = a/2; i<a ; i++){
            sum2 += sym[i];
		}
        std::ofstream fileout;
        fileout.open(argv[2]);
        fileout << sum2 - sum1;
        fileout.close();
    }
    
    return 0;
}
