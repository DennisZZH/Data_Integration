#pragma once
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

string NOMINEE_SCHEMA = "Nominee (person_id, name, birthday, birthplace, height, race, religion, sexual_orientation, won)";
string MOVIE_SCHEMA = "Movie (movie_id, title, year, genre, country, language, duration)";
string PRINCIPAL_SCHEMA = "Principal (person_id, movie_id, job_category)";
string OSCAR_SCHEMA = "Oscar (winner_name, year_ceremony, award_catagory, film_title)";
string RATING_SCHEMA = "Rating (title, description, rating)";
string FINANCE_SCHEMA = "Finance (title, budget, income)";
string POPULAR_MODERN_ACTOR_SCHEMA = "Popular modern actor (name)";
string MINORITY_ACTOR_SCHEMA = "Minority actor (name, race, sexual_orientation)";
string FOREIGN_ACTOR_SCHEMA = "Foreign actor (name, birthplace)";
string SUCCESSFUL_MODERN_MOVIE_SCHEMA = "Successful modern movie (movie_id, title, income, rating, genre, language, year)";
string OSCAR_MOVIE_RATING_SCHEMA = "Oscar movie rating (movie_id, title, year_ceremony, rating)";

vector<string> NOMINEE_PARAS = {"person_id", "name", "birthday", "birthplace", "height", "race", "religion", "sexual_orientation", "won"};
vector<string> MOVIE_PARAS = {"movie_id", "title", "year", "genre", "country", "language", "duration"};
vector<string> PRINCIPAL_PARAS = {"person_id", "movie_id", "job_category"};
vector<string> OSCAR_PARAS = {"winner_name", "year_ceremony", "award_catagory", "film_title"};
vector<string> RATING_PARAS = {"title", "description", "rating"};
vector<string> FINANCE_PARAS = {"title", "budget", "income"};
vector<string> POPULAR_MODERN_ACTOR_PARAS = {"name"};
vector<string> MINORITY_ACTOR_PARAS = {"name", "race", "sexual_orientation"};
vector<string> FOREIGN_ACTOR_PARAS = {"name", "birthplace"};
vector<string> SUCCESSFUL_MODERN_MOVIE_PARAS = {"movie_id", "title", "income", "rating", "genre", "language", "year"};
vector<string> OSCAR_MOVIE_RATING_PARAS = {"movie_id", "title", "year_ceremony", "rating"};

// Local Schemas
vector<string> MOVIES {"imdb_title_id","title","year","genre","country","language","duration","description","avg_vote","budget","worlwide_gross_income"};
vector<string> TITLE_PRINCIPALS {"imdb_name_id","imdb_title_id","category"};
vector<string> OSCAR {"name","year_ceremony","category","title", "year_movie"};
vector<string> OP {"name","race_ethnicity","religion","sexual_orientation","_golden"};
vector<string> NAMES {"imdb_name_id","name","date_of_birth","place_of_birth","height"};