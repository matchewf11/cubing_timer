#ifndef DB_H
#define DB_H

#include <sqlite3.h>

#include "../scramble/scramble.h"

// 0 -> ok
// else err
int init_db(sqlite3 **db);

// return SQLITE_OK if ok
// else is err
int init_tables(sqlite3 *db);

// return SQLITE_OK if ok
// else err
int insert_solve(sqlite3 *db, double time, const CubeMove *scramble,
                 int move_len);

// Return SQLITE_OK if ok
// else err
int get_avg_all_time(sqlite3 *db, double *out_avg, int *out_count);

// -1 if err
// SQLITE_OK if ok
// free out_scramble if not an error
int get_personal_best(sqlite3 *db, double *out_pb, char **out_scramble);

// SQLITE_OK if ok else there is an error.
// times and out_scramble_list will be the same len (out_len)
//
// Free times, and scramble_list (and each scramble when done)
int get_curr_5(sqlite3 *db, double **times, char ***out_scramble_list,
               int *out_len);

// SQLITE_OK if ok, else it is an error
int delete_last_solve(sqlite3 *db);

// return SQLITE_OK if ok
// else error
int add_two_last_scramble(sqlite3 *db);

#endif
