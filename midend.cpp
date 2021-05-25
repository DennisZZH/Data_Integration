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

		if (schema_name == "Nominee") {
			//STUB
		}

	}
	
	/*
	if(sc=="Nominee"){
		vector<string> oscar_personnel(27, "NA");
		vector<string> names(17, "NA");
		oscar_personnel[0] = "oscar_personnel"; // special case, unfolded to two tables
		names[0] = "names";

		names[1] = schema[1];
		names[2] = schema[2]; // or oscar_personnel[xxx]
		oscar_personnel[8] = schema[3];
		oscar_personnel[6] = schema[4];
		names[4] = schema[5];
		oscar_personnel[10] = schema[6];
		oscar_personnel[12] = schema[7];
		oscar_personnel[14] = schema[8];
		oscar_personnel[2] = schema[9];
		
		// Transform to SQL Here!!!
		
	}*/


	return local_quries;
}

vector<string> traslating(vector<vector<string>> local_queries) {

}