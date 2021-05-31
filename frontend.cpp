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

vector<string> listen_and_store(string n){
	// listen for input
	string input;
	getline(cin, input);
	stringstream ss(input);
	vector<string> list;
	if(n!=""){
		list.push_back(n);
	}

	// store parsed input to list
	while(ss.good()){
		string sub;
    	getline(ss, sub, ',');
    	list.push_back(sub);
	}

	return list;
}

vector<vector<string> > front_end() {

	vector<vector<string> > global_conj_queries;

	// print global schema, ask for schema input
	cout<<"\nGLOBAL SCHEMAS"<<endl;
	cout << "1. "  << NOMINEE_GLOBAL_SCHEMA << endl;
    cout << "2. "  << MOVIE_GLOBAL_SCHEMA << endl;
    cout << "3. "  << PRINCIPAL_GLOBAL_SCHEMA << endl;
    cout << "4. "  << OSCAR_GLOBAL_SCHEMA << endl;
    cout << "5. "  << RATING_GLOBAL_SCHEMA << endl;
    cout << "6. "  << FINANCE_GLOBAL_SCHEMA << endl;
    cout << "7. "  << MINORITY_ACTOR_GLOBAL_SCHEMA << endl;
    cout << "8. "  << ACTOR_BY_COUNTRY_GLOBAL_SCHEMA << endl;
    cout << "9. " << COMMERCIALLY_SUCCESSFUL_MOVIE_GLOBAL_SCHEMA << endl;
	cout << "10. " << HIGH_RATING_MOVIE_GLOBAL_SCHEMA << endl;
    cout << "11. " << OSCAR_MOVIE_RATING_GLOBAL_SCHEMA << endl;
    
	cout << "\nPlease specify the schemas you wish to include, and press ENTER to finish. E.g. Nominee,Movie,Principal [ENTER]" << endl;

	// ask and store global schema
	vector<string> schema_list;
	schema_list = listen_and_store("");
    cout << endl;

	// prompting for parameters
	cout << "Please enter schema parameters, if not specified, use '_'. E.g. a,b,_,d,_,f [ENTER]" << endl;

	// asking for parameters for each schema
	for (int i=0; i < schema_list.size(); i++) {
		string schema_name = schema_list[i];
		vector<string> para_list;
		cout << "For "+ schema_name + ":" << endl;
		para_list = listen_and_store(schema_name);
		global_conj_queries.push_back(para_list);
		cout << endl;
	}
	
    return global_conj_queries;
}

vector<string> get_answer_selection() {
	cout << "Please select the fields for answer, if return all fields, use '*'. E.g. title,name [ENTER]" << endl;
	vector<string> res = listen_and_store("");
	return res;
}

int main()
{
	
    vector<vector<string>> global_conj_queries = front_end();
	vector<string> answer_selection = get_answer_selection();
    print_query_vector(global_conj_queries, "global_conj_queries");

	vector<vector<string>> local_conj_queries = unfolding(global_conj_queries);
    print_query_vector(local_conj_queries, "local_conj_queries");

	vector<string> sql_queries = translating(local_conj_queries);
	print_sql_vector(sql_queries, "sql_queries");

	string sql_query_to_db = join_queries(sql_queries, local_conj_queries, answer_selection);
	cout << "------------------------------------Testing: Print final sql query" << "------------------------------------" << endl << sql_query_to_db << endl;
	
	cout << endl << "Sending SQL query to DB..." << endl;

	query_db(sql_query_to_db);
	

	//string test1 = "SELECT budget FROM (SELECT movies.imdb_title_id, movies.title, movies.year_film, movies.genre, movies.duration, movies.country, movies.language FROM movies WHERE genre=\"Drama\") t0 INNER JOIN (SELECT title_principals.imdb_title_id, title_principals.imdb_name_id, title_principals.job_category FROM title_principals WHERE job_category=\"actor\" ) t1 ON t0.imdb_title_id = t1.imdb_title_id INNER JOIN (SELECT names.imdb_name_id, names.name, names.height FROM names ) t2 ON t1.imdb_name_id = t2.imdb_name_id INNER JOIN (SELECT oscar_personnel.won, oscar_personnel.place_of_birth, oscar_personnel.date_of_birth, oscar_personnel.race, oscar_personnel.religion, oscar_personnel.sexual_orientation, oscar_personnel.name FROM oscar_personnel WHERE won=\"FALSE\"  AND sexual_orientation=\"Gay\") t3 ON t2.name = t3.name ;";
	//string test2 = "SELECT movies.title FROM movies INNER JOIN title_principals ON title_principals.imdb_title_id=movies.imdb_title_id INNER JOIN names ON names.imdb_name_id=title_principals.imdb_name_id INNER JOIN oscar_personnel ON oscar_personnel.name=names.name WHERE movies.genre=\"Drama\" AND title_principals.job_category=\"actor\" AND oscar_personnel.sexual_orientation=\"Gay\";";
	//query_db(test1);
	
	
    return 0;
}