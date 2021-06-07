#pragma once
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print_query_str(const string& query_str, const string& comment) {
    cout << "\n------------------------------------Testing: Print " << comment << "------------------------------------" << endl;
    cout << query_str << endl;
}

void print_str_vector(const vector<string>& str_vec, const string& comment) {
     cout << "\n------------------------------------Testing: Print " << comment << "------------------------------------" << endl;
     for (auto& s : str_vec) cout << s << " ";
     cout << endl;
}

void print_query_vector(const vector<vector<string>>& query_vector, const string& comment) {
    cout << "\n------------------------------------Testing: Print " << comment << "------------------------------------" << endl;
    for (int i = 0; i < query_vector.size(); i++){
    	cout << i + 1 << ". ";
    	for (int j = 0; j < query_vector[i].size(); j++){
            if (j == 0) cout << "[" + query_vector[i][j];
            else if (j == query_vector[i].size() - 1) cout << query_vector[i][j] + "]";
    		else cout << query_vector[i][j];
            if (j != query_vector[i].size() - 1) cout << ",";
    	}
    	cout << endl;
    }
    cout << endl;
}

void print_sql_vector(const vector<string>& sql_queries, const string& comment) {
    cout << "\n------------------------------------Testing: Print " << comment << "------------------------------------" << endl;
    for (int i = 0; i < sql_queries.size(); i++){
    	cout << i + 1 << ". ";
    	cout << sql_queries[i] << endl;
    }
    cout << endl;
}


