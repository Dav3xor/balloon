CREATE TABLE IF NOT EXISTS targets (
  latitude  REAL NOT NULL,
  longitude REAL NOT NULL,
  priority  REAL DEFAULT 5 NOT NULL,
  name      TEXT NOT NULL,
  comment   TEXT
);

