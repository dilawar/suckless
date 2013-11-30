#!/usr/bin/env python
import os
import sys
import subprocess
import sqlite3 as sql
import method

if len(sys.argv) < 2 :
    sys.exit(-1)

kaluPath = '/etc/kalu'
if not os.path.isdir(kaluPath):
    os.mkdir(kaluPath)

dbPath = os.path.join(kaluPath, 'kalu.db')

if os.path.isfile(dbPath):
    db = sql.connect(dbPath)
    c = db.cursor()

    c.execute(
        """CREATE TABLE IF NOT EXISTS package (
        name VARCHAR
        , id VARCHAR
        , version VARCHAR
        , installedOn DATETIME
        , type VARCHAR
        , path VARCHAR
        , installed INTEGER
        , PRIMARY KEY (name, version)
        ) """
    )

    c.execute("""CREATE TABLE IF NOT EXISTS files (
        name VARCHAR
        , id VARCHAR
        , version VARCHAR
        , comment TEXT
        , description TEXT
        , type VARCHAR
        , url VARCHAR
        , PRIMARY KEY (name, version)
        ) """
    )

    c.execute("""CREATE TABLE IF NOT EXISTS dependency (
        name VARCHAR
        , neededFor VARCHAR
        , requiredBy VARCHAR
        )"""
    )
    sql.commit()

localPkgDir= os.path.join(os.environ['HOME'], '.packages')

if os.argv[1] == "mkcache":
    print("Making cache")
    # Go through the local packages.
    pkgFiles=$(find $LOCAL_PKGS_DIR -name "*.files")
    for pF in $pkgFiles; do
        updateDB $pF $DBPATH
    done
fi
