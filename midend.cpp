#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

#include "parameters.h"
#include "utility.h"

using namespace std;

string find_match_conds(string t1, string t2) {
	if (t1 == t2) {
		if (t1 == "movies") return "imdb_title_id";
		if (t1 == "names") return "imdb_name_id";
		if (t1 == "oscar_personnel") return "name";
	}
	if ( (t1 == "movies" && t2 == "title_principals") || (t2 == "movies" && t1 == "title_principals") ) return "imdb_title_id";
	if ( (t1 == "names" && t2 == "title_principals") || (t2 == "names" && t1 == "title_principals") ) return "imdb_name_id";
	if ( (t1 == "oscar_personnel" && t2 == "names") || (t2 == "oscar_personnel" && t1 == "names") ) return "name";
	if ( (t1 == "movies" && t2 == "the_oscar_award") || (t2 == "movies" && t1 == "the_oscar_award") ) return "title";
	cout << "ERROR: find_match_conds(): Unable to find matching condiction for table " + t1 + " and table " + t2  + " !"<< endl;
	exit(0);
}

bool isLastArg(vector<string>& query, int index) {
	for (int i = index + 1; i < query.size(); i++) {
		if (query[i] != "_") return false;
	}
	return true;
}

bool isLastCond(vector<string>& query, int index) {
	for (int i = index + 1; i < query.size(); i++) {
		if (query[i] != "_" && query[i] != "S") return false;
	}
	return true;
}

string sql_builder(vector<string>& query, const vector<string> paras){
	string sql = "SELECT ";
	string table_name = query[0];
	for (int i = 1; i < query.size(); i++){
		if (query[i] == "_") continue;
		if (!isLastArg(query, i)) {
			sql += table_name + "." + paras[i-1] + ", ";
		}
		else{
			sql += table_name + "." + paras[i-1] + " ";
		}
	}
	sql += "FROM " + table_name + " ";
	if (!isLastCond(query,0)) {
		sql += "WHERE ";
		for (int i = 1; i < query.size(); i++) {
			if (query[i] == "_" || query[i] == "S") continue;

			// check for !=
			if(query[i][1]=='!'){
				sql += paras[i-1] + "!=" + "\"" + query[i].substr(2,query[i].length()-2);
			}
			// check for >
			// WHERE CAST(worldwide_gross_income AS INT) > 2000000
			else if (query[i][0]=='>'){
				sql += "CAST(" + paras[i-1] + " AS INT)" + ">" + query[i].substr(1,query[i].length()-1);
			}
			else{
				sql += paras[i-1] + "=" + query[i];
			}

			if(!isLastCond(query, i)) {
				sql +=  + " AND ";
			}
		}
	}
	return sql;
}

