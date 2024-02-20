#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string fname, vector<string> &names, vector<int> &scores, vector<char> &grades){
    string mytext;
    ifstream MyReadFile(fname);
    while (getline (MyReadFile,mytext)) {
        char name[100];
        int score_temp1, score_temp2, score_temp3;
        sscanf(mytext.c_str(), "%[^:]: %d %d %d", name, &score_temp1, &score_temp2, &score_temp3);
        names.push_back(name);
        scores.push_back(score_temp1+score_temp2+score_temp3);
        grades.push_back(score2grade(score_temp1+score_temp2+score_temp3));
    }
    MyReadFile.close();
}

void getCommand(string &command, string &key){
    cout << "Please input your command: ";
    cin >> command;
    if(toUpperStr(command)=="NAME"||toUpperStr(command)=="GRADE"){
        cin.ignore();
        getline(cin,key);
    }
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
bool hasFound = false;
    cout << "---------------------------------\n";
    for(unsigned int i = 0; i < names.size(); i++){
       if(toUpperStr(key)==toUpperStr(names[i])){
           hasFound = true;
           cout << names[i] << "'s score = " << scores[i] << endl;
           cout << names[i] << "'s grade = " << grades[i] << endl;
       }
    }
    if(!hasFound){
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
bool hasFound = false;
    cout << "---------------------------------\n";
    for(unsigned int i = 0; i < names.size(); i++){
       if(*key.c_str()==grades[i]){
           hasFound = true;
           cout << names[i] <<" (" << scores[i] << ")" << endl;
       }
    }
    if(!hasFound){
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
