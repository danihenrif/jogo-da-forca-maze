#include <iostream>

#include <thread>
#include <chrono>

  char seisErros[] = 
  {
    '\0', '\0', 'O', '\0', '\0',
    '/', '|', '\\', '\0', '\0',
    '\0', '/', '\\', '\0', '\0',

  };
  char cincoErros[] = 
  {
    '\0', '\0', 'O', '\0', '\0',
    '/', '|', '\\', '\0', '\0',
    '\0', '/', '\0', '\0', '\0',

  };
  char quatroErros[] = 
  {
    '\0', '\0', 'O', '\0', '\0',
    '/', '|', '\\', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0',

  };
  char tresErros[] = 
  {
    '\0', '\0', 'O', '\0', '\0',
    '/', '|', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0',

  };
  char doisErros[] = 
  {
    '\0', '\0', 'O', '\0', '\0',
    '\0', '\0', '|', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0',

  };
  char umErro[] = 
  {
    '\0', '\0', 'O', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0',

  };
  char zeroErros[] = 
  {
    '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0',

  };

    //Printa a forca
    void printaForca(int erros){
        switch(erros){
            case 0:
                for(int i = 0 ; i < 15 ; i++){
                    cout << zeroErros[i] << " ";
                    if(i == 4 || i == 9 || i == 14){cout << endl;}
                }
                break;
            case 1:
                for(int i = 0 ; i < 15 ; i++){
                    cout << umErro[i] << " ";
                    if(i == 4 || i == 9 || i == 14){cout << endl;}
                }
                break;
            case 2:
                for(int i = 0 ; i < 15 ; i++){
                    cout << doisErros[i] << " ";
                    if(i == 4 || i == 9 || i == 14){cout << endl;}
                }
                break;
            case 3:
                for(int i = 0 ; i < 15 ; i++){
                    cout << tresErros[i] << " ";
                    if(i == 4 || i == 9 || i == 14){cout << endl;}
                }
                break;
            case 4:
                for(int i = 0 ; i < 15 ; i++){
                    cout << quatroErros[i] << " ";
                    if(i == 4 || i == 9 || i == 14){cout << endl;}
                }
                break;
            case 5:
                for(int i = 0 ; i < 15 ; i++){
                    cout << cincoErros[i] << " ";
                    if(i == 4 || i == 9 || i == 14){cout << endl;}
                }
                break;
            case 6:
                for(int i = 0 ; i < 15 ; i++){
                    cout << seisErros[i] << " ";
                    if(i == 4 || i == 9 || i == 14){cout << endl;}
                }
                break;
            default:
                break;
        }
    }
    
void wait(int ms){
    this_thread::sleep_for(chrono::milliseconds(ms));
}

void clearScreen(){
    #if defined _WIN32
        system("cls");
    #elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
    #elif defined(__APPLE__)
        system("clear");
    #endif
}