vector<vector<string>> unfolding(vector<vector<string>>& global_quries){
	vector<vector<string>> local_quries;

	for (auto& query : global_quries) {
		string schema_name = query[0];

		// Direct unfolding

		if (schema_name == "Movie") {
			vector<string> movies(MOVIES_LOCAL_SCHEMA_PARAS.size() + 1, "_");
			movies[0] = "movies";
			query[1] == "_" ? movies[1] = "S" : movies[1] = query[1];
			query[2] == "_" ? movies[2] = "S" : movies[2] = query[2];
			query[3] == "_" ? movies[3] = "S" : movies[3] = query[3];
			query[4] == "_" ? movies[5] = "S" : movies[5] = query[4];
			query[5] == "_" ? movies[7] = "S" : movies[7] = query[5];
			query[6] == "_" ? movies[8] = "S" : movies[8] = query[6];
			query[7] == "_" ? movies[6] = "S" : movies[6] = query[7];
			local_quries.push_back(movies);
			continue;
		}

		if (schema_name == "Principal") {
			vector<string> title_principals(TITLE_PRINCIPALS_LOCAL_SCHEMA_PARAS.size() + 1, "_");
			title_principals[0] = "title_principals";
			query[1] == "_" ? title_principals[2] = "S" : title_principals[2] = query[1];
			query[2] == "_" ? title_principals[1] = "S" : title_principals[1] = query[2];
			query[3] == "_" ? title_principals[3] = "S" : title_principals[3] = query[3];
			local_quries.push_back(title_principals);
			continue;
		}

		if (schema_name == "Oscar") {
			vector<string> the_oscar_award(THE_OSCAR_AWARD_LOCAL_SCHEMA_PARAS.size() + 1, "_");
			the_oscar_award[0] = "the_oscar_award";
			query[1] == "_" ? the_oscar_award[5] = "S" : the_oscar_award[5] = query[1]; 
			the_oscar_award[7] = "True";	// winner name = name + winner=="True"
			query[2] == "_" ? the_oscar_award[2] = "S" : the_oscar_award[2] = query[2];
			query[3] == "_" ? the_oscar_award[4] = "S" : the_oscar_award[4] = query[3];
			query[4] == "_" ? the_oscar_award[6] = "S" : the_oscar_award[6] = query[4];
			local_quries.push_back(the_oscar_award);
			continue;
		}

		if (schema_name == "Rating") {
			vector<string> movies(MOVIES_LOCAL_SCHEMA_PARAS.size() + 1, "_"); // same table as Movie
			movies[0] = "movies";
			query[1] == "_" ? movies[2] = "S" : movies[2] = query[1];
			query[2] == "_" ? movies[10] = "S" : movies[10] = query[2];
			query[3] == "_" ? movies[11] = "S" : movies[11] = query[3];
			local_quries.push_back(movies);
			continue;
		}

		if (schema_name == "Finance") {
			vector<string> movies(MOVIES_LOCAL_SCHEMA_PARAS.size() + 1, "_"); // same table as Movie
			movies[0] = "movies";
			query[1] == "_" ? movies[2] = "S" : movies[2] = query[1];
			query[2] == "_" ? movies[12] = "S" : movies[12] = query[2];
			query[3] == "_" ? movies[13] = "S" : movies[13] = query[3]; // income is global
			local_quries.push_back(movies);
			continue;
		}

		// Indirect unfolding, run unfolding algorithm

		if (schema_name == "Nominee") {	// special case, unfolded to two tables
			vector<string> oscar_personnel(OSCAR_PERSONNEL_LOCAL_SCHEMA_PARAS.size() + 1, "_");
			vector<string> names(NAMES_LOCAL_SCHEMA_PARAS.size() + 1, "_");
			oscar_personnel[0] = "oscar_personnel"; 
			names[0] = "names";
			query[1] == "_" ? names[1] = "S" : names[1] = query[1];

			query[2] == "_" ? names[2] = "S" : names[2] = query[2]; // IMPORTANT, MUST HAVE BOTH!!!
			query[2] == "_" ? oscar_personnel[11] = "S" : oscar_personnel[11] = query[2];

			query[3] == "_" ? oscar_personnel[3] = "S" : oscar_personnel[3] = query[3];
			query[4] == "_" ? oscar_personnel[2] = "S" : oscar_personnel[2] = query[4];
			query[5] == "_" ? names[3] = "S" : names[3] = query[5];
			query[6] == "_" ? oscar_personnel[4] = "S" : oscar_personnel[4] = query[6];
			query[7] == "_" ? oscar_personnel[5] = "S" : oscar_personnel[5] = query[7];
			query[8] == "_" ? oscar_personnel[6] = "S" : oscar_personnel[6] = query[8];
			query[9] == "_" ? oscar_personnel[1] = "S" : oscar_personnel[1] = query[9];
			local_quries.push_back(names);
			local_quries.push_back(oscar_personnel);
			continue;
		}

		if (schema_name == "Minority actor") {
			vector<string> oscar_personnel(OSCAR_PERSONNEL_LOCAL_SCHEMA_PARAS.size() + 1, "_");
			oscar_personnel[0] = "oscar_personnel";
			query[1] == "_" ? oscar_personnel[11] = "S" : oscar_personnel[11] = query[1]; 
			oscar_personnel[4] = "\"!White\"";
            oscar_personnel[6] = "\"!Straight\"";
			local_quries.push_back(oscar_personnel);
			continue;
		}

		if (schema_name == "Actor by country") {
			vector<string> names(NAMES_LOCAL_SCHEMA_PARAS.size() + 1, "_");
			names[0] = "names";
			query[1] == "_" ? names[2] = "S" : names[2] = query[1];
			query[2] == "_" ? names[6] = "S" : names[6] = query[2];
			local_quries.push_back(names);
			continue;
		}

		if (schema_name == "Commercially successful movie") {
			vector<string> movies(MOVIES_LOCAL_SCHEMA_PARAS.size() + 1, "_"); // same table as Movie
			movies[0] = "movies";
			query[1] == "_" ? movies[1] = "S" : movies[1] = query[1];
			query[2] == "_" ? movies[2] = "S" : movies[2] = query[2];
			query[3] == "_" ? movies[11] = "S" : movies[11] = query[3];
			query[4] == "_" ? movies[5] = "S" : movies[5] = query[4];
			query[5] == "_" ? movies[8] = "S" : movies[8] = query[5];
			query[6] == "_" ? movies[3] = "S" : movies[3] = query[6];
			movies[13] = ">100000000"; // 100 million
			local_quries.push_back(movies);
			continue;
		}

		if (schema_name == "High rating movie") {
			vector<string> movies(MOVIES_LOCAL_SCHEMA_PARAS.size() + 1, "_"); // same table as Movie
			movies[0] = "movies";
			query[1] == "_" ? movies[1] = "S" : movies[1] = query[1];
			query[2] == "_" ? movies[2] = "S" : movies[2] = query[2];
			query[3] == "_" ? movies[13] = "S" : movies[13] = query[3]; 
			query[4] == "_" ? movies[5] = "S" : movies[5] = query[4];
			query[5] == "_" ? movies[8] = "S" : movies[8] = query[5];
			query[6] == "_" ? movies[3] = "S" : movies[3] = query[6];
			movies[11] = "\">9.5\"";
			local_quries.push_back(movies);
			continue;
		}

		if (schema_name == "Oscar movie rating") {
			vector<string> the_oscar_award(THE_OSCAR_AWARD_LOCAL_SCHEMA_PARAS.size() + 1, "_");
			vector<string> movies(MOVIES_LOCAL_SCHEMA_PARAS.size() + 1, "_");
			the_oscar_award[0] = "the_oscar_award"; 
			movies[0] = "movies";
			query[1] == "_" ? movies[1] = "S" : movies[1] = query[1];
			query[2] == "_" ? movies[2] = "S" : movies[2] = query[2];
			query[2] == "_" ? the_oscar_award[6] = "S" : the_oscar_award[6] = query[2];
			query[3] == "_" ? the_oscar_award[2] = "S" : the_oscar_award[2] = query[3];
			query[4] == "_" ? movies[11] = "S" : movies[11] = query[4];
			the_oscar_award[7] = "\"True\"";
			local_quries.push_back(the_oscar_award);
			local_quries.push_back(movies);
			continue;
		}

	}
	
	return local_quries;
}

