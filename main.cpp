#include <iostream>
#include <vector>
#include <sstream>
#include <utility>

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

vector<vector<string> > front_end(){

	vector<vector<string> > front_end;

	// print global schema, ask for schema input
	cout<<"\nGLOBAL SCHEMAS"<<endl;
	cout<<endl;
	string p = "1. Nominee (person_id, name, birthday, birthplace, height, race, religion, sexual_orientation, won)\n2. Movie (movie_id, title, year, genre, country, language, duration)\n3. Principal (person_id, movie_id, job_category)\n4. Oscar (winner_name, year_ceremony, award_catagory, film_title)\n5. Rating (title, description, rating)\n6. Finance (title, budget, income)\n7. Popular modern actor (name)\n8. Minority actor (name, race, sexual_orientation)\n9. Foreign actor (name, birthplace)\n10. Successful modern movie (movie_id, title, income, rating, genre, language, year)\n11. Oscar movie rating (movie_id, title, year_ceremony, rating)\n";
	cout<<p<<endl;
	cout<<"Please specify the schemas you wish to include, and press ENTER to finish.\n E.g. Nominee,Movie,Principal[ENTER]\n";

	// ask and store global schema
	vector<string> schema_list;
	schema_list = listen_and_store("");
	cout<<endl;

	// prompting for parameters
	cout<<"Please enter schema parameters, if not specified, use NA, # par need to match: e.g. a,b,NA,d,NA,f[ENTER]\n"<<endl;

	// asking for parameters for each schema
	for(int i=0;i<schema_list.size();i++){
		string sc = schema_list[i];
		vector<string> para_list;
		cout<<"For "+sc+":"<<endl;
		para_list = listen_and_store(sc);
		front_end.push_back(para_list);
		cout<<endl;
	}
	
	// print frontend
	cout<<"### Front End vectors"<<endl;
    for(int i=0;i<front_end.size();i++){
    	cout<<"### "<<i<<": ";
    	for(int j=0;j<front_end[i].size();j++){
    		cout<<front_end[i][j]<<" ";
    	}
    	cout<<endl;
    }
    cout<<endl;

    return front_end;
}

// tt01,Transformer,2005,Action,USA,English,120

string to_sql(string db, vector<string> para, vector<string> schema){
	string sql = "SELECT ";
	for(int i=0;i<para.size();i++){
		if(i!=para.size()-1){
			sql += db + "." + para[i] + ",";
		}
		else{
			sql += db + "." + para[i] + "\n";
		}
	}
	
	sql += "FROM " + db + "\n";
	sql += "WHERE ";
	for(int i=0;i<schema.size();i++){
		if(schema[i]!="NA"){
		    sql += para[i] + "=\"" + schema[i] + "\"";
		    if(i!=schema.size()-1){
		        sql +=  + " AND ";
		    }
		}	
	}
	return sql;
}

vector<string> unfold(vector<string> schema){
	vector<string> ret;
	string sc = schema[0];

	// Direct unfolding
	if(sc=="Movie"){
		/*
		vector<string> movies(22, "NA");
		movies[0] = "movies";
		movies[1] = schema[1];
		movies[2] = schema[2];
		movies[4] = schema[3];
		movies[6] = schema[4];
		movies[8] = schema[5];
		movies[9] = schema[6];
		movies[7] = schema[7];
		*/

		string db = "movies";
		vector<string> para {"imdb_title_id","title","year","genre","country","language","duration"};
		string sql = to_sql(db,para,schema);

		// return xx;
	}
	if(sc=="Principal"){

		/*
		vector<string> title_principals(6, "NA");
		title_principals[0] = "title_principals";
		title_principals[3] = schema[1];
		title_principals[1] = schema[2];
		title_principals[4] = schema[3];
		return title_principals;
		*/
		string db = "title_principals";
		vector<string> para {"imdb_name_id","imdb_title_id","category"};
		string sql = to_sql(db,para,schema);
	}
	if(sc=="Oscar"){
		/*
		vector<string> the_oscar_award(7, "NA");
		the_oscar_award[0] = "the_oscar_award";
		the_oscar_award[5] = schema[1]; // winner name = name + winner=="True"
		the_oscar_award[7] = "True";
		the_oscar_award[2] = schema[2];
		the_oscar_award[4] = schema[3];
		the_oscar_award[6] = schema[4];
		return the_oscar_award;*/
		string db = "the_oscar_award";
		vector<string> para {"name","year_ceremony","category","film"};
		string sql = to_sql(db,para,schema);
		sql += " AND winner=\"True\"";
	}
	if(sc=="Rating"){
		/*
		vector<string> movies(22, "NA"); // same table as Movie
		movies[0] = "movies";
		movies[2] = schema[1];
		movies[14] = schema[2];
		movies[15] = schema[3];
		return movies;*/
		string db = "movies";
		vector<string> para {"title","description","avg_vote"};
		string sql = to_sql(db,para,schema);
	}
	if(sc=="Finance"){
		/*
		vector<string> movies(22, "NA"); // same table as Movie
		movies[0] = "movies";
		movies[2] = schema[1];
		movies[17] = schema[2];
		movies[19] = schema[3]; // income is global
		return movies;*/
		string db = "movies";
		vector<string> para {"title","budget","worlwide_gross_income"};
		string sql = to_sql(db,para,schema);
	}

	// Indirect unfolding
	
	if(sc=="Nominee"){

		/*
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
		*/

		// Transform to SQL Here

    	string db1 = "names";
    	vector<string> name_para {"imdb_name_id","name","date_of_birth","place_of_birth","height"};
    	string names_sql = to_sql(db1,name_para,schema);

    	string db2 = "oscar_personnel";
    	vector<string> op_para {"race","religion","sexual_orientation","_golden"};
    	string op_sql = to_sql(db2,name_para,schema);
		
		// How to join two tables ???
	}
	return ret;
}

void mid_end(vector<vector<string> > v){
	vector<vector<string> > mid_end;
	for(int i=0;i<v.size();i++){
		vector<string> unfolded = unfold(v[i]);
		mid_end.push_back(unfolded);
	}
	/*
	// print midend
	cout<<"### Mid End vectors"<<endl;
	for(int j=0;j<mid_end.size();j++){
		cout<<"### "<<j<<": ";
		for(int l=0;l<mid_end[j].size();l++){
			cout<<mid_end[j][l]<<" ";
		}
		cout<<endl;
	}*/

}

int main()
{	
	/*
	// test front to midend
    vector<vector<string> > front = front_end();
    mid_end(front);
    */

    // test to_sql
    vector<string> schema {"101","SB", "NA", "CA", "180"};
    string db = "names";
    vector<string> para {"imdb_name_id","name","date_of_birth","place_of_birth","height"};
	string sql = to_sql(db,para,schema);
	cout<<sql<<endl;


    return 0;
}