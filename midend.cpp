#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

#include "parameters.h"
#include "utility.h"

using namespace std;

string sql_builder(vector<string>& query, vector<string>& paras){
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
	int acc = 0;
	for (int i = 1; i < query.size(); i++) {
		if (query[i] != "_") {
		    sql += paras[acc++] + "=\"" + query[i] + "\"";
		    if(acc < paras.size()) {
		        sql +=  + " AND ";
		    }
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
			vector<string> movies(23, "_");
			movies[0] = "Movie_movies";
			movies[1] = query[1];
			movies[2] = query[2];
			movies[4] = query[3];
			movies[6] = query[4];
			movies[8] = query[5];
			movies[9] = query[6];
			movies[7] = query[7];
			local_quries.push_back(movies);
			continue;
		}

		if (schema_name == "Principal") {
			vector<string> title_principals(7, "_");
			title_principals[0] = "Principal_title_principals";
			title_principals[3] = query[1];
			title_principals[1] = query[2];
			title_principals[4] = query[3];
			local_quries.push_back(title_principals);
			continue;
		}

		if (schema_name == "Oscar") {
			vector<string> the_oscar_award(8, "_");
			the_oscar_award[0] = "Oscar_the_oscar_award";
			the_oscar_award[5] = query[1]; // winner name = name + winner=="True"
			the_oscar_award[7] = "True";
			the_oscar_award[2] = query[2];
			the_oscar_award[4] = query[3];
			the_oscar_award[6] = query[4];
			local_quries.push_back(the_oscar_award);
			continue;
		}

		if (schema_name == "Rating") {
			vector<string> movies(23, "_"); // same table as Movie
			movies[0] = "Rating_movies";
			movies[2] = query[1];
			movies[14] = query[2];
			movies[15] = query[3];
			local_quries.push_back(movies);
			continue;
		}

		if (schema_name == "Finance") {
			vector<string> movies(23, "_"); // same table as Movie
			movies[0] = "Finance_movies";
			movies[2] = query[1];
			movies[17] = query[2];
			movies[19] = query[3]; // income is global
			local_quries.push_back(movies);
			continue;
		}

		// Indirect unfolding, run unfolding algorithm

		if (schema_name == "Nominee") {	// special case, unfolded to two tables
			vector<string> oscar_personnel(28, "NA");
			vector<string> names(18, "NA");
			oscar_personnel[0] = "Nominee_oscar_personnel"; 
			names[0] = "Nominee_names";
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
	string sql;

	for (auto& query : local_queries) {
		string schema_name = query[0];

		if (schema_name == "Movie_movies") {
			query[0] = "movies";
			sql = sql_builder(query, MOVIE_PARAS);
		}

		else if (schema_name == "Principal_title_principals") {
			query[0] = "title_principals";
			sql = sql_builder(query, PRINCIPAL_PARAS);
		}

		else if (schema_name == "Oscar_the_oscar_award") {
			query[0] = "the_oscar_award";
			sql = sql_builder(query, OSCAR_PARAS);
		}

		else if (schema_name == "Rating_movies") {
			query[0] = "movies";
			sql = sql_builder(query, RATING_PARAS);
		}

		else if (schema_name == "Finance_movies") {
			query[0] = "movies";
			sql = sql_builder(query, FINANCE_PARAS);
		}

		else if (schema_name == "Nominee_oscar_personnel") {
			query[0] = "oscar_personnel";
			sql = sql_builder(query, NOMINEE_PERSONNEL_PARAS);
		}

		else if (schema_name == "Nominee_names") {
			query[0] = "names";
			sql = sql_builder(query, NOMINEE_NAMES_PARAS);
		}

		else if (schema_name == "") {}

		else if (schema_name == "") {}

		else if (schema_name == "") {}

		else if (schema_name == "") {}

		else if (schema_name == "") {}

		else {}

		sql_queries.push_back(sql);
	}

	return sql_queries;
}


string join_queries(vector<string> local_sql_queires) {
	string res = "";
}