vector<string> translating(vector<vector<string>>& local_queries) {
	vector<string> sql_queries;
	string sql;

	for (auto& query : local_queries) {
		string schema_name = query[0];

		if (schema_name == "movies") {
			sql = sql_builder(query, MOVIES_LOCAL_SCHEMA_PARAS);
		}

		else if (schema_name == "title_principals") {
			sql = sql_builder(query, TITLE_PRINCIPALS_LOCAL_SCHEMA_PARAS);
		}

		else if (schema_name == "the_oscar_award") {
			sql = sql_builder(query, THE_OSCAR_AWARD_LOCAL_SCHEMA_PARAS);
		}

		else if (schema_name == "oscar_personnel") {
			sql = sql_builder(query, OSCAR_PERSONNEL_LOCAL_SCHEMA_PARAS);
		}

		else if (schema_name == "names") {
			sql = sql_builder(query, NAMES_LOCAL_SCHEMA_PARAS);
		}

		else {
			cout << "ERROR: translating(): Unable to match local schema " << schema_name << "!" << endl;
		}

		sql_queries.push_back(sql);
	}

	return sql_queries;
}


string join_queries(vector<string>& sql_queries, vector<vector<string>>& local_queries, vector<string> answer_selection) {
	string res = "";
	res += "SELECT ";
	for (int i = 0; i < answer_selection.size(); i++) {
		if (i != answer_selection.size() - 1) {
			res += answer_selection[i] + ", ";
		}
		else {
			res += answer_selection[i] + "\n";
		}
	}
	res += "FROM\n";
	
	for (int i = 0; i < sql_queries.size(); i++) {
		string curr = "(" + sql_queries[i] + ") " + "t" + to_string(i);
		if (i != 0) {
			res += "INNER JOIN\n";
			res += curr + "\n";
			string match_cond = find_match_conds(local_queries[i-1][0], local_queries[i][0]);
			res += "ON t" + to_string(i-1) + "." + match_cond + " = t" + to_string(i) + "." + match_cond + "\n";
		}
		else {
			res += curr + "\n";
		}
	} 
    
	res += ";";
	return res;
}
