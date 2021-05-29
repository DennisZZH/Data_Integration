#pragma once
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print_query_vector(vector<vector<string>> query_vector) {
    cout << "Testing: Print query vectors" << endl;
    for (int i = 0; i < query_vector.size(); i++){
    	cout << i + 1 << ". ";
    	for (int j = 0; j < query_vector[i].size(); j++){
            if (j == 0) cout << query_vector[i][j] + " (";
            else if (j == query_vector[i].size() - 1) cout << query_vector[i][j] + ")";
    		else cout << query_vector[i][j] + ",";
    	}
    	cout << endl;
    }
    cout << endl;
}

void print_mid_end_vector(vector<vector<vector<string>>> midend){
    cout<<"Mid End vector:"<<endl;
    for(int i=0;i<midend.size();i++){
    	cout<<i<<": ";
    	for(int j=0;j<midend[i].size();j++){
    		cout<<"[";
    		for(int k=0;k<midend[i][j].size();k++){
                if(k!=midend[i][j].size()-1){
                    cout<<midend[i][j][k]<<",";
                }
                else{
                    cout<<midend[i][j][k];
                }
    		}
            if(j!=midend[i].size()-1){
                cout<<"]";
            }
            else{
                cout<<"],";
            }
    	}
    	cout << endl;
    }
    cout << endl;
}

