#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

#include "parameters.h"
#include "utility.h"

using namespace std;

vector<vector<vector<string> > > unfold_to_local_schema(vector<vector<string> > data){

	vector<vector<vector<string> > > local_schema;

	for(int k=0;k<data.size();k++){

		vector<vector<string> > ret; // vector of [local_schema_name, parameter_name, value]
		string sc = data[k][0];
		// Direct unfolding
		if(sc=="Movie"){
			for(int i=1;i<data[k].size();i++){
				vector<string> v {"movies",MOVIES[i-1],data[k][i]};
				ret.push_back(v);
			}
			local_schema.push_back(ret);
		}
		if(sc=="Rating"){
			vector<string> v {"movies",MOVIES[1],data[k][1]};
			ret.push_back(v);
			for(int i=2;i<data[k].size();i++){
				vector<string> v {"movies",MOVIES[i-1+5],data[k][i]};
				ret.push_back(v);
			}
			local_schema.push_back(ret);
		}
		if(sc=="Finance"){
			vector<string> v {"movies",MOVIES[1],data[k][1]};
			ret.push_back(v);
			for(int i=2;i<data[k].size();i++){
				vector<string> v {"movies",MOVIES[i-1+8],data[k][i]};
				ret.push_back(v);
			}
			local_schema.push_back(ret);
		}
		if(sc=="Principal"){
			for(int i=1;i<data[k].size();i++){
				vector<string> v {"title_principals",TITLE_PRINCIPALS[i-1],data[k][i]};
				ret.push_back(v);
			}
			local_schema.push_back(ret);
		}
		if(sc=="Oscar"){
			for(int i=1;i<data[k].size();i++){
				vector<string> v {"oscar",OSCAR[i-1],data[k][i]};
				ret.push_back(v);
			}
			local_schema.push_back(ret);
		}

		// indirect unfolding
		if(sc=="Nominee"){
			vector<vector<string> >ret1;
			vector<vector<string> >ret2;

			for(int i=1;i<6;i++){
				vector<string> v {"names",NAMES[i-1],data[k][i]};
				ret1.push_back(v);
			}
			local_schema.push_back(ret1);

			vector<string> v {"op","name",data[k][2]};
			ret2.push_back(v);

			for(int i=6;i<data[k].size();i++){
				vector<string> v {"op",OP[i-5],data[k][i]};
				ret2.push_back(v);
			}
			local_schema.push_back(ret2);
		}
	}

	return local_schema;
}

vector<string> get_target(vector<vector<vector<string> > > v){
	vector<string> ret;
	for(int i=0;i<v.size();i++){
		for(int j=0;j<v[i].size();j++){
			for(int k=0;k<v[i][j].size();k++){
				if(v[i][j][k]=="x"){
					ret.push_back(v[i][j][0]);
					ret.push_back(v[i][j][1]);
				}
			}
		}
	}
	return ret;
}

string local_query_to_sql(vector<vector<vector< string> > > g){

	vector<string> target = get_target(g);
	string target_schema = target[0];
	string target_par = target[1];

	string ret;
	ret += "SELECT "+target_schema+"."+target_par+" FROM movies"; // hardcode movies
	ret +=" ";
	ret += "INNER JOIN title_principals ON title_principals.imdb_title_id=movies.imdb_title_id INNER JOIN names ON names.imdb_name_id=title_principals.imdb_name_id INNER JOIN op ON op.name=names.name INNER JOIN oscar ON oscar.name=names.name";
	ret +=" ";
	ret += "WHERE ";
	for(int i=0;i<g.size();i++){
		for(int j=0;j<g[i].size();j++){
			string val = g[i][j][2];
			string para = g[i][j][1];
			string schema = g[i][j][0];
			if(val!="_" && val!="x"){
				ret += schema+"."+para+"="+"\""+val+"\""+" AND ";
			}
		}
	}
	ret = ret.substr(0,ret.length()-5);
	ret += ";";

    return ret;

}