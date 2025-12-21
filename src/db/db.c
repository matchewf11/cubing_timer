#include <sqlite3.h>
#include <stdlib.h>

#include "../scramble/scramble.h"

int init_db(sqlite3 **db) {
  int rs = sqlite3_open("cubing.db", db);
  if (rs != 0) {
    return rs;
  }
  // turn on settings
  return SQLITE_OK;
}

int init_tables(sqlite3 *db) {
  const char *sql = "CREATE TABLE IF NOT EXISTS solves ("
                    "scramble TEXT NOT NULL,"
                    "time REAL NOT NULL,"
                    "created_at DATETIME DEFAULT CURRENT_TIMESTAMP"
                    ");";
  return sqlite3_exec(db, sql, NULL, NULL, NULL);
}

int insert_solve(sqlite3 *db, double time, const CubeMove *scramble,
                 int move_len) {

  const char *sql = "INSERT INTO solves (scramble, time) VALUES (?, ?)";
  sqlite3_stmt *stmt;

  int rs = sqlite3_prepare(db, sql, -1, &stmt, NULL);
  if (rs != SQLITE_OK) {
    return -1;
  }

  char *sc_str = scramble_to_string(scramble, move_len);
  if (sc_str == NULL) {
    sqlite3_finalize(stmt);
    return -1;
  }

  // be careful to free stmt b4 string
  rs = sqlite3_bind_text(stmt, 1, sc_str, -1, NULL);
  if (rs != SQLITE_OK) {
    sqlite3_finalize(stmt);
    free(sc_str);
    return -1;
  }

  rs = sqlite3_bind_double(stmt, 2, time);
  if (rs != SQLITE_OK) {
    sqlite3_finalize(stmt);
    free(sc_str);
    return -1;
  }

  rs = sqlite3_step(stmt);
  if (rs != SQLITE_DONE) {
    sqlite3_finalize(stmt);
    free(sc_str);
    return -1;
  }

  sqlite3_finalize(stmt);
  free(sc_str);

  return 0;
}
