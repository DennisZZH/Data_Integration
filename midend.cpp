#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

#include "parameters.h"
#include "utility.h"

using namespace std;

vector<vector<string>> unfolding(vector<vector<string>> global_quries){
	vector<vector<string>> local_quries;

	for (auto& query : global_quries) {
		string schema_name = query[0];

		// Direct unfolding

		if (schema_name == "Movie") {
			vector<string> movies(22, "_");
			movies[0] = "movies";
			for (int i = 1; i < query.size(); i++) movies[i] = query[i];
			local_quries.push_back(movies);
			continue;
		}

		if (schema_name == "Principal") {
			vector<string> title_principals(6, "_");
			title_principals[0] = "title_principals";
			title_principals[3] = query[1];
			title_principals[1] = query[2];
			title_principals[4] = query[3];
			local_quries.push_back(title_principals);
			continue;
		}

		if (schema_name == "Oscar") {
			vector<string> the_oscar_award(7, "_");
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
			vector<string> movies(22, "_"); // same table as Movie
			movies[0] = "movies";
			movies[2] = query[1];
			movies[14] = query[2];
			movies[15] = query[3];
			local_quries.push_back(movies);
			continue;
		}

		if (schema_name == "Finance") {
			vector<string> movies(22, "_"); // same table as Movie
			movies[0] = "movies";
			movies[2] = query[1];
			movies[17] = query[2];
			movies[19] = query[3]; // income is global
			local_quries.push_back(movies);
			continue;
		}

		// Indirect unfolding, run unfolding algorithm

		if (schema_name == "Nominee") {	// special case, unfolded to two tables
			vector<string> oscar_personnel(27, "NA");
			vector<string> names(17, "NA");
			oscar_personnel[0] = "oscar_personnel"; 
			names[0] = "names";
			names[1] = query[1];
			names[2] = query[2]; // or oscar_personnel[xxx]
			oscar_personnel[8] = query[3];
			oscar_personnel[6] = query[4];
			names[4] = query[5];
			oscar_personnel[10] = query[6];
			oscar_personnel[12] = query[7];
			oscar_personnel[14] = query[8];
			oscar_personnel[2] = query[9];
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

	for (auto& query : local_queries) {
		string schema_name = query[0];

		if (schema_name == "movies") {
			string sql = sql_builder(query, MOVIE_PARAS);
		}

		if (schema_name == "title_principals") {
			string sql = sql_builder(query, PRINCIPAL_PARAS);
		}

		if (schema_name == "the_oscar_award") {
			string sql = sql_builder(query, OSCAR_PARAS);
		}

		if (schema_name == "") {}

		if (schema_name == "") {}

		if (schema_name == "") {}

		if (schema_name == "") {}

		if (schema_name == "") {}

		if (schema_name == "") {}

		if (schema_name == "") {}

		if (schema_name == "") {}

	}

	return sql_queries;
}

string sql_builder(vector<string> query, vector<string> paras){
	string sql = "SELECT ";
	string table_name = query[0];
	for (int i = 0; i < paras.size(); i++){
		if (i != paras.size() - 1) {
			sql += table_name + "." + paras[i] + ",";
		}
		else{
			sql += table_name + "." + paras[i] + "\n";
		}
	}
	
	sql += "FROM " + table_name + "\n";
	sql += "WHERE ";
	for (int i = 1; i < query.size(); i++) {
		if (query[i] != "_") {
		    sql += paras[i - 1] + "=\"" + query[i] + "\"";
		    if(i != query.size() - 1) {
		        sql +=  + " AND ";
		    }
		}	
	}
	return sql;
}