#pragma once
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;


const string DB_NAME = "proj.db";

const string MOVIE_GLOBAL_SCHEMA = "Movie (movie_id, title, year, genre, country, language, duration)";
const string PRINCIPAL_GLOBAL_SCHEMA = "Principal (person_id, movie_id, job_category)";
const string OSCAR_GLOBAL_SCHEMA = "Oscar (winner_name, year_ceremony, award_catagory, film_title)";
const string RATING_GLOBAL_SCHEMA = "Rating (title, description, rating)";
const string FINANCE_GLOBAL_SCHEMA = "Finance (title, budget, income)";
const string NOMINEE_GLOBAL_SCHEMA = "Nominee (person_id, name, birthday, birthplace, height, race, religion, sexual_orientation, won)";

const string POPULAR_MODERN_ACTOR_GLOBAL_SCHEMA = "Popular modern actor (name)";
const string MINORITY_ACTOR_GLOBAL_SCHEMA = "Minority actor (name, race, sexual_orientation)";
const string FOREIGN_ACTOR_GLOBAL_SCHEMA = "Foreign actor (name, birthplace)";
const string SUCCESSFUL_MODERN_MOVIE_GLOBAL_SCHEMA = "Successful modern movie (movie_id, title, income, rating, genre, language, year)";
const string OSCAR_MOVIE_RATING_GLOBAL_SCHEMA = "Oscar movie rating (movie_id, title, year_ceremony, rating)";


const vector<string> MOVIES_LOCAL_SCHEMA_PARAS = {"imdb_title_id","title","year_film","date_published","genre","duration","country","language",
                                "production_company","description","ave_vote","budget","worldwide_gross_income"};

const vector<string> NAMES_LOCAL_SCHEMA_PARAS = {"imdb_name_id","name","height","bio","date_of_birth","place_of_birth","spouses","divorces","children"};

const vector<string> OSCAR_PERSONNEL_LOCAL_SCHEMA_PARAS = {"won","place_of_birth","date_of_birth","race","religion","sexual_orientation",
                                                        "year_ceremony","category","biourl","title","name"};

const vector<string> THE_OSCAR_AWARD_LOCAL_SCHEMA_PARAS = {"year_film","year_ceremony","ceremony","category","name","title","won"};

const vector<string> TITLE_PRINCIPALS_LOCAL_SCHEMA_PARAS = {"imdb_title_id","imdb_name_id","category"};

