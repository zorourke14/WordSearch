#include <iostream>
#include <vector>
#include <cstring>
#include "colormod.h"
using namespace std;

vector<vector<bool>> matchVector;
int type, counter;

void match(vector< vector<char> > &matrix, char *word, int x, int y,int type){
    switch (type){

        //Word goes to the right
        case 0: 
            for(int i = 0; i<matchVector[0].size();i++){
                matchVector[x][y+i]=1;
                if(i==strlen(word)-1){
                    break;
                }
            }
        break;

        //Word goes to the left
        case 1: 
            for(int i = 0; i<matchVector[0].size();i++){
                matchVector[x][y-i]=1;
                if(i==strlen(word)-1){
                    break;
                }
            }
        break;

        //Word goes up
        case 2: 
            for(int i = 0; i<matchVector.size();i++){
                matchVector[x-i][y]=1;
                if(i==strlen(word)-1){
                    break;
                }
            }
        break;

        //Word goes down
        case 3: 
            for(int i = 0; i<matchVector.size();i++){
                matchVector[x+i][y]=1;
                if(i==strlen(word)-1){
                    break;
                }
            }
        break;

        //Word goes top right
        case 4: 
        counter = 0;
            while(true){
                matchVector[x-counter][y+counter]=1;
                if(counter==strlen(word)-1){
                    break;
                }
                counter++;
            }
        break;

        //Word goes top left
        case 5: 
        counter = 0;
            while(true){
                matchVector[x-counter][y-counter]=1;
                if(counter==strlen(word)-1){
                    break;
                }
                counter++;
            }
        break;

        //Word goes bottom right
        case 6: 
        counter = 0;
            while(true){
                matchVector[x+counter][y+counter]=1;
                if(counter==strlen(word)-1){
                    break;
                }
                counter++;
            }
        break;

        //Word goes bottom left
        case 7: 
        counter = 0;
            while(true){
                matchVector[x+counter][y-counter]=1;
                if(counter==strlen(word)-1){
                    break;
                }
                counter++;
            }
        break;

    }
}

bool testWord(vector< vector<char> > &matrix, char *word, int x, int y, int dx, int dy) {
    for (int i = 0; i < strlen(word); i++) {
        if (x < 0 || x >= matrix.size() || y < 0 || y >= matrix[0].size() || matrix[x][y] != word[i]) {
            return false;
        }
        x += dx;
        y += dy;
    }
    return true;
}

bool searchWordDirectional(vector< vector<char> > &matrix, char *word, int x, int y, int dx, int dy) {
    for (int i = 0; i < strlen(word); i++) {
        if (matrix[x][y] != word[i]) {
            return false;
        }
        x += dx;
        y += dy;
    }
    return true;
}

bool findWord(vector< vector<char> > &matrix, char *word, int x, int y){
    for(int dx = -1; dx<2; dx++){
        for(int dy = -1; dy<2; dy++){
            if(dx != 0 || dy != 0){
                if (testWord(matrix, word, x, y, dx, dy)) {
                    if (searchWordDirectional(matrix, word, x, y, dx, dy)) {
                        if(dx==0 && dy==1){
                            type =0;
                        }
                        else if(dx==0 && dy==-1){
                            type =1;
                        }
                        else if(dx==-1 && dy==0){
                            type =2;
                        }
                        else if(dx==1 && dy==0){
                            type =3;
                        }
                        else if(dx==-1 && dy==+1){
                            type =4;
                        }
                        else if(dx==-1 && dy==-1){
                            type =5;
                        }
                        else if(dx==+1 && dy==+1){
                            type =6;
                        }
                        else if(dx==+1 && dy==-1){
                            type =7;
                        }
                        match(matrix,word,x,y,type);
                    }
                }
            }
        }
    }
    return false;
}

int main(int argC, char *argv[]){
    Color::Setting red(Color::FG_RED); 
    Color::Setting def(Color::FG_DEFAULT);
    int x,y;
    char z;

    //Enter values
    cin >> x;
    cin >> y;

    //Declare vectors and resize
    vector<vector<char>> vec; 
    vec.resize(x); 
    matchVector.resize(x); 
    for(int i = 0; i<vec.size();i++){
        vec[i].resize(y);
        matchVector[i].resize(y);
    }

    //Insert char z into each index
    for(int i = 0; i < vec.size(); i++) {
        for(int j = 0; j < vec[i].size(); j++) {
            cin>>z;
            vec[i][j]=z; 
            //Make every element of matching vector hold 0
            matchVector[i][j] = 0; 
        }
            cout<<endl;
    }

    //Iterate through word search grid
    for(int k = 1; k<argC; k++){
        for(int i = 0; i < vec.size(); i++) {
            for(int j = 0; j < vec[i].size(); j++) { 
                if(vec[i][j]==(argv[k])[0]){
                    findWord(vec, argv[k], i, j);
                }
            }
        }
    }

    //Print colored Vector
    for(int i = 0; i < matchVector.size(); i++) {
        for(int j = 0; j < matchVector[i].size(); j++) {
            if(matchVector[i][j]==1){
                cout<<red<<vec[i][j]<<def<<" "; 
            }

            else{
                cout<<vec[i][j]<< " "; 
            }
        }
            cout<<endl;
    }

    return 0;
}