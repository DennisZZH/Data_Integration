#include <iostream>
#include <vector>
#include <sstream>
#include <utility>
#include <cctype>
#include <algorithm>

using namespace std;


// temp store global variable here
vector<string> MOVIE {"imdb_title_id","title","year","genre","country","language","duration"};
vector<string> PRINCIPAL {"imdb_name_id","imdb_title_id","category"};
vector<string> OSCAR {"name","year_ceremony","category","title"};
vector<string> RATING {"title","description","avg_vote"};
vector<string> FINANCE {"title","budget","worlwide_gross_income"};

vector<string> NOMINEE {"imdb_name_id","name","date_of_birth","place_of_birth","height","race","religion","sexual_orientation","_golden","person"};


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
    	sub.erase(remove_if(sub.begin(), sub.end(), ::isspace), sub.end()); // remove spaces
    	list.push_back(sub);
	}

	return list;
}

vector<string> split_vector(vector<string> a, int s, int e){
    vector<string> ret;
    for(int i=s;i<=e;i++){
        ret.push_back(a[i]);
    }
    return ret;
}

string to_sql_helper(string table_name, string db, vector<string> para, vector<string> schema){
	string sql = "CREATE TABLE "+ table_name + " AS\nSELECT ";
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
	for(int i=1;i<schema.size();i++){
		if(schema[i]!="NA"){
		    sql += para[i-1] + "=\"" + schema[i] + "\"";
		    if(i!=schema.size()-1){
		        sql +=  + " AND ";
		    }
		}	
	}
	return sql;
}


vector<vector<string> > front_end(){

	vector<vector<string> > front_end;

	// print global schema, ask for schema input
	cout<<"\nGLOBAL SCHEMAS"<<endl;
	cout<<endl;
	string p = "1. Nominee (person_id, name, birthday, birthplace, height, race, religion, sexual_orientation, won)\n2. Movie (movie_id, title, year, genre, country, language, duration)\n3. Principal (person_id, movie_id, job_category)\n4. Oscar (winner_name, year_ceremony, award_catagory, title)\n5. Rating (title, description, rating)\n6. Finance (title, budget, income)\n7. Popular modern actor (name)\n8. Minority actor (name, race, sexual_orientation)\n9. Foreign actor (name, birthplace)\n10. Successful modern movie (movie_id, title, income, rating, genre, language, year)\n11. Oscar movie rating (movie_id, title, year_ceremony, rating)\n";
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


pair<string, string> unfold_to_sql(vector<string> schema){

	pair<string, string> ret; // pair(sql,table_name)
	string sc = schema[0];
	string sql;

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
		string tn = "movies_unfolded";
		string db = "movies";
		vector<string> para {"imdb_title_id","title","year","genre","country","language","duration"};
		sql = to_sql_helper(tn,db,para,schema);

		ret.first = sql;
		ret.second = tn;
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
		string tn = "title_principals_unfolded";
		string db = "title_principals";
		vector<string> para {"imdb_name_id","imdb_title_id","category"};
		sql = to_sql_helper(tn,db,para,schema);

		ret.first = sql;
		ret.second = tn;
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
		string tn = "the_oscar_award_unfolded";
		string db = "the_oscar_award";
		vector<string> para {"name","year_ceremony","category","title"};
		sql = to_sql_helper(tn,db,para,schema);
		sql += " AND winner=\"True\"";

		ret.first = sql;
		ret.second = tn;
	}
	if(sc=="Rating"){
		/*
		vector<string> movies(22, "NA"); // same table as Movie
		movies[0] = "movies";
		movies[2] = schema[1];
		movies[14] = schema[2];
		movies[15] = schema[3];
		return movies;*/
		string tn = "rating_unfolded";
		string db = "movies";
		vector<string> para {"title","description","avg_vote"};
		sql = to_sql_helper(tn,db,para,schema);

		ret.first = sql;
		ret.second = tn;
	}
	if(sc=="Finance"){
		/*
		vector<string> movies(22, "NA"); // same table as Movie
		movies[0] = "movies";
		movies[2] = schema[1];
		movies[17] = schema[2];
		movies[19] = schema[3]; // income is global
		return movies;*/
		string tn = "finance_unfolded";
		string db = "movies";
		vector<string> para {"title","budget","worlwide_gross_income"};
		sql = to_sql_helper(tn,db,para,schema);

		ret.first = sql;
		ret.second = tn;
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
		// first create two temp tables satisfy user inputs
		// then join two temp tables

		schema.push_back(schema[1]); // since op needs person(name), manually add a name in the back of schema vector

		vector<string> schema_name = split_vector(schema,0,4);
		vector<string> schema_op = split_vector(schema,5,8+1);

		vector<string> name_para {"imdb_name_id","name","date_of_birth","place_of_birth","height"};
		sql = to_sql_helper("names_tmp","names", name_para, schema_name);
		sql += "\n\n";

		vector<string> op_para {"race","religion","sexual_orientation","_golden","person"};
		sql += to_sql_helper("op_tmp", "oscar_personnel", op_para, schema_op);
		sql += "\n\n";

		string names_para = "names_tmp.imdb_name_id, names_tmp.name, names_tmp.date_of_birth, names_tmp.place_of_birth, names_tmp.height";
		string oscar_personnel_para = "op_tmp.person, op_tmp.race, op_tmp.religion, op_tmp.sexual_orientation, op_tmp._golden";

		sql += "CREATE TABLE nominee_unfolded AS\n";
		sql += "SELECT " + names_para + ", " + oscar_personnel_para + "\n";
		sql += "FROM names_tmp\n";
		sql += "INNER JOIN op_tmp\n";
		sql += "ON names_tmp.name=op_tmp.person\n";

		ret.first = sql;
		ret.second = "nominee_unfolded";
	}

	return ret;
}

void mid_end(vector<vector<string> > v){
	vector<pair<string,string> > sql_components;

	for(int i=0;i<v.size();i++){
		pair<string,string> p = unfold_to_sql(v[i]);
		sql_components.push_back(p);
	}
	
	/*
	// print midend
	cout<<"### Mid End SQLs"<<endl;
	for(int j=0;j<sql_components.size();j++){
		cout<<sql_components[j].first<<endl;
	}*/

	// two unfolded tables join on what PARAMETER?
	vector<string> final_table = _TB_NAME_;
	//vector<>


}

int main()
{	
	
	// test front to midend
    vector<vector<string> > front = front_end();
    mid_end(front);
    
	/*
    // test to_sql
    vector<string> schema {"101","SB", "NA", "CA", "180"};
    string db = "names";
    vector<string> para {"imdb_name_id","name","date_of_birth","place_of_birth","height"};
	string sql = to_sql(db,para,schema);
	cout<<sql<<endl;
	*/


    return 0;
}