#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
                    "id INTEGER PRIMARY KEY,"
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

  int rs = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
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

int get_avg_all_time(sqlite3 *db, double *out_avg, int *out_count) {

  const char *sql = "SELECT AVG(time), COUNT(*) FROM solves";
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
    return -1;
  }

  if (sqlite3_step(stmt) != SQLITE_ROW) {
    sqlite3_finalize(stmt);
    return -1;
  }

  *out_avg = sqlite3_column_double(stmt, 0);
  *out_count = sqlite3_column_int(stmt, 1);

  sqlite3_finalize(stmt);
  return SQLITE_OK;
}

int get_personal_best(sqlite3 *db, double *out_pb, char **out_scramble) {
  const char *sql = "SELECT time, scramble FROM solves ORDER BY time LIMIT 1";
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
    return -1;
  }

  if (sqlite3_step(stmt) != SQLITE_ROW) {
    sqlite3_finalize(stmt);
    return -1;
  }

  *out_pb = sqlite3_column_double(stmt, 0);

  const char *temp_text = (const char *)sqlite3_column_text(stmt, 1);
  char *text = malloc(sizeof(char) * (strlen(temp_text) + 1));
  if (text == NULL) {
    sqlite3_finalize(stmt);
    return -1;
  }

  strcpy(text, temp_text);
  *out_scramble = text;
  sqlite3_finalize(stmt);

  return SQLITE_OK;
}

int get_curr_5(sqlite3 *db, double **times, char ***out_scramble_list,
               int *out_len) {

  const char *sql =
      "SELECT time, scramble FROM solves ORDER BY created_at DESC LIMIT 5";
  sqlite3_stmt *stmt;

  *out_len = 0;
  *times = NULL;
  *out_scramble_list = NULL;

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
    return -1;
  }

  *times = malloc(sizeof(double) * 5);
  if (*times == NULL) {
    sqlite3_finalize(stmt);
    return -1;
  }

  *out_scramble_list = malloc(sizeof(char *) * 5);
  if (*out_scramble_list == NULL) {
    sqlite3_finalize(stmt);
    free(*times);
    return -1;
  }

  while (sqlite3_step(stmt) == SQLITE_ROW && *out_len < 5) {
    (*times)[*out_len] = sqlite3_column_double(stmt, 0);

    const unsigned char *buffer = sqlite3_column_text(stmt, 1);
    char *str = malloc(sizeof(char) * (1 + strlen((char *)buffer)));
    if (str == NULL) {
      sqlite3_finalize(stmt);
      free(*times);
      for (int i = 0; i < *out_len; i++) {
        free((*out_scramble_list)[i]);
      }

      free(*out_scramble_list);

      return -1;
    }
    strcpy(str, (char *)buffer);
    (*out_scramble_list)[*out_len] = str;
    (*out_len)++;
  }

  sqlite3_finalize(stmt);
  return SQLITE_OK;
}

int delete_last_solve(sqlite3 *db) {
  const char *sql = "DELETE FROM solves WHERE id = (SELECT id FROM solves "
                    "ORDER BY created_at DESC LIMIT 1)";
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
    return -1;
  }

  if (sqlite3_step(stmt) != SQLITE_DONE) {
    sqlite3_finalize(stmt);
    return -1;
  }

  sqlite3_finalize(stmt);
  return SQLITE_OK;
}

int add_two_last_scramble(sqlite3 *db) {
  const char *sql = "UPDATE solves "
                    "SET time = time + 2.0 "
                    "WHERE id = ("
                    " SELECT id "
                    " FROM solves "
                    " ORDER BY created_at DESC "
                    " LIMIT 1"
                    ")";
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
    return -1;
  }

  int rs = sqlite3_step(stmt);
  sqlite3_finalize(stmt);
  return rs == SQLITE_DONE ? SQLITE_OK : -1;
}
