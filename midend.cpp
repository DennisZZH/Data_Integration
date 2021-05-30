#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

#include "parameters.h"
#include "utility.h"

using namespace std;

bool isLastArg(vector<string>& query, int index) {
	for (int i = index + 1; i < query.size(); i++) {
		if (query[i] != "_") return false;
	}
	return true;
}

string sql_builder(vector<string>& query, const vector<string> paras){
	string sql = "SELECT ";
	string table_name = query[0];
	for (int i = 0; i < paras.size(); i++){
		if (query[i] == "_") continue;
		if (!isLastArg(query, i)) {
			sql += table_name + "." + paras[i] + " AS " + paras[i] + ", ";
		}
		else{
			sql += table_name + "." + paras[i] + " AS " + paras[i] + "\n";
		}
	}
	sql += "FROM " + table_name + "\n";
	sql += "WHERE ";
	for (int i = 1; i < paras.size(); i++) {
		if (query[i] == "_") continue;
		sql += paras[i] + "=" + query[i];
		if(!isLastArg(query, i)) {
		    sql +=  + " AND ";
		}
	}
	return sql;
}

vector<vector<string>> unfolding(vector<vector<string>> global_quries){
	vector<vector<string>> local_quries;

	for (auto& query : global_quries) {
		string schema_name = query[0];

		// Direct unfolding

		if (schema_name == "Movie") {
			vector<string> movies(MOVIES_LOCAL_SCHEMA_PARAS.size() + 1, "_");
			movies[0] = "movies";
			movies[1] = query[1];
			movies[2] = query[2];
			movies[3] = query[3];
			movies[5] = query[4];
			movies[7] = query[5];
			movies[8] = query[6];
			movies[6] = query[7];
			local_quries.push_back(movies);
			continue;
		}

		if (schema_name == "Principal") {
			vector<string> title_principals(TITLE_PRINCIPALS_LOCAL_SCHEMA_PARAS.size() + 1, "_");
			title_principals[0] = "title_principals";
			title_principals[2] = query[1];
			title_principals[1] = query[2];
			title_principals[3] = query[3];
			local_quries.push_back(title_principals);
			continue;
		}

		if (schema_name == "Oscar") {
			vector<string> the_oscar_award(THE_OSCAR_AWARD_LOCAL_SCHEMA_PARAS.size() + 1, "_");
			the_oscar_award[0] = "the_oscar_award";
			the_oscar_award[5] = query[1]; // winner name = name + winner=="True"
			the_oscar_award[7] = "True";
			the_oscar_award[2] = query[2];
			the_oscar_award[4] = query[3];
			the_oscar_award[6] = query[4];
			local_quries.push_back(the_oscar_award);
			continue;
		}

		if (schema_name == "Rating") {
			vector<string> movies(MOVIES_LOCAL_SCHEMA_PARAS.size() + 1, "_"); // same table as Movie
			movies[0] = "movies";
			movies[2] = query[1];
			movies[10] = query[2];
			movies[11] = query[3];
			local_quries.push_back(movies);
			continue;
		}

		if (schema_name == "Finance") {
			vector<string> movies(MOVIES_LOCAL_SCHEMA_PARAS.size() + 1, "_"); // same table as Movie
			movies[0] = "movies";
			movies[2] = query[1];
			movies[12] = query[2];
			movies[13] = query[3]; // income is global
			local_quries.push_back(movies);
			continue;
		}

		// Indirect unfolding, run unfolding algorithm

		if (schema_name == "Nominee") {	// special case, unfolded to two tables
			vector<string> oscar_personnel(OSCAR_PERSONNEL_LOCAL_SCHEMA_PARAS.size() + 1, "_");
			vector<string> names(NAMES_LOCAL_SCHEMA_PARAS.size() + 1, "_");
			oscar_personnel[0] = "oscar_personnel"; 
			names[0] = "names";
			names[1] = query[1];
			names[2] = query[2]; // or oscar_personnel[xxx]
			oscar_personnel[3] = query[3];
			oscar_personnel[2] = query[4];
			names[3] = query[5];
			oscar_personnel[4] = query[6];
			oscar_personnel[5] = query[7];
			oscar_personnel[6] = query[8];
			oscar_personnel[1] = query[9];
			local_quries.push_back(oscar_personnel);
			local_quries.push_back(names);
			continue;
		}

		if (schema_name == "Popular modern actor") {}

		if (schema_name == "Minority actor") {}

		if (schema_name == "Foreign actor") {}

		if (schema_name == "Successful modern movie") {}

		if (schema_name == "Oscar movie rating") {}

	}
	
	return local_quries;
}

vector<string> translating(vector<vector<string>> local_queries) {
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


string join_queries(vector<string> sql_queires) {
	string res = "";
    for (int i = 0; i < sql_queires.size(); i++) {
		res += sql_queires[i];
		if (i != sql_queires.size() - 1) {
			res += "\n";
		    res += "UNION";
		    res += "\n";
		}
	}
    res += ";";
	return res;
}
