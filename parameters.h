#pragma once
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;


const string DB_NAME = "proj.db";

const string MOVIE_GLOBAL_SCHEMA = "Movie (imdb_title_id, title, year_film, genre, country, language, duration)";
const string PRINCIPAL_GLOBAL_SCHEMA = "Principal (imdb_name_id, imdb_title_id, job_category)";
const string OSCAR_GLOBAL_SCHEMA = "Oscar (name, year_ceremony, award_catagory, title)";
const string RATING_GLOBAL_SCHEMA = "Rating (title, description, avg_vote)";
const string FINANCE_GLOBAL_SCHEMA = "Finance (title, budget, worldwide_gross_income)";
const string NOMINEE_GLOBAL_SCHEMA = "Nominee (imdb_name_id, name, date_of_birth, place_of_birth, height, race, religion, sexual_orientation, won)";


const string MINORITY_ACTOR_GLOBAL_SCHEMA = "Minority actor (name)";
const string ACTOR_BY_COUNTRY_GLOBAL_SCHEMA = "Actor by country (name, place_of_birth)";
const string COMMERCIALLY_SUCCESSFUL_MOVIE_GLOBAL_SCHEMA = "Commercially successful movie (imdb_title_id, title, avg_vote, genre, language, year_film)";
const string HIGH_RATING_MOVIE_GLOBAL_SCHEMA = "High rating movie (imdb_title_id, title, worldwide_gross_income, genre, language, year_film)";
const string OSCAR_MOVIE_RATING_GLOBAL_SCHEMA = "Oscar movie rating (imdb_title_id, title, year_ceremony, avg_vote)";


const vector<string> MOVIES_LOCAL_SCHEMA_PARAS = {"imdb_title_id","title","year_film","date_published","genre","duration","country","language",
                                "production_company","description","avg_vote","budget","worldwide_gross_income"};

const vector<string> NAMES_LOCAL_SCHEMA_PARAS = {"imdb_name_id","name","height","bio","date_of_birth","place_of_birth","spouses","divorces","children"};

const vector<string> OSCAR_PERSONNEL_LOCAL_SCHEMA_PARAS = {"won","place_of_birth","date_of_birth","race","religion","sexual_orientation",
                                                        "year_ceremony","award_category","biourl","title","name"};

const vector<string> THE_OSCAR_AWARD_LOCAL_SCHEMA_PARAS = {"year_film","year_ceremony","ceremony","award_category","name","title","won"};

const vector<string> TITLE_PRINCIPALS_LOCAL_SCHEMA_PARAS = {"imdb_title_id","imdb_name_id","job_category"};

