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

#endif
