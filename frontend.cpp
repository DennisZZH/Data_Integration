#include <iostream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <utility>
#include <sqlite3.h>

#include "midend.cpp"
#include "backend.cpp"
#include "parameters.h"
#include "utility.h"

using namespace std;

vector<string> str_split_semicol(string str) {
	vector<string> res;
	size_t start = 0, pos = str.find(";");
	string s;
	while (pos != string::npos) {
		s = str.substr(start, pos - 1 - start);
		res.push_back(s);
		start = pos + 1;
		pos = str.find(";", start);
	}
	if (start != str.length()) {
		s = str.substr(start);
		res.push_back(s);
	}
	return res;
}

/* Flag bit is set if we want to include schema name into the vector*/
vector<string> str_strip_parens(string str, bool flag) {
	vector<string> res;
	string title_str, paras_str;
	size_t pos_start = str.find("("), pos_end = str.find(")");

	if (flag) {
		title_str = str.substr(0, pos_start);
		res.push_back(title_str);
	}
	
	paras_str = str.substr(pos_start + 1, pos_end - pos_start - 1);
	size_t start = 0, pos = paras_str.find(",");
	string s;
	while (pos != string::npos) {
		s = paras_str.substr(start, pos - start);
		res.push_back(s);
		start = pos + 1;
		pos = paras_str.find(",", start);
	}
	if (start != paras_str.length()) {
		s = paras_str.substr(start);
		res.push_back(s);
	}

	return res;
}

vector<string> get_answer_selection(string conj_str) {
	size_t pos = conj_str.find("<-");
	string ans_str = conj_str.substr(0, pos);
	return str_strip_parens(ans_str, false);
}

vector<vector<string>> get_global_conj_query_vectors(string conj_str) {
	vector<vector<string>> res;
	size_t pos = conj_str.find("<-") + 2;
	string query_str = conj_str.substr(pos);
	vector<string> queries = str_split_semicol(query_str);
	for (auto& s : queries) {
		vector<string> q = str_strip_parens(s, true);
		res.push_back(q);
	}
	return res;
}

string front_end() {

	string global_conj_str;

	// print global schema, ask for schema input
	cout << "\nGLOBAL SCHEMAS" << endl;
	cout << "1. "  << NOMINEE_GLOBAL_SCHEMA << endl;
    cout << "2. "  << MOVIE_GLOBAL_SCHEMA << endl;
    cout << "3. "  << PRINCIPAL_GLOBAL_SCHEMA << endl;
    cout << "4. "  << OSCAR_GLOBAL_SCHEMA << endl;
    cout << "5. "  << RATING_GLOBAL_SCHEMA << endl;
    cout << "6. "  << FINANCE_GLOBAL_SCHEMA << endl;
    cout << "7. "  << MINORITY_ACTOR_GLOBAL_SCHEMA << endl;
    cout << "8. "  << ACTOR_BY_COUNTRY_GLOBAL_SCHEMA << endl;
    cout << "9. "  << COMMERCIALLY_SUCCESSFUL_MOVIE_GLOBAL_SCHEMA << endl;
	cout << "10. " << HIGH_RATING_MOVIE_GLOBAL_SCHEMA << endl;
    cout << "11. " << OSCAR_MOVIE_RATING_GLOBAL_SCHEMA << endl;
	cout << "\nPlease input a Conjunctive Query, and press ENTER to finish. E.g. ans(*)<-Movie(imdb_title_id,_,_,_,_,_,_);Principal(imdb_title_id,_,_) [ENTER]" << endl;
	cin  >> global_conj_str;

    return global_conj_str;
}

int main()
{
	// Print prompt and Get user input conj query string
	string global_conj_str = front_end();
	print_query_str(global_conj_str, "user input conj query str");

	// Break the 1st half of conj query string into answer selection
	// Break the 2nd half of conj query string into global conj query vectors
	vector<string> answer_selection = get_answer_selection(global_conj_str);
	print_str_vector(answer_selection, "answer selection");
	vector<vector<string>> global_conj_query_vectors = get_global_conj_query_vectors(global_conj_str);
    print_query_vector(global_conj_query_vectors, "global_conj_query_vectors");

	// Unfold the global conj query vectors into local conj query vectors
	vector<vector<string>> local_conj_query_vectors = unfolding(global_conj_query_vectors);
    print_query_vector(local_conj_query_vectors, "local_conj_query_vectors");

	// Translate the local conj query vectors into sql queries
	vector<string> sql_queries = translating(local_conj_query_vectors);
	print_sql_vector(sql_queries, "sql_queries");

	// Join the sql queries into a final sql query
	string sql_query_to_db = join_queries(sql_queries, local_conj_query_vectors, answer_selection);
	print_query_str(sql_query_to_db, "final sql query");

	exit(0);
	
	// Send the final sql query to backend, Query the DB
	cout << endl << "Sending SQL query to DB..." << endl;
	query_db(sql_query_to_db);
	
    return 0;
}